//1.���ڶ��߳��첽��ͬ������5���Ի���
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<process.h>

int array[] = { 1,2,3,4,5 };

void synchronize() {
	//ͬ����
	for (int i = 0; i < 5; i++)
	{
		MessageBoxA(0, "����", "����", 0);
	}
}

void go(void *parameter) {
	int *a = parameter;
	char str[10] = { 0 };
	sprintf(str,"%d",*a);
	MessageBoxA(0, str, "����", 0);
}

void asynchronous() {
	for (int i = 0; i < 5; i++)
	{
		_beginthread(go,0,&array[i]);
		printf("%d %d\n",&array[i], *(&array[i]));
	}
}

int main() {
	//synchronize();
	asynchronous();

	system("pause");
}