#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
	����C�����ṩ���ļ�����Api����ȡ�ļ��е����ݲ�ɸѡ
*/
void main() {
	char loadPath[100] = { "C:\\Users\\Administrator\\Desktop\\��˵�еĴ�����.txt" };
	char savePath[100] = { 0 };

	char buffer[1024] = { 0 };
	char target[10] = { 0 };

	scanf("%s",target);
	
	sprintf(savePath, "C:\\Users\\Administrator\\Desktop\\%s.txt", target);

	FILE* file = fopen(loadPath, "r");
	FILE* saveFile = fopen(savePath, "w");
	
	int i = 0;
	for (;!feof(file);i++)
	{
		//������������Զ���ȡһ��,��Ҫ�ֶ����ö�ȡ����
		//fread(buffer, sizeof(char), 400, file);
		fgets(buffer, 1024, file);
		char* p = strstr(buffer, target);

		if (p != NULL || i == 0)
		{
			printf("%s\n", buffer);
			fputs(buffer, saveFile);
		}
	}
	//һ��Ҫ�ǵùر��ļ�
	fclose(file);
	fclose(saveFile);
	printf("����%d��\n",i);
	system("pause");
}