setlocal

set SSCMD="C:\Program Files\Microsoft Visual Studio"\Common\VSS\win32\SS.EXE
set SSDIR=\\hawkeye\vss

d:
cd \programs
%SSCMD% GET "-Ybuild,nightly" $/ZQProjs/build/* -R -GWR -i-

call ZQAutoBuild.bat --nightly

endlocal

