#include<stdio.h>
#include<stdlib.h>
/*
	1.ָ���������
	a�൱��һ��������int *��ָ��,ָ��һ��������Ԫ��,������һ�����ָ��,ʹ��aʱ�൱����&a[0],��һ��Ԫ��Ϊ��λ,��+1�൱����ǰ��һ��Ԫ��.
	&a��һ������ָ��int *[5],ָ�����һ������Ŀ�ʼ��ַ,����������Ϊ��λ,+1�൱�ڿ��һ������.
	sizeof(*a)�ȼ���int����Ԫ�صĴ�С
	sizeof(*&a)�ȼ���sizeof(*(&a)),��ǰ��˵��&a��һ������ָ��,�������С��������Ĵ�С
	sizeof(a)�ȼ���sizeof(*(&a)),ͬ��.*�ſ���ȡ�����ʹ�С
*/
void function1() {
	int a[] = { 1,2,3,4,5 };
	printf("a = %p,a + 1 = %p\n", a, a + 1);
	printf("&a = %p,&a + 1 = %p\n", &a, &a + 1);

	printf("sizeof(a) = %d\n", sizeof(a));
	printf("sizeof(*a) = %d\n", sizeof(*a));
	printf("sizeof(*&a) = %d\n", sizeof(*&a));
}
/*
	ʵս1:��ת����
*/
void reverse(int *p,int length) {
	int *head = p;
	int *tail = p + (length - 1);
	while(head < tail)
	{
		int temp = *head;
		*head = *tail;
		*tail = temp;
		head++;
		tail--;
	}
}
/*
	ʵս2:ʵ��strcopy
*/
void* strcopy(char *source,char *destination,int length) {
	if (*source == NULL || *destination == NULL) {
		return source;
	}
	for (int i = 0; i < length; i++) {
		*(source + i) = *(destination + i);
	}
	return source;
}
void show(int *p) {
	for (int i = 0; i < 5; i++)
	{
		printf("%d ",*(p + i));
	}
	printf("\n");
}
void main() {
	//function1();
	int a[] = { 1, 2, 3, 4, 5 };
	reverse(a,5);
	show(a);
	char ch[50] = {"cunzhang is great!"};
	/*
		���ﴫ�ݵ���Ҫ���޸ĵ�source�������ַ�������ָ��,����:
		char *p = "xxxx";������char a[N]����.
		��Ϊ*p = "xxx"�������Ǵ������ĳ���,ֻ�ܶ������޸�
	*/
	char *p = strcopy(ch, "expert", 6);
	printf("%s\n",p);
	system("pause");
}