#include<stdio.h>
#include<stdlib.h>
void function1() {
	/*
	1.ָ�����������������ֵļӼ���������ָ��ļ���,��������û������
	2.ָ��ļ���������ͬ���͵�ָ��
	3.����Ľ��������ָ��֮�������ڴ���,�ټ�ȥsizeof(��ָ����ָ�������)
	*/
	int array[] = { 1,2,3,4,5 };
	int *p1 = &array[1];
	int *p2 = &array[4];
	//p2-p1 = (p2 - p1) / sizeof(int)
	printf("%d\n", (p2 - p1));
}
void function2() {
	/*
	ָ��һ�㲻����ֱ�Ӹ�ֵ,�������Ԥ֪,�����Ѿ�ȷ�������ַ����.
	*/
	int *p = 0x123;
	*p = 10;
	printf("%d\n", *p);
}
void function3() {
	/*
		constָ��
		1.const int *p;
			const��*�������������intʱ,ָ����ָ���ֵ*p���ܱ��޸�,ָ���ֵp�����޸�.
		2.int * const p;
			const��*���ұ�����ָ�����pʱ,ָ����ָ���ֵ*p���Ա��޸�,ָ���ֵp�����޸�.
		3.const int * const p;
			��const�޸�����int��ָ�����pʱ,ָ����ָ���ֵ*p��ָ���ֵp�����ܱ��޸�
		4.������array�ı�����int * const array����
			�������޸���������ָ��,���ǿ����޸�����ָ���ֵ.
		5.constָ���������Ȩ�޿���.
			const int *p����ɶ�����дȨ��.
			int * const p����ɶ�,��д,��������תȨ��
			const int * const p����ɶ�,����д,�Ҳ�����תȨ��
	*/
	int array[] = { 1,2,3 };
	int array2[] = { 4,5,6};

	/*
	const int *p1 = &array;
	//*p1 = 40;
	p1 = &array2;

	for (int i = 0; i < 3; i++)
	{
		printf("%d ", *(p1 + i));
	}
	printf("\n");
	

	int * const p2 = &array;
	*p2 = 40;
	//p2 = &array2;

	for (int i = 0; i < 3; i++)
	{
	printf("%d ", *(p2 + i));
	}
	printf("\n");
	
	
	const int * const p3 = &array;
	//*p3 = 50;
	//p3 = &array2;

	for (int i = 0; i < 3; i++)
	{
		printf("%d ", *(p3 + i));
	}
	printf("\n");
	*/
	
	//array = &array2;
	*array = 60;
	for (int i = 0; i < 3; i++)
	{
		printf("%d ", *(array + i));
	}
	printf("\n");
}
void main() {
	//function1();
	//function2();
	function3();
	system("pause");
}

