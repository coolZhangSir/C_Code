#include "courseDesign.h"

void main() {
	CodeAnalysis *codeAnalysis = (CodeAnalysis *)malloc(sizeof(CodeAnalysis));
	codeAnalysis->codeLineCount = 0;
	codeAnalysis->commentLineCount = 0;
	codeAnalysis->emptyLineCount = 0;
	memset(codeAnalysis->fileName,0,sizeof(char));
	codeAnalysis->functionAnalysis = (FunctionAnalysis *)malloc(sizeof(FunctionAnalysis));
	codeAnalysis->functionAnalysis->codeLineCount = 0;
	memset(codeAnalysis->functionAnalysis->functionName, 0, sizeof(char));
	
	char functionCountString[9] = FUNCTION_COUNT;
	functionCountString[8] = '\0';
	{
		int i = 0;
		while (functionCountString[i] != '\0')
		{
			codeAnalysis->functionAnalysis->functionName[i] = functionCountString[i];
			i++;
		}
		codeAnalysis->functionAnalysis->functionName[i] = '\0';
	}
	codeAnalysis->functionAnalysis->next = NULL;
	
	Stack *signStack = (Stack *)malloc(sizeof(Stack));
	initStack(&signStack);
	
	//char fileName[20] = { 0 };
	//inputFileName(fileName);
	char fileName[100] = FILE_PATH;
	FILE *file = NULL;
	//ANSI����,ע�ⲻҪ����UTF-8������ı�,������
	file = fopen(fileName,"r");
	if (file == NULL)
	{
		output(OPEN_FILE_ERROR);
		return;
	}
	
	/*
	�����ж��Ƿ����ļ�β�ķ�ʽ�ڴ��ڴ���ģ���Ϊfgets�����������س���\r'�����صģ������ڶ������һ��ʱ��
	�����ļ�ָ�벢û��ָ���ļ�β������ָ��\r'������feof ��Ȼ����0���ļ���û���� ����������ʱoperations���ǻ�ִ��
	while (!feof(fp))
	{
		fgets(temp, 100, fp);
		Operation(temp);
	}
	Ӧ���޸�Ϊ����������ʽ:
	*/
	char buffer[BUFFER_SIZE] = { 0 };
	while (1) {
		fgets(buffer, BUFFER_SIZE, file);
		//����ʼ
		//output(buffer);

		if (buffer[0] == '\t') {
			printf("");
		}
		handleLineString(buffer, codeAnalysis, signStack);
		
		if (feof(file))
		{
			break;
		}
	}

	printf("�ļ���:%s\n",codeAnalysis->fileName);
	printf("����������:%d\n",codeAnalysis->codeLineCount);
	printf("ע��������:%d\n", codeAnalysis->commentLineCount);
	printf("����������:%d\n", codeAnalysis->emptyLineCount);
	
	printf("\n");
	FunctionAnalysis *next = codeAnalysis->functionAnalysis;
	printf("%s:%d\n", next->functionName,next->codeLineCount);
	next = next->next;
	printf("\n");
	
	while (next != NULL)
	{
		printf("������:%s\n",next->functionName);
		printf("����������:%d\n", next->codeLineCount);
		printf("\n");
		next = next->next;
	}

	fclose(file);
	destroyStack(&signStack);
	next = codeAnalysis->functionAnalysis->next;
	FunctionAnalysis *current = codeAnalysis->functionAnalysis;
	while (next != NULL)
	{
		free(current);
		current = next;
		next = next->next;
	}
	free(current);
	current = NULL;
	next = NULL;
	free(codeAnalysis);
	system("pause");
}