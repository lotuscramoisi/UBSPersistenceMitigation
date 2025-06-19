#include <windows.h>
#include <stdio.h>

int main() {
    HKEY hKey;
    LPCSTR path = "Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon";
    LPCSTR name = "PersistenceWinlogon";

    LONG result = RegOpenKeyExA(HKEY_CURRENT_USER, path, 0, KEY_SET_VALUE, &hKey);
    if (result != ERROR_SUCCESS) {
        printf("[-] Failed to open key: %ld\n", result);
        return 1;
    }

    result = RegDeleteValueA(hKey, name);
    if (result == ERROR_SUCCESS) {
        printf("[+] Registry value reset to default successfully.\n");
    } else {
        printf("[-] Failed to reset value: %ld\n", result);
    }

    RegCloseKey(hKey);
    return 0;
}
