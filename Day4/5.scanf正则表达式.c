#include<stdio.h>
#include<stdlib.h>
/*
	scanf��������ʽû��������,û�д�����ĸ�����ֵķ���,����\\d,\\w��Щ��û�õ�
	��������һ�����ָ�������ʽ��ƥ����ַ���ֹͣ������.
*/
void test1(){
	char str[100] = {0};
	scanf("%[^0-9]",str);
	printf("%s\n",str);
}

void test2(){
	
}
int main(){
	test1();
	return 0;
}