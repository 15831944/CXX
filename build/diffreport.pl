use Getopt::Long;
use Win32;
use Cwd;
use env;

&main();

sub main()
{
	&GetOptions(
				'help'		=>	\$opt_help,
				'list'		=>	\$opt_list,
				'branch=s'	=>	\$opt_branch,
				'date=s'	=>	\$opt_date,
				'lastdate=s'	=>	\$opt_lastdate,
		   );
	usage() if $opt_help;
	require "profile.pl";
	
	
	my @branchnames = split(/,/, $opt_branch);
        	
	if ($opt_list)
	{
		print "List all project Branchs:\n";
		foreach $branch (@ALL_Branchs)
		{
			print "  $branch \n";
		}
		#print "\n";
		exit 0;
	}
	my @stamp = (localtime(time))[0,1,2,3,4,5];
	my $DIFF_TIME = sprintf "%02d-%02d-%04d %02d:%02d", $stamp[4]+1, $stamp[3], $stamp[5]+1900, $stamp[2], $stamp[1], $stamp[0];
	
	
  	@BRANCHLIST = ();
	my $bn;
	foreach $bn (@branchnames)
	{
		foreach $bran (@ALL_Branchs)
		{
  			push (@BRANCHLIST, @$bran) if trim($bn) eq trim($bran);
  		}
  	}
  	die("A manual install must specify a valid project name by using --project=<PN>, please using --list to print all valid project") if !@BRANCHLIST;
  	
	my @SRC_BRANCH_STACK;
	$standard_date=covTime($opt_date);
	$last_date=covTime($opt_lastdate) if($opt_lastdate);
	$last_date=$DIFF_TIME if(!$opt_lastdate);
	
	die "you should give the right date for get the histroy, for more detail please use \"--help\"" if(!$standard_date);
	
	
	my @prj_Tree=GetProjectTree();
	my $branch;
	mkdir "fileinfo";
	&log("\n******Get project File Information Starts*******");
	foreach $branch (@prj_Tree)
	{
		my @FileStacks = GetFileStack($branch);
		my $File_count = scalar(@FileStacks);
		my $File_num=0;
		while($File_num<$File_count)
		{
			GetFileHistory("$FileStacks[$File_num][0]","$FileStacks[$File_num][1]");
			$File_num ++;
		}
	}
	&log("\n******Get project File Information ends*******");
	system ("rmdir /S /Q fileinfos");
	system ("package.bat");
}

# ------------------------------------------------------
# Get verbose Project Tree for get file information
# ------------------------------------------------------
sub GetProjectTree
{
	@SRC_BRANCH_STACK = @BRANCHLIST;
	my $branch = "";
	my @pro_subTree = ();
	&log("\tGet project subTree");
	foreach $branch (@SRC_BRANCH_STACK)
	{
		&log("\tGet project $branch subTree");
		my @list = ();
		push (@pro_subTree, $branch);
		my $cmd=sprintf "echo Y | $SSCMD -command GetProjectTree -server $SOSSERVER -name $SOSUSER -password $SOSPASSWD -database $SOSDATABASE -project \"$branch\">temp.txt";
		system ($cmd);
		open MF,"<temp.txt";
		my @list=<MF>;
		close MF;
		unlink "temp.txt";
		$pro_tree_num=scalar(@list);
		$i=1;
		@projectTree = ();
		while($i<$pro_tree_num)
		{
			$Length1=length($list[$i]);
			$Length2=length(trim($list[$i]));
			$proj_name=trim($list[$i]);
			$type = ($Length1-$Length2-1)/4 + 1;
			@{$projectTree[$i-1]} = ("$proj_name", "$type");
			$i++;
		}
		@list = ();
		$mul_tree=scalar(@projectTree);
		$number = 1;
		while($number<$mul_tree)
		{
			@temp = ();
			@temp=search_num($number-1,$projectTree[$number][1]-1) if($projectTree[$number][1]>1);
			$subTree = "$projectTree[$number][0]";
			foreach $t (@temp)
			{
				$subTree="$t"."/$subTree" if($t);
			}
			$subTree = "$branch"."/$subTree";
			&log("\t$branch subTree $subTree in stack");
			push (@pro_subTree, $subTree);
			$number++;
		}
	}
	return (@pro_subTree);
}

# ------------------------------------------------------
# search a num for projectTree
# ------------------------------------------------------
sub search_num($$)
{
	my($num, $standard_num) = @_;
	@array=();
	while($standard_num>1)
	{
		while($num>0)
		{
			if($projectTree[$num][1] == $standard_num)
			{
				$names=$projectTree[$num][0];
				$numss=$num;
				$num=0;
			}
		else
		{
			$num--;
		}
	}
		$num=$numss;
		push (@array, $names);
		$standard_num--;
	}
	return(@array);
}




sub GetFileStack($)
{
	my $branch = shift;
	my @FileStack = ();
	my $cmd=sprintf "echo Y | $SSCMD -command GetFileList -server $SOSSERVER -name $SOSUSER -password $SOSPASSWD -database $SOSDATABASE -project \"$branch\">temp.txt";
	system ($cmd);
	open MF,"<temp.txt";
	my @Filelist=<MF>;
	close MF;
	unlink "temp.txt";
	$file_num=scalar(@Filelist);
	my $filenum=0;
	my $FileStackNum=0;
	open FileInfo, ">>fileinfo\\SourceStat.txt";
	while($filenum<$file_num)
	{
		my $file_name=trim($Filelist[$filenum]);
		my $file_date=trim($Filelist[$filenum+3]);
		my $check_list=trim($Filelist[$filenum+4]);
		my $datecompare = timecompare($file_date,$standard_date);
		if($datecompare)
		{
			@{$FileStack[$FileStackNum]} = ("$branch", "$file_name");
			$FileStackNum++;
		}
		if($check_list)
		{
			printf FileInfo "Filename:$branch/$file_name ";
			printf FileInfo "Date:$file_date ";
			printf FileInfo "Check Out by:$check_list\n" ;
		}
		$filenum=$filenum+5;
	}
	close FileInfo;
	return (@FileStack);
}


# ------------------------------------------------------
# Get File History info
# ------------------------------------------------------

sub GetFileHistory()
{
    (my $branch, my $filename) = @_;
    my $cmd=sprintf "echo Y | $SSCMD -command GetFileHistory -server $SOSSERVER -name $SOSUSER -password $SOSPASSWD -database $SOSDATABASE -project \"$branch\" -file \"$filename\">temp.txt";
    system ($cmd);
    open MF,"<temp.txt";
    my @FileHistory=<MF>;
    close MF;
    unlink "temp.txt";
    open FileHistory,">>fileinfo\\Revisions.txt";
    my $history_cou=scalar(@FileHistory);
    my $history_sta=0;
    my @version=();
    while($history_sta<$history_cou)
    {
        my $File_OperateTime = trim($FileHistory[$history_sta+2]);
	my $date_compare = timecompare($File_OperateTime,$standard_date);
	my $date_compare2 = timecompare($last_date,$File_OperateTime);
	if($date_compare&&$date_compare2)
        {
            my $File_Version = trim($FileHistory[$history_sta]);
            my $File_Operator = trim($FileHistory[$history_sta+1]);
            my $File_Label = trim($FileHistory[$history_sta+4]);
            printf FileHistory "FileName:$branch/$filename, Version:$File_Version, Operator:$File_Operator, Time:$File_OperateTime\n" if((!($File_Label =~ m/^build batch/)) && ($File_Version));
            push (@version, $File_Version) if((!($File_Label =~ m/^build batch/)) && ($File_Version));
            $history_sta=$history_sta+5;
	}
	elsif(($date_compare)&&(!$date_compare2))
	{
		$history_sta=$history_sta+5;
	}
        else
        {
            $history_sta=$history_cou;
        }
    }
    close FileHistory;
    
    my $operate_times = scalar(@version);
    if ($operate_times > 0)
    {
        if($version[0]>1)
        {
        if($version[$operate_times-1]>1)
        {
        	$original=$version[$operate_times-1]-1;
        }
        else
        {
        	$original=$version[$operate_times-1];
        }
	&log("\n******Compare file $branch/$filename ver $original with $version[0]*******");
        open FileDiff, ">>fileinfo\\Diffs.txt";
        printf FileDiff "******** $branch/$filename\n";
        printf FileDiff "      **    original version:$original with current version:$version[0] difference:\n";
        close FileDiff;
        $cmd = sprintf "echo Y | $SSCMD -command GetFile -server $SOSSERVER -name $SOSUSER -password $SOSPASSWD -database $SOSDATABASE -project \"$branch\" -file \"$filename\" -revision $original -workdir fileinfos";
        system ($cmd);
        system ("ren fileinfos\\$filename $original");
        $cmd = sprintf "echo Y | $SSCMD -command GetFile -server $SOSSERVER -name $SOSUSER -password $SOSPASSWD -database $SOSDATABASE -project \"$branch\" -file \"$filename\" -revision $version[0] -workdir fileinfos";
        system ($cmd);
	system ("diff.exe \"fileinfos\\$original\" \"fileinfos\\$filename\" -w -b>>fileinfo\\Diffs.txt");
	open FileDiff, ">>fileinfo\\Diffs.txt";
	printf FileDiff "\n\n";
	close FileDiff;
	system ("del /F /Q fileinfos\\$original");
	system ("del /F /Q fileinfos\\$filename");
        }
        else
        {
        	printf FileDiff "******** $branch/$filename\n";
        	printf FileDiff "This is the first check in\n";
        }
     }   
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
# build up the list of source branch about to get from the VSS
# ------------------------------------------------------
sub buildBranchStack
{
    my $proj;
    my $branch;

     &log("**\tprepare necessary branch list");
	
	my $buildsetting = fixPathToOS($BUILD_ROOT."/".$BUILD_SETTINGS);
	
#    push @SRC_BRANCH_STACK, $BUILD_SETTINGS if not -d $buildsetting;
     @SRC_BRANCH_STACK = @Branch;
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


sub Die
{
   &log(@_);
   $BUILD_BATCH{failed} = 1;
   emailReport() if $EMAILNOTIF;
   exit -1;
}

sub timecompare()
{
	my ($time1, $time2) = @_;
	my @timestamp1=split(/ /, $time1);
	my @timestamp2=split(/ /, $time2);
	my $date1 = $timestamp1[0];
	my $date2 = $timestamp2[0];
	my $time1 = $timestamp1[1];
	my $time2 = $timestamp2[1];
	my @timestampss1 = ();
	my @timestampss2 = ();
	if ($time1)
	{
		@timestampss1 = split(/:/, $time1);
		$hour1 = $timestampss1[0];
		$minute1 = $timestampss1[1];
	}
	if ($time2)
	{
		@timestampss2 = split(/:/, $time2);
		$hour2 = $timestampss2[0];
		$minute2 = $timestampss2[1];
	}
	my @datestamp1 = split(/-/, $date1);
	my @datestamp2 = split(/-/, $date2);
	my $month1 = $datestamp1[0];
	my $day1 = $datestamp1[1];
	my $year1 = $datestamp1[2];
	my $month2 = $datestamp2[0];
	my $day2 = $datestamp2[1];
	my $year2 = $datestamp2[2];
	if($year1 > $year2)
	{
		return (1);
	}
	elsif($year1 < $year2)
	{
		return 0;
	}
	else
	{
		if($month1 > $month2)
		{
			return 1;
		}
		elsif($month1 < $month2)
		{
			return 0;
		}
		else
		{
			if($day1 > $day2)
			{
				return 1;
			}
			elsif($day1 < $day2)
			{
				return 0;
			}
			else
			{
				if($hour1 > $hour2)
				{
					return 1;
				}
				elsif($hour1 < $hour2)
				{
					return 0;
				}
				else
				{
					if($minute1 < $minute2)
					{
						return 0;
					}
					else
					{
						return 1;
					}
				}
			}
		}
	}
	
}


sub usage
{
   print <<EOF;
FileReport, by Mei Zhang <mei.zhang\@i-zq.com>

Usage: FileHistroy <options>
FileHistroy is a simple Perl program that can get ZQ projects file information based on the project profiles

options
    --branch=<BN>[,<BN>...]
    	specify branch(s) to get file information in this run
    	where <BN>s are short name which defined in the project profile.pl
    --logfile=<filename>
        specify the build log file
    --date=<date>
        specify the standard date, the script will get the file information after this date, use the format \"yy-mm-ddThh:mm\", it's 24-hour clock
    --lastdate=<lastdate>
        specify the last date, we can get the info before this specify date, use the format \"yy-mm-ddThh:mm\" default is localtime, it's 24-hour clock
    --list
        list all the project profiles
    --help
        display this screen

EOF

exit 0;
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
      print "$line\n" if !$succ;
   }
   close LOG if $succ;
}


sub covTime($)
{
	my $profile = shift;
	@date_cov = split (/T/,$profile);
	@date_cov2 = split (/-/,$date_cov[0]);
	$cov_time = "$date_cov2[1]-$date_cov2[2]-$date_cov2[0] $date_cov[1]";
	return ($cov_time);
}