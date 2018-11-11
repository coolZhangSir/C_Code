#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int bool;

void plainMatch();
void plainMatchEnhance();

void main() {
	
	plainMatch();
	plainMatchEnhance();

	system("pause");
}

/*
	ƾ�о�д��,��������ѭ��
*/
void plainMatch() {
	char str1[] = "goodgoogle";
	char str2[] = "google";

	for (int i = 0; str1[i] != '\0'; i++)
	{
		bool flag = TRUE;
		for (int j = 0, k = i; str2[j] != '\0'; j++, k++)
		{
			if (str1[k] == '\0' || str2[j] != str1[k])
			{
				flag = FALSE;
				break;
			}
		}
		if (flag == TRUE)
		{
			printf("���ҳɹ�!,��������ʼ�±�Ϊ%d\n",i);
			return;
		}
	}
	printf("����ʧ��!\n");
}

/*
	���ϵ�˼·ֻ����һ��ѭ��,��Ҫ����i=i-j+1/2�����������ĸ�ֵ����
*/
void plainMatchEnhance() {
	char str1[] = "goodgoogle";
	char str2[] = "google";

	int i = 0;//��������ʼ�±�
	int j = 0;//�Ӵ�����ʼ�±�

	while (str1[i] != '\0' && str2[j] != '\0')
	{
		if (str1[i] == str2[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}

		if (str2[j] == '\0')
		{
			printf("���ҳɹ�!,��������ʼ�±�Ϊ%d\n", i - j);
		}
		else {
			printf("����ʧ��!\n");
		}
}