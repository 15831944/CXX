# -----------------
# global declares
# -----------------

use vars qw(
	$VSSROOT $VSSUSER $VSSPASSWD $VSSSERVER $SOSDATABASE
	$BUILD_SETTINGS $BUILD_ROOT $RELEASE_ROOT %BUILD_BATCH $SSCMD $MSDEV6CMD $MSDEV7CMD
	$EMAILATTNS
	);

($VSSROOT, $VSSSERVER, $VSSUSER, $VSSPASSWD, $SOSDATABASE, $BUILD_SETTINGS, $BUILD_ROOT, $RELEASE_ROOT)
=  ("\\\\192.168.80.7\\vss\\vssmore\\DSE1\\VSS-DSE1Main","192.168.87.4:8080", "build", "nightly", "D:\\VSS\\vssmore\\DSE1\\VSS-DSE1Main\\srcsafe.ini", "ZQProjs/build", "d:\\build", "\\\\10.50.12.2\\e\$\\build");
# =  ("\\\\ProjectServer\\vssmore\\DSE1\\VSS-DSE1Main", "build", "nightly", "ZQProjs/build", "c:\\temp", "\\\\hawkeye\\builds");

$MSVS6_INST = "C:\\Program Files (x86)\\Microsoft Visual Studio";
$MSVS7_INST = "C:\\Program Files (x86)\\Microsoft Visual Studio .NET 2003";
$MSVS8_INST = "C:\\Program Files (x86)\\Microsoft Visual Studio 8";
$SSCMD = "\"C:\\Program Files (x86)\\SourceOffSite\\soscmd.exe\"";
$MSDEV6CMD = "\"$MSVS6_INST\\Common\\MSDev98\\Bin\\MSDEV.EXE\"";
$MSDEV7CMD = "\"$MSVS7_INST\\Common7\\IDE\\DEVENV.EXE\"";
$MSDEV8CMD = "\"$MSVS8_INST\\Common7\\IDE\\DEVENV.EXE\"";

$EMAILATTNS='hui.shao@i-zq.com,jie.zhang@i-zq.com,bernie.zhao@i-zq.com,ken.qian@i-zq.com,daniel.wang@i-zq.com,lin.ouyang@i-zq.com,mei.zhang@i-zq.com';

use vars qw (
	@NIGHLY_PROJLIST,
	@WORK_PROJLIST,
);
	
# -----------------
# projects build profiles
# -----------------

my %ProjTemplate = (
	'name'			=> 'ProjectTemplate',	# short name of the project, no white spaces allowed here
	'environment'           => {
        	                     'variable'  => 'path',
        	                },   # set private environment variable for this project
	'prod_ver'		=> '0.1.0',		# <major_ver>.<minor_ver>.<patch_number>
	'sources'		=> ['ZQProjs/Common',
						'ZQProjs/ProjTemplate'], # necessary source sub-tree to build this project
	'work_path'		=> 'ZQProjs\\ProjTemplate',		 # the working path when build this project
	'rc_h_files'	=> ['ZQProjs\\ProjTemplate\\console\\ZQResource.h'], # the ZQResource.h files that must be updated with the version info
	'build_cmds'	=> ["$MSDEV6CMD ProjTemplate.dsw /MAKE \"console - Win32 Release\" /REBUILD" ], # the command lines to run the build processes
	'output_pkg'	=> ["ZQProjs\\ProjTemplate\\console\\Release\\console.exe" ], # the final packages from the build process(es)
);

%McastFwd = (
	'name'		=> 'McastFwd',
	'desc'		=> 'Multicast Tunneling',
	'owner'		=> 'hui.shao@i-zq.com',
	'prod_ver'	=> '1.2.4',
	'sources'	=> ['ZQProjs/Common', 'ZQProjs/MulticastForwarding'],
	'work_path'	=> "ZQProjs\\MulticastForwarding",
	'rc_h_files'	=> ["ZQProjs\\MulticastForwarding\\McastFwd\\ZQResource.h",
			    "ZQProjs\\MulticastForwarding\\McastTest\\ZQResource.h"],
	'build_cmds'=> ["$MSDEV7CMD /rebuild Release McastFwd.sln",
                    "package.bat" ],
	'output_pkg'	=> ["ZQProjs\\MulticastForwarding\\McastFwd.zip" ],
);

%ISAComponents = (
	'name'		=> 'ISA',
	'desc'		=> 'TWC ISA Components',
	'owner'		=> 'jie.zhang@i-zq.com',
	'environment'           => {
       	                     'ITVSDKPATH'     => 'D:\\SDK\\SeaChangeKits\\ITV_V03.5.RELEASE.SDK',
                                'VSTRMKITPATH'   => 'D:\\SDK\\SeaChangeKits\\VstrmKitV5.3.2a',
                                'ACE_ROOT'       => 'D:\\SDK\\3rdPartyKits\\ACE_5.3a_p15',
                                'RegExppKit'     => 'D:\\SDK\\3rdPartyKits\\regexpp3',
      	                },  
	'prod_ver'	=> '4.1.16',
	'sources'	=> ['ZQProjs/Common', 'ZQProjs/ISA'],
	'work_path'	=> "ZQProjs\\ISA",
	'rc_h_files'	=> ['ZQProjs/ISA/ZQISAVersion.h',
						],
	'build_cmds'=> ["$MSDEV7CMD /REBUILD Release /project buildoldver SeacISA15.sln",
                       "isapkg_v7.bat"],
	'output_pkg'	=> ["ZQProjs\\ISA\\isa.zip" ]
);

%ISAComponents_IngestCard = (
	'name'		=> 'ISA_IngestCard',
	'desc'		=> 'TWC ISA Components',
	'owner'		=> 'jie.zhang@i-zq.com',
	'environment'           => {
        	                     'ITVSDKPATH'     => 'D:\\SDK\\SeaChangeKits\\ITV_V03.5.RELEASE.SDK',
                                 'VSTRMKITPATH'   => 'D:\\SDK\\SeaChangeKits\\VstrmKitV5.3.10',
                                 'ACE_ROOT'       => 'D:\\SDK\\3rdPartyKits\\ACE_5.3a_p15',
                                 'RegExppKit'     => 'D:\\SDK\\3rdPartyKits\regexpp3',
        	                },  
	'prod_ver'	=> '4.5.0',
	'sources'	=> ['ZQProjs/Common', 'ZQProjs/ISA'],
	'work_path'	=> "ZQProjs\\ISA",
	'rc_h_files'	=> ['ZQProjs/ISA/ZQISAVersion.h',
						],
	'build_cmds'=> ["$MSDEV7CMD /REBUILD Release /project buildall SeacISA15.sln",
                        "isapkgv7_ingestcard.bat"],
	'output_pkg'	=> ["ZQProjs\\ISA\\isa.zip" ]
);

%ISAComponents_IngestCard_SSP23 = (
	'name'		=> 'ISA_IngestCard_SSP23',
	'desc'		=> 'TWC ISA Components',
	'owner'		=> 'bernie.zhao@i-zq.com',
	'environment'           => {
        	                     'ITVSDKPATH'     => 'D:\\ITVSDK-v4.0.RC1',
        	                     #'ITVSDKPATH'     => 'D:\\SDK\\SeaChangeKits\\ITVSDK-v4.0.20070225.BZ',
                                 'VSTRMKITPATH'   => 'D:\\SDK\\SeaChangeKits\\VstrmKitV5.3.10',
                                 'ACE_ROOT'       => 'D:\\SDK\\3rdPartyKits\\ACE_5.3a_p15',
                                 'RegExppKit'     => 'D:\\SDK\\3rdPartyKits\regexpp3',
        	                },  
	'prod_ver'	=> '4.6.2',
	'sources'	=> ['ZQProjs/Common', 'ZQProjs/ISA'],
	'work_path'	=> "ZQProjs\\ISA",
	'rc_h_files'	=> ['ZQProjs/ISA/ZQISAVersion.h',
						],
	'build_cmds'=> ["$MSDEV7CMD /REBUILD Release /project buildall_SSP23 SeacISA15.sln",
                        "isapkgv7_ingestcard.bat"],
	'output_pkg'	=> ["ZQProjs\\ISA\\isa.zip" ]
);

%FtpMover = (
	'name'		=> 'FtpMover',
	'desc'		=> 'ZQ FtpMover Serivce',
	'owner'		=> 'kaliven.lee@i-zq.com',
	'prod_ver'	=> '1.0.0',
	'sources'	=> ['ZQProjs/Common', 'ZQProjs/Generic/FtpMover'],
	'work_path'	=> "ZQProjs\\Generic\\FtpMover",
	'rc_h_files'	=> ['ZQProjs/Generic/FtpMover/ZQResource.h'],
	'build_cmds'=> ["$MSDEV6CMD FtpMover.dsw /MAKE \"FtpMover - Win32 Release\" /REBUILD","package.bat"],
	'output_pkg'	=> ["ZQProjs\\Generic\\FtpMover\\FtpMover.zip" ],
);
%DBSync = (
	'name'		=> 'DBSync',
	'desc'		=> 'ZQ DBSync Serivce',
	'dependence'    => ['DBSync_withoutPlugin','DBSync_forTelewest'],
	'environment'           => {
		                     #'ITVSDKPATH'       => 'D:\\SDK\\SeaChangeKits\\ITVSDK-v3.2.INTERNAL',
		                     'ITVSDKPATH'       => 'D:\\SDK\\SeaChangeKits\\ITV_V03.5.RELEASE.SDK',
		                },
	'owner'		=> ['ken.qian@i-zq.com','shuai.chen@i-zq.com'],
	'prod_ver'	=> '3.6.9',
	'sources'	=> ['ZQProjs/Common','ZQProjs/Generic/DBSync','ZQProjs/Generic/DBSADI','ZQProjs/Generic/JMSCppLib'],
	'work_path'	=> "ZQProjs\\Generic\\DBSync",
	'rc_h_files'	=> ['ZQProjs/Generic/DBSync/ZQResource.h',
	                    'ZQProjs/Generic/DBSADI/IDSSyncEventPlugin/IDSSyncEventPlugin/ZQResource.h',
	                    'ZQProjs/Generic/DBSADI/ManualSyncAddin/ManualSyncAddin/ZQResource.h',],
	'build_cmds'=> [
	                "$MSDEV6CMD DBSyncServ.dsw /MAKE \"DBSyncServ - Win32 Release\" /REBUILD",
			"package_withPlugIn.bat"],
	'output_pkg'	=> ["ZQProjs\\Generic\\DBSync\\DBSync.zip" ],
);
%DBSync_withoutPlugin = (
	'name'		=> 'DBSync_withoutPlugin',
	'desc'		=> 'ZQ DBSync Serivce without Plugin',
	'environment'           => {
		                     #'ITVSDKPATH'       => 'D:\\SDK\\SeaChangeKits\\ITVSDK-v3.2.INTERNAL',
		                     'ITVSDKPATH'       => 'D:\\SDK\\SeaChangeKits\\ITV_V03.5.RELEASE.SDK',
		                },
	'owner'		=> ['ken.qian@i-zq.com','shuai.chen@i-zq.com'],
	'prod_ver'	=> '3.6.9',
	'sources'	=> ['ZQProjs/Common','ZQProjs/Generic/DBSync','ZQProjs/Generic/DBSADI','ZQProjs/Generic/JMSCppLib'],
	'work_path'	=> "ZQProjs\\Generic\\DBSync",
	'rc_h_files'	=> ['ZQProjs/Generic/DBSync/ZQResource.h',
	                    'ZQProjs/Generic/DBSADI/IDSSyncEventPlugin/IDSSyncEventPlugin/ZQResource.h',
	                    'ZQProjs/Generic/DBSADI/ManualSyncAddin/ManualSyncAddin/ZQResource.h',],
	'build_cmds'=> [
	                "$MSDEV6CMD DBSyncServ.dsw /MAKE \"DBSyncServ - Win32 Release\" /REBUILD",
	                "package_withoutPlugin.bat"],
	'output_pkg'	=> ["ZQProjs\\Generic\\DBSync\\DBSync_withoutPlugin.zip"],
);
%DBSync_forTelewest = (
	'name'		=> 'DBSync_forTelewest',
	'desc'		=> 'ZQ DBSync Serivce for Telewest without Plugin',
	'environment'           => {
		                     #'ITVSDKPATH'       => 'D:\\SDK\\SeaChangeKits\\ITVSDK-v3.2.INTERNAL',
		                     'ITVSDKPATH'       => 'D:\\sdk\\SeaChangeKits\\ITVSDK-v2.5.INTERNAL',
		                },
	'owner'		=> ['ken.qian@i-zq.com','shuai.chen@i-zq.com'],
	'prod_ver'	=> '3.6.9',
	'sources'	=> ['ZQProjs/Common','ZQProjs/Generic/DBSync','ZQProjs/Generic/DBSADI','ZQProjs/Generic/JMSCppLib'],
	'work_path'	=> "ZQProjs\\Generic\\DBSync",
	'rc_h_files'	=> ['ZQProjs/Generic/DBSync/ZQResource.h',
	                    'ZQProjs/Generic/DBSADI/IDSSyncEventPlugin/IDSSyncEventPlugin/ZQResource.h',
	                    'ZQProjs/Generic/DBSADI/ManualSyncAddin/ManualSyncAddin/ZQResource.h',],
	'build_cmds'=> [
	                "$MSDEV6CMD DBSyncServ.dsw /MAKE \"DBSyncServ - Win32 Release\" /REBUILD",
	                "package_forTelewest.bat"],
	'output_pkg'	=> ["ZQProjs\\Generic\\DBSync\\DBSync_forTelewest.zip"],
);
%srvLoad = (
	'name'		=> 'SrvLoad',
	'desc'		=> 'ZQ SrvLoad Serivce For Telewest',
	'owner'		=> 'ken.qian@i-zq.com',
	'dependence'    => ['SrvLoad_forTeleWest'],
	'prod_ver'	=> '1.0.1',
	'sources'	=> ['ZQProjs/Common', 'ZQProjs/Telewest/CmsRetiever'],
	'work_path'	=> "ZQProjs\\Telewest\\CmsRetiever",
	'rc_h_files'	=> ['ZQProjs/Telewest/CmsRetiever/ZQResource.h'],
	'build_cmds'=> ["$MSDEV6CMD CmsRetriever.dsw /MAKE \"CmsRetriever - Win32 Release\" /REBUILD","package.bat"],
	'output_pkg'	=> ["ZQProjs\\telewest\\CMSRetiever\\SrvLoad.zip" ]
);

%SrvLoad_forTelewest = (
	'name'		=> 'SrvLoad_forTelewest',
	'desc'		=> 'ZQ SrvLoad Serivce For Telewest',
	'environment'           => {
		                     'ITVSDKPATH'       => 'D:\\sdk\\SeaChangeKits\\ITVSDK-v2.5.INTERNAL',
		                },
	'owner'		=> 'ken.qian@i-zq.com',
	'prod_ver'	=> '1.0.1',
	'sources'	=> ['ZQProjs/Common', 'ZQProjs/Telewest/CmsRetiever'],
	'work_path'	=> "ZQProjs\\Telewest\\CmsRetiever",
	'rc_h_files'	=> ['ZQProjs/Telewest/CmsRetiever/ZQResource.h'],
	'build_cmds'=> ["$MSDEV6CMD CmsRetriever.dsw /MAKE \"CmsRetriever - Win32 Release\" /REBUILD","package.bat"],
	'output_pkg'	=> ["ZQProjs\\telewest\\CMSRetiever\\SrvLoad.zip" ]
);
%NSSync = (
	'name'		=> 'NSSync',
	'desc'		=> 'ZQ NSSync Service For Telewest',
	'owner'		=> 'bernie.zhao@i-zq.com',
	'environment'           => {
		                     'ITVSDKPATH'       => 'D:\\SDK\\SeaChangeKits\\ITVSDK-v3.2.INTERNAL',
		                },
	'dependence'    => ['NSSync_forVirginMedia'],
	'prod_ver'	=> '1.2.3',
	'sources'	=> ['ZQProjs/Common', 'ZQProjs/Telewest/NSSync'],
	'work_path'	=> "ZQProjs\\Telewest\\NSSync",
	'rc_h_files'	=> ['ZQProjs/Telewest/NSSync/Navigator/ZQResource.h'],
	'build_cmds'=> ["$MSDEV7CMD /rebuild \"Release\" NavigatorServ.sln","package.bat"],
	'output_pkg'	=> ["ZQProjs\\telewest\\NSSync\\NSSync.zip" ]
);
%NSSync_forVirginMedia = (
	'name'		=> 'NSSync_forVirginMedia',
	'desc'		=> 'ZQ NSSync Service For Virgin Media',
	'environment'           => {
		                     'ITVSDKPATH'       => 'D:\\sdk\\SeaChangeKits\\ITVSDK-v2.5.INTERNAL',
		                },
	'owner'		=> 'bernie.zhao@i-zq.com',
	'prod_ver'	=> '1.2.3',
	'sources'	=> ['ZQProjs/Common','ZQProjs/Telewest/NSSync'],
	'work_path'	=> "ZQProjs\\Telewest\\NSSync",
	'rc_h_files'	=> ['ZQProjs/Telewest/NSSync/Navigator/ZQResource.h'],
	'build_cmds'=> ["$MSDEV7CMD /rebuild \"Release\" NavigatorServ.sln","package_forVirginMedia.bat"],
	'output_pkg'	=> ["ZQProjs\\telewest\\NSSync\\NSSync_forVirginMedia.zip" ]
);

%PlaylistAS = (
	'name'		=> 'PlaylistAS',
	'desc'		=> 'ZQ PlaylistAS Service For Telewest',
	'owner'		=> 'bernie.zhao@i-zq.com',
	'prod_ver'	=> '1.0.8',
	'sources'	=> ['ZQProjs/Common', 'ZQProjs/Telewest/PlaylistAS'],
	'work_path'	=> "ZQProjs\\Telewest\\PlaylistAS",
	'rc_h_files'	=> ['ZQProjs/Telewest/PlaylistAS/PLAYLISTAS/ZQResource.h'],
	'build_cmds'=> ["$MSDEV6CMD PlaylistAS.dsw /MAKE \"PlaylistSoapUDTMapper - Win32 Unicode Release MinDependency\" \"PlaylistAS - Win32 Release\" /REBUILD","package.bat"],
	'output_pkg'	=> ["ZQProjs\\telewest\\PLAYLISTAS\\PLAYLISTAS.zip" ]
);
%ScheduledTV = (
	'name'		=> 'ITVPlayback',
	'desc'		=> 'ZQ ITVPlayback Service For ScheduleTV',
	'owner'		=> 'bernie.zhao@i-zq.com',
	'prod_ver'	=> '1.0.1',
	'sources'	=> ['ZQProjs/Common', 'ZQProjs/ScheduledTV_new'],
	'work_path'	=> "ZQProjs\\ScheduledTV_new\\MainCtrl",
	'rc_h_files'	=> ['ZQProjs/ScheduledTV_new/MainCtrl/ZQResource.h'],
	'build_cmds'=> ["$MSDEV6CMD ScheduleTVServ.dsw /MAKE \"ScheduleTVServ - Win32 Release\" /REBUILD","package.bat"],
	'output_pkg'	=> ["ZQProjs\\ScheduledTV_new\\MainCtrl\\ITVPlayback.zip" ]
);
%MODAuthorization = (
	'name'		=> 'MODAuthorization',
	'desc'		=> 'MOD Plug-in used to integrate with external system',
	'owner'		=> 'ken.qian@i-zq.com',
	'prod_ver'	=> '1.0.8',
	'sources'	=> ['ZQProjs/Common','ZQProjs/Telewest/MODPlugin'],
	'work_path'	=> "ZQProjs\\Telewest\\MODPlugin",
	'rc_h_files'	=> ['ZQProjs\\Telewest\\MODPlugin\\MODAuthorization\\ZQResource.h'],
	'build_cmds'=> ["$MSDEV6CMD MODAuthorization.dsw /MAKE \"MODAuthorization - Win32 Release\" /REBUILD","package.bat"],
	'output_pkg'	=> ["ZQProjs\\Telewest\\MODPlugin\\MODPlugIn.zip" ]
);
%NoiseSim = (
	'name'		=> 'NoiseSim',
	'desc'		=> 'Generating noise to simulating a noisy network',
	'owner'		=> 'lin.ouyang@i-zq.com',
	'prod_ver'	=> '0.2.0',
	'sources'	=> ['ZQProjs/Generic/NoiseSim'],
	'work_path'	=> "ZQProjs\\Generic\\NoiseSim",
	'rc_h_files'	=> ['ZQProjs\\Generic\\NoiseSim\\ZQResource.h'],
	'build_cmds'	=> ["$MSDEV6CMD NoiseSim.dsw /MAKE \"NoiseSim - Win32 Release\" /REBUILD","package.bat"],
	'output_pkg'	=> ["ZQProjs\\Generic\\NoiseSim\\NoiseSim.zip" ]
);
%JMSCpp = (
	'name'		=> 'JMSCpp',
	'desc'		=> 'C++ lib and samples to access JMS Services',
	'owner'		=> 'jianjun.li@i-zq.com',
	'prod_ver'	=> '0.1.0',
	'sources'	=> ['ZQProjs/Generic/JMSCppLib'],
	'work_path'	=> "ZQProjs\\Generic\\JMSCppLib\\JMSCpp",
	'rc_h_files'	=> ['ZQProjs\\Generic\\JMSCppLib\\JMSCpp\\ZQResource.h'],
	'build_cmds'	=> ["$MSDEV6CMD JMSCpp.dsw /MAKE \"JMSCpp - Win32 Release\" /REBUILD",
			    "$MSDEV6CMD JMSCpp.dsw /MAKE \"JMSCpp - Win32 Debug\" /REBUILD",
			    "package.bat"],
	'output_pkg'	=> ["ZQProjs\\Generic\\JMSCppLib\\JMSCpp\\JMSCpp.zip" ]
);
%IngestSim = (
	'name'		=> 'IngestSim',
	'desc'		=> 'Injest message to ftp server',
        'environment'   => {
        	'WPCAPSDKPATH'   => 'D:\\SDK\\3rdPartyKits\\WinPcap3.1\\WpdPack',
                       },
	'owner'		=> 'lin.ouyang@i-zq.com',
	'prod_ver'	=> '0.1.0',
	'sources'	=> ['ZQProjs/Generic/IngestSim', 'ZQProjs/Common'],
	'work_path'	=> "ZQProjs\\Generic\\IngestSim",
	'rc_h_files'	=> ['ZQProjs\\Generic\\IngestSim\\ZQResource.h'],
	'build_cmds'	=> ["$MSDEV6CMD IngestSim.dsw /MAKE \"IngestSim - Win32 Release\" /REBUILD","package.bat"],
	'output_pkg'	=> ["ZQProjs\\Generic\\IngestSim\\IngestSim.zip" ],
);
%nPVR = (
	'name'		=> 'nPVR',
	'desc'		=> 'nPVR',
	'environment'   => {
			    'GSOAPPATH'    => 'D:\\SDK\\3rdPartyKits\\gsoap-win32-2.7', 
			    'ACE_ROOT'     => 'D:\\sdk\\3rdPartyKits\\ACE_5.3a_p15',
			    'RegExppKit'     => 'D:\\SDK\\3rdPartyKits\\regexpp3',
			    'ITVSDKPATH'   => 'D:\\SDK\\SeaChangeKits\\ITVSDK-v3.2.INTERNAL',
			   },
	'owner'		=> 'jie.zhang@i-zq.com',
	'prod_ver'	=> '1.1.1',
	'sources'	=>  ['ZQProjs/Common','ZQProjs/Generic/JMSCppLib','ZQProjs/nPVR', 'ZQProjs/ISA'],
	'work_path'	=> "ZQProjs\\nPVR",
	'rc_h_files'	=> ['ZQProjs\\nPVR\\nPVRVersion.h'],
	'build_cmds'	=> ["$MSDEV6CMD AssetGear.dsw /MAKE \"AGTest - Win32 Release\" /BUILD","npvrpkg.bat"],
	'output_pkg'	=> ["ZQProjs\\nPVR\\nPVR.zip" ]
);


%ZQSpot = (
	'name'		=> 'ZQSpot',
	'desc'		=> 'ZQSpot',
        'environment'           => {
		                     'ITVSDKPATH'        => 'D:\\SDK\\SeaChangeKits\\ITV_V03.2.SDK.INTERNAL-PRERELEASE',
        	                     'VSTRMPATH'         => 'D:\\SDK\\SeaChangeKits\\VstrmKitV5.2.1\\Sdk',
        	                     'OPENSSLPATH'       => 'D:\\SDK\\3rdPartyKits\\openssl',
        	                     'ICE_ROOT'		 => 'D:\\SDK\\3rdPartyKits\\Ice-3.1.0-VC60',
        	                     'STLPORT_ROOT'	 => 'D:\\SDK\\3rdPartyKits\\Ice-3.1.0-VC60\\include\\stlport',
        	                     '3RDPARTYKITS_PATH' => 'D:\\SDK\\3rdPartyKits',
        	                     'ExpatPath'         => 'D:\\SDK\\3rdPartyKits\\expat',
        	                }, 
	'owner'		=> ['li.huang@i-zq.com'],
	'prod_ver'	=> '1.0.0',
	'sources'	=> ['ZQProjs/Common', 'ZQProjs/Generic/ZQSpot','ZQProjs/TianShan'],
	'work_path'	=> "ZQProjs\\Generic\\ZQSpot",
	'rc_h_files'	=> ['ZQProjs/Generic/ZQSpot/SpotExplorer/resource.h',],
	'build_cmds'=> ["$MSDEV6CMD .\\SpotExplorer\\SpotExplorer.dsw /MAKE \"SpotExplorer - Win32 Release\" /REBUILD","package.bat"],
	'output_pkg'	=> ["ZQProjs\\Generic\\ZQSpot\\ZQSpot.zip" ]
);

%TianShanSDK = (
	'name'		=> 'TianShanSDK',
	'desc'		=> 'TianShan SDK',
        'environment'           => {
        	                     'ICE_ROOT'		 => 'D:\\SDK\\3rdPartyKits\\Ice-3.1.0-VC60',
        	                     'STLPORT_ROOT'	 => 'D:\\SDK\\3rdPartyKits\\Ice-3.1.0-VC60\\include\\stlport',
        	                     '3RDPARTYKITS_PATH' => 'D:\\SDK\\3rdPartyKits',
        	                     'ExpatPath'         => 'D:\\SDK\\3rdPartyKits\\expat',
        	                     'ANT_HOME'          => 'D:\\SDK\\3rdPartyKits\\apache-ant-1.6.5',
        	                }, 
	'owner'		=> ['hui.shao@i-zq.com'],
	'prod_ver'	=> '1.18.0',
	'sources'	=> ['ZQProjs/Common', 'ZQProjs/TianShan'],
	'work_path'	=> "ZQProjs\\TianShan",
	'rc_h_files'	=> [],
	'build_cmds'=> ["$MSDEV6CMD .\\SDK\\sdk.dsw /MAKE \"TianShanIce - Win32 Debug\" /REBUILD",
                    "$MSDEV6CMD .\\SDK\\sdk.dsw /MAKE \"TianShanIce - Win32 Release\" /REBUILD",
                    "$MSDEV6CMD .\\SDK\\sdk.dsw /MAKE \"TianShanIce - Win32 Java\" /REBUILD",
                    ".\\SDK\\packsdk.bat"],
	'output_pkg'	=> ["ZQProjs\\TianShan\\sdk\\TianShanSDK.zip" ]
);

%WMSService = (
	'name'		=> 'WMSService',
	'desc'		=> 'WMSService',
        'environment'           => {
        	                     'OPENSSLPATH'      => 'D:\\SDK\\3rdPartyKits\\openssl',
        	                     'ICE_ROOT'		=> 'D:\\SDK\\3rdPartyKits\\Ice-3.1.0-VC60',
        	                }, 
	'owner'		=> ['cary.xiao@i-zq.com'],
	'prod_ver'	=> '0.0.0',
	'sources'	=> ['ZQProjs/Common','ZQProjs/TianShan'],
	'work_path'	=> "ZQProjs\\TianShan\\wms",
	'rc_h_files'	=> ['ZQProjs/TianShan/wms/ZQResource.h',],
	'build_cmds'=> ["$MSDEV6CMD WMSService.dsw /MAKE \"WMSService - Win32 Release\" /REBUILD","package.bat"],
	'output_pkg'	=> ["ZQProjs\\TianShan\\wms\\WMSService.zip" ]
);


%ColorBar = (
	'name'		=> 'ColorBar',
	'desc'		=> 'ColorBar',
	'owner'		=> 'yonghua.deng@i-zq.com',
	'prod_ver'	=> '1.0.0',
	'sources'	=> ['ZQProjs/Generic/COLORBAR/'],
	'work_path'	=> "ZQProjs\\Generic\\COLORBAR\\Source",
	'rc_h_files'	=> [],
	'build_cmds'=> ["$MSDEV6CMD ColorBar.dsw /MAKE \"ColorBar - Win32 Unicode Release MinDependency\" /REBUILD",
	                 "$MSDEV6CMD ColorBar.dsw /MAKE \"ColorBar - Win32 Unicode Debug\" /REBUILD",
	                 "package.bat"],
	'output_pkg'	=> ["ZQProjs\\Generic\\ColarBar\\ColarBar.zip" ],
);

%ColorBarContainer = (
	'name'		=> 'ColorBarContainer',
	'desc'		=> 'ColorBarContainer',
	'owner'		=> 'yonghua.deng@i-zq.com',
	'prod_ver'	=> '1.0.0',
	'sources'	=> ['ZQProjs/Generic/COLORBARContainer/','ZQProjs/ChannelOnDemand/','ZQProjs/Common','ZQProjs/TianShan/Ice','ZQProjs/TianShan/Common'],
	'work_path'	=> "ZQProjs\\Generic\\COLORBARContainer\\Source",
	'rc_h_files'	=> [],
	'build_cmds'=> ["$MSDEV6CMD CBarContainer.dsw /MAKE \"CBarContainer - Win32 Release MinDependency\" /REBUILD",
	                 "$MSDEV6CMD CBarContainer.dsw /MAKE \"CBarContainer - Win32 Debug\" /REBUILD",
	                 "package.bat"],
	'output_pkg'	=> ["ZQProjs\\Generic\\COLORBARContainer\\Source\\ColorBarContainer.zip"],
);

%DODServer = (
	'name'		=> 'DODServer',
	'desc'		=> 'DataOnDemand Application Service',
	'owner'		=> ['cary.xiao@i-zq.com','li.huang@i-zq.com'],
	'prod_ver'	=> '2.10.5',
	'sources'	=> ['ZQProjs/DODServer','ZQProjs/generic/JMSCppLib'],
	'work_path'	=> "ZQProjs\\DODServer",
	'rc_h_files'	=> ["ZQProjs\\DODServer\\project\\DSA\\ZQResource.h",
	                    "ZQProjs\\DODServer\\project\\DCA\\ZQResource.h",
	                    "ZQProjs\\DODServer\\project\\SRM\\ZQResource.h",
	                    "ZQProjs\\DODServer\\project\\DevKit\\ZQResource.h",],
	'build_cmds'=> [
	                "$MSDEV7CMD /rebuild \"Release\" .\\project\\DSA\\DSA\\DSA.sln",
	                "$MSDEV7CMD /rebuild \"Release\" .\\project\\DCA\\DCA.sln",
	                "$MSDEV7CMD /rebuild \"Release\" .\\project\\SRM\\SRM.sln",
	                 "package.bat"],
	'output_pkg'	=> ["ZQProjs\\DODServer\\DODServer_Setup.zip" ],
);

%SMSVODService = (
	'name'          =>'SMSVODService',
	'desc'          =>'SMSVODService',
	'owner'         =>['shuai.chen@i-zq.com'],
	'prod_ver'      =>'1.0.6',
	'sources'       =>['ZQProjs/Common', 'ZQProjs/SMS/SMSService', 'ZQProjs/SMS/SMSCommon'],
	'work_path'     =>"ZQProjs\\SMS\\SMSService",
	'rc_h_files'    =>['ZQProjs/SMS/SMSService/ZQResource.h'],
	'build_cmds'    =>["$MSDEV6CMD SMSVODService.dsw /MAKE \"SMSVODService - WIN32 Release\" /REBUILD","package.bat"],
	'output_pkg'    => ["ZQProjs\\SMS\\SMSService\\SMSVODService.zip"]
);

%NPVRSMS = (
	'name'          =>'NPVRSMS',
	'desc'          =>'NPVRSMS',
	'owner'         =>['shuai.chen@i-zq.com'],
	'prod_ver'      =>'1.0.8',
	'sources'       =>['ZQProjs/Common', 'ZQProjs/SMS/NPVRSMS', 'ZQProjs/SMS/SMSCommon'],
	'work_path'     =>"ZQProjs\\SMS\\NPVRSMS",
	'rc_h_files'    =>['ZQProjs/SMS/NPVRSMS/ZQResource.h'],
	'build_cmds'    =>["$MSDEV6CMD NPVRSMS.dsw /MAKE \"NPVRSMS - WIN32 Release\" /REBUILD","package.bat"],
	'output_pkg'    => ["ZQProjs\\SMS\\NPVRSMS\\NPVRSMS.zip"]
);

%MessageAgent = (
	'name'          =>'MessageAgent',
	'desc'          =>'MessageAgent',
	'owner'         =>['ken.qian@i-zq.com'],
	'prod_ver'      =>'1.0.1',
	'sources'       =>['ZQProjs/Common','ZQProjs/TianShan','ZQProjs/generic/JMSCppLib'],
	'work_path'     =>"ZQProjs\\TianShan\\MessageAgent",
	'rc_h_files'    =>['ZQProjs/TianShan/MessageAgent/ZQResource.h'],
	'build_cmds'    =>["$MSDEV6CMD TianShanMessageAgent.dsw /MAKE \"TianShanMessageAgent - WIN32 Release\" /REBUILD","package.bat"],
	'output_pkg'    =>["ZQProjs\\TianShan\\MessageAgent\\MessageAgent.zip"],
);

%SMSGateway = (
	'name'          =>'SMSGateway',
	'desc'          =>'SMSGateway',
	'owner'         =>['shuai.chen@i-zq.com'],
	'prod_ver'      =>'1.0.9',
	'sources'       =>['ZQProjs/Common','ZQProjs/SMS/SMSCommon','ZQProjs/SMS/SMSGateway','ZQProjs/SMS/ModemGateway',],
	'work_path'     =>"ZQProjs\\SMS\\SMSGateway",
	'rc_h_files'    =>['ZQProjs/SMS/SMSGateway/ZQResource.h'],
	'build_cmds'    =>["$MSDEV6CMD SMSGateway.dsw /MAKE \"SMSGateway - WIN32 Release\" /REBUILD",
			   "package.bat"],
	'output_pkg'    =>["ZQProjs\\SMS\\SMSGateway\\SMSGateway.zip"],
);

%ModemGateway = (
	'name'          =>'ModemGateway',
	'desc'          =>'ModemGateway',
	'owner'         =>['shuai.chen@i-zq.com'],
	'prod_ver'      =>'1.0.7',
	'sources'       =>['ZQProjs/Common','ZQProjs/SMS/SMSCommon','ZQProjs/SMS/SMSGateway','ZQProjs/SMS/ModemGateway',],
	'work_path'     =>"ZQProjs\\SMS\\ModemGateway",
	'rc_h_files'    =>['ZQProjs/SMS/ModemGateway/ZQResource.h'],
	'build_cmds'    =>["$MSDEV6CMD ModemGateway.dsw /MAKE \"SMSVODService - WIN32 Release\" /REBUILD",
			   "package.bat"],
	'output_pkg'    =>["ZQProjs\\SMS\\ModemGateway\\ModemGateway.zip"],
);

%DataOnDemand = (
	'name'		=> 'DataOnDemand',
	'desc'		=> 'DataOnDemand Application Service',
	'owner'		=> ['cary.xiao@i-zq.com','li.huang@i-zq.com'],
	'prod_ver'	=> '3.0.0',
	'sources'	=> ['ZQProjs/DataOnDemand','ZQProjs/Common','ZQProjs/TianShan','ZQProjs/generic/JMSCppLib'],
	'work_path'	=> "ZQProjs\\DataOnDemand",
	'rc_h_files'	=> ["ZQProjs\\DataOnDemand\\Phase1\\DODApp\\ZQResource.h",
	                    "ZQProjs\\DataOnDemand\\Phase1\\DODSTREAMER\\Project\\DSA\\ZQResource.h",
	                    "ZQProjs\\DataOnDemand\\Phase1\\DODApp\\JMSDispatch\\ZQResource.h",
	                    ],
	'build_cmds'=> [
	                "$MSDEV7CMD /rebuild \"Release\" .\\Phase1\\DODSTREAMER\\project\\DSA\\DSA\\DSA.sln",
	                "$MSDEV6CMD .\\Phase1\\DODApp\\DODApp.dsw /MAKE \"DODApp - Win32 Release\" /REBUILD",
	                 "DataOnDemandPkg.bat"],
	'output_pkg'	=> ["ZQProjs\\DataOnDemand\\DataOnDemand_Setup.zip" ],
);

%TianShanDataOnDemand = (
	'name'		=> 'TianShanDataOnDemand',
	'desc'		=> 'DataOnDemand Application Service',
	'owner'		=> ['Ken.Qian@i-zq.com','cary.xiao@i-zq.com','li.huang@i-zq.com'],
	'prod_ver'	=> '3.1.1',
	'sources'	=> ['ZQProjs/DataOnDemand','ZQProjs/Common','ZQProjs/TianShan','ZQProjs/generic/JMSCppLib','ZQProjs/generic/ContentProcess'],
	'work_path'	=> "ZQProjs\\DataOnDemand",
	'rc_h_files'	=> ["ZQProjs\\DataOnDemand\\Phase2\\DODApp\\ZQResource.h",
	                    "ZQProjs\\DataOnDemand\\Phase2\\DataStream\\ZQResource.h",
	                    "ZQProjs\\DataOnDemand\\Phase2\\DODApp\\JMSDispatch\\ZQResource.h",
	                    "ZQProjs\\DataOnDemand\\Phase2\\DODContentStore\\ZQResource.h",
	                    "ZQProjs\\DataOnDemand\\Phase2\\DodPho\\ZQResource.h",
	                    "ZQProjs\\TianShan\\Shell\\\ZQShell\\ZQResource.h",
	                    ],
	'build_cmds'=> [
			"$MSDEV6CMD .\\DataOnDemand.dsw /MAKE \"buildall - Win32 Release\" /BUILD",
	                "DataOnDemand.bat"],
	'output_pkg'	=> ["ZQProjs\\DataOnDemand\\DataOnDemand_Setup.zip" ],
);

%TianShan = (
	'name'		=> 'TianShan',
	'desc'		=> 'TianShan Components',
	#'dependence'    => ['TianShan_x64'],
	'xml_path'	=> ['ZQProjs\\TianShan\\etc'],
        'environment'           => {
		                     'ITVSDKPATH'       => 'D:\\SDK\\SeaChangeKits\\ITVSDK-v3.2.INTERNAL',
        	                    # 'VSTRMKITPATH'        => 'D:\\SDK\\SeaChangeKits\\VstrmKitV5.4.3',           #For NGOD
        	                     #'VSTRMKITPATH'        => 'D:\\SDK\\SeaChangeKits\\VstrmKitV6.0.2.2',
        	                     #'VSTRMKITPATH'        => 'D:\\SDK\\SeaChangeKits\\VstrmKit6.1.0-RC19',
        	                     #'VSTRMKITPATH'        => 'D:\\VstrmKitV6.3.0-20100916-18-04-42',
        	                     #'VSTRMKITPATH'        => 'D:\\VstrmKitV6.3.0-20110128-09-09-33',
        	                     'VSTRMKITPATH'        => 'D:\\VstrmKitV6.3.0-BL11',
        	                     'WPCAPSDKPATH'	 => 'D:\\SDK\\3rdPartyKits\\WpdPack_4_1_beta5', #For RTICPNode
        	                     'RTFLIBSDKPATH'      => 'D:\\SDK\\SeaChangeKits\\CTFLib_1.0.0_2010.10.01.65',
        	                     #'RTFLIBSDKPATH'      => 'D:\\SDK\\SeaChangeKits\\RTFLib_SDK_1.6',
        	                     'OPENSSLPATH'      => 'D:\\SDK\\3rdPartyKits\\openssl',
        	                     'ICE_ROOT'		=> 'D:\\SDK\\3rdPartyKits\\Ice-3.2.1-VC80-x86',
        	                     'STLPORT_ROOT'	=> 'D:\\SDK\\3rdPartyKits\\Ice-3.2.1-VC80-x86\\include\\stlport',
        	                     #'ICE_ROOT'		=> 'D:\\SDK\\3rdPartyKits\\Ice-3.3.0-VC80',
        	                     #'STLPORT_ROOT'	=> 'D:\\SDK\\3rdPartyKits\\Ice-3.3.0-VC80\\include\\stlport',
        	                     '3RDPARTYKITS_PATH' => 'D:\\SDK\\3rdPartyKits',
        	                     'ExpatPath'         => 'D:\\SDK\\3rdPartyKits\\expat',
        	                     'RegExppKit'        => 'D:\\SDK\\3rdPartyKits\\regexpp1331',
        	                     'ANT_HOME'          => 'D:\\SDK\\3rdPartyKits\\apache-ant-1.6.5',
        	                     'SNMP_PLUS_ROOT'    => 'D:\\SDK\\3rdPartyKits\\SNMP_3.2.24',
        	                     'GSOAPPATH'	=>  'D:\\SDK\\3rdPartyKits\\gsoap-2.7.10\\gsoap',
        	                  }, 
	'owner'		=> ['hui.shao@i-zq.com','ken.qian@i-zq.com','jie.zhang@i-zq.com'],
	'prod_ver'	=> '1.18.0',
	'sources'	=> ['ZQProjs/Common','ZQProjs/TianShan','ZQProjs/generic/JndiClient','ZQProjs/generic/JMSCppLib','ZQProjs/Generic/COLORBARContainer','ZQProjs/Generic/ReadDB','ZQProjs/Generic/writeDB','ZQProjs/Generic/ContentProcess','ZQProjs/Generic/zqsnmp','ZQProjs/Generic/TsHammer'],
	'work_path'	=> "ZQProjs\\TianShan",
	'rc_h_files'	=> [
			    "ZQProjs/Common/ZQCommVer.h",
	                    "ZQProjs/TianShan/ChannelOnDemand/PauseTVVersion.h",
	                    "ZQProjs/TianShan/BroadcastChannel/ZQResource.h",
	                    "ZQProjs/TianShan/CDNLib/CRM_C2Locator/ZQResource.h",
	                    "ZQProjs/TianShan/CDNLib/Management/c2loc_web/ZQResource.h",
	                    "ZQProjs/TianShan/StreamService/StreamSmith/ZQResource.h",
	                    "ZQProjs/TianShan/StreamSmith/Service/ZQResource.h",
	                    "ZQProjs/TianShan/StreamSmith/Service/RtspProxyResource.h",
	                    "ZQProjs/TianShan/ContentStore/MediaClusterCS/ZQResource.h",
	                    "ZQProjs/TianShan/ContentStore/ContentClient/ZQResource.h",
	                    "ZQProjs/TianShan/ContentStore/BaseCS/ZQResource.h",
	                    "ZQProjs/TianShan/StreamSmith/Modules/SsmTianShanS1_Now/ZQResource.h",
	                    "ZQProjs/TianShan/StreamSmith/Modules/ssm_tianshan/ZQResource.h",
	                    "ZQProjs/TianShan/StreamSmith/Modules/ssm_richurl/ZQResource.h",
	                    "ZQProjs/TianShan/OpenVBO/ssm_OpenVBO/ZQResource.h",
	                    "ZQProjs/TianShan/ContentStore/MediaClusterCS/ZQResource.h",
	                    "ZQProjs/TianShan/EventRE/ZQResource.h",
	                    "ZQProjs/TianShan/Weiwoo/Service/ZQResource.h",
	                    "ZQProjs/TianShan/AccreditedPath/AdminControl/ZQResource.h",
	                    "ZQProjs/TianShan/AccreditedPath/ZQResource.h",
	                    "ZQProjs/TianShan/AccreditedPath/TestAdminCtl/ZQResource.h",
	                    "ZQProjs/TianShan/AccreditedPath/pho/pho_SeaChange/ZQResource.h",
	                    #"ZQProjs/TianShan/application/MOD/ZQResource.h",
	                    "ZQProjs/TianShan/application/MOD2/ZQResource.h",
	                    "ZQProjs/TianShan/application/MODPlugIn/ZQResource.h",
	                    "ZQProjs/TianShan/Shell/ZQShell/ZQResource.h",
	                    "ZQProjs/TianShan/Sentry/Service/ZQResource.h",
	                    "ZQProjs/TianShan/SiteAdmin/ZQResource.h",
	                    "ZQProjs/TianShan/ComcastNGOD/ssmNGODr2c1(Improved)/ZQResource.h",
	                    "ZQProjs/TianShan/ComcastNGOD/pho_NGOD/pho_NGOD/ZQResource.h",
	                    "ZQProjs/TianShan/ComcastNGOD/ssm_ngod/ZQResource.h",
	                    "ZQProjs/TianShan/ComcastNGOD/ssm_ngod2_logPlugin/ZQResource.h",
	                    "ZQProjs/TianShan/ComcastNGOD/ssm_ngod2/ngod2view/ZQResource.h",
	                    "ZQProjs/TianShan/ComcastNGOD/NSS/ZQResource.h",
	                    "ZQProjs/TianShan/ComcastNGOD/CRM_A3Message/ZQResource.h",
	                    "ZQProjs/TianShan/ComcastNGOD/CRM_A3Server/A3_Web/ZQResource.h",
	                    "ZQProjs/TianShan/ComcastNGOD/SNMP/ZQResource.h",
	                    "ZQProjs/TianShan/TSHammer/ZQResource.h",
	                    "ZQProjs/TianShan/CRG/HttpCRG/ZQResource.h",
	                    "ZQProjs/TianShan/VirtualStreamingService/NGOD/ZQResource.h",
	                    "ZQProjs/TianShan/Sentry/Plug_EventSender/snmp/ZQResource.h",
	                    "ZQProjs/TianShan/Sentry/Plug_EventSender/ZQResource.h",
	                    "ZQProjs/TianShan/Sentry/CodMan_web/ZQResource.h",
	                    "ZQProjs/TianShan/Sentry/AdminCtrl_web/ZQResource.h",
	                    "ZQProjs/TianShan/Sentry/CPCMan_web/ZQResource.h",
	                    "ZQProjs/TianShan/Sentry/CPEMan_web/ZQResource.h",
	                    "ZQProjs/TianShan/Sentry/MsgSender/MsgSender/ZQResource.h",
	                    "ZQProjs/TianShan/Sentry/BcastChMan_web/ZQResource.h",
	                    "ZQProjs/TianShan/Sentry/ErmMan_web/ZQResource.h",
	                    "ZQProjs/TianShan/Sentry/Module/SysLogSender/ZQResource.h",
	                    "ZQProjs/TianShan/Sentry/ClibMan_web/ZQResource.h",
	                    "ZQProjs/TianShan/Sentry/ZQSNMPExtAgent/ZQResource.h",
	                    "ZQProjs/TianShan/Shell/ZQCfgPkg/ZQResource.h",
	                    "ZQProjs/TianShan/Shell/ZQSNMPManPkg/ZQResource.h",
	                    "ZQProjs/TianShan/AccreditedPath/admin/ZQResource.h",
	                    "ZQProjs/TianShan/SiteAdminSvc/admin/ZQResource.h",
	                    "ZQProjs/TianShan/CPE/ZQResource.h",
	                    "ZQProjs/TianShan/CPE/CPH_RDS/ZQResource.h",
	                    "ZQProjs/TianShan/CPE/CPH_RTFRDS/ZQResource.h",
	                    "ZQProjs/TianShan/CPE/CPH_NASCOPY/ZQResource.h",
	                    "ZQProjs/TianShan/CPE/CPH_RTI/ZQResource.h",
	                    "ZQProjs/TianShan/CPE/CPH_RTINAS/ZQResource.h",
	                    "ZQProjs/TianShan/CPE/CPH_nPVR/ZQResource.h",
	                    "ZQProjs/TianShan/CPE/CPH_C2Propagation/ZQResource.h",
	                    "ZQProjs/TianShan/EdgeRM/service/ZQResource.h",
	                    "ZQProjs/TianShan/EdgeRM/Pho_ERM/ZQResource.h",
	                    "ZQProjs/TianShan/VirtualStreamingService/Pho/ZQResource.h",
	                    "ZQProjs/TianShan/AccreditedPath/pho/pho_SeaChange/ZQResource.h",
	                    "ZQProjs/TianShan/EdgeRM/EdgeRMClient/ZQResource.h",
	                    "ZQProjs/TianShan/EventGateway/service/ZQResource.h",
	                    "ZQProjs/TianShan/EventGateway/Modules/EGH_SOAP/EGH_SOAP_CME/ZQResource.h",
	                    "ZQProjs/TianShan/EventGateway/Modules/EGH_JMS/ZQResource.h",
	                    "ZQProjs/TianShan/EventGateway/Modules/EGH_SnmpTrap/ZQResource.h",
	                    "ZQProjs/TianShan/EventChannel/service/ZQResource.h",
	                    "ZQProjs/TianShan/Sentry/Module/MDB_web/ZQResource.h",
	                    "ZQProjs/TianShan/Sentry/Module/Storage_web/ZQResource.h",
	                    "ZQProjs/TianShan/ICE/TianShanIce.ICE",
	                    "ZQProjs/TianShan/ICE/ZQResource.h",
	                    "ZQProjs/TianShan/DataOnDemand/Phase2/DODApp/ZQResource.h",
	                    "ZQProjs/TianShan/DataOnDemand/Phase2/DataStream/ZQResource.h",
	                    "ZQProjs/TianShan/DataOnDemand/Phase2/DODApp/JMSDispatch/ZQResource.h",
	                    "ZQProjs/TianShan/DataOnDemand/Phase2/DODContentStore/ZQResource.h",
	                    "ZQProjs/TianShan/DataOnDemand/Phase2/DodPho/ZQResource.h",
	                    "ZQProjs/TianShan/DataOnDemand/Phase2/TsDump/ZQResource.h",
	                    "ZQProjs/TianShan/ContentLib/ZQResource.h",
	                    "ZQProjs/generic/JndiClient/ZQResource.h",
	                    "ZQProjs/TianShan/DummySS/ZQResource.h",
	                    "ZQProjs/TianShan/Sentry/TSClient/ZQResource.h",
	                    "ZQProjs/TianShan/Sentry/webLayout/ZQResource.h",
	                    "ZQProjs/TianShan/Shell/zqshellmsgs/ZQResource.h",
	                    "ZQProjs/TianShan/Sentry/LogPage/ZQResource.h",
	                    "ZQProjs/Generic/zqsnmp/ZQResource.h",
	                    "ZQProjs/TianShan/ChannelOnDemand/Tests/ChPub/ZQResource.h",
	                    "ZQProjs/TianShan/StreamService/NSS/ZQResource.h",
	                    "ZQProjs/TianShan/OpenVBO/OpenVBO_web/ZQResource.h",
	                    "ZQProjs/TianShan/StreamSmith/StreamClient/ZQResource.h",
	                    "ZQProjs/TianShan/GB-SAC/ssm_GBss/ZQResource.h",
	                    "ZQProjs/TianShan/GB-SAC/GBvss/ZQResource.h",
	                    "ZQProjs/TianShan/GB-SAC/ssm_GBstb/ZQResource.h",
	                    ],
	'build_cmds'=> [
		       	"if exist CPE\\CPH_RDS\\RTFLib.h del CPE\\CPH_RDS\\RTFLib.h",
				"set VSTRMKITPATH=D:\\VstrmKitV6.3.0-BL11\n$MSDEV8CMD /ReBuild  \"Release|x64\" /project Buildall_x64 /out TianShan_x64.log TianShanBuild.sln",
	                "set VSTRMKITPATH=D:\\VstrmKitV6.3.0-BL11\nTianShanPKG_64.bat",
	                "if exist CPE\\CPH_RDS\\RTFLib.h del CPE\\CPH_RDS\\RTFLib.h",
	                "del /s /q CPE\\*.obj",
					"$MSDEV8CMD /Rebuild  \"Release|win32\" /project Buildall /out TianShan_x86.log TianShanBuild.sln",
	                "Components4CTF.V1.0.bat",
	                "$MSDEV8CMD /Rebuild  \"Java|win32\" /project TianShanIce TianShanBuild.sln",
	                #"$MSDEV8CMD /Rebuild  \"Java|win32\" /project JavaClient TianShanBuild.sln",
	                #".\\ChannelOnDemand\\JavaClient\\PkJavaClient.bat",
                        ".\\SDK\\packsdk.bat",
	                "TianShanPKG.bat",
	                ],
	'output_pkg'	=> ["ZQProjs\\TianShan\\TianShan_setup.zip","ZQProjs\\TianShan\\TianShanSymbols.zip" ],
);

%ServerLoad = (
	'name'		=> 'ServerLoad',
	'desc'		=> 'ZQ ServerLoad',
        'environment'           => {
		                     'ITVSDKPATH'       => 'D:\\sdk\\SeaChangeKits\\ITVSDK-v3.2.INTERNAL',
        	                      'VSTRMKITPATH'        => 'D:\\SDK\\SeaChangeKits\\VstrmKitV5.3.10',      #For RDA
        	                      'VSTRMPATH'        => 'D:\\SDK\\SeaChangeKits\\VstrmKitV5.3.10\\SDK',         #For RDA

        	                     'OPENSSLPATH'      => 'D:\\SDK\\3rdPartyKits\\openssl',
        	                     'ICE_ROOT'		=> 'D:\\SDK\\3rdPartyKits\\Ice-3.2.1-VC80-x86',
        	                     'STLPORT_ROOT'	=> 'D:\\SDK\\3rdPartyKits\\Ice-3.2.1-VC80-x86\\include\\stlport',
        	                     '3RDPARTYKITS_PATH' => 'D:\\SDK\\3rdPartyKits',
        	                     'ExpatPath'         => 'D:\\SDK\\3rdPartyKits\\expat',
        	                     'ANT_HOME'          => 'D:\\SDK\\3rdPartyKits\\apache-ant-1.6.5',
        	                }, 
	'owner'		=> ['Guan.han@i-zq.com'],
	'prod_ver'	=> '1.1.0',
	'sources'	=> ['ZQProjs/Common','ZQProjs/TianShan','ZQProjs/generic/ServerLoad',],
	'work_path'	=> "ZQProjs\\Generic\\ServerLoad",
	'rc_h_files'	=> [
	                    "ZQProjs/Generic/ServerLoad/ZQResource.h",
	                    "ZQProjs/TianShan/Shell/zqshellmsgs/ZQResource.h",
	                    "ZQProjs/TianShan/Shell/ZQShell/ZQResource.h",
	                    "ZQProjs/TianShan/Shell/ZQCfgPkg/ZQResource.h",
	                    ],
	'build_cmds'=> [
					"$MSDEV8CMD /Rebuild  \"Release|win32\" /project ServerLoad /out serverload.log ServerLoad.sln",
	                #"$MSDEV6CMD .\\ServerLoad.dsw /MAKE \"ServerLoad - Win32 Release\" /BUILD",
	                "package.bat",
	                ],
	'output_pkg'	=> ["ZQProjs\\Generic\\ServerLoad\\ServerLoad_setup.zip" ]
);




%SNMPSvcs = (
	'name'		=> 'SNMPSvcs',
	'desc'		=> 'ZQ SNMPSvcs Service',
	'owner'		=> 'Jason.zhang@i-zq.com',
	'environment'           => {
		                     'ITVSDKPATH'       => 'D:\\SDK\\SeaChangeKits\\ITVSDK-v3.2.INTERNAL',
		                     'SNMP_PLUS_ROOT'   =>'D:\\SDK\\SeaChangeKits\\SNMP_3.2.24',
		                     'RegExppKit'        => 'D:\\SDK\\3rdPartyKits\\regexpp3',
		                },
	'prod_ver'	=> '1.0.1',
	'sources'	=> ['ZQProjs/Common','ZQProjs/Telewest/SNMPSvcs'],
	'work_path'	=> "ZQProjs\\Telewest\\SNMPSvcs",
	'rc_h_files'	=> ['ZQProjs/Telewest/SNMPSvcs/SNMPService/ZQResource.h'],
	'build_cmds'=> [
	"$MSDEV6CMD .\\SNMPService\\SNMPService.dsw /MAKE \"SNMPService - Win32 Release\" /REBUILD",
	"package.bat"],
	'output_pkg'	=> ["ZQProjs\\telewest\\SNMPSvcs\\SNMPSvcs.zip" ],
);

%ContentLink = (
	'name'		=> 'ContentLink',
	'desc'		=> 'ZQ ContentDistribution Service',
	'owner'		=> 'li.huang@i-zq.com,xia.chen@i-zq.com,haoyuan.lu@i-zq.com',
	'environment'           => {
		                     'ACE_ROOT'       => 'D:\\SDK\\3rdPartyKits\\ACE_5.3a_p15',
		                     'WMThomsonSDKPath'       => 'D:\\WatermarkingSDK\\Thomson',
		                     'ICE_ROOT'		=> 'D:\\SDK\\3rdPartyKits\\Ice-3.2.1-VC80-x86',
        	                     'STLPORT_ROOT'	=> 'D:\\SDK\\3rdPartyKits\\Ice-3.2.1-VC80-x86\\include\\stlport',
        	                     'ExpatPath'         => 'D:\\SDK\\3rdPartyKits\\expat',
		                     
		                },
	'prod_ver'	=> '1.0.2',
	'sources'	=> ['ZQProjs/Common','ZQProjs/TianShan/common','ZQProjs/TianShan/Shell','ZQProjs/TianShan/Include','ZQProjs/ContentDistribution','ZQProjs/generic/JMSCppLib'],
	'work_path'	=> "ZQProjs\\ContentDistribution",
	'rc_h_files'	=> ['ZQProjs/ContentDistribution/Source/TransEngine/ZQResource.h',
			    'ZQProjs/ContentDistribution/Source/TransMissionMgr/ZQResource.h',
			    'ZQProjs/ContentDistribution/Source/TaskScheduler/ZQResource.h',
			    'ZQProjs/ContentDistribution/Source/TransMSchedule/ZQResource.h',	
			    'ZQProjs/ContentDistribution/Source/ReceiverManager/ZQResource.h',	
			    'ZQProjs/ContentDistribution/Source/ProvisionAgent/ZQResource.h',	
			    'ZQProjs/ContentDistribution/Source/ContentPitcher/ZQResource.h',
			    'ZQProjs/ContentDistribution/Source/ProvisionAMS/ZQResource.h',
			    'ZQProjs/ContentDistribution/Source/WaterMarking/ZQResource.h',
			    'ZQProjs/ContentDistribution/Source/EncryptDll/ZQResource.h',
			    'ZQProjs/TianShan/Shell/ZQShell/ZQResource.h',
			    'ZQProjs/Common/ZQCommVer.h',
			   ],
	'build_cmds'=> [
	"$MSDEV8CMD /Rebuild  \"Release|win32\" /project BuildAll /out Buildall.log .\\source\\BuildAll.sln",
	"CDSPKG.bat"],
	'output_pkg'	=> ["ZQProjs\\ContentDistribution\\CDS_Setup.zip" ],
);

%CLink = (
	'name'		=> 'CLink',
	'desc'		=> 'ZQ ContentDistribution Service',
	'owner'		=> 'li.huang@i-zq.com,xia.chen@i-zq.com,haoyuan.lu@i-zq.com',
	'xml_path'	=> ['ZQProjs\\ContentDistribution\\source\\etc'],
	'environment'           => {
		                     'ACE_ROOT'       => 'D:\\SDK\\3rdPartyKits\\ACE_5.3a_p15',
		                     'WMThomsonSDKPath'       => 'D:\\WatermarkingSDK\\Thomson',
		                     'ICE_ROOT'		=> 'D:\\SDK\\3rdPartyKits\\Ice-3.2.1-VC80-x86',
        	                     'STLPORT_ROOT'	=> 'D:\\SDK\\3rdPartyKits\\Ice-3.2.1-VC80-x86\\include\\stlport',
        	                     'ExpatPath'         => 'D:\\SDK\\3rdPartyKits\\expat',
        	                     'RegExppKit'        => 'D:\\sdk\\3rdPartyKits\\regexpp1331',
		                     
		                },
	'prod_ver'	=> '1.0.3',
	'sources'	=> ['ZQProjs/Common','ZQProjs/TianShan/common','ZQProjs/TianShan/Shell','ZQProjs/TianShan/Include','ZQProjs/TianShan/Ice','ZQProjs/TianShan/EventChannel','ZQProjs/TianShan/EventGateway','ZQProjs/ContentDistribution','ZQProjs/generic/JMSCppLib'],
	'work_path'	=> "ZQProjs\\ContentDistribution",
	'rc_h_files'	=> ['ZQProjs/ContentDistribution/Source/TransEngine/ZQResource.h',
			    'ZQProjs/ContentDistribution/Source/TransMissionMgr/ZQResource.h',
			    'ZQProjs/ContentDistribution/Source/TaskScheduler/ZQResource.h',
			    'ZQProjs/ContentDistribution/Source/TransMSchedule/ZQResource.h',	
			    'ZQProjs/ContentDistribution/Source/ReceiverManager/ZQResource.h',	
			    'ZQProjs/ContentDistribution/Source/ProvisionAgent/ZQResource.h',	
			    'ZQProjs/ContentDistribution/Source/ContentPitcher/ZQResource.h',
			    'ZQProjs/ContentDistribution/Source/ProvisionAMS/ZQResource.h',
			    'ZQProjs/ContentDistribution/Source/WaterMarking/ZQResource.h',
			    'ZQProjs/ContentDistribution/Source/EncryptDll/ZQResource.h',
			    'ZQProjs/TianShan/Shell/ZQShell/ZQResource.h',
			    "ZQProjs/TianShan/EventGateway/service/ZQResource.h",
			    "ZQProjs/TianShan/EventChannel/service/ZQResource.h",
			    'ZQProjs/Common/ZQCommVer.h',
			   ],
	'build_cmds'=> [
	"$MSDEV8CMD /Rebuild  \"Release|win32\" /project BuildAll /out Buildall.log .\\source\\BuildAll.sln",
	"CDSPKG.bat"],
	'output_pkg'	=> ["ZQProjs\\ContentDistribution\\CDS_Setup.zip" ],
);

@NIGHLY_PROJLIST = (
#	ProjTemplate,
	McastFwd,
	ISAComponents,
	DBSync,
	DBSync_forTelewest,
	DBSync_withoutPlugin,
	SrvLoad,
	FtpMover,
	NSSync,
	PlaylistAS,
#	ScheduledTV,
	MODAuthorization,
	NoiseSim,
	JMSCpp,
	IngestSim,
	ZQSpot,
	TianShanSDK,
	WMSService,
	RtspProxy,
	ColorBar,
    DODServer,
    SMSVODService,
    NPVRSMS,
    MessageAgent,
    SMSGateway,
    ModemGateway,
    DataOnDemand,
    TianShan,
    SNMPSvcs,
    ServerLoad,
    ContentLink,
    CLink,
);

@ALL_PROJS =(
	ProjTemplate,
	McastFwd,
	ISAComponents,
	ISAComponents_IngestCard,
	ISAComponents_IngestCard_SSP23,
	DBSync,
	DBSync_forTelewest,
	DBSync_withoutPlugin,
	SrvLoad,
	SrvLoad_forTelewest,
	FtpMover,
	NSSync,
	NSSync_forVirginMedia,
	PlaylistAS,
	ScheduledTV,
	MODAuthorization,
	NoiseSim,
	JMSCpp,
	IngestSim,
	nPVR,
	ZQSpot,
	TianShanSDK,
	WMSService,
	ColorBar,
    DODServer,
    SMSVODService,
    NPVRSMS,
    MessageAgent,
    ColorBarContainer,
    SMSGateway,
    ModemGateway,
    DataOnDemand,
    TianShan,
    TianShanDataOnDemand,
    SNMPSvcs,
    TianShan_Internal,
    ServerLoad,
    ContentLink,
    TianShan_x64,
    CLink,
);

