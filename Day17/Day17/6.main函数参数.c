#include<stdio.h>
#include<stdlib.h>
/*
	argc:��������
	args:����Ĳ���
	void main(int argc,char **args) {
		for (int i = 0; i < argc; i++)
		{
			printf("%s\n",*(args + i));
		}
		system("pause");
	}
*/
void main(int argc,char **args,char **envp) {
	/*
		ѭ����ֹ�������ַ���(*(envp + i))ΪNULL
	*/
	for (int i = 0; *(envp + i) != NULL; i++)
	{
		printf("%s\n",*(envp + i));
	}
	system("pause");
}