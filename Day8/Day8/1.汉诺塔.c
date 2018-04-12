#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
/*
	��ŵ�����������Ƶ�:
		A,B,C��������,��Ҫ��N�����Ӵ�A���ƶ���C��.
		Ҫ�ƶ�N������,����Ҫ�ƶ������N-1�����ӵ��м���,�����ƶ����һ�����ӵ�Ŀ����.
		1.����Ŀ����C���ƶ�N-1�����ӵ��м���B��
		2.����N�������ƶ�Ŀ��C��
		3.�ٽ�N-1�����Ӵ�B������A���ƶ���C��
*/
void move(char from,char to) {
	printf("%c---->%c\n",from,to);
}

void hannoi(int count,char from,char middle,char to) {
	if (count == 1) {
		move(from, to);
	}
	else {
		hannoi(count - 1, from, to, middle);
		move(from, to);
		hannoi(count - 1, middle, from, to);
	}
}
void main() {
	int count = 0;
	char from = 'A';
	char middle = 'B';
	char to = 'C';

	scanf("%d",&count);

	hannoi(count, from, middle, to);
	system("pause");
}

