# -----------------
# global declares
# -----------------

use vars qw(
	$VSSROOT $VSSUSER $VSSPASSWD $VSSSERVER $SOSDATABASE
	$BUILD_SETTINGS $BUILD_ROOT $RELEASE_ROOT %BUILD_BATCH $SSCMD $MSDEV6CMD $MSDEV7CMD
	$EMAILATTNS
	);

($SOSROOT, $SOSSERVER, $SOSUSER, $SOSPASSWD, $SOSDATABASE, $Get_SETTINGS, $Get_ROOT)
=  ("\\\\192.168.80.7\\vss\\vssmore\\DSE1\\VSS-DSE1Main","192.168.87.4:8080", "build", "nightly", "D:\\VSS\\vssmore\\DSE1\\VSS-DSE1Main\\srcsafe.ini", "ZQProjs/build", "e:\\build");
# =  ("\\\\ProjectServer\\vssmore\\DSE1\\VSS-DSE1Main", "build", "nightly", "ZQProjs/build", "c:\\temp", "\\\\hawkeye\\builds");

$MSVS6_INST = "C:\\Program Files\\Microsoft Visual Studio";
$MSVS7_INST = "C:\\Program Files\\Microsoft Visual Studio .NET 2003";
$SSCMD = "\"C:\\Program Files\\SourceOffSite\\soscmd.exe\"";
$MSDEV6CMD = "\"$MSVS6_INST\\Common\\MSDev98\\Bin\\MSDEV.EXE\"";
$MSDEV7CMD = "\"$MSVS7_INST\\Common7\\IDE\\DEVENV.EXE\"";
$MSDEV8CMD = "\"$MSVS8_INST\\Common7\\IDE\\DEVENV.EXE\"";


@Branch1 = ('ZQProjs/Common', 'ZQProjs/MulticastForwarding');
@Branch2 = ('ZQProjs/TianShan','ZQProjs/Generic/ContentProcess');
@Branch3 = ('ZQProjs/Telewest');
@Branch4 = ('ZQProjs/ContentDistribution','ZQProjs/TianShan/Shell');

@ALL_Branchs = (
		Branch1,
		Branch2,
		Branch3,
		Branch4,
		);

