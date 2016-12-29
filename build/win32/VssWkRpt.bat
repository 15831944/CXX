@rem = '-*- Perl -*-';
@rem = '
@echo off
perl -w -S %0 %1 %2 %3 %4 %5 %6 %7 %8 %9
goto EndOfPerl
';
###################################################################
# File Name:     VssWkRpt.bat
# Author:        Interactive ZQ
# Security:      Tech Mgm
# Description:   This program generates weekly checkin report, 
#                and email them out or upload records to database
# Modification Log:
# When           Version        Who						What
# -----------------------------------------------------------
# 2004-12-01     0.1           Hui.Shao            Create
###################################################################

################
# main entry   #
################
 ($SERVER,        $FTPUSER,   $FTPPASSWD, $FTPLOC)
=("192.168.0.73", "reporter", "ftp123",   "/tmp/crr_upd");

my $emailReport=1; # flag to enable email
my $submitToDB=1;  # flag to enable submit records

use Env qw(TEMP);
$tempdir = $TEMP;
use Env qw(PATH);
$PATH="$PATH;C:\\Program Files\\Microsoft Visual Studio\\Common\\VSS\\win32";

my @projlist;
my $now = time;
my $from = $now - 3600*24*7; # as a weekly report

# date-time display format
($sec, $min, $hrs, $day, $month, $year) = (localtime($from)) [0,1,2,3,4,5];
my $display_from = sprintf "%04d-%02d-%02d %02d:%02d", $year+1900, $month+1, $day, $hrs, $min;

($sec, $min, $hrs, $day, $month, $year) = (localtime($now)) [0,1,2,3,4,5];
my $display_to = sprintf "%04d-%02d-%02d %02d:%02d", $year+1900, $month+1, $day, $hrs, $min;

# fetch and build up the component list to report
fetchProjList();

# call to append per-vssdb reports
my $i=0;

# generates the reports
open(DBDATA, "> $tempdir\\dbdata.txt") if ($submitToDB ne 0);
while($projlist[$i])
{
	my @array = split(/,/, $projlist[$i++]);
	print "prepare report for project($array[0]): $array[1]/$array[2]\n";
	open(REPORT, "> $tempdir\\vssrpt-$array[0].txt");
	chgReport($array[0], $array[1], $array[2], $array[3], $array[4], $from, $now);
	close(REPORT);
}

# submit the checkin records to the database
if ($submitToDB ne 0)
{
	close(DBDATA);
	submitCheckinRecords("dbdata.txt");
}

# prepare per-supervisor reports and send email out
emailReport() if ($emailReport ne 0);
################
# end of main entry
################

#########################################################
# per-vssdb checkin report
# paramters: vssdir, vssroot, vssuser, vsspassword, from, to
#########################################################
sub chgReport
{
	my $compid = shift;
	use Env qw(SSDIR);
	$SSDIR = shift;
	my $vssroot = shift;
	my $vssusr = shift;
	my $vsspasswd = trim(shift);

	my $from = shift;
	my $to   = shift;

	my $output  = shift;

	($sec, $min, $hrs, $day, $month, $year) = (localtime($from)) [0,1,2,3,4,5];
	$from = sprintf "%04d-%02d-%02d;%02d:%02d", $year+1900, $month+1, $day, $hrs, $min;
	($sec, $min, $hrs, $day, $month, $year) = (localtime($to)) [0,1,2,3,4,5];
	$to = sprintf "%04d-%02d-%02d;%02d:%02d", $year+1900, $month+1, $day, $hrs, $min;

#	print "id=$compid; root=$SSDIR, loc=$vssroot, user=$vssusr, passwd=$vsspasswd\n";
	print REPORT ">>>> Project(s): $SSDIR/$vssroot\n";
   my $cmd = sprintf "ss history \"-Y%s,%s\" -R -Vd%s~d%s %s", $vssusr, $vsspasswd, $to, $from, $vssroot;
#	print "$cmd\n";
    
    open(SS, "$cmd |");
    
    # a typical output from vss
	# *****  threadplayer.cpp  *****
	# Version 4
	# User: Simin.xue     Date: 04-02-12   Time: 16:41
	# Checked in $/SeaMarker/source/mediamarker/APP

	ITEM:
    while($_=readln())
    {
		# the filename line
       	if(/^\*{5}[\s]*([^\*]+)\s+\*{5}?/)
    	{
    		$file = trim($1);
    
    		# version line
    		$_=readln();
    		next ITEM if (!(/^Version[\s]*(.+)?/));
           	$version = $1;
    
    		# user/ time line
    		$_=readln();
    		next ITEM if(!(m@^User:[\s]*([^\s]+)\s+Date:\s+(\d+)-(\d+)-(\d+)\s+Time:\s+(\d+):(\d+)@));
      		($user, $yr, $mo, $day, $hr, $min) = ($1, $2, $3, $4, $5, $6);
    
    	  	# checkin line
    		$_=readln();
    		next ITEM if (!(/^Checked in[\s]*([^\n]+)?/));
         $checkinloc = trim($1);
    
    		# comment line
    		$_=readln();
    		$comment ="";
	        if (/^Comment:[\s]*([^\n]+)?"$/)
    	    {
        	    $comment = $1;
	        }

	        # append the report line
			print REPORT "\n$yr-$mo-$day $hr:$min $user checked in $checkinloc/$file($version): $comment";
			print DBDATA "\n$compid>>$user>>$checkinloc/$file>>$version>>$yr-$mo-$day $hr:$min:00>>$comment" if ($submitToDB ne 0);
	    }
	}
    close(SS);
	print REPORT "\n";
}

#########################################################
# read a text line
#########################################################
sub readln
{
  my $line;
  $line = pop @linebuffer if(defined(@linebuffer));
  if (! defined($line))
  {
    $line = <SS>;
  }
  return $line;
}

#########################################################
# trim a string
#########################################################
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

#########################################################
# submit the checkin records to DB
# paramters: datafile - the datafile in $TEMP to upload
#########################################################
sub submitCheckinRecords
{
	my $rptfile = shift;
	print "submit the checkin records to database\n";
	
# upload checkin report
	open(FTPCMDS, "> $tempdir\\ftp.txt");
	print FTPCMDS "user $FTPUSER $FTPPASSWD\nprompt off\n";
	print FTPCMDS "cd $FTPLOC\n";
#	print FTPCMDS "ls -l\n";
	print FTPCMDS "bin\nput $tempdir\\$rptfile\n";
#	print FTPCMDS "ls -l\n";
	print FTPCMDS "bye\nquit\n";

	close(FTPCMDS);
	system("ftp -n $SERVER < $tempdir\\ftp.txt");

	open(MYSQLCMDS, "> $tempdir\\submit.sql");
	print MYSQLCMDS "LOAD DATA INFILE '$FTPLOC/$rptfile' IGNORE INTO TABLE checkin FIELDS TERMINATED BY '>>' IGNORE 1 LINES;\n";
	close(MYSQLCMDS);
	my $cmd ="mysql -h $SERVER -u root --password=toor CodeReview < $tempdir\\submit.sql";
	system($cmd);
}

#########################################################
# fetch and create project list
#########################################################
sub fetchProjList
{
# clean up the ftp dir
	open(FTPCMDS, "> $tempdir\\ftp.txt");
	print FTPCMDS "user $FTPUSER $FTPPASSWD\nprompt off\n";
	print FTPCMDS "mkdir $FTPLOC\ncd $FTPLOC\n";
#	print FTPCMDS "ls -l\n";
	print FTPCMDS "mdelete *.*\n";
#	print FTPCMDS "ls -l\n";
	print FTPCMDS "bye\nquit\n";
	close(FTPCMDS);
	system("ftp -n $SERVER < $tempdir\\ftp.txt");

	open(MYSQLCMDS, "> $tempdir\\list.sql");
	print MYSQLCMDS "SELECT id, dbroot, location, dbuser, dbpasswd FROM project WHERE reportable='T' INTO OUTFILE '$FTPLOC/projs.txt' FIELDS TERMINATED BY ',';";
	print MYSQLCMDS "SELECT email, refid FROM supervisor ORDER BY email INTO OUTFILE '$FTPLOC/svs.txt' FIELDS TERMINATED BY ',';";
	close(MYSQLCMDS);
	my $cmd ="mysql -h $SERVER -u root --password=toor CodeReview < $tempdir\\list.sql";
	system($cmd);

	open(FTPCMDS, "> $tempdir\\ftp.txt");
	print FTPCMDS "user $FTPUSER $FTPPASSWD\nprompt off\n";
	print FTPCMDS "bin\nget $FTPLOC/projs.txt\nget $FTPLOC/svs.txt\n";
	print FTPCMDS "bye\nquit\n";
	close(FTPCMDS);
	system("ftp -n $SERVER < $tempdir\\ftp.txt");

# build up component list
	open(PROJLIST, "< projs.txt");
 	
	my $line = <PROJLIST>;
	while (defined($line))
  	{
#		print "($#projlist)$line\n";
		push(@projlist, $line);
    	$line = <PROJLIST>;
	}
	close(PROJLIST);
}

#########################################################
# build up per-supervisor email and send out
#########################################################
sub emailReport
{
	#build up supervisor list
	open(LIST, "< svs.txt");
	$line = <LIST>;

	# generate email body
	open(MAIL, "> $tempdir\\emailbody.txt");
	print MAIL "Dear team leaders or PMs,\n\n";
	print MAIL "Attached please find a VSS check-in report for your weekly code review.\n";
	print MAIL "\n\nThis email and the report were generated automatically.\n";
	print MAIL "\n\nQA reporter\n";
	close(MAIL);

	# create the supervisor map/list
	my @row;
	my @svlist;
	my $email = "";
	while (defined($line))
  	{
		my @array = split(/,/, trim($line));
		if ($email ne $array[0])
		{
			if ($#row >1)
			{
				push(@svlist, @row);
				$#row=0;
			}
			$email = $array[0];
			push(@row, $email);
		}
		push(@row, $array[1]);
		push(@projlist, $array[1]);
    	$line = <LIST>;
	}

	push(@svlist, @row) if ($#row >1);
	close(LIST);
	
	# create the attachment and send mail out
	my $i=0;
#	print "svlist: @svlist\n";
	while($_ = $svlist[$i])
	{
		my $email="";
		my $attachment = "";
		if (!/\d/)
		{
			$email = $svlist[$i];
			open(MAIL, "> $tempdir\\vssrpt.txt");
			print MAIL "Checkin report for $email\n\n";
			close(MAIL);
			while(($_ = $svlist[++$i]) and /\d/)
			{
				print "Append report with vssrpt-$_.txt\n";
				system("type $tempdir\\vssrpt-$_.txt >> $tempdir\\vssrpt.txt");
				system("echo.>> $tempdir\\vssrpt.txt");
			}

	   # send email out
		my $cmd = "blat \"$tempdir\\emailbody.txt\" -t \"$email\" -s \"Weekly Check-in Report asof $display_to\" -attach \"$tempdir\\vssrpt.txt\"";
		system($cmd);
		}
		else
		{
			$i++;
		}
	}
}

endprog:
__END__

:EndOfPerl

