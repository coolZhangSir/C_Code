#include<stdio.h>
#include<stdlib.h>
int main(){
	//puts��gets�����ڴ��ļ����ض�����ض������ļ���
	char str[100] = {0};
	gets(str);
	system(str);
	puts(str);
	char ch = getchar();
	putchar(ch);
	return 0;
}