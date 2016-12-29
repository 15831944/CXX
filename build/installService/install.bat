@rem = '-*- Perl -*-';
@rem = '
@echo off
@rem if %1x == DEBUGx goto PerlDebug
@echo off
perl -w -S %0 %1 %2 %3 %4 %5 %6 %7 %8 %9

@goto Done

:PerlDebug
perl -Sd %0 %2 %3 %4 %5 %6 %7 %8 %9

:Done
@goto EndOfPerl
';

use File::Find;
use Cwd;
use vars qw(%Service $LOGFILE $VERBOSE %Config);

use Win32::Service;
use Win32;


push (@INC,cwd);
require "profile.pl";

$CurrentPath 	= 	cwd;
$IP 		 	= 	"localHost";
#-----------------------------------------------------------------------
#	function:
#			write down the log to your specified logfile($LOGFILE)
#	input:
#	$log	the string u need write to the log file
#	$Level	Log	level if the log level is below your setting $VERBOSE
#			the log will not be written into log file. 
#-----------------------------------------------------------------------
sub Log
{
	my($log,$Level) = @_;

	if($Level <= $VERBOSE)
	{
		my (@lt) = localtime;
   		my $time = sprintf "%d\/%02d\/%02d %02d\:%02d\:%02d",
      		$lt[5]+1900, $lt[4]+1, $lt[3], $lt[2], $lt[1], $lt[0];	
		my $succ = open LOG, ">> $LOGFILE";
		my (@lines) = split(/\n/,$log);
		foreach $line (@lines)
   		{
      		print LOG "$time\t\t$Level:\t$line\n" if $succ;
      		print "$line\n" if $Level<3;
   		}		
		close LOG;
	}	
}
#-----------------------------------------------------------------------
#	function:
#					Execute a system command.
#	input:
#	$cmd			the cmd you will execute.
#	$enableOutput	if the value is 1,log the output after execute the cmd.
#					and print the message to the screen.
#					if the value is 0,only log the output and do not print
#					it to the screen.
#	return:
#					the value of execute command
#-----------------------------------------------------------------------
sub WinExec
{
	my ($cmd,$enableOutput) = @_;	
	Log("Execute $cmd",4);
	my($succ)= open CMD, "$cmd |";		
	my $line;
	while($line = <CMD>)
	{		
		if($enableOutput == 1)	
		{
			Log($line,0);
		}
		else
		{
			Log($line,4);
		}
	}	
	close CMD;
	return $succ;
}
#-----------------------------------------------------------------------
#	function:
#			callback when search file in package directory
#	input:
#			none
#-----------------------------------------------------------------------
sub wanted
{
	my($FileName) = $_;	
	my($FileDir)= $File::Find::dir;
	my(%serv) = %Service;
	my($InstallPath) = $serv{'installpath'};	
	my($DestineFile) = $InstallPath.$FileName;	
	$DestineFile =~ s/\\\\/\\/g;
	$DestineFile =~ s/\\/\\\\/g;
	
	my($InstallFile) = $FileDir.$FileName;	
	$InstallFile =~ s/\\\\/\\/g;
	$InstallFile =~ s/\\/\\\\/g;
	
	if ($FileName ne ".")
	{
		#urgly string
		my($cmd) = "\"".$CurrentPath."\\CopyInstallFile.exe\" \"$InstallFile\" \"$DestineFile\"\n";
		#printf $cmd;
		&WinExec($cmd,1);		
	}
}
#-----------------------------------------------------------------------
#	function:
#			call the copyinstallFile to exam the version of install file
#			if the version is newer update the file.
#	input:
#			Service reference
#-----------------------------------------------------------------------
sub CopyFiles
{
	my(%Service)= @_;
	my($InstallPath) = $Service{'installpath'};
	# parse the service get each value	
	my($PackagePath) = $Service{'packagepath'};
	$PackagePath = $CurrentPath.'\\Package\\';
	mkdir($InstallPath,0000);
	Log("Copying files to $InstallPath .........",1);
	&find(\&wanted,$PackagePath);
}
#-----------------------------------------------------------------------
#	function:
#				convert the hostname to IP
#	input:
#	$hostname	name of the host
#	return:
#				the string of the IP if can convert
#-----------------------------------------------------------------------
sub GetIPAddress
{  
    my($hostname) = @_;   	
      
   	my ($name,$aliases,$addrtype,$length,@addrs) = gethostbyname($hostname);   	
   	my ($a,$b,$c,$d) = unpack('C4', $addrs[0]);
   	my $IP = "$a.$b.$c.$d";
   	return $IP;
}
#-----------------------------------------------------------------------
#	function:
#			install service setup its displayname
#	input:
#	%Service	reference of service
#-----------------------------------------------------------------------
sub InstallService
{
	my(%Service) = @_;
	my($ServName) = $Service{'name'};
	my($DisName)  = $Service{'lname'};
	my($Shell) = $Service{'installpath'}.$Service{'shellimage'};
	my($account) = $Service{'account'};
	my($password) = $Service{'password'};
	&Log("Installing Service $ServName in $IP.",1);
	my($cmd) = "InstServ.exe $ServName \"$Shell\" $IP $account $password MANUL OWN";
	&WinExec($cmd,0);	
	if($DisName ne $ServName)
	{
		&Log("Set display name of $ServName as $DisName",1);
		$cmd = "InstServ.exe $ServName displayname=\"".$DisName."\"";
		&WinExec($cmd,0);
	}	
	
}
#-----------------------------------------------------------------------
#	function:
#			uninstall service 
#	input:
#	%Service	reference of service
#-----------------------------------------------------------------------
sub UnInstallService
{
	my(%Service) = @_;
	my($ServName) = $Service{'name'};
	&Log("Uninstall Service $ServName in $IP.",1);
	my($cmd) = "InstServ.exe $ServName remove $IP";
	#printf $cmd;
	&WinExec($cmd,0);
}
#-----------------------------------------------------------------------
#	function:
#				check service status,if installed,stop it and uninstall it
#	input:
#	%Service	reference of service
#	return:
#	0:			the service is not installed in the machine.
#	1:			error status.sometime service's status is "be set as delete"
#				Perhaps u should restart your machine.
#	2:			the service is uninstalled.
#-----------------------------------------------------------------------
sub CheckService
{
	my(%Service)= @_;
	$IP = &GetIPAddress($Service{'machine'});
	my($ServName) = $Service{'name'};
	# get the state of the service in current system
	&Win32::Service::GetStatus($IP, $ServName, \%status);		
	# if the service is running in the system stop it
	if (!$status{CurrentState})
	{
		Log("Can not find Service $ServName in machine $IP.",1);
		return 0;
	}
	if($status{CurrentState} =~ /[1-7]/)
	{	
		Log("Service $ServName is installed in the machine $IP.",1);
		if(!($status{CurrentState} == 1))
		{
			Log("Service $ServName is not stopped in the machine $IP.\nStopping it...",4);
			printf "Service $ServName is not stopped in the machine $IP.\nStopping it.";
			&Win32::Service::StopService($IP,$ServName);
			#wait until the service is stopped
			
			my($count) = 0;
			do
			{
				sleep(1);
				printf ".";
				&Win32::Service::GetStatus($IP, $ServName, \%status);	
				
				$count++;
				# if sleep more than 30s exit setup process.error status of service
				if($count == 30)
				{
					printf "\n";
					&Log("Error status.Check your status of Service $ServName.",0);
					return 1;
				}								
			}while($status{CurrentState}!= 1);		
			printf "\n";
		
			&UnInstallService(%Service);
			return 2;
		}
		else
		{
			&UnInstallService(%Service);
			return 2;
		}
	}

}
#-----------------------------------------------------------------------
#	function:
#				setup the registry as %config.this function will build a 
#				tmp regfile.reg to register configuration of service.
#				and after registed, the file will be deleted.
#	input:
#	%Service	reference of service
#-----------------------------------------------------------------------
sub SetupRegistry
{
	my(%Service) =  @_;
	my($ServName) = $Service{'name'};
	my($ProName) = $Service{'proname'};
	my($Description) = $Service{'description'};	
	my($InstallPath) = $Service{'installpath'};
	$InstallPath =~ s/\\/\\\\/g;
	my($MsgDll) = $InstallPath.$Service{'msgfile'};
	my($ShellMsgDll) = $InstallPath.$Service{'shellMsgFile'};
	my($MgmtPort) = sprintf "%x",$Service{'mgmtport'};
	my($ShellMgmtPort) = sprintf "%x",$Service{'shellmgmtport'};
	my($ImagePath) = $InstallPath.$Service{'exe'};
	#my(@Configs) = $Service{'ExternConfig'};
	&Log("Setuping registry information for $ServName...",1);
	open REGFILE, ">> regfile.reg";
	print REGFILE "Windows Registry Editor Version 5.00\n\n";
	print REGFILE "[HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\$ServName]\n";
	print REGFILE "\"ProductName\"=\"$ProName\"\n";
	print REGFILE "\"Description\"=\"$Description\"\n\n";
	
	print REGFILE "[HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\Eventlog\\Application\\$ServName]\n";
	print REGFILE "\"EventMessageFile\"=\"$MsgDll\"\n";
	print REGFILE "\"Typessupported\"=dword:7\n\n";
	
	print REGFILE "[HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\Eventlog\\Application\\".$ServName."_shell]\n";
	print REGFILE "\"EventMessageFile\"=\"$ShellMsgDll\"\n";
	print REGFILE "\"Typessupported\"=dword:7\n\n";	
	
	print REGFILE "[HKEY_LOCAL_MACHINE\\SOFTWARE\\SeaChange\\Management\\CurrentVersion\\Services\\$ServName]\n";
	print REGFILE "\"MgmtPortNumber\"=dword:$MgmtPort\n\n";
	
	print REGFILE "[HKEY_LOCAL_MACHINE\\SOFTWARE\\SeaChange\\Management\\CurrentVersion\\Services\\".$ServName."_shell]\n";
	print REGFILE "\"MgmtPortNumber\"=dword:$ShellMgmtPort\n\n";		
	
	print REGFILE "[HKEY_LOCAL_MACHINE\\SOFTWARE\\SeaChange\\$ProName\\CurrentVersion\\Services\\".$ServName."_shell]\n";
	print REGFILE "\"ImagePath\"=\"$ImagePath\"\n";
	print REGFILE "\"MgmtPortNumber\"=dword:$ShellMgmtPort\n\n";
	
	print REGFILE "[HKEY_LOCAL_MACHINE\\SOFTWARE\\SeaChange\\$ProName\\CurrentVersion\\Services\\$ServName]\n";
	print REGFILE "\"MgmtPortNumber\"=dword:$MgmtPort\n";	
	
	
	my($pointer) = \%Config;
	

	my($Key);
	my($Type);
	my($Value);
	my($list);
	foreach $Key(sort keys %$pointer)
	{	
		$list = $$pointer{$Key};  		
		$Type = $list->[0];		
		$Value = $list->[1];
		
		my($RegLine);
		$Type = lc($Type);
		if($Type eq "string")
		{
			$Value =~ s/\\/\\\\/g;
			$RegLine = "\"$Key\"=\"$Value\"\n";
		}else
		{
			$RegLine = "\"$Key\"=$Type:".$Value."\n";
		}		
		print REGFILE $RegLine;
	}
	close REGFILE;
	
	
	&WinExec("regedit.exe -s regfile.reg",0);
	&WinExec("del regfile.reg",0);
}
#-------------------------------------------------------------------------
#		main procedure
#-------------------------------------------------------------------------

&Log("***************************************************************",0);
&Log("*          SeaChange Service Installation Script for 			 ",0);
&Log("*          Currently Used Only for ZQ Interactive         	 ",0);
&Log("*          			Author	:Kaliven Lee	       	         ",0);
&Log("*          			Mail	:Kaliven.Lee\@i-zq.com 	         ",0);
&Log("***************************************************************",0);
&Log("\n\t\tInstall Service ".$Service{'name'},0);
printf "\n";



$Rtn = &CheckService(%Service);
if($Rtn != 1)	
{
#	printf cwd;
	&CopyFiles(%Service);
	&InstallService(%Service);

	
	&SetupRegistry(%Service);
#	&PostCopy();
	
	
}else
{
	Log("abnormal Service status.Skip setup.",0);
}

__END__
:EndOfPerl

