#include<stdio.h>
#include<stdlib.h>
/*
	������ܵ���һ��һ��ָ��,�����ݵ�Ҳ��һ��������ָ��,
	�����ͨ���޸ĸ�ָ���ֵ���޸ĵı����Ļ�,Ӧ���ö���ָ�����޸ĸñ�����ֵ.
	�������Ļ��ָ��ָ��20(ʮ������14)�����ַ��λ,�������ʳ�ͻ.
*/
void change(int *p) {
	*p = 20;
}
/*
	��ȷ���޸ķ�ʽ
*/
void correctChange(int **p) {
	**p = 20;
}
void main() {
	int a = 10;
	int b = 20;
	int *p1 = &a;
	int **p2 = &p1;

	//��ָ���������ݵ�ָ��
	printf("&a:%p\n", &a);
	printf("p1:%p\n", p1);
	printf("&p1:%p\n", &p1);
	printf("p2:%p\n", p2);
	printf("*p2:%p\n", *p2);
	printf("&p2:%p\n", &p2);

	//ͨ������ָ���޸���ֵ
	**p2 = b;
	printf("**p2=%d\n",**p2);


	//change(&p1);
	correctChange(&p1);
	printf("*p1=%d\n", *p1);
	system("pause");
}