#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
/*
	1.ʵ������һ��ʵ����ʵ��1.234 ���ڶ�λ�������룬����λ����6��
*/
int main() {
	float number = 0.0f;
	scanf("%f", &number);
	printf("�������Ϊ%.3f\n",number);
	int integer = 0;

	//����λ5��6��
	float third = number;
	third *= 100;				//123.4
	third += 0.4f;				//123.8
	integer = (int)third;		//123
	third = integer / 100.0f;	//1.23
	printf("����λ5��6��Ϊ%.3f\n", third);

	//�ڶ�λ��������	1.234
	//�������λС��
	float thirdDecimal = number * 100 - (int)(number * 100); //123.4 - 123

	float second = number;
	second *= 10;	//12.34
	second += 0.5f;	//12.84
	integer = (int)second;
	second = (integer + thirdDecimal / 10.0f) / 10;
	printf("�ڶ�λ4��5��Ϊ%.3f\n", second);

	getchar();
	getchar();
	return 0;
}