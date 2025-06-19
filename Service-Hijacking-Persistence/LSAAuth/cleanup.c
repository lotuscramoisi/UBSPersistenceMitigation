#include <windows.h>
#include <stdio.h>
#include <string.h>

int main() {
    const char* dllPath = "C:\\Windows\\System32\\package.dll";
    
    if (DeleteFileA(dllPath)) {
        printf("[+] Deleted DLL: %s\n", dllPath);
    } else {
        DWORD err = GetLastError();
        if (err == ERROR_FILE_NOT_FOUND) {
            printf("[*] DLL already deleted or missing.\n");
        } else {
            printf("[-] Failed to delete DLL. Error: %lu\n", err);
        }
    }

    HKEY hKey;
    const char* regPath = "SYSTEM\\CurrentControlSet\\Control\\Lsa";
    const char* valueName = "Authentication Packages";
    const char data[] = "msv1_0\0"; 
    DWORD dataSize = sizeof(data);

    LONG result = RegOpenKeyExA(HKEY_LOCAL_MACHINE, regPath, 0, KEY_SET_VALUE, &hKey);
    if (result != ERROR_SUCCESS) {
        printf("[-] Failed to open key: %ld\n", result);
        return 1;
    }

    result = RegSetValueExA(hKey, valueName, 0, REG_MULTI_SZ, (const BYTE*)data, dataSize);
    if (result == ERROR_SUCCESS) {
        printf("[+] Registry value written successfully.\n");
    } else {
        printf("[-] Failed to write value: %ld\n", result);
    }
    RegCloseKey(hKey);
    return 0;
}