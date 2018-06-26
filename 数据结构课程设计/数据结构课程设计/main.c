//���ļ��ǲ����ļ�,����������ʵ�ֵľ���ϸ���޹�
#include "CourseDesign.h"

CodeAnalysis *initCodeAnalysis(char *fileName);
FILE *initFile(char *fileName);
void process(CodeAnalysis *codeAnalysis, Stack *signStack, FILE *file);
void showEnglish(CodeAnalysis *codeAnalysis);
void showChinese(CodeAnalysis *codeAnalysis);
void release(FILE *file, Stack *signStack, CodeAnalysis *codeAnalysis);
int calculate(int divide, int divided);
float calculateAverage(CodeAnalysis *codeAnalysis);
char evaluateCodeStyle(int codeLine, char *evaluate);
char evaluateCommentStyle(int commentRate, char *evaluate);
char evaluateEmptyLineStyle(int emptyLineRate,char *evaluate);

void main() {
	//��ʼ��
	system("color F2");
	char fileName[BUFFER_SIZE] = { 0 };
	FILE *file = NULL;
	while (file == NULL)
	{
		//inputFileName(fileName);
		sprintf(fileName, "%s", FILE_PATH);
		file = initFile(fileName);
	}

	CodeAnalysis *codeAnalysis = initCodeAnalysis(fileName);
	Stack *signStack = (Stack *)malloc(sizeof(Stack));
	initStack(&signStack);
	
	process(codeAnalysis, signStack, file);

	showEnglish(codeAnalysis);

	printf("\n\n�������İ�������!\n\n");

	showChinese(codeAnalysis);

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
	divide:����
	divided:������
*/
int calculate(int divide,int divided) {
	return (int)(divide * 1.0 / divided * 100);
}

/*
	�����ܿ������˻�
*/
void showChinese(CodeAnalysis *codeAnalysis) {
	printf("\n");
	printf("\"%s\"�ļ��ķ����������:\n", codeAnalysis->fileName);
	printf("\n");
	printf("\t%-8s:%d\n", "��������", codeAnalysis->codeLineCount);
	printf("\t%-8s:%d\n", "ע������", codeAnalysis->commentLineCount);
	printf("\t%-8s:%d\n", "������ ", codeAnalysis->emptyLineCount);
	printf("\t\n");
	printf("\t%s  %s  %s\n", "�������", "ע�ͱ���", "���б���");
	printf("\t%s  %s  %s\n", "========", "======== ", "========");
	int pureCodeLine = codeAnalysis->codeLineCount - codeAnalysis->commentLineCount - codeAnalysis->emptyLineCount;
	int emptyLineRate = calculate(codeAnalysis->emptyLineCount, codeAnalysis->codeLineCount);
	int commentRate = calculate(codeAnalysis->commentLineCount, codeAnalysis->codeLineCount);

	printf("\t%-2d%%        %-2d%%       %-2d%%\n\n", calculate(pureCodeLine, codeAnalysis->codeLineCount),
		commentRate, emptyLineRate);

	printf("��������������:\n\n");
	FunctionAnalysis *next = codeAnalysis->functionAnalysis;
	printf("\t%s:%d\n", next->functionName, next->codeLineCount);
	next = next->next;
	printf("\n");

	while (next != NULL)
	{
	printf("\t������:%s\n", next->functionName);
	printf("\t����������:%d\n", next->codeLineCount);
	printf("\n");
	next = next->next;
	}
}

/*
	�������ʾ���Ľ��
*/
void showEnglish(CodeAnalysis *codeAnalysis) {
	printf("\n");
	printf("The results of analysing program file \"%s\":\n", codeAnalysis->fileName);
	printf("\n");
	printf("\t%-18s:%d\n","Lines of code",codeAnalysis->codeLineCount);
	printf("\t%-18s:%d\n", "Lines of comments",codeAnalysis->commentLineCount);
	printf("\t%-18s:%d\n", "Blank lines",codeAnalysis->emptyLineCount);
	printf("\t\n");
	printf("\t%s  %s  %s\n", "Code", "Comment", "Space");
	printf("\t%s  %s  %s\n", "====", "=======", "=====");
	
	int pureCodeLine = codeAnalysis->codeLineCount - codeAnalysis->commentLineCount - codeAnalysis->emptyLineCount;
	int emptyLineRate = calculate(codeAnalysis->emptyLineCount, codeAnalysis->codeLineCount);
	int commentRate = calculate(codeAnalysis->commentLineCount, codeAnalysis->codeLineCount);
	
	printf("\t%-2d%%   %-2d%%      %-2d%%\n", calculate(pureCodeLine, codeAnalysis->codeLineCount),
		commentRate, emptyLineRate);
	printf("\n");
	printf("\tThe program includes %d functions.\n", codeAnalysis->functionAnalysis->codeLineCount);

	printf("\tThe average lengths of a section of code is %.1f lines.\n", calculateAverage(codeAnalysis));
	printf("\n");

	char evaluate[10] = { 0 };
	char grade = evaluateCodeStyle(pureCodeLine,evaluate);
	printf("\tGrade %C: %s routine size style.\n", grade, evaluate);
	
	memset(evaluate, 0, sizeof(char));
	grade = evaluateCommentStyle(commentRate, evaluate);
	printf("\tGrade %C: %s commenting style.\n", grade, evaluate);
	
	memset(evaluate, 0, sizeof(char));
	grade = evaluateEmptyLineStyle(emptyLineRate, evaluate);
	printf("\tGrade %C: %s empty line style.\n", grade, evaluate);
	printf("\n");
}

/*
	�������к�����ƽ������
*/
float calculateAverage(CodeAnalysis *codeAnalysis){
	int functioncount = codeAnalysis->functionAnalysis->codeLineCount;
	int sumOfCodeLine = 0;
	FunctionAnalysis *next = codeAnalysis->functionAnalysis->next;
	while (next != NULL)
	{
		sumOfCodeLine += next->codeLineCount;
		next = next->next;
	}
	return (float)(sumOfCodeLine * 1.0 / functioncount);
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

char evaluateCodeStyle(int codeLine, char *evaluate) {
	if (codeLine >= 10 && codeLine <= 15)
	{
		sprintf(evaluate,"%s",EVALUATE_EXCELLENT);
		return 'A';
	}
	else if ((codeLine >= 8 && codeLine <= 9) || (codeLine >= 16 && codeLine <= 20))
	{
		sprintf(evaluate, "%s", EVALUATE_AWSOME);
		return 'B';
	}
	else if ((codeLine >= 5 && codeLine <= 7) || (codeLine >= 21 && codeLine <= 24))
	{
		sprintf(evaluate, "%s", EVALUATE_GREATE);
		return 'C';
	}
	else if (codeLine < 5 || codeLine > 24)
	{
		sprintf(evaluate, "%s", EVALUATE_GOOD);
		return 'D';
	}
	else
	{
		//���������ʵ����D,���ǻ���Ҫ�����ϵ�����д����
		sprintf(evaluate, "%s", EVALUATE_GOOD);
		return 'D';
	}
}
char evaluateCommentStyle(int commentRate, char *evaluate) {
	if (commentRate >= 15 && commentRate <= 25)
	{
		sprintf(evaluate, "%s", EVALUATE_EXCELLENT);
		return 'A';
	}
	else if ((commentRate >= 10 && commentRate <= 14) || (commentRate >= 26 && commentRate <= 30))
	{
		sprintf(evaluate, "%s", EVALUATE_AWSOME);
		return 'B';
	}
	else if ((commentRate >= 5 && commentRate <= 9) || (commentRate >= 31 && commentRate <=	35))
	{
		sprintf(evaluate, "%s", EVALUATE_GREATE);
		return 'C';
	}
	else if (commentRate < 5 || commentRate > 35)
	{
		sprintf(evaluate, "%s", EVALUATE_GOOD);
		return 'D';
	}
	else
	{
		//���������ʵ����D,���ǻ���Ҫ�����ϵ�����д����
		sprintf(evaluate, "%s", EVALUATE_GOOD);
		return 'D';
	}
}
char evaluateEmptyLineStyle(int emptyLineRate, char *evaluate) {
	if (emptyLineRate >= 15 && emptyLineRate <= 25)
	{
		sprintf(evaluate, "%s", EVALUATE_EXCELLENT);
		return 'A';
	}
	else if ((emptyLineRate >= 10 && emptyLineRate <= 14) || (emptyLineRate >= 26 && emptyLineRate <= 30))
	{
		sprintf(evaluate, "%s", EVALUATE_AWSOME);
		return 'B';
	}
	else if ((emptyLineRate >= 5 && emptyLineRate <= 9) || (emptyLineRate >= 31 && emptyLineRate <=	35))
	{
		sprintf(evaluate, "%s", EVALUATE_GREATE);
		return 'C';
	}
	else if (emptyLineRate < 5 || emptyLineRate > 35)
	{
		sprintf(evaluate, "%s", EVALUATE_GOOD);
		return 'D';
	}
	else
	{
		//���������ʵ����D,���ǻ���Ҫ�����ϵ�����д����
		sprintf(evaluate, "%s", EVALUATE_GOOD);
		return 'D';
	}
}