//1.���ֶ�����10���������飬ʵ�ִӴ�С����С������������ð�ݣ����룬ѡ��ʵ�֡�Ҫ��ֱ�ʵ��һ���޸�ԭ������Ͳ��޸�ԭ������
#include<stdio.h>
#include<stdlib.h>
#define N 10

//ð������ - ��С�����޸�ԭ������
void bubbleSortMinToMax(int *arr);
//ð������-��С�����޸�ԭ������
void bubbleSortMinToMaxNotModify(const int *pArr[N]);

//�������� - ��С�����޸�ԭ������
void insertSortMinToMax(int *arr);
//�������� - ��С�����޸�ԭ������
void insertSortMinToMaxNotModify(const int *pArr[N]);

//ѡ������ - ��С�����޸�ԭ������
void selectSortMinToMax(int *arr);
//ѡ������ - ��С�����޸�ԭ������
void selectSortMinToMaxNotModify(const int *pArr[N]);

void main() {
	int arr[N] = { 4,2,5,8,7,6,1,3,9,0 };
	int *pArr[N] = {&arr[0],&arr[1],&arr[2],&arr[3],&arr[4],&arr[5],&arr[6],&arr[7],&arr[8],&arr[9]};
	
	//bubbleSortMinToMax(arr);
	//bubbleSortMinToMaxNotModify(pArr);
	//insertSortMinToMax(arr);
	insertSortMinToMaxNotModify(pArr);
	//selectSortMinToMax(arr);
	//selectSortMinToMaxNotModify(pArr);
	for (int i = 0; i < N; i++)
	{
		//printf("%d ",arr[i]);
		printf("%d ", *pArr[i]);
	}

	printf("\n");
	system("pause");
}

//ð������-��С����,���޸�����,const:��ֹ�޸ĸõ�ַ��Ӧ��ֵ
void bubbleSortMinToMaxNotModify(const int *arr[N])
{
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = 0; j < N - 1 - i; j++)
		{
			if (*arr[j] > *arr[j + 1]) {
				int *temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

//ð������-��С����,�޸�����
void bubbleSortMinToMax(int *arr) {
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = 0; j < N - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

//�������� - ��С�����޸�ԭ������
void insertSortMinToMax(int *arr) {
	for (int i = 1; i < N; i++)
	{
		int temp = arr[i];
		int index = i;
		while (index > 0 && arr[index - 1] > temp) {
			arr[index] = arr[index - 1];
			index--;
		}
		arr[index] = temp;
	}
}

//�������� - ��С�����޸�ԭ������
void insertSortMinToMaxNotModify(const int *pArr[N]) {
	for (int i = 1; i < N; i++)
	{
		int* temp = pArr[i];
		int index = i;
		while (index > 0 && *pArr[index - 1] > *temp) {
			pArr[index] = pArr[index - 1];
			index--;
		}
		pArr[index] = temp;
	}
}

//ѡ������,�޸�ԭ������
void selectSortMinToMax(int *arr) {
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = i + 1; j < N; j++) {
			if (arr[i] > arr[j]) {
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

//ѡ������ - ��С�����޸�ԭ������
void selectSortMinToMaxNotModify(const int *pArr[N]) {
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = i + 1; j < N; j++) {
			if (*pArr[i] > *pArr[j]) {
				int *temp = pArr[i];
				pArr[i] = pArr[j];
				pArr[j] = temp;
			}
		}
	}
}