use vars qw(@NSSync @struct);
my @struct=(
         ["key","description","name","default","type"]
        );

@NSSync = (
                ["SOFTWARE\\SeaChange\\ITV\\CurrentVersion\\Services\\NSSync","Instance","Instance","1","D"],
                ["SOFTWARE\\SeaChange\\ITV\\CurrentVersion\\Services\\NSSync","KeepAliveIntervals","KeepAliveIntervals","2000","D"],
                ["SOFTWARE\\SeaChange\\ITV\\CurrentVersion\\Services\\NSSync","LogBufferSize","LogBufferSize","4096","D"],
                ["SOFTWARE\\SeaChange\\ITV\\CurrentVersion\\Services\\NSSync","LogFileName","LogFileName","%LOGDIR%\\NSSync.log","S"],
                ["SOFTWARE\\SeaChange\\ITV\\CurrentVersion\\Services\\NSSync","LogFileSize","LogFileSize","40960000","D"],
                ["SOFTWARE\\SeaChange\\ITV\\CurrentVersion\\Services\\NSSync","LogFileTimeOut","LogFileTimeOut","2000","D"],
                ["SOFTWARE\\SeaChange\\ITV\\CurrentVersion\\Services\\NSSync","LogLevel","LogLevel","7","D"],
                ["SOFTWARE\\SeaChange\\ITV\\CurrentVersion\\Services\\NSSync","ShutdownWaitTime","ShutdownWaitTime","10000","D"],
                ["SOFTWARE\\SeaChange\\ITV\\CurrentVersion\\Services\\NSSync","SuperviseInterval","SuperviseInterval","60","D"],
                ["SOFTWARE\\SeaChange\\ITV\\CurrentVersion\\Services\\NSSync","DB connection/operation timeout in seconds","IZQDBTimeout","30","D"],
                ["SOFTWARE\\SeaChange\\ITV\\CurrentVersion\\Services\\NSSync","DSN name for NSSync to connect local database","IZQDBDSN","LAM","S"],
                ["SOFTWARE\\SeaChange\\ITV\\CurrentVersion\\Services\\NSSync","Username for NSSync to access local database","IZQDBUserName","am","S"],
                ["SOFTWARE\\SeaChange\\ITV\\CurrentVersion\\Services\\NSSync","Password for NSSync to access local database","IZQDBPassword","am","S"],
                ["SOFTWARE\\SeaChange\\ITV\\CurrentVersion\\Services\\NSSync","Local database name for NSSync to access","IZQDBName","am","S"],
                ["SOFTWARE\\SeaChange\\ITV\\CurrentVersion\\Services\\NSSync","Local database type","IZQDBType","SQL Server","S"],
                ["SOFTWARE\\SeaChange\\ITV\\CurrentVersion\\Services\\NSSync","The time interval in millisecond for NSSync to retrieve data from local database","TeaTime","200","D"],
                ["SOFTWARE\\SeaChange\\ITV\\CurrentVersion\\Services\\NSSync","Region ID for current NSSync instance","RegionID","TWT","S"],
                ["SOFTWARE\\SeaChange\\ITV\\CurrentVersion\\Services\\NSSync","A ceiling number, once the workqueue records reach the celling, NSSync will do rebuild instead of process one by one","MaxWQOptRebuild","100","D"],
                ["SOFTWARE\\SeaChange\\ITV\\CurrentVersion\\Services\\NSSync_shell","ImagePath","ImagePath","%EXEDIR%\\NSSync.exe","S"],
                ["SOFTWARE\\SeaChange\\Management\\CurrentVersion\\Services\\NSSync","Management Port Number for NSSync","MgmtPortNumber","0x00001B18","D"],
                ["SOFTWARE\\SeaChange\\Management\\CurrentVersion\\Services\\NSSync_shell","Management Port Number for NSSync_shell","MgmtPortNumber","0x00001B19","D"],
                ["SYSTEM\\CurrentControlSet\\Services\\NSSync","Product Name","ProductName","ITV","S"],
                ["SYSTEM\\CurrentControlSet\\Services\\NSSync","ImagePath of SrvShell","ImagePath","%EXEDIR%\\SrvShell.exe","S"],
		["SYSTEM\\CurrentControlSet\\Services\\Eventlog\\Application\\NSSync","The Event Message File of NSSync","EventMessageFile","%EXEDIR%\\ItvMessages.dll","S"],
		["SYSTEM\\CurrentControlSet\\Services\\Eventlog\\Application\\NSSync","The type of Supported of NSSync","Typessupported","7","D"],
                ["SYSTEM\\CurrentControlSet\\Services\\Eventlog\\Application\\NSSync_shell","The Event Message File Of NSSync_shell","EventMessageFile","%EXEDIR%\\ShellMsgs.dll","S"],
                ["SYSTEM\\CurrentControlSet\\Services\\Eventlog\\Application\\NSSync_shell","The type of Supported Of NSSync_shell","Typessupported","7","D"],
                );