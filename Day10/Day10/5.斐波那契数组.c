#include<stdio.h>
#include<stdlib.h>
/*
	ͨ��ѭ����ֵ�ȵݹ����쳲���������ֵ���ٶ�Ҫ��ܶ�
*/
int recursive(int number) {
	if (number == 1 || number == 2) {
		return 1;
	}
	else {
		return recursive(number - 1) + recursive(number - 2);
	}
}
/*
	����return�и�������,�������ﷵ��һ���ֲ������ĵ�ַ������ʱ����Ӧ��ûʲô���ë��.��������˵��
*/
int* array() {
	int a[100] = { 0 };
	a[0] = 1;
	a[1] = 1;

	for (int i = 2; i < 40; i++)
	{
		a[i] = a[i - 1] + a[i - 2];
	}

	return a;
}
void main() {
	int *a = NULL;
	a = array();
	printf("%d\n", a[39]);

	int result = recursive(40);
	printf("%d\n",result);

	getchar();
}