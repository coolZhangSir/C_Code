#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
void *myMemchr(void *buffer,int val,int maxCount) {
	if (buffer == NULL || maxCount == 0)
	{
		return NULL;
	}
	char *temp = buffer;
	for (int i = 0; i < maxCount; i++)
	{
		if (*temp == val) {
			return temp;
		}
		temp++;
	}
	return NULL;
}
void main() {
	char *p = "abcde";
	//����:��ָ���ڴ������в���ĳһ�ַ�,�ҵ��������ַ,�Ҳ�������NULL
	//void *address = memchr(p,'w',6);
	void *address = myMemchr(p, 'b', 6);
	printf("%p,%s\n",address,address);
	system("pause");
}