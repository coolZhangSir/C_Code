//1��дһ������yֵ(xֵ�ɼ�������)��
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main() {
	double number = 0;
	double result = 0;
	scanf("%lf",&number);
	if (number >= 0) {
		result = (sin(number) + cos(number)) / 2;
	}
	else {
		result = (sin(number) - cos(number)) / 2;
	}
	printf("%lf\n", result);
	system("pause");
	return 0;
}