#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 9999
void OptimalBST(int, float*, float**, int**);
void OptimalBSTPrint(int, int, int**);
void main()
{
	int i, num;
	printf("���������:\n");
	scanf("%d", &num);
	float *p = (float*)malloc(sizeof(float)*(num + 1));
	printf("�����������:\n");
	for (i = 1; i<num + 1; i++)
		scanf("%f", &p[i]);
	//��������
	float **c = (float**)malloc(sizeof(float*)*(num + 2));
	for (i = 0; i<num + 2; i++)
		c[i] = (float*)malloc(sizeof(float)*(num + 1));
	//��������
	int **r = (int**)malloc(sizeof(int*)*(num + 2));
	for (i = 0; i<num + 2; i++)
		r[i] = (int*)malloc(sizeof(int)*(num + 1));
	//��̬�滮ʵ�����Ŷ��������������������⡣��
	OptimalBST(num, p, c, r);
	printf("�����Ŷ������������������Ϊ��%f \n", c[1][num]);
	//�������Ŷ����������������������
	printf("����ɵ����Ŷ��������������������Ϊ��");
	OptimalBSTPrint(1, 4, r);
	system("pause");
}
void OptimalBST(int num, float*p, float**c, int**r)
{
	int d, i, j, k, s, kmin;
	float temp, sum;
	for (i = 1; i<num + 1; i++)//����͸���Ԫ�صĳ�ʼ��
	{

		c[i][i - 1] = 0;
		c[i][i] = p[i];
		r[i][i] = i;
	}
	c[num + 1][num] = 0;
	for (d = 1; d <= num - 1; d++)//����ڵ�����
	{
		for (i = 1; i <= num - d; i++)
		{
			j = i + d;
			temp = MAX;
			for (k = i; k <= j; k++)//�����Ÿ�
			{
				if (c[i][k - 1] + c[k + 1][j]<temp)
				{
					temp = c[i][k - 1] + c[k + 1][j];
					kmin = k;
				}
			}
			r[i][j] = kmin;//��¼���Ÿ�
			sum = p[i];
			for (s = i + 1; s <= j; s++)
				sum += p[s];
			c[i][j] = temp + sum;
		}
	}
}
//���õݹ鷽ʽʵ�����Ÿ�����������Ÿ����Ǳ�����r[i][j]�еġ�����
void OptimalBSTPrint(int first, int last, int**r)
{
	int k;
	if (first <= last)
	{
		k = r[first][last];
		printf("%d  ", k);
		OptimalBSTPrint(first, k - 1, r);
		OptimalBSTPrint(k + 1, last, r);
	}
}