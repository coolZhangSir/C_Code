#include<stdio.h>
#include<stdlib.h>
#define N 10
/*
	��ѭ���ж�һ�������Ƿ����
int isIncrease(int arr[N]) {
	for (int i = 0; i < N - 1;i++) {
		if (arr[i] >= arr[i + 1]) {
			return 0;
		}
	}
	return 1;
}
*/
/*
	�õݹ��ж�һ�������Ƿ����
*/
int isIncrease(int arr[N],int i,int flag) {
	if (i == (N - 2)) {
		flag = arr[i] < arr[i + 1];
		return flag;
	}
	if (flag == 0) {
		return flag;
	}
	else {
		flag = arr[i] < arr[i + 1];
		return isIncrease(arr, i + 1, flag);
	}
}
void main() {
	int flag = 1;
	int arr[N] = { 1,2,3,4,5,6,7,8,9,10 };
	int result = isIncrease(arr,0,flag);
	if (result)
	{
		printf("�ǵ���\n");
	}
	else {
		printf("���ǵ���\n");
	}
	getchar();
}