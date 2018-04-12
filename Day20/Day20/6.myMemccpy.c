#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
void *myMemccpy(void *dest,void *src,int val,int maxCount) {
	if (dest == NULL || src == NULL || maxCount == 0)
	{
		return NULL;
	}

	char *destBuffer = dest;
	char *srcBuffer = src;

	for (int i = 0; i < maxCount; i++)
	{
		if (*(destBuffer - 1) == val) {
			return destBuffer;
		}
		*destBuffer = *srcBuffer;
		destBuffer++;
		srcBuffer++;
	}
	return NULL;
}
void main() {
	/*
		��dest�п����ַ�,ֱ�����ַ�C��������ߴﵽmaxCount����
		��C�������򷵻����һ���ַ���ַ,���򷵻�NULL
	*/
	char *p = "I am ZhangHao!";
	char str[15] = { 0 };
	//char *next = _memccpy(str, p, 'H', 15);
	char *next = myMemccpy(str, p, 'H', 15);
	*next = '5';
	printf("%s\n",str);
	system("pause");
}