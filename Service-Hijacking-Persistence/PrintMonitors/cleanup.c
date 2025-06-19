#include <windows.h>
#include <stdio.h>

int main() {
    const char* dllPath = "C:\\Windows\\System32\\spool\\prtprocs\\x64\\servDLL.dll";
    const char* regPath = "SYSTEM\\CurrentControlSet\\Control\\Print\\Environments\\Windows x64\\Print Processors\\servDLL";
    const char* logPath = "C:\\Users\\Public\\dll_log.txt";


    printf("[*] Stopping Print Spooler service...\n");
    if (system("net stop spooler") == 0) {
        printf("[+] Print Spooler stopped successfully.\n");
    } else {
        printf("[-] Failed to stop Print Spooler. Continuing anyway.\n");
    }

    if (DeleteFileA(dllPath)) {
        printf("[+] DLL deleted from spool folder.\n");
    } else {
        printf("[-] Failed to delete DLL. Error: %lu\n", GetLastError());
    }

    if (DeleteFileA(logPath)) {
        printf("[+] Delete C:\\Users\\Public\\dll_log.txt dll_log folder.\n");
    } else {
        printf("[-] Failed to delete the log folder. Error: %lu\n", GetLastError());
    }

    LONG result = RegDeleteKeyA(HKEY_LOCAL_MACHINE, regPath);
    if (result == ERROR_SUCCESS) {
        printf("[+] Registry key deleted successfully.\n");
    } else {
        printf("[-] Failed to delete registry key. Error: %ld\n", result);
    }


    printf("[*] Starting Print Spooler service...\n");
    if (system("net start spooler") == 0) {
        printf("[+] Print Spooler started successfully.\n");
    } else {
        printf("[-] Failed to start Print Spooler.\n");
    }

    return 0;
}
