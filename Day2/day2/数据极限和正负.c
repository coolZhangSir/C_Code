#include<stdio.h>
#include<limits.h>	//����ͷ�ļ�

int main() {
	int max = INT_MAX;	//int���������Сֵ�ĺ궨��
	int min = INT_MIN;

	/*
		ÿ�����͵Ĵ洢��ʽ����һ���ļ���,�������Խ��,�ͻᵼ�½��������
		����:һ���ֽ�������+1��Ϊ0
			1111 1111
			+		1
		   10000 0000(����Խ���1)
		    =		0
	*/

	printf("%d,%d\n",max,min);
	getchar();
	return 0;
}