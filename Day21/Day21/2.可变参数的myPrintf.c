#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
/*
	printf()�����ɽ��ܿɱ����,��Ҫ�õ�stdarg.hͷ�ļ�.
	ͨ����ʹ��varϵ�к�������ȡ���������ݽ����Ŀɱ����
*/
/*
	java�еĿɱ������..
	C�����еĿɱ������...
*/
void myPrintf(char *format,...) {
	//��ſɱ�����е����в������ַ�ָ��
	va_list ap = NULL;
	//��ʼ������ָ��ɱ�����б��еĵ�һ������,��һ����list����,�ڶ����ǿɱ����ǰһ�������ĵ�ַ
	//һ����...ǰ��һ��
	va_start(ap,format);
	//�����������޷�ͨ��������ȡ��,�����ַ�����ȡ
	//1.ͨ������ָ���ɱ��������
	//2.�Լ�ͨ��ÿ������ͳ��,��������ǰ���и�ʽ���Ʒ�,���ǿ���ͨ��������ʽ���Ʒ�ֱ��\0
	//3.va_arg��ͨ���ڶ�������(ָ���Ĳ�������)����һ����Ӧ���͵�ֵ
	int integer = 0;
	char *str = NULL;
	float real = 0.0f;
	while (1) {
		char c = *(format++);
		if (c == '%')
		{
			c = *(format++);
			switch (c)
			{
			case 'd':
				integer = va_arg(ap,int);
				putchar('0' + integer);
				break;
			case 's':
				str = va_arg(ap, char*);
				puts(str);
				break;
			case 'f':
				real = va_arg(ap,double);
				//����֮ǰ��ftoa��ӡС��
				printf("%f",real);
				break;
			default:
				break;
			}
		}
		else
		{
			putchar(c);
			if (c == '\0') {
				va_end(ap);
				break;
			}
		}
	}
}
void main() {
	int a = 1;
	char *b = "just a test!";
	double c = 3.14;
	printf("a=%d,b=%s,c=%f\n",a,b,c);
	myPrintf("a=%d,b=%s,c=%f\n", a, b, c);
	system("pause");
}