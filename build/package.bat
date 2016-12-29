setlocal
set PATH=%PATH%;%ZQPROJSPATH%\build\utils
if .%PACKCMD%.==.. set PACKCMD=%ZQPROJSPATH%\build\utils\zip.exe

if exist fileinfo.zip del fileinfo.zip

cd fileinfo

..\utils\zip.exe -r ..\fileinfo.zip .

cd ..
rem rd /s/q fileinfo

endlocal