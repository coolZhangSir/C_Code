#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
void main() {
	char url[100] = "https://www.bilibili.com/video/av6538245/?p=\n";
	char buffer[100] = { 0 };
	printf("������Ҫ���ɵ�����,���ı���ɾȥ,��:\n");
	printf("");
	gets(url);

	int start = 0,end = 0;
	printf("��ʼֵ:\n");
	scanf("%d",&start);

	printf("����ֵ:\n");
	scanf("%d", &end);

	for (int i = start; i <= end; i++)
	{
		sprintf(buffer,"%s%d",url,i);
		printf("%s\n",buffer);
	}

	system("pause");
}