#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
HMODULE hook;
int seed;
void CALLBACK timerProc(
	_In_ HWND     hwnd,
	_In_ UINT     uMsg,
	_In_ UINT_PTR idEvent,
	_In_ DWORD    dwTime
) {
	printf("%d\n",uMsg);

	FARPROC endHook = GetProcAddress(hook, "endHook");
	(*endHook)();
	KillTimer(NULL, seed);
}
void main() {
	seed = SetTimer(0,0,6000, timerProc);

	hook = LoadLibrary("./����.dll");
	FARPROC initHook = GetProcAddress(hook,"initHook");
	(*initHook)();
	while (1) {

	}
	//����©����Ϣ������Ȼ���ղ����κζ���
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	system("pause");
}