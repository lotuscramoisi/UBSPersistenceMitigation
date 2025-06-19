#include <windows.h>
#include <stdio.h>

int main() {
    HKEY hKey;
    LPCSTR subKey = "SYSTEM\\CurrentControlSet\\Services\\NTDS";
    LPCSTR valueName = "LsaDbExtPt";

    LONG result = RegOpenKeyExA(HKEY_LOCAL_MACHINE, subKey, 0, KEY_SET_VALUE, &hKey);
    if (result != ERROR_SUCCESS) {
        printf("[-] Failed to open registry key: %ld\n", result);
        return 1;
    }

    result = RegDeleteValueA(hKey, valueName);
    if (result != ERROR_SUCCESS) {
        printf("[-] Failed to delete registry value '%s': %ld\n", valueName, result);
        RegCloseKey(hKey);
        return 1;
    }

    printf("[+] Registry value '%s' deleted successfully.\n", valueName);
    RegCloseKey(hKey);
    return 0;
}
