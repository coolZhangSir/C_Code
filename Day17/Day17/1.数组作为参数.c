#include<stdio.h>
#include<stdlib.h>
void function1(int *p,int length) {
	/*
		һά������Ϊ����
			�βο���һ��ָ�����һ��һά����
		ʵ��:��תһ�������������
	*/
	for (int *tail = p + length - 1; p != tail; p++,tail--)
	{
		int temp = *p;
		*p = *tail;
		*tail = temp;
	}
}
void show1(int *p,int length) {
	for (int i = 0; i < length; i++)
	{
		printf("%d ",*(p + i));
	}
	printf("\n");
}
void function2(int (*p)[4],int rows,int n) {
	/*
		��ά������Ϊ����
			�βο��ö�ά�����������ָ��,�����Խ����е�ַͳһ�����һ��ָ����������
			��������һ���ô����ǿ��Զ�ָ̬������,ʾ������:
				void function2(int **p,int row,int column);
				int a[3][4] = {0};
				int *p[3] = {NULL};
				for(int i = 0;i < row;i++){
					p[i] = a + i;
				}
				function2(p,3,4);
			ʵ��:����3��ѧ��,��4���ɼ�,����ƽ�����Լ���n���˵ĳɼ�
	*/
	int scoreOfEachStudent = 0;
	float totalAverage = 0;
	for (int i = 0; i < rows; i++)
	{
		if (n == i) {
			printf("��%d��ѧ���ɼ�:",n);
		}
		scoreOfEachStudent = 0;
		for (int j = 0; j < 4; j++)
		{
			if (n == i) {
				printf("%d ",*(*(p + i) + j));
			}
			scoreOfEachStudent += *(*(p + i) + j);
		}
		if (n == i) {
			printf("\n");
		}
		totalAverage += (scoreOfEachStudent / 4.0f);
	}
	printf("��ƽ����:%.1f\n", totalAverage / 3.0f);
}
void main() {
	int a[] = { 1,2,3,4,5 };
	//function1(a, 5);
	//show1(a, 5);
	int score[3][4] = {89,78,65,71,82,94,93,70,100,98,99,91};
	function2(score, 3, 2);
	system("pause");
}