#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
/*
	ͨ�������̼߳��ӷ���,alloca���������ڴ治��һֱ����,�ᱻ����.
	���Եó�����,alloca������ڴ�����ջ��
*/
void function1() {
	int *p = alloca(sizeof(int) * 10);
	for (int i = 0; i < 10; i++)
	{
		*(p + i) = i + 1;
	}
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", *(p + i));
	}
	printf("\n");

}
void main() {
	function1();
	//����Ӽ����ϵ�鿴�ڴ��еı仯
	printf("\n");
	printf("\n");
	printf("\n");
	system("pause");
}