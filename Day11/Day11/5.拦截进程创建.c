#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include"detours.h"
#include<string.h>

#pragma comment(lib,"detours.lib")

BOOL
(WINAPI *oldCreateProcessW)(
	 LPCWSTR lpApplicationName,
	 LPWSTR lpCommandLine,
	 LPSECURITY_ATTRIBUTES lpProcessAttributes,
	 LPSECURITY_ATTRIBUTES lpThreadAttributes,
	 BOOL bInheritHandles,
	 DWORD dwCreationFlags,
	 LPVOID lpEnvironment,
	 LPCWSTR lpCurrentDirectory,
	 LPSTARTUPINFOW lpStartupInfo,
	 LPPROCESS_INFORMATION lpProcessInformation
) = CreateProcessW;

BOOL
WINAPI 
newCreateProcess(
	LPCWSTR lpApplicationName,
	LPWSTR lpCommandLine,
	LPSECURITY_ATTRIBUTES lpProcessAttributes,
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	BOOL bInheritHandles,
	DWORD dwCreationFlags,
	LPVOID lpEnvironment,
	LPCWSTR lpCurrentDirectory,
	LPSTARTUPINFOW lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation
	){

	printf("���سɹ�\n");

	wchar_t *p1 = NULL;
	wchar_t *p2 = NULL;

	p1 = wcsstr(lpApplicationName, L"360");//�����ǿ��ַ��ıȽ�,����ֻ����wcsstr�������бȽ�
	p2 = wcsstr(lpCommandLine, L"360");

	if (p1 != NULL || p2 != NULL) {
		MessageBoxA(0,"�Ѿ���������","��צ��?",0);
	}
	else {
		oldCreateProcessW(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);
	}
	
}

void hook() {
	DetourRestoreAfterWith();
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach((void**)&oldCreateProcessW,newCreateProcess);
	DetourTransactionCommit();
}
/*
	createProcess������һ�����ʻ��ĺ���,��������Ҫ����createProcessW
*/
void main() {
	STARTUPINFOW si = {sizeof(si)};
	si.wShowWindow = TRUE;
	si.dwFlags = STARTF_USESHOWWINDOW;
	PROCESS_INFORMATION pi;
	
	hook();

	wchar_t cmd[100] = L"C:\\Program Files (x86)\\360\\360Safe\\360Safe.exe";
	CreateProcessW(cmd, "", NULL, NULL, 0, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
}