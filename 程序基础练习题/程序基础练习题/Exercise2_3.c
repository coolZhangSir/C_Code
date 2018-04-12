//3.���ҳ�����A[10], B[10]���е�Ԫ�أ�����C[10].
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

#define N 10

void initArray(int *array) {
	for (int i = 0; i < N; i++)
	{
		*(array + i) = rand() % 30 + 1;
	}
}

void work(int *a,int *b,int *c) {
	int cIndex = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (*(a + i) == *(b + j))
			{
				*(c + cIndex) = *(a + i);
				cIndex++;
				break;
			}
		}
	}
}

void show(int *array,char ch) {
	printf("%c:\n",ch);
	for (int  i = 0; i < N; i++)
	{
		printf("%2d ",*(array + i));
	}
	printf("\n");
}

void main() {
	//�����ȡ�Ĳ���ϵͳ�ĵ�ǰʱ��(��)Ϊ����,��ε���������С��1��������ͬ�������
	srand((unsigned int)time(NULL));
	int a[N], b[N], c[N] = { 0 };

	initArray(a);
	initArray(b);

	work(a, b, c);

	show(a,'A');
	show(b,'B');
	show(c,'C');

	system("pause");
}
