#include<stdio.h>
#include<stdlib.h>
#define M 20
/*
	��ֵ���ҷ�:
		�������ȽϾ��ȵ�������,��ֵ���ұȶ��ַ�����Ҫ��.
	ԭ��:
		�������ȽϾ��ȵ�������,����Ҫ���ҵ�ֵΪtarget,����:
		target - start      target - a[start]
		����������������������������  =  ����������������������������������������
		   end - start      a[end] - a[start]

		target = 
		start + (end - start) * (target - a[start]) / 
		(a[end] - a[start])
*/
void insertSearch(int a[20], int target) {
	int start = 0;
	int end = 20 - 1;
	int index = -1;
	int middle = 0;
	int count = 0;

	while (start <= middle) {
		middle = start + (end - start) * 1.0 *
			(target - a[start]) /
			(a[end] - a[start]);
		
		if (target == a[middle]) {
			index = middle;
			break;
		}
		else if (target > a[middle]) {
			start = middle + 1;
			
		}
		else if (target < a[middle]) {
			end = middle - 1;
		}
		count++;
	}

	if (index != -1) {
		printf("�ҵ���,�ǵ�%d����,����%d��\n", index + 1, count);
	}
	else {
		printf("�Ҳ���\n");
	}
}
/*
	���ַ���ԭ����ͨ���ȶ�Ŀ��ֵ���м�ֵ�Ĵ�С��ϵ,һ��ȥ��һ��ĳ���,��߲���Ч��
*/
void binarySearch(int a[20],int target) {
	int start = 0;
	int end = 20 - 1;
	int middle = (end - start) / 2;
	int index = -1;
	int count = 0;

	while (start <= end) {
		if (a[middle] == target) {
			index = middle;
			break;
		}
		else if (target > a[middle]) {
			start = middle + 1;
			middle = (end - start) / 2;
		}
		else if (target < a[middle]) {
			end = middle - 1;
			middle = (end - start) / 2;
		}

		count++;
	}
	
	if (index != -1) {
		printf("�ҵ���,�ǵ�%d����,����%d��\n",index + 1,count);
	}
	else {
		printf("�Ҳ���\n");
	}
}
void main() {
	int a[20] = { 0 };
	for (int i = 0; i < 20; i++) {
		a[i] = i + 1;
	}

	//binarySearch(a,5);
	insertSearch(a,5);
	getchar();
}