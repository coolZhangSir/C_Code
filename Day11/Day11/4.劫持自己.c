#include<stdio.h>
#include<stdlib.h>
#include<Windows.h> //detours.h����windows.h�е�����,��Ҫ�Ȱ�����
#include "detours.h"
#include "detver.h"

#pragma comment(lib,"detours.lib")

int (WINAPI *oldMessageBoxA)(
	HWND hWnd,
	LPCSTR lpText,
	LPCSTR lpCaption,
	UINT uType) = MessageBoxA;

int WINAPI newMessageBoxA(
	HWND hWnd,
	LPCSTR lpText,
	LPCSTR lpCaption,
	UINT uType) {
		printf("%s\n",lpText);
}

void hook() {
	//�ָ�ԭʼ�ĵ�ַӳ���,���ⷴ������
	DetourRestoreAfterWith();
	//��ʼһ���µ��������ڸ��ӻ�ȡ������
	DetourTransactionBegin();
	//�ڵ�ǰ�����л�ȡһ���߳������޸ĺ�������ָ��ĵ�ַ
	DetourUpdateThread(GetCurrentThread());
	//ʹ�ڶ��������ϵĺ������ص�һ�������ϵĺ���
	DetourAttach((void**)&oldMessageBoxA, newMessageBoxA);
	//�ύ��������
	DetourTransactionCommit();
}

void main() {
	MessageBoxA(0, "�ٳ�ǰ", "�ٳ�", 0);

	hook();

	MessageBoxA(0, "�ٳֺ�", "�ٳ�", 0);

	system("pause");
}
