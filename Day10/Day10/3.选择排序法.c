#include<stdio.h>
#include<stdlib.h>

void main() {

	int a[10] = { 5,2,3,6,7,1,9,4,8,10 };
	//���һ��������Ҫ�ٽ�������
	for (int i = 0; i < 10 - 1; i++)
	{
		int index = 9 - i;
		for (int j = 0; j < 10 - i; j++)
		{
			if (a[index] <= a[j]) {
				index = j;
			}
		}
		
		//����±겻���ڳ�ʼֵ,��˵���и����ֵ����,��Ҫ���н���
		if (index != (9 - i)) {
			int temp = a[9 - i];
			a[9 - i] = a[index];
			a[index] = temp;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		printf("%d ",a[i]);
	}

	getchar();
}