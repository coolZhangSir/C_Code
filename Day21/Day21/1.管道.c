#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
	ʹ�ùܵ�ִ��cmd�����ȡ���
*/
void main()
{
	FILE* pipe = NULL;
	char buffer[1024] = {0};
	char *result = NULL;
	pipe = _popen("ipconfig","r");
	if(pipe == NULL){
		printf("Ŷ��!\n");
		return;
	}
	while(!feof(pipe)){
		fgets(buffer,1024,pipe);
		result = strstr(buffer,"IPv4 ��ַ");
		//printf("%s\n",buffer);
		if(result != NULL){
			printf("%s\n",result);

		}
	}
	_pclose(pipe);
	system("pause");
}
