#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#include<Windows.h>
void run(void *p) {
	MessageBox(NULL, "һ��8��8", "���߼�����", 0);
}

void runWithParameter(void *p) {
	//��void*ת����int*
	int *p1 = p;
	char str[10] = { 0 };
	//��int��ֵ���뵽�ַ�����
	sprintf(str,"һ��%d��8",*p1);
	MessageBox(NULL, str, "���߼�����", 0);
}
void main() {
	int array[] = { 4,5,6,7,8 };
	for (int i = 0; i < 5; i++)
	{
		//_beginthread(run, 0, NULL);
		//�������̲߳����ݲ���,ע����̷߳���ͬһ������ͻ������
		_beginthread(runWithParameter,0,(array + i));
	}
	system("pause");
}