#include<stdio.h>
#include<stdlib.h>

#define N 10

/*1����a[0:n-1]�����ź�������顣���д���������㷨��
	ʹ�õ�����Ԫ�ز���������ʱ������С��x�����Ԫ��λ��i�ʹ���x����Сλ��j.
	������Ԫ����������ʱ,i��j��ͬ,��Ϊx�������е�λ��
*/

void enhanceBinarySearch(int *arr,int target,int *i,int *j);

void main(){
	int arr[N] = {1,2,3,4,5,6,7,8,9,12};
	int target = 2;
	int i = 0;
	int j = N - 1;
	enhanceBinarySearch(arr,target,&i,&j);
	printf("i = %d,j = %d\n",i + 1,j + 1);
	system("pause");
}

void enhanceBinarySearch(int *arr,int target,int *i,int *j){
	int first = 0;
	int last = N - 1;
	int middle = (first + last) / 2;
	while(middle > first && middle < last){
		if(*(arr + middle) == target){
			*j = middle;
			*i = middle;
			return;
		}else if(*(arr + middle) > target){
			last = middle - 1;
			
		}else if(*(arr + middle) < target){
			first = middle + 1;
			
		}
		*j = last;
		*i = first;
		middle = (first + last) / 2;
	}
}