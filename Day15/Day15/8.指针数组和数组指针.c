#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void function1() {
	/*
		ָ������:int *p[10]
		��;:�洢��������ĵ�ַ,������
		ʵ��:��һ����������������,Ҫ���ܸı�ԭ����
	*/
	int array[10] = { 0 };
	int *pArray[10] = { NULL };
	//��ʼ��
	time_t t;
	srand((unsigned int)time(&t));
	for (int i = 0; i < 10; i++)
	{
		array[i] = rand() % 100 + 1;
	}
	for (int i = 0; i < 10; i++)
	{
		pArray[i] = &array[i];
	}

	//����ð������
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10 - 1 - i; j++)
		{
			//*(pArray + j)ȡ��ָ�������j��Ԫ�����洢�ĵ�ַ,��*ȡ�������ֵ
			if (*(*(pArray + j)) < *(*(pArray + j + 1)))
			{
				int *temp = *(pArray + j);
				*(pArray + j) = *(pArray + j + 1);
				*(pArray + j + 1) = temp;
			}
		}
	}
	for (int i = 0; i < 10; i++)
	{
		printf("%d ",*(*(pArray + i)));
	}
	putchar(10);
}
void function2() {
	/*
		����ָ��:int (*p)[10]
	*/
	int array[] = { 1,2,3 };
	//���Ǵ����,���Ͳ�ƥ��,a��һ��int *����,&a����һ������ָ������
	//int(*p)[3] = array;
	int(*p)[3] = &array;
	//����һ��һά����,����pֱ��ָ����һ������,+1��ǰ�ƶ�һ����λ,��*ȡ������
	printf("%d\n",*(*p + 1));
}
void main() {
	//function1();
	function2();
	system("pause");
}