#include <windows.h>
#include <stdio.h>

int main() {
    HKEY hKey;
    LPCSTR path = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    LPCSTR name = "PersistenceRunKeys";

    LONG result = RegOpenKeyExA(HKEY_CURRENT_USER, path, 0, KEY_SET_VALUE, &hKey);
    if (result != ERROR_SUCCESS) {
        printf("[-] Failed to open key: %ld\n", result);
        return 1;
    }

    result = RegDeleteValueA(hKey, name);
    if (result == ERROR_SUCCESS) {
        printf("[+] Registry value deleted successfully.\n");
    } else {
        printf("[-] Failed to delete value: %ld\n", result);
    }

    RegCloseKey(hKey);
    return 0;
}
