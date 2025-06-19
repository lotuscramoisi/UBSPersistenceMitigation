//g++ -shared -o servDLL.dll servDLL.cpp -static-libgcc -static-libstdc++ -Wl,--subsystem,windows
#include <windows.h>
#include <fstream>
#include <winsplp.h>

void LogStep(const char* msg) {
    SYSTEMTIME st;
    GetLocalTime(&st);

    char buffer[512];
    snprintf(buffer, sizeof(buffer),
             "[%04d-%02d-%02d %02d:%02d:%02d.%03d] %s",
             st.wYear, st.wMonth, st.wDay,
             st.wHour, st.wMinute, st.wSecond, st.wMilliseconds,
             msg);

    HANDLE hFile = CreateFileA("C:\\Users\\Public\\global_loggin.txt",
        FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
        DWORD written;
        WriteFile(hFile, buffer, (DWORD)strlen(buffer), &written, NULL);
        WriteFile(hFile, "\r\n", 2, &written, NULL);
        CloseHandle(hFile);
    }
}

DWORD WINAPI RunPayload(LPVOID) {
    LogStep("PRINT MONITOR | Thread started");
    Beep(500, 300);
    LogStep("PRINT MONITOR | Beeped");
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) {
    LogStep("PRINT MONITOR | DllMain called");
    if (reason == DLL_PROCESS_ATTACH) {
        LogStep("PRINT MONITOR | PROCESS_ATTACH");
        DisableThreadLibraryCalls(hModule);
        QueueUserWorkItem(RunPayload, NULL, WT_EXECUTEDEFAULT);

    }
    return TRUE;
}
