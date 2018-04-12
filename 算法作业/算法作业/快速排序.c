#include<stdio.h>
#include<stdlib.h>
#define N 7

void swap(int *arr, int i, int j);
void sort(int *arr, int start, int end);
int partition(int *arr,int start,int end);
void show(int *arr);

void main() {
	int arr[N] = {2,5,4,7,3,1,6};
	sort(arr,0,N - 1);

	show(arr);
	system("pause");
}

void sort(int *arr,int start,int end) {
	if (start < end)
	{
		int index = partition(arr,start,end);
		sort(arr,start,index - 1);
		sort(arr, index + 1,end);
	}
}
/*
˼·:
	����Ԫ�ص��ɻ�׼ֵ,�����һ��Ԫ�ؿ�ʼ��ǰ���׼ֵ���бȽ�,�������С�ڻ�׼ֵ��Ԫ�ؾ�ֹͣסǰ.
	����Ԫ����ǰ���ָ����н���.
	Ȼ���ٴӵ�һ��Ԫ�ؿ�ʼס�����׼ֵ���бȽ�,������ֱȻ�׼ֵ��ľ�ֹͣ����.
	����Ԫ����ǰ���ָ����н���.
	�������,ֱ����ͷԪ����ĳһ���±���ͷ,��ֱ�ӽ���׼ֵ�����±���н���.
*/
int partition(int *arr,int start,int end) {
	int i = start;
	int j = end;
	int base = *(arr + start);
	while(i < j)
	{
		while ((*(arr + j)) > base && j > i)
		{
			j--;
		}
		*(arr + i) = *(arr + j);

		while ((*(arr + i)) < base && j > i)
		{
			i++;
		}
		*(arr + j) = *(arr + i);
	}
	*(arr + i) = base;
	return i;
}

void swap(int *arr,int i,int j) {
	int temp = *(arr + i);
	*(arr + i) = *(arr + j);
	*(arr + j) = temp;
}

void show(int *arr) {
	for (int i = 0; i < N; i++)
	{
		printf("%d ", arr[i]);
	}
	putchar(10);
}