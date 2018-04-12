/*
	���� ������N��Ԫ�أ��ҳ���m��С��Ԫ�أ�����ʱ���ΪO(n)
*/
#include<stdio.h>
#include<stdlib.h>
#define N 22
#define DIVISION 5

int findMiddle(int *arr,int division,int start ,int end);
void sort(int *arr,int start,int end);
void swap(int *arr,int index1,int index2);
int partition(int *arr,int start,int end);
void show(int *arr);
int select(int *arr, int division, int start, int end, int total,int* middleCount,int targetOrder);

void main(){
	int targetOrder = 2;
	int arr[] = {2,3,7,5,1,8,4,9,10,34,12,57,56,45,13,16,41,24,39,43,22,54};
	int middleCount = 0;
	int result = 0;
	findMiddle(arr,DIVISION,0,N - 1);
	result = select(arr, DIVISION, 0, 4,N,&middleCount,targetOrder);
	printf("��%dС����=%d\n",targetOrder,result);
	system("pause");
}
//1.�ҳ���λ������
int findMiddle(int *arr,int division,int start ,int end){
	int i;
	for (i = 0; i < N; i += division)
	{
		//��ÿ��N/division�����н�������
		if((i + division - 1) > N){
			sort(arr,i,N - 1);
		}else{
			sort(arr,i,i + division - 1);
		}
	}
	show(arr);
}

/*�����������������ҳ���λ��
	˼·:�ݹ齫ÿһ��N/5�������е���λ����������Ӧ��ǰ���Ԫ��,
	Ȼ���ٴ��������ҵ���λ������λ��.
*/
int select(int *arr,int division,int start,int end,int total,int* middleCount,int targetOrder){
/*
	1  2  3  5  7
	4  8  9  10 34
	12 13 45 56 57
	16 24 39 41 43
	22 54
*/
	if ((end - start + 1) < division)
	{

		int middleIndex = 0;
		//�ڵݹ�Ľ�����������ѡ��������λ������λ��
		//���Ÿ���
		sort(arr, 0, (*middleCount) - 1);
		//ȷ����λ������λ����λ��
		if ((*middleCount) % 2 != 0)
		{
			middleIndex = (*middleCount / 2);
		}
		else
		{
			if ((*middleCount / 2) > (*middleCount / 2 + 1))
			{
				middleIndex = (*middleCount / 2);
			}
			else
			{
				middleIndex = (*middleCount / 2 + 1);
			}
		}
		show(arr);
		//��һ�˻���
		swap(arr, 0, middleIndex);
		//x:��λ������λ��
		int x = partition(arr, 0, N - 1);
		show(arr);
		if (targetOrder == x) {
			return *(arr + x);
		}
		else if(targetOrder >= x){
			*middleCount = 0;
			findMiddle(arr, division, x + 1, (N - x + 1));
			return select(arr, division, x + 1, (x + 1 + 4), (N - x + 1), middleCount, targetOrder);
		}
		else if (targetOrder <= x) {
			*middleCount = 0;
			findMiddle(arr, division, 0, x);
			return select(arr, division, 0, 4, x, middleCount, targetOrder);
		}
	}
	else
	{
		int changeIndex = start / division;
		int middleIndex = start + (end - start) / 2;
		//�ѵ�n�������е���λ����������һ��
		swap(arr, changeIndex, middleIndex);
		//��ǰ�����˼�����λ��
		(*middleCount)++;
		if (start + division < total)
		{
			if (end + division < total)
			{
				return select(arr, division, start + division, end + division,total,middleCount,targetOrder);
			}
			else
			{
				return select(arr, division, start + division, total - 1,total,middleCount,targetOrder);
			}
		}
		else {
			return select(arr, division, end, end,total,middleCount,targetOrder);
		}
	}
}

//���������ÿ�������н�������
void sort(int *arr,int start,int end){
	if (start < end)
	{
		int index = partition(arr,start,end);
		sort(arr,start,index - 1);
		sort(arr,index + 1,end);
	}
}

//����
int partition(int *arr,int start,int end){
	int base = *(arr + start);
	int i = start,j = end;
	while(i < j){
		while(*(arr + j) > base){
			j--;
		}
		
		while(*(arr + i) < base){
			i++;
		}
		swap(arr,i,j);
	}
	*(arr + j) = base;
	return i;
}
//���������е�����Ԫ��
void swap(int *arr,int index1,int index2){
	int temp = *(arr + index1);
	*(arr + index1) = *(arr + index2);
	*(arr + index2) = temp;
}

//��ʾ������ÿ��������
void show(int *arr){
	int i;
	for (i = 0; i < N; i++)
	{
		printf("%-2d ",*(arr + i));
		if((i + 1) % 5 == 0){
			putchar(10);
		}
	}
	putchar(10);
}