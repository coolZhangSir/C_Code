#include<stdio.h>
#include<stdlib.h>
#define N 6
/*
	��ӡ��������:
	1  2  3  4
	12 13 14 5
	11 16 15 6
	10 9  8  7
*/
void move(int (*arr)[N]);
void show(int (*arr)[N]);
void main() {
	int arr[N][N] = { 0 };
	move(arr);
	show(arr);
	system("pause");
}
void move(int (*arr)[N]) {
	//�۲췢��,�������ҿ�ʼ�Ĵ�����ÿһ����/2,������Ҫ��1��.��������(N+1)/2
	int number = 1;
	for (int i = 0; i < ((N + 1) / 2); i++)
	{
		//������,��,��,�ϵ�˳���ӡ����
		int row = i;
		int column = i;
		//��
		while (column < (N - i))
		{
			(*(arr + row))[column++] = number++;
		}
		show(arr);
		column--;
		row++;

		//��
		while (row < (N - i))
		{
			(*(arr + row++))[column] = number++;
		}
		show(arr);
		row--;
		column--;

		//��
		while (column >= i)
		{
			(*(arr + row))[column--] = number++;
		}
		show(arr);
		column++;
		row--;

		//��
		while (row > i)
		{
			(*(arr + row--))[column] = number++;
		}

		show(arr);
	}
}

void show(int (*arr)[N]) {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%2d ",(*(arr + i))[j]);
		}
		printf("\n");
	}
	printf("\n");
}