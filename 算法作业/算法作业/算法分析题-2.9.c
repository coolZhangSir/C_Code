#include<stdio.h>
#include<stdlib.h>
#define N 8

/*
	��������a[0:k-1]��a[k:n-1]���ź���(0<=k<=n-1).
		�����һ���ϲ�֮����������Ϊ�ź��������a[0:n-1]���㷨.
		Ҫ���㷨�����������õļ���ʱ��ΪO(n),��ֻ�õ�O(1)�����ռ�.
		(0:k-1): 2 4 6 8
		(k:n-1): 1 3 5 7
		(0:n-1): 1 2 3 4 5 6 7 8
*/
void merge(int *arr,int k,int *result);
void main(){
	int arr[N] = {1,3,5,7,2,4,6,8};
	int k = 4;
	int result[N] = {0};
	int i = 0;

	merge(arr,k,result);

	for (i = 0; i < N; i++)
	{
		printf("%d ",result[i]);
	}
	system("pause");
}

void merge(int *arr,int k,int *result){
	int i = 0;
	int j = k;
	int resultIndex = 0;
	while(i < k && j < N)
	{
		if(*(arr + i) > *(arr + j)){
			*(result + resultIndex) = *(arr + j);
			j++;
		}else{
			*(result + resultIndex) = *(arr + i);
			i++;
		}
		resultIndex++;
	}
	while (i < k)
	{
		*(result + (resultIndex++)) = *(arr + (i++));
	}
	while (j < N)
	{
		*(result + (resultIndex++)) = *(arr + (j++));
	}
}