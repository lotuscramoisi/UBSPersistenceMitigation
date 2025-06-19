https://github.com/oxfemale/LogonCredentialsSteal/tree/master/lsass_lib

Have to be run as administrator.

Create a key under: SYSTEM\\CurrentControlSet\\Services\\NTDS

Will use the file from: C:\vagrant\persistence-pocs\Persistence\Registry-Based-Persistence\LSAASDriver\lsass_lib.dll


Dump any logon credentials to c:\temp\credentials.txt
