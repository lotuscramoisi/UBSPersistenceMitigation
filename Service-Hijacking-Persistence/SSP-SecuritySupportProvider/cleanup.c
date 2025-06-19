#include <windows.h>
#include <stdio.h>

int main() {
    HKEY hKey;
    LPCSTR path = "System\\CurrentControlSet\\Control\\Lsa";
    LPCSTR valueName  = "Security Packages";

    const char data[] = "\"\"\0"; 
    DWORD dataSize = sizeof(data);

    LONG result = RegOpenKeyExA(HKEY_LOCAL_MACHINE, path, 0, KEY_SET_VALUE, &hKey);
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
