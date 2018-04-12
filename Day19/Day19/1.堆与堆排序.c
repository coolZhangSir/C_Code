#include<stdio.h>
#include<stdlib.h>
/*
	����˼·:
		�󶥶�:�κ�һ������㶼��Ȼ���������ӽ��
		С����:�κ�һ������㶼��ȻС�������ӽ��
		����һ����,ʱ�̱�������Ķ�����,�󶥶ѵ������,�������Ԫ�ر�Ȼ������.
		�����ʱ��ֻ��Ҫ����˵�Ԫ�غ����һ��Ԫ�ؽ���,�ٴε�����ṹ,ʹ֮��������Լ���

*/
#define N 10
void show(int *p) {
	for (int i = 0; i < N; i++)
	{
		printf("%d ",p[i]);
	}
	printf("\n");
}
void swap(int *pA,int *pB) {
	int temp = *pA;
	*pA = *pB;
	*pB = temp;
}
void heap(int *p,int length) {
	/*
		�ѿ������ڲ������ֵ
	*/
	for (int i = length; i > 0; i--)
	{
		int parent = i / 2;
		int maxChild = 2 * parent + 1;
		while (maxChild < length) {
			if (maxChild < length - 1 && p[maxChild] < p[maxChild + 1])
			{
				maxChild++;
			}
			if (p[maxChild] > p[parent])
			{
				swap(p + maxChild, p + parent);
			}
			else
			{
				break;
			}
			parent = maxChild;
			maxChild = 2 * parent + 1;
		}
		show(p);
	}
}
void heapSort(int *p,int length) {
	for (int i = 0; i < N; i++)
	{
		heap(p,N - i);
		swap(p,p + N -1 - i);
		show(p);
	}
}
void main() {
	int array[] = { 3,2,5,4,6,7,1,9,8,0};
	//int array[] = { 0,1,2,3,4,};
	//heap(array,N);
	//printf("max:%d\n",array[0]);
	heapSort(array,N);
	show(array);
	system("pause");
}