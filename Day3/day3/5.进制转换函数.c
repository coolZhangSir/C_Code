#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
/*
	5.�������ļ��������ݣ���ӡ�������ƣ��˽���,16����
*/

int main() {
	int number = 0;
	char result[100] = { 0 };
	
	while (number != -1) {
		scanf("%d", &number);
		
		_itoa(number,result,2);
		printf("%s\n",result);
		
		_itoa(number, result, 8);
		printf("%s\n", result);
		
		_itoa(number, result, 16);
		printf("%s\n", result);
	}

	getchar();
	getchar();

	return 0;
}