/*
	�Ի���������з���,�����ۻ��������������ԭ��ͷ���,������һ��ʾ������:
	����������ɵĹ���,��ʲô����»���ֻ����������?
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void fun(char *str) {
	char buf[8];
	strcpy(buf,str);
	printf("%s\n",buf);
}

void main(int argc,char *argv[]) {
	/*
	for (int i = 0; i < argc; i++)
	{
		printf("%s\n",argv[i]);
	}
	*/
	if (argc > 0) {
		fun(argv[1]);
	}
}