#include<stdio.h>
#include<stdlib.h>
/*
	����һ��������Сֵ�����ҳ���ֵ
*/
void getExtremeValue(int a[10]) {
	for (int i = 0; i < 9; i++)
	{
		if (a[i] >= a[i + 1]) {
			int temp = a[j];
			a[j] = a[j + 1];
			a[j + 1] = temp;
		}
	}
}
/*
	��ν����ֵ������Сֵ���׼����������
*/
void sort(int a[10]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9 - i; j++)
		{
			if (a[j] >= a[j + 1])
			{
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		printf("%d ", a[i]);
	}
}

void main() {
	int a[10] = { 5,2,3,6,7,10,9,4,8,1 };
	//sort(a);
	


	getchar();
}