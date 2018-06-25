//���ļ��ǲ����ļ�,����������ʵ�ֵľ���ϸ���޹�
#include "CourseDesign.h"

CodeAnalysis *initCodeAnalysis(char *fileName);
FILE *initFile(char *fileName);
void process(CodeAnalysis *codeAnalysis, Stack *signStack, FILE *file);
void show(CodeAnalysis *codeAnalysis);
void release(FILE *file, Stack *signStack, CodeAnalysis *codeAnalysis);

void main() {
	//char fileName[20] = { 0 };
	//inputFileName(fileName);
	char fileName[100] = FILE_PATH;

	//��ʼ��
	CodeAnalysis *codeAnalysis = initCodeAnalysis(fileName);
	Stack *signStack = (Stack *)malloc(sizeof(Stack));
	initStack(&signStack);
	FILE *file = initFile(fileName);
	if (file == NULL)
	{
		return;
	}
	
	process(codeAnalysis, signStack, file);

	show(codeAnalysis);

	release(file, signStack, codeAnalysis);

	system("pause");
}

/*
	������,��һ�д���һ��
*/
void process(CodeAnalysis *codeAnalysis,Stack *signStack,FILE *file) {
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

		if (buffer[0] == '\t') {
			printf("");
		}

		handleLineString(buffer, codeAnalysis, signStack);

		if (feof(file))
		{
			break;
		}
	}
}

/*
	��ʼ��CodeAnalysis�ṹ������Ա
*/
CodeAnalysis *initCodeAnalysis(char *fileName) {
	CodeAnalysis *codeAnalysis = (CodeAnalysis *)malloc(sizeof(CodeAnalysis));
	codeAnalysis->codeLineCount = 0;
	codeAnalysis->commentLineCount = 0;
	codeAnalysis->emptyLineCount = 0;
	memset(codeAnalysis->fileName, 0, sizeof(char));
	//�����ļ���
	int i = 0;
	while (fileName[i] != '\0')
	{
		codeAnalysis->fileName[i] = fileName[i];
		i++;
	}
	codeAnalysis->fileName[i] = '\0';

	//��ʼ������ĺ������
	codeAnalysis->functionAnalysis = (FunctionAnalysis *)malloc(sizeof(FunctionAnalysis));
	codeAnalysis->functionAnalysis->codeLineCount = 0;
	memset(codeAnalysis->functionAnalysis->functionName, 0, sizeof(char));

	//��������ͷ�������ͳ�ƺ�������:functionName="��������"
	char functionCountString[9] = FUNCTION_COUNT;
	functionCountString[8] = '\0';
	i = 0;
	while (functionCountString[i] != '\0')
	{
		codeAnalysis->functionAnalysis->functionName[i] = functionCountString[i];
		i++;
	}
	codeAnalysis->functionAnalysis->functionName[i] = '\0';
	codeAnalysis->functionAnalysis->next = NULL;

	return codeAnalysis;
}

FILE *initFile(char *fileName) {
	//ANSI����,ע�ⲻҪ����UTF-8������ı�,������
	FILE *file = fopen(fileName, "r");
	if (file == NULL)
	{
		output(OPEN_FILE_ERROR);
		return NULL;
	}
	return file;
}

/*
	������
*/
void show(CodeAnalysis *codeAnalysis) {
	printf("�ļ���:%s\n", codeAnalysis->fileName);
	printf("����������:%d\n", codeAnalysis->codeLineCount);
	printf("ע��������:%d\n", codeAnalysis->commentLineCount);
	printf("����������:%d\n", codeAnalysis->emptyLineCount);

	printf("\n");
	FunctionAnalysis *next = codeAnalysis->functionAnalysis;
	printf("%s:%d\n", next->functionName, next->codeLineCount);
	next = next->next;
	printf("\n");

	while (next != NULL)
	{
		printf("������:%s\n", next->functionName);
		printf("����������:%d\n", next->codeLineCount);
		printf("\n");
		next = next->next;
	}
}

/*
	�ͷ��ļ���Դ���ڴ�
*/
void release(FILE *file, Stack *signStack, CodeAnalysis *codeAnalysis) {
	fclose(file);
	destroyStack(&signStack);
	FunctionAnalysis *next = codeAnalysis->functionAnalysis->next;
	FunctionAnalysis *current = codeAnalysis->functionAnalysis;
	while (next != NULL)
	{
		free(current);
		current = next;
		next = next->next;
	}
	free(current);
	free(codeAnalysis);

	//�ÿ�,������;ָ��
	file = NULL;
	signStack = NULL;
	current = NULL;
	next = NULL;
	codeAnalysis = NULL;
}