#include<stdio.h>
#include<stdlib.h>
void main() {
	double array[100];
	for (int i = 0; i < 100; i++)
	{
		array[i] = i + 1;
	}
	/*
		double*һ��ָ��һ����Ҫ�ƶ�8���ֽ�
	*/
	double* p = array + 1;
	printf("��ʱ��ֵ:%f\n",*p);
	double** pp = &p;
	printf("double**�Ĵ�С=%d\n",sizeof(pp));
	/*
		ָ������ͷǳ���Ҫ,������ֱ��ȡ��array�ĵ�ַ,������.
		�����ֱ���������ĵ�ַ0x0000������ʮ�����Ƶ���ֵ,��ôǰ���ĵ�ַ����Ҫ������������һ�����ƶ����ֽڳ���
	*/
	*pp = array + 80;
	printf("�޸�֮���ֵ:%f\n", *p);
	system("pause");
}