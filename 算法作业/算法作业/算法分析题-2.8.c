/*
	��a[0:n-1]����n��Ԫ�ص�����,k(0<=k<=n-1)��һ���Ǹ�����,
	�����һ���㷨��������a[0:k-1]��a[k:n-1]��λ
	Ҫ���㷨�������º�ʱO(n),��ֻ�õ�O(1)�ĸ����ռ�.
*/
#include<stdio.h>
#include<stdlib.h>
#define N 10

void swap(int *arr,int k);

void main(){
	int arr[N] = {1,3,6,7,9,0,4,2,5,8};
	int k = 3;
	int i = 0;
	
	swap(arr,k);

	printf("k=%dʱ:\n",k);
	for(i = 0;i < N;i++){
		printf("%d ",arr[i]);
	}
	putchar(10);
	system("pause");
}

void swap(int *arr,int k){
	int i = 0;
	if(k <= 0 || k >= N){
		return;
	}
	for(i = 0; i < k;i++){
		int temp = *(arr + i);
		*(arr + i) = *(arr + (k + i));
		*(arr + (k + i)) = temp;
	}
}