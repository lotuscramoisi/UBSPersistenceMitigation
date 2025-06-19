#include <windows.h>
#include <stdio.h>

int main() {
    system("net stop w32time >nul 2>&1");

    LONG result = RegDeleteKeyA(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\W32Time\\TimeProviders\\ServDLL");
    if (result == ERROR_SUCCESS) {
        printf("[+] Registry key deleted successfully.\n");
    } else {
        printf("[-] Failed to delete registry key: %ld\n", result);
    }

    if (DeleteFileA("C:\\Users\\Public\\servDLL.dll")) {
        printf("[+] DLL deleted successfully.\n");
    } else {
        printf("[-] Failed to delete DLL: %ld\n", GetLastError());
    }

    system("net start w32time >nul 2>&1");

    return 0;
}
