#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
/*
	��void*����ת��Ϊchar*����,�������ַ�����
*/
void* myMemcpy(void *dest,void *src,int size) {
	if (dest == NULL || src == NULL)
	{
		return NULL;
	}
	char *dest_temp = dest;
	char *src_temp = src;
	for (int i = 0; i < size; i++)
	{
		*(dest_temp + i) = *(src_temp + i);
	}
	return dest;
}

void main() {
	char *p = "abcd";
	char *str = malloc(sizeof(char) * 5);
	//memcpy(str,p,5);
	myMemcpy(str, p, 5);
	printf("%s\n",str);
	free(str);
	system("pause");
}