#include<stdio.h>
#include<stdlib.h>
/*
	�����Ĳ����и�������.��������,�������͵Ĳ��������βζ���ʵ�εĸ���,�������������������Ч��.
	��Ϊ��ֻ��������������������ֵ,��δ��ʵ������κ�Ӱ��.
*/
void swap(int a,int b) {
	int temp = a;
	a = b;
	b = temp;
}
/*
	Ҫ����⸱�����ƶԽ������Ӱ����Դ���ʵ�εĵ�ַ,��ָ����в���,
*/
void swapByPoint(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
/*
	����û�и�������,��Ϊ��������ø������ƻ��˷��ڴ�ռ�.
*/
void swapForArray(int *array1, int *array2,int length) {
	for (int i = 0; i < 2; i++)
	{
		int temp = *(array1 + i);
		*(array1 + i) = *(array2 + i);
		*(array2 + i) = temp;
	}
}
/*
	��������û�и�������,ָ��Ҳ���и������Ƶ�.
	����ͨ�����н������,ָ����ָ���ֵ��һ����,�����ǲ���ͬһ��ָ����,��Ϊ���ǵ�ַ��һ��.
*/
void swapForPoint(int *p1, int *p2) {
	printf("�����е�ָ��ָ���ֵ:\n");
	printf("p1:%d\n", *p1);
	printf("p2:%d\n", *p2);
	printf("�����е�ָ���ַ:\n");
	printf("p1:%p\n",&p1);
	printf("p2:%p\n", &p2);
}
void main() {
	int a = 10;
	int b = 5;
	//swap(a, b);
	swapByPoint(&a, &b);
	printf("a=%d,b=%d\n",a,b);

	int array1[] = { 1,2 };
	int array2[] = { 3,4 };
	swapForArray(array1, array2, 2);

	printf("array1:");
	for (int i = 0; i < 2; i++)
	{
		printf("%d ",array1[i]);
	}
	printf("\n");
	printf("array2:");
	for (int i = 0; i < 2; i++)
	{
		printf("%d ", array2[i]);
	}
	printf("\n");
	int *p1 = &a;
	int *p2 = &b;
	
	printf("main�е�ָ��ָ���ֵ:\n");
	printf("p1:%d\n", *p1);
	printf("p2:%d\n", *p2);
	printf("main�е�ָ���ַ:\n");
	printf("p1:%p\n", &p1);
	printf("p2:%p\n", &p2);
	printf("\n");

	swapForPoint(p1, p2);

	system("pause");
}