#include <windows.h>
#include <stdio.h>

int main() {
    HKEY hKeyRoot = HKEY_LOCAL_MACHINE;
    LPCSTR path = "Software\\Microsoft\\Active Setup\\Installed Components\\{C9E9A340-D1F1-11D0-821E-444553540600}";

    LONG result = RegDeleteKeyA(hKeyRoot, path);
    if (result == ERROR_SUCCESS) {
        printf("[+] Registry value deleted successfully.\n");
    } else {
        printf("[-] Failed to delete value: %ld\n", result);
    }

    return 0;
}
