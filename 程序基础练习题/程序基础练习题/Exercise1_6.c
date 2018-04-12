//6.���Զ�����1024���������0 - 1024֮�䣩��������ö��ֲ��ң���ֵ�����ҵ���
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 1024

void initialize(int arr[N]);
void showArr(int arr[N]);
void insertionSort(int arr[N]);
int binarySearch(int arr[N], int target);

void main() {
	int index = -1;
	int target = 3;
	int arr[N] = { 0 };
	initialize(arr);
	insertionSort(arr);
	showArr(arr);

	//index = binarySearch(arr, target);
	index = interpolationSearch(arr, target);

	if (-1 == index)
	{
		printf("�������в�����%d\n",target);
	}
	else {
		printf("��һ��%d��Ӧ���±�Ϊ%d\n", target, index);
	}

	system("pause");
}

void showArr(int arr[N]) {
	for (int i = 0; i < N; i++)
	{
		printf("%-4d ",arr[i]);
		if ((i + 1) % 10 == 0) {
			printf("\n");
		}
	}
	printf("\n--------------------------------------\n");
}

void initialize(int arr[N]) {
	srand(NULL);
	for (int i = 0; i < N; i++)
	{
		arr[i] = rand() % N;
	}
}

/*ò��ѡ��,ð��,�����⼸�������㷨���Ӷȶ������O(n^2),�������п��ܻ����Щ����*/
void insertionSort(int arr[N]) {
	//��������ľ����Ƕ�һ����һ��,�ӵ�һ����ʼ��ÿһ�����ŵ����ʵ�λ��
	for (int i = 1; i < N; i++)//ֻ��һ����ʱ����Ҫ����
	{
		//���浱ǰ��Ҫ������±��ֵ,��ֹ�ƶ�ǰ���Ԫ�ص�ʱ�򱻸���
		int temp = arr[i];
		//���ڻ��漰��Ԫ�ص��ƶ�,��Ҫ��¼�ƶ�����һ���±���
		int index = i;
		while (index > 0 && arr[index - 1] > temp) {
			arr[index] = arr[index - 1];
			index--;
		}
		arr[index] = temp;
	}
}

/*
	���ַ�����,�ҵ������±�,δ�ҵ�����-1
*/
int binarySearch(int arr[N],int target) {
	int count = 0;
	int start = 0;
	int end = N - 1;
	int middle = (start + end) / 2;

	while (middle >= start && middle <= end)
	{
		if (arr[middle] == target)
		{
			printf("binaryCount = %d\n", count);
			return middle;
		}
		else if (arr[middle] > target)
		{
			end = middle - 1;
		}
		else if (arr[middle] < target)
		{
			start = middle + 1;
		}
		middle = (start + end) / 2;
		count++;
	}
	return -1;
}

/*
	��ֵ����,�������޸Ķ��ֲ��ҵĹ�ʽ
	����:middle = start + (end - start) / 2
	��ֵ:arr[middle] - arr[start]        middle - start
		-------------------------  ==   ----------------
		 arr[end] - arr[start]            end - start
	
	������ı������ɵõ�:
		middle = start + (end - start) * (arr[middle] - arr[start]) / (arr[end] - arr[start])
*/
int interpolationSearch(int arr[N],int target) {
	int count = 0;
	int start = 0;
	int end = N - 1;
	int middle = start + (end - start) * (target - arr[start]) / (arr[end] - arr[start]);

	while (middle >= start && middle <= end) {
		if (arr[middle] == target) {
			printf("interpolationCount = %d\n", count);
			return middle;
		}
		else if (arr[middle] < target)
		{
			start = middle + 1;
		}
		else if(arr[middle] > target)
		{
			end = middle - 1;
		}
		middle = start + (end - start) * (target - arr[start]) / (arr[end] - arr[start]);
		count++;
	}
	return -1;
}