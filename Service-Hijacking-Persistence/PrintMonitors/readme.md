The build DLL has to be placed under this folder that can be found using this command: 
Get-ChildItem "C:\Windows\System32\spool\prtprocs" -Recurse It may give something like this: C:\Windows\System32\spool\prtprocs\x64

In order to restart the system: 
net stop spooler
net start spooler