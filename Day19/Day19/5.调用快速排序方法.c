#include<stdio.h>
#include<stdlib.h>
/*
	�Ƚ���
		

	Compare �����ķ���ֵ			����
		< 0				elem1��������elem2ǰ��
		= 0				elem1 ���� elem2
		> 0				elem1 ��������elem2���� 
*/
int compartor(const void *pA, const void *pB) {
	int a = *((int *)pA);
	int b = *((int *)pB);
	if (a == b)
	{
		return 0;
	}
	if (a > b)
	{
		return 1;
	}
	if (a < b)
	{
		return -1;
	}
}
void show(int *array) {
	for (int i = 0; i < 6; i++)
	{
		printf("%d ",array[i]);
	}
	printf("\n");
}
void main() {
	int array[] = { 1,3,2,6,4,5 };
	qsort(array,6,sizeof(int),compartor);
	show(array);
	system("pause");
}