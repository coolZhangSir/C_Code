#include<stdio.h>
#include<stdlib.h>
char* function1() {
	/*
		����ʾ��:str��ջ��
			�������ܷ���ָ��ջ�����ڴ�,��ջ���������ڽ���֮����ڴ�����ᱻ����
		��ȷ����:
			�����Ҫ����һ���ڴ�,Ӧ���ڶ��д����������ݱ������ô����������ַ
			���߷��ش������ĳ����ַ�
	*/
	char str[] = { "china no.1" };
	return str;
}
char* function2() {
	//��ȷ����1:ָ���ַ��������ص�ַ
	//char *str = "china no.1";
	//��ȷ����2:�ڶ��д����ڴ沢���ص�ַ
	char *str = (char *)malloc(sizeof(char) * 11);
	str[0] = 'c';
	str[1] = 'h';
	str[2] = 'i';
	str[3] = 'n';
	str[4] = 'a';
	str[5] = ' ';
	str[6] = 'n';
	str[7] = 'o';
	str[8] = '.';
	str[9] = '1';
	str[10] = '\0';
	return str;
}
int function3() {
	/*
		�����ĸ�������
			�����ķ���ֵ�����ڴ�,������cpu�Ļ�����,���ܶ���ȡ��ַ
	*/
	int a = 5;
	return a;
}
void main() {
	//char *p = function1();
	/*{
		char *p = function2();
		printf("%s\n", p);
		free(p);
	}*/
	{
		int a = function3();
		printf("%d\n",a);
	}
	system("pause");
}