#include<stdio.h>
#include<stdlib.h>
/*
	��������������г��������,����һ�������ֵ�
*/
char words[] = "abc";
int count = 0;
void show(char *array) {
	for (char *p = array; *p; p++)
	{
		printf("%c ",*p);
	}
	printf("\n");
}
void swap(char *pA,char *pB) {
	char temp = *pA;
	*pA = *pB;
	*pB = temp;
}
/*
	�㷨:����Ҫ���е�����Ϊ"a b c"
		1.abc�����е���a+bc������
		2.bc�����е���b������+c������
		3.c������ֻ��һ��
*/
void arrangement(char *array) {
	if (*array == '\0')
	{
		count++;
		printf("%d:%s\n",count,words);
	}
	for (char *p = array; *p != '\0'; p++)
	{
		swap(p,array);
		arrangement(array + 1);
		swap(p,array);
	}
}
void main() {
	arrangement(words);
	system("pause");
}