/*
	�����ٳּ���ԭ��������ָ��ĵ�ַ�����޸�,�ﵽ�ٳֵ�Ŀ��.
	Ŀǰ����ʹ��detours express3.0���߽����κκ����Ľٳ�
*/
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

void show() {
	MessageBoxA(0,"�ٳ�ǰ","test",0);
}

void hijack() {
	MessageBoxA(0,"�ٳֺ�","test",0);
}

void main() {
	void (*p)() = show;
	p();
	p = hijack;
	p();
}