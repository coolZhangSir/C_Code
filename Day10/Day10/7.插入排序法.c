#include<stdio.h>
#include<stdlib.h>
/*
	���������˼·�ǽ�ѭ��ÿ�����һ��Ԫ�ز��뵽���ʵ�λ��,�Ӷ���������
*/
void sort(int a[10]) {
	for (int i = 0; i < 9; i++)
	{
		int last = a[9 - i];
		for (int j = 9; j > 0; j--)
		{
			if (a[j] <= a[j - 1]) {
				int temp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = temp;
			}
		}
		for (int j = 0; j < 10; j++)
		{
			printf("%d ",a[j]);
		}

		putchar(10);
	}

}
void main() {
	int a[10] = { 5,2,3,6,7,10,9,4,8,1 };
	
	sort(a);

	getchar();
}