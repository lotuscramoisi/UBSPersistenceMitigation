/*
   Atomic Test T1547.003

   Author:    traceflow
              https://github.com/traceflow

   Credits:   https://github.com/scottlundgren/w32time
              https://pentestlab.blog/2019/10/22/persistence-time-providers/

   Resources: https://docs.microsoft.com/en-us/windows/win32/sysinfo/creating-a-time-provider
              https://docs.microsoft.com/en-us/windows/win32/sysinfo/sample-time-provider
*/
// g++ -shared -o dll.dll dll.c -static-libgcc -static-libstdc++ -Wl,--subsystem,windows

#include <windows.h>
#include <winsplp.h>
#include <fstream>
#include "timeprov.h"

TimeProvSysCallbacks sc;
const TimeProvHandle htp = (TimeProvHandle)1;
TpcGetSamplesArgs Samples;
DWORD dwPollInterval;

void Run(void) {
    SYSTEMTIME st;
    GetLocalTime(&st);

    char buffer[512];
    snprintf(buffer, sizeof(buffer),
             "[%04d-%02d-%02d %02d:%02d:%02d.%03d] %s",
             st.wYear, st.wMonth, st.wDay,
             st.wHour, st.wMinute, st.wSecond, st.wMilliseconds,
             "time_provider");
    
    HANDLE hFile = CreateFileA("C:\\Users\\Public\\global_loggin.txt",
        FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
        DWORD written;
        WriteFile(hFile, buffer, (DWORD)strlen(buffer), &written, NULL);
        WriteFile(hFile, "\r\n", 2, &written, NULL);
        CloseHandle(hFile);
    } 

   return;

}

HRESULT CALLBACK TimeProvOpen(WCHAR *wszName, TimeProvSysCallbacks *pSysCallback, TimeProvHandle *phTimeProv) {

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE) Run, 0, 0, 0);

	CopyMemory(&sc, (PVOID)pSysCallback, sizeof(TimeProvSysCallbacks));
	*phTimeProv = htp;

   return S_OK;
}

HRESULT CALLBACK TimeProvCommand(TimeProvHandle hTimeProv, TimeProvCmd eCmd, PVOID pvArgs) {
   
   switch( eCmd ) {
      case TPC_GetSamples:
      // Return the Samples structure in pvArgs.
         CopyMemory(pvArgs, &Samples, sizeof(TpcGetSamplesArgs));
         break;
      case TPC_PollIntervalChanged:
      // Retrieve the new value.
         sc.pfnGetTimeSysInfo( TSI_PollInterval, &dwPollInterval );
         break;
      case TPC_TimeJumped:
      // Discard samples saved in the Samples structure.
         ZeroMemory(&Samples, sizeof(TpcGetSamplesArgs));
         break;
      case TPC_UpdateConfig:
      // Read the configuration sirmation from the registry.
         break;
   }
   return S_OK;
}

HRESULT CALLBACK TimeProvClose(TimeProvHandle hTimeProv) {
   return S_OK;
}