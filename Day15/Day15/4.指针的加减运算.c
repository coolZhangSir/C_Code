#include<stdio.h>
#include<stdlib.h>
void function1(int *p) {
	//*(p + i)�ȼ���p[i]
	printf("*(p + 3)=%d\n",*(p + 3));
	printf("p[3]=%d\n", p[3]);
}
void function2(int *p) {
	//�ȼ���p=p+3,ǰ��3����λ,ָ���4��Ԫ��
	p += 3;
	//*(p++)�ȼ���*(p);p++;��ȡ��ǰp��ֵ,p������,���Ϊ4
	printf("*(p++)=%d\n", *(p++));
	//*p������һ��p������,���Ϊ5
	printf("*p=%d\n", *p);
	//*(++p)�ȼ���p++;*(p + 1);p������,��ȡp��ֵ,���Ϊ6
	printf("*(++p)=%d\n", *(++p));
}
void function3(int *p) {
	/*
		����ı����洢��ջ��,�洢�����ǴӸߵ�ַ���͵�ַ��.
		ջ�ĳ�������.�����Ǹߵ�ַ,�����ǵ͵�ַ.
	*/
	int a = 1, b = 2, c = 3;
	printf("%p\n", &a);
	printf("%p\n", &b);
}
void main() {
	int array[] = { 1,2,3,4,5,6,7,8,9,0 };
	//function1(array);
	//function2(array);
	function3(array);
	system("pause");
}