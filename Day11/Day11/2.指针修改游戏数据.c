#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <process.h>
//����ֲ���ս��ʬ��������ڴ��ַ:1F70E168
_declspec(dllexport) void go() {
	int *p = 0x1F70E168;
	while (1) {
		if (*p < 50) {
			*p = 100;
		}
		Sleep(1000);
	}
}