@echo off
setlocal

REM Set path to vcvars64 if needed
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

cl /LD /FeMyTlsSSP.dll exploit.cpp MyTlsSSP.def /link /INCREMENTAL:NO /NODEFAULTLIB /ENTRY:DllMain /SUBSYSTEM:WINDOWS

endlocal
