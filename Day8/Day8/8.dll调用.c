#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
/*
	�˽�dll�������õ����̺ͷ���
	�ܽ�:
		1.�Ƚ�dll���Ƶ���Ӧ��Ŀ�¸�Ŀ¼
		2.ͨ��window.h�е�loadLibraryA("dllName")��ȡ��dllģ��
		3.�����dll����ɹ�,�����ͨ��getProcAddress("moduleName","functionName")��ȡ��Ӧ�Ľӿں���,Ȼ����ת���ɶ�Ӧ�ĺ���ָ������
		4.ֱ�ӵ��øú�������,�����вλ����޲εķ�ʽ
		5.����֮��ͨ��freeLibrary("mudouleName")�ͷŸ�dllģ��
*/
//����ָ��,�ú�����void p(�����б�)��Ϊvoid (*ָ����)(�����б�)
//����ָ������ԭ��Ϊ:void (*)(�����б�)
void (*p)();
void(*p1)(char *content);
void main() {
	HMODULE module = LoadLibraryA("�����õ�dll.dll");
	if (module != NULL) {
		p = (void (*)())GetProcAddress(module, "go");
		if (p != NULL) {
			p();
		}
		else {
			MessageBoxA(0, "load function error", "error", 0);
		}
		
		p1 = (void(*)(char* content))GetProcAddress(module, "run");
		if (p1 != NULL)
		{
			p1("����dll���вκ����ɹ�");
		}
		else {
			MessageBoxA(0, "load function error", "error", 0);
		}
	}
	else {
		MessageBoxA(0, "load module error!", "error", 0);
	}
	FreeLibrary(module);
}