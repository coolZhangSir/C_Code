#include <stdlib.h>
#include <stdio.h>
void main1() {
	/*����,ָ�����ʹ���ĵ�ַ,����ֵ.�����һ��ֵ��ֵ��ָ��,�ڶ�����в�����ʱ��Ὣ��ֵ��Ϊ��ַ���в���,����õ�ַ��������������ʹ�õ�,��������ж��쳣
	int *p = 10;
	*p = 100;
	printf("%d\n",*p);
	getchar();
	*/
}
//һ��ָ��
void main2(){
	int a = 3;
	int *p = &a;
	*p = 10;

	printf("%d\n",a);
	getchar();
}
//����ָ��
void main() {
	int a = 3;
	int b = 5;

	//��ָ��pָ�����a
	int *p = &a;

	/*
		�ö���ָ��p2ָ��һ��ָ��p,��*p2 = p,**p2 = a
	*/
	int **p2 = &p;
	printf("%p,%p\n%p,%p,%p\n",&a,p,&p,p2,*p2);

	**p2 = 20;

	*p2 = &b;
	*p = 10;
	
	printf("%d,%d\n",a,b);
	getchar();
}