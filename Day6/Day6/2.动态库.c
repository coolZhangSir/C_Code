#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

//pragma comment(linker,"/subsystem:"windows" /entry:"mainCRTStartup"")
//linker����,��dos����ĳ�windowģʽ����,����ȥ��Dos����,ͬʱdos����Ĳ���,���������������
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

void main() {
	MessageBoxA(0, "ȥ��Dos����", "Windowģʽ����", 0);
	printf("���ܿ���ô?\n");
	int num = 0;
	scanf("%d",&num);
}

//�����ӿ����ڵ���
_declspec(dllexport) void go() {

	MessageBoxA(0, "����ע��ɹ�", "�峤��ʾ", 0);

}