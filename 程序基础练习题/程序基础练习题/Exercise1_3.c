//����12��������ά���飬ȡ��ÿ�����ֵ����Сֵ��ÿ�����ֵ��Сֵ��
#include<stdio.h>
#include<stdlib.h>

#define ROW 3
#define COL 4

void getEachRowMax(int arr[ROW][COL]);
void getEachColumnMax(int arr[ROW][COL]);

void main() {
	int arr[ROW][COL] = { 234,654,567,2,7,8,9,234,732,568,345,457 };
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			printf("%4d ",arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	getEachRowMax(arr);
	printf("\n");
	getEachColumnMax(arr);
	printf("\n");

	system("pause");
}

void getEachRowMax(int arr[ROW][COL]) {
	for (int i = 0; i < ROW; i++)
	{
		int max = arr[i][0];
		int min = arr[i][0];
		for (int j = 1; j < COL; j++) {
			if (max < arr[i][j]) {
				max = arr[i][j];
			}
			if (min > arr[i][j]) {
				min = arr[i][j];
			}
		}
		printf("��%d�����ֵ=%d,��Сֵ=%d\n",i + 1,max,min);
	}
}

void getEachColumnMax(int arr[ROW][COL]) {
	for (int i = 0; i < COL; i++)
	{
		int max = arr[0][i];
		int min = arr[0][i];
		for (int j = 1; j < ROW; j++) {
			if (max < arr[j][i]) {
				max = arr[j][i];
			}
			if (min > arr[j][i]) {
				min = arr[j][i];
			}
		}
		printf("��%d�����ֵ=%d,��Сֵ=%d\n", i + 1, max, min);
	}
}
