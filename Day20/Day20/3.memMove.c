#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
void* myMemmove(void *dest,void *src,int size) {
	if (dest == NULL || src == NULL)
	{
		return NULL;
	}
	//����һ���ڴ汣����Ҫ����������
	char *temp = malloc(sizeof(char) * size);
	memcpy(temp, src,size);
	//Ȼ������ʱ�ڴ���������ݽ��и�ֵ
	memcpy(dest, temp, size);
	free(temp);
	return dest;
}
/*
	memcpy��memmove����:
	memcpy:�������ֽڿ���,���Ŀ���ڴ��Դ�ڴ��غ�,�����Ϊδ����
	memmove:�����Ƚ�Դ�ڴ����ݿ�����ȥȻ���ٽ��п���,������غ����,���ܱ�֤Դ�ڴ��ɹ�����
*/
void main() {
	char str1[] = "aabbcc";
	printf("The string: %s\n", str1);
	memcpy(str1 + 2, str1, 4);
	printf("New string: %s\n", str1);

	strcpy_s(str1, sizeof(str1), "aabbcc");   // reset string

	printf("The string: %s\n", str1);
	myMemmove(str1 + 2, str1, 4);
	printf("New string: %s\n", str1);

	system("pause");
}