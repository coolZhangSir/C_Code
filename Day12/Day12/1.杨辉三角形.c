#define N 5
#include<stdio.h>
#include<stdlib.h>

/*
	���������:���ұ߽��϶�Ϊ1,��ÿһ�����������Ϸ�����֮��
*/
void main() {
	int a[N][N] = { 0 };

	for (int i = 0;i < N;i++)
	{
		for (int j = 0;j < N;j++)
		{
			a[i][0] = 1;//��ʼ����߽��ϵ�ֵΪ1
			if (i == j) {
				//��ʼ���Խ����ϵ�ֵΪ1
				a[i][j] = 1;
			}
			else if(j < i){
				//��ʼ������ֵ�����Ϸ�������֮��
				a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
			}
		}
	}

	for (int i = 0;i < N;i++)
	{
		printf("%*d", 21 - 2 * i, a[i][0]);
		for (int j = 1;j < N;j++)
		{
			if (j <= i) {
				printf("%4d",a[i][j]);
			}
		}
		printf("\n");
	}

	system("pause");
}