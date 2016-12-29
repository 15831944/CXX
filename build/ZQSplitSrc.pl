# -----------------------------------------------------------------
# File Name:     ZQSplitSrc.pl
# Author:        Interactive ZQ
# Security:      Tech Mgm
# Description:   This program build defined project automaticall, 
#                and email report to attns
# Modification Log:
# -----------------------------------------------------------
# 2005-09-02  0.1 Hui.Shao  Create
# -----------------------------------------------------------------

use Getopt::Long;
use Win32;
use File::Copy;
use Cwd;

# -----------------
# global declares
# -----------------
use vars qw(
	$VSSROOT $VSSUSER $VSSPASSWD
	$BUILD_SETTINGS $BUILD_ROOT $RELEASE_ROOT %BUILD_BATCH
	$SSCMD $MSDEV6CMD $MSDEV7CMD
	);
($VSSROOT, $RELEASE_ROOT, $VSSUSER, $VSSPASSWD, $BUILD_SETTINGS)
# =  ("D:\\temp\\ISA_4.1a", "d:\\temp\\relVSS", "build", "nightly", "ZQProjs/build");
=  ("\\\\hawkeye\\vss", "\\\\hawkeye\\RelVSS", "build", "nightly", "ZQProjs/build");

$MSVS6_INST = "C:\\Program Files\\Microsoft Visual Studio";
$SSCMD = "\"$MSVS6_INST\"\\Common\\VSS\\win32\\SS.EXE";

my $LOGFILE;

use Env qw(SSDIR ZQPROJSPATH TEMP ITVSDKPATH);

my (@SRC_BRANCH_STACK, @CLEAN_BRANCH_STACK, @PURGE_BRANCH_STACK);

my @OUTPUT_STACK;
my $LOCAL_BUILD_BATCH_FN;

my $BUILD_OPTS_DESC;
my $BUILD_PRJS_DESC;

require "profiles.pl";

use vars qw(@ALL_PROJS @NIGHLY_PROJLIST);

my @PROJLIST = ();

%BUILD_BATCH = (
	'batch_num' => 0,
	'batch_fn'  => 'buildbatch.txt',
	'failed'    => 0,
	'crnt_step' => 'initialization',
#	'comp_owner' => $EMAILATTNS, 
);

# ------------------
# main procedure 
# ------------------

#read arguments
if ($ARGV[0])
{
	&GetOptions(
	       'help'     =>		\$opt_help,
		'list'     =>		\$opt_list,
               'releaseroot=s' =>     \$opt_releaseroot,
               'releasename=s' =>     \$opt_releasename,
               'projects=s'     => 	\$opt_projname,
			   
               'vssroot=s' =>       \$opt_vssroot,
               'vssuser=s' =>       \$opt_vssuser,
               'vsspasswd=s' =>     \$opt_vsspasswd,

	       'logfile=s' =>		\$opt_logfile,
               'test'   => 		\$opt_test,
		);
		
		$RELEASE_ROOT = fixPathToOS($opt_releaseroot) if $opt_releaseroot;
		$RELEASE_NAME = $opt_releasename;

		$VSSROOT = fixPathToOS($opt_vssroot)			if $opt_vssroot;
		$VSSUSER = $opt_vssuser			if $opt_vssuser;
		$VSSPASSWD = $opt_vsspasswd		if $opt_vsspasswd;
		

		$LOGFILE  =fixPathToOS($opt_logfile) 	if $opt_logfile;
}

if ($opt_list)
{
	print "List all project profiles:\n";
	foreach $proj (@ALL_PROJS)
	{
		print "  [$proj->{name}] $proj->{desc}\n";
	}
	print "\n";
	exit 0;
}

usage() if $opt_help;
   
my @stamp = (localtime(time))[0,1,2,3,4,5];
my $BUILD_TIME = sprintf "%04d-%02d-%02d %02d:%02d", $stamp[5]+1900, $stamp[4]+1, $stamp[3], $stamp[2], $stamp[1], $stamp[0];

$LOGFILE = fixPathToOS($TEMP."/ZQSplitSrc.log") if !$LOGFILE;

my @projnames = ();
@projnames = split(/,/, $opt_projname) if $opt_projname;
@PROJLIST = ();
foreach $proj (@ALL_PROJS)
{
	my $pn;
	foreach $pn (@projnames)
	{
  		push @PROJLIST, $proj if $pn eq trim($proj->{name});
  	}
}
Die("Project(s) must be specified by using --projects=\"<PN>[,<PN>...]\" to split source") if !@PROJLIST;
Die("Release name must be specified by using --releasename=<RN>") if !$RELEASE_NAME;

&log("********** SplitSrc starts **********");
$BUILD_OPTS_DESC  = "**\tOptions:\n";
$BUILD_OPTS_DESC .= "\tSourceVSS    = $VSSUSER:****\@$VSSROOT\n";
$BUILD_OPTS_DESC .= "\tReleaseName  = $RELEASE_NAME\n";
$BUILD_OPTS_DESC .= "\tReleaseFolder= $RELEASE_ROOT\n";
$BUILD_OPTS_DESC .= "\tProjects     = $opt_projname\n";
&log($BUILD_OPTS_DESC);

my $ch = prompt ("Please double check the above settings\nHit 'Enter' to continue, or 'CTRL-C' to cancel and quit");

$ch = prompt ("Have you updated ZQProjs/build/profiles.PL the version numbers for projects: $opt_projname? [y|N]");
$ch = substr($ch, 0, 1);
Die("User cancelled to update version numbers for the projects") if $ch ne "Y" && $ch ne "y";

$SSDIR = $RELEASE_ROOT."\\".$RELEASE_NAME;
&log("**\tswitching working VSS Database to $SSDIR");

&replicateVssDB($VSSROOT, $SSDIR);

&buildBranchStack();

&buildCleanProjsStack();

&cleanProjs();

# &purgeProjs();

&labelSplit();

&log("\nSource has been splited into $SSDIR for projects: $opt_projname\n");
my $buildcmd = "ZQAutoBuild.bat --vssroot=$SSDIR --projects=$opt_projname";
&log("\n!! you must\n\t1)increase the version number in working database");
&log("\t2)execute a clean build to validate the split, suggested build command:\n\t  $buildcmd\n");

$ch = prompt ("Start build now? [Y|n]");
$ch = substr($ch, 0, 1);
system($buildcmd) if $ch ne "N" && $ch ne "n";

&log("\n********** SplitSrc ends **********\n");
exit 0;

# ------------------------------------------------------
# usage screen
# ------------------------------------------------------
sub usage
{
   print <<EOF;
ZQSplitSrc, by Hui Shao <hui.shao\@i-zq.com>

Usage: ZQSplitSrc <options>
ZQSplitSrc is a simple Perl program that can split ZQ working VSS database based on the project profiles

options
    --projects="<PN>[,<PN>...]"
        specify the project(s) to build in this run, valid only in manual mode
        where <PN>s are the short name defined in the project build profiles
		
    --vssroot=<path>
        specify the source VSS database
    --vssuser=<user>
        specify the login user name to the VSS database
    --vsspasswd=<password>
        password for the VSS user to access the database

    --releaseroot=<releaseroot>
        specify the root folder to keep the splited VSS database
    --releasename=<releasename>
        the name of the splited VSS database
			   
    --logfile=<filename>
        specify the build log file

    --test
        test build, will skip commit build to VSS and skip publishing
    --help
        display this screen

EOF

exit 0;
}

# ------------------------------------------------------
# replicate the source VSS to a copy
# ------------------------------------------------------
sub replicateVssDB
{
	my $SrcDB = shift;
	my $NewDB = shift;
	
	Die("source VSS database $SrcDB does not exist") if (!-e $SrcDB);
	if (-e $NewDB)
	{
		my $ch = prompt ("$NewDB already exists, delete first?[y|N]");
		$ch = substr($ch, 0, 1);
		exit 0 if $ch ne "Y" && $ch ne "y";
		&log("!!\t$NewDB already exists, delete first");
		system("rd /s/q ".$NewDB);
	}

	&log("**\treplicate new VSS database $NewDB from $SrcDB");
	system("mkdir ".$NewDB);
	Die("Failed to create new VSS DB under $NewDB") if (!-e $NewDB);
	system("xcopy /IEFD ".fixPathToOS($SrcDB."/users")." ".fixPathToOS($NewDB."/users"));
	system("xcopy /IEFD ".fixPathToOS($SrcDB."/data")." ".fixPathToOS($NewDB."/data"));
	system("copy /Y ".fixPathToOS($SrcDB."/*.*")." ".fixPathToOS($NewDB));

	#change the Database_Name = ZQProjs to $RELEASE_NAME
	my $ini_fn = fixPathToOS($NewDB."/srcsafe.ini");
	system("copy /Y $ini_fn $ini_fn.old");
	&log("\t  Change VSS Database name to $RELEASE_NAME");
	open SSINI_I, "< $ini_fn.old" or Die("failed to read $ini_fn.old");
	open SSINI_O, "> $ini_fn" or Die("failed to create $ini_fn");

	my $line;
	next_line: while ($line = <SSINI_I>)
	{
		$_=$line;
		if(/^[\s]*Database_Name[\s]*=[\s]*.*?/)
		{
			printf SSINI_O "Database_Name = $RELEASE_NAME\n";
			next next_line;
		}
		printf SSINI_O $line;
	}
	close SSINI_O;
	close SSINI_I;
}

# ------------------------------------------------------
# build a list of unnecessary branches about to clean
# ------------------------------------------------------
sub buildCleanProjsStack
{
	&log("**\tbuild the unecessary source branch list for projects");
    	buildBranchStack() if !@SRC_BRANCH_STACK;
    	
	my $cmd = "$SSCMD dir \$/ZQProjs \"-Y$VSSUSER,$VSSPASSWD\" -F- -R";
	open(SS,"$cmd |");
	
	my $line;
  	ss_line: while($line = <SS>) 
  	{
		$_ = $line;
      		next ss_line if(!/^\$\/([^:]+):$/);
      		
		my $SrcBranch = $1;
		my $SrcBranchlen = length($SrcBranch);
		my $need_clean = 1;
		my $count = scalar(@SRC_BRANCH_STACK);
		my $i = 0;
		for($i=0 ; $i < $count && $need_clean; $i ++)
		{
			my $NeededBranchLen = length($SRC_BRANCH_STACK[$i]);
			if ($NeededBranchLen >= $SrcBranchlen)
			{
				$need_clean = 0 if (substr($SRC_BRANCH_STACK[$i], 0, $SrcBranchlen) eq $SrcBranch);
                	}
			else
			{
				$need_clean = 0 if (substr($SrcBranch, 0, $NeededBranchLen) eq $SRC_BRANCH_STACK[$i]);
			}
            	}
		
		push @PURGE_BRANCH_STACK, $SrcBranch if !$need_clean;

		my $count2 = scalar(@CLEAN_BRANCH_STACK);
		my $j = 0;
		for($j=0 ; $j < $count2 && $need_clean; $j ++)
		{
			my $cleanedLen = length($CLEAN_BRANCH_STACK[$j]);
			if ($cleanedLen >= $SrcBranchlen)
			{
				if (substr($CLEAN_BRANCH_STACK[$j], 0, $SrcBranchlen) eq $SrcBranch)
				{
			                $CLEAN_BRANCH_STACK[$j] = $SrcBranch if $need_clean;
					$need_clean = 0;
				}
			}
			else
			{
				$need_clean = 0 if (substr($SrcBranch, 0, $cleanedLen) eq $CLEAN_BRANCH_STACK[$j]);
			}
                }
			
		push @CLEAN_BRANCH_STACK, $SrcBranch if $need_clean;
	}
	
	my $branch;
	&log("\t  Unnecessary branches about to clean:");
	foreach $branch (@CLEAN_BRANCH_STACK)
	{
		&log("\t  + $branch");
	}
}

# ------------------------------------------------------
# clean the unnecessary source branches
# ------------------------------------------------------
sub cleanProjs
{
    # clean the unnecessary branches from the release VSS database for the projects

    buildCleanProjsStack() if !@CLEAN_BRANCH_STACK;
	
    my $branch;
    &log("\n**\tCleaning the unnecessary branches");
    # get each necessary VSS branch for building
    open YYF, ">> $TEMP\\YYF";
    my $i=0;
    for ( $i=0; $i<1024; $i++)
   {
      print YYF "Y\n";
   }
   close YYF;

    loc_cleansrc: foreach $branch (@CLEAN_BRANCH_STACK)
    {
        next loc_getsrc if !$branch;
	$branch = fixPathToLogic($branch);

	&log("\t  + /$branch");
        my $cmd = sprintf "type \"$TEMP\\YYF\" | $SSCMD Destroy \"-Y%s,%s\" \$/$branch", $VSSUSER, $VSSPASSWD;
        system($cmd) == 0 or Die("ERROR\tCommand \'$cmd\' failed.");
    }

    &log('unnecessary branches have been cleaned');
}

# ------------------------------------------------------
# purge the delete applied against the remained branches
# ------------------------------------------------------
sub purgeProjs
{
    # purge the pending changes on the branches for the projects
    buildCleanProjsStack() if !@CLEAN_BRANCH_STACK;

    my $branch;
	
    &log("\n**\tPurging the pending changes on the branches for the projects");
    # get each necessary VSS branch for building
    loc_purgesrc: foreach $branch (@PURGE_BRANCH_STACK)
    {
        next loc_purgesrc if !$branch;
	$branch = fixPathToLogic($branch);

        my $cmd = sprintf "echo Y | $SSCMD PURGE \"-Y%s,%s\" \$/$branch -I-", $VSSUSER, $VSSPASSWD;
        system($cmd) == 0 or Die("ERROR\tCommand \'$cmd\' failed.");
    }

	&log('source trees are purged');
}

# ------------------------------------------------------
# build up the list of source branch about to get from the VSS
# ------------------------------------------------------
sub buildBranchStack
{
    my $proj;
    my $branch;

    &log("**\tbuild the required source branch list for projects");

    my $buildsetting = fixPathToOS($BUILD_ROOT."/".$BUILD_SETTINGS);
	
    push @SRC_BRANCH_STACK, $BUILD_SETTINGS; # if not -d $buildsetting;
    foreach $proj (@PROJLIST)
    {
		$BUILD_BATCH{crnt_step} = "push source branch for project: ".$proj->{name};
        my $src_deps = $proj->{sources};
        my $dep;
        foreach $dep (@$src_deps)
        {
            my $need_push = 1;
            my $count = scalar(@SRC_BRANCH_STACK);
            my $i = 0;
            for($i=0 ; $i < $count ; $i ++)
            {
                my $len = length($dep);
                if (length($SRC_BRANCH_STACK[$i]) >= $len)
                {
                    my $tmpstr = substr($SRC_BRANCH_STACK[$i], 0, $len);
                    if ($tmpstr eq $dep)
                    {
                        $SRC_BRANCH_STACK[$i] = $dep if $need_push;
                        $SRC_BRANCH_STACK[$i] = '' if !$need_push;  # TODO: should delete this item from the stack, leave for now
                        $need_push = 0;
                    }
                }
            }
            push @SRC_BRANCH_STACK, $dep if $need_push;
        }
    }
}

# ------------------------------------------------------
# renew the build numbers based on the last successful build
# ------------------------------------------------------
sub renewBuildNumber
{
    &log("\nRenew batch number based on the last successful build");
	$BUILD_BATCH{crnt_step}='renew batch number based on the last successful build';
	my $batchfile = fixPathToOS($BUILD_ROOT."/".$BUILD_SETTINGS."/".$BUILD_BATCH{batch_fn});
	
    open BUILDBTH_F, "< $batchfile" or Die("failed to read $batchfile");
	my $line;
	$BUILD_BATCH{batch_num} =0;
	ver_h_next_line: while ($line = <BUILDBTH_F>)
    {
	    $_=$line;
		if(/^[\s]*[\s]*LAST_BUILD_BATCH[\s]*=[\s]*(\d+).*?/)
		{
		    $BUILD_BATCH{batch_num} = $1;
			next ver_h_next_line;
		}
		
		if(/^[\s]*[\s]*LB_([^\s]*)[\s]*=[\s]*(\d+).*?/)
		{
		    %BUILD_BATCH->{'LB_'.$1} = $2;
		    next ver_h_next_line;
		}
	}
	close BUILDBTH_F;
	chdir ($BUILD_ROOT);
	
	$BUILD_PRJS_DESC = "Projects to build:\n";
    foreach $proj (@PROJLIST)
    {
		my $key='LB_'.trim($proj->{name}).'_V'.trim($proj->{prod_ver});
		if ($BUILD_BATCH{$key})
		{
			$proj->{build_num} = $BUILD_BATCH{$key} +1;
		}
		else
		{
			$proj->{build_num} = 1;
		}
		$BUILD_BATCH{ $key } = $proj->{build_num};
		$BUILD_PRJS_DESC .= "[$proj->{name}, V$proj->{prod_ver}, build $proj->{build_num}]\n\t$proj->{desc}\n";
	}
	
    my $logmsg = sprintf "**\tlast build batch# %d, current build batch# ", $BUILD_BATCH{batch_num};
    $BUILD_BATCH{batch_num} +=1;
    $logmsg .= $BUILD_BATCH{batch_num}; 
	&log($logmsg);
}

# ------------------------------------------------------
# lable source with this build number
# ------------------------------------------------------
sub labelSplit
{
    &log("\nCommit build to the source tree");

    $BUILD_BATCH{crnt_step}="commit build to the source tree ";
    my $label = "Source Split for $opt_projname at $BUILD_TIME";
    my $comment = "Source Splited for $opt_projname onto $SSDIR\n";
	
    buildBranchStack() if !@SRC_BRANCH_STACK;
	
    my $cmd;
    my $branch;

    &log("**\tlable splited database");
    $cmd = sprintf "echo Y | $SSCMD LABEL \"-Y%s,%s\" \"-L$label\" \"-C$label\" \$/ -i-", $VSSUSER, $VSSPASSWD;
    system($cmd) == 0 or &log("WARNING\tLabel command \'$cmd\' failed.");

    &log("\tlable original source");
    my $tempss=$SSDIR;
    $SSDIR=$VSSROOT;
    $cmd = sprintf "echo Y | $SSCMD LABEL \"-Y%s,%s\" \"-L$label\" \"-C$label\" \$/ -i-", $VSSUSER, $VSSPASSWD;
    loc_lblsrc: foreach $branch (@SRC_BRANCH_STACK)
    {
        next loc_lblsrc if !$branch;
	$branch = fixPathToLogic($branch);
        #call vss client
        $cmd = sprintf "echo Y | $SSCMD LABEL \"-Y%s,%s\" \"-L$label\" \"-C$label\" \$/$branch -i-", $VSSUSER, $VSSPASSWD;
        system($cmd) == 0 or &log("WARNING\tLabel command \'$cmd\' failed.");
    }
    $SSDIR=$tempss;

    $BUILD_BATCH{crnt_step}="commited build to the source tree ";
}

# ------------------------------------------------------
# trim a string
# ------------------------------------------------------
sub trim
{
my @out = @_;
   for (@out)
	{
   	s/^\s+//;
      s/\s+$//;
      s/^\n+$//;
   }
   return wantarray ? @out : $out[0];
}

# ------------------------------------------------------
# fixPathToOS
# ------------------------------------------------------
sub fixPathToOS
{
	my @out = @_;
	for (@out)
	{
		s/\//\\/g;
	   }
	return wantarray ? @out : $out[0];
}

# ------------------------------------------------------
# fixPathToLogic
# ------------------------------------------------------
sub fixPathToLogic
{
	my @out = @_;
	for (@out)
	{
		s/\\/\//g;
	}
	return wantarray ? @out : $out[0];
}

sub Die
{
   &log(@_);
   $BUILD_BATCH{failed} = 1;
#   emailReport() if $EMAILNOTIF;
   exit -1;
}

sub log
{
   my ($log) = @_;
   # Only print to the log file if we are initialized.
   my (@lines) = split(/\n/,$log);
   my (@lt) = localtime;
   my $time = sprintf "%d\/%02d\/%02d %02d\:%02d\:%02d",
      $lt[5]+1900, $lt[4]+1, $lt[3], $lt[2], $lt[1], $lt[0];
   my $succ = open LOG, ">> $LOGFILE";
   foreach $line (@lines)
   {
      print LOG "$time  $line\n" if $succ;
      print "$line\n";
   }
   close LOG if $succ;
}

sub prompt
{
	my ($msg) = @_;
	my (@lines) = split(/\n/,$msg);
   	foreach $line (@lines)
   	{
      		print "\n$line";
   	}
	my $ch = <STDIN>;
	
	return trim($ch);
}
