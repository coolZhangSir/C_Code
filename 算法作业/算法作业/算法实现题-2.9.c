/*
	��������:�����ĺ�ŵ��,��������������.
		1.�����������Ǻ�ɫ,ż������������ɫ
		2.���ƶ���ʱ������������ɫһ�������ӻ����ص�
*/
#define  _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>

int writeInputData(FILE** inputFile, char* inputPath);
int solveProblem(FILE** inputFile, char* inputPath, FILE** outputFile, char* outputPath);
int writeOutputResult(FILE** output, char* outputPath, char *step);
void hano(FILE** outputFile, char* outputPath, int n, char a, char b, char c);
void showDialog(char *inputPath);

void main() {
	char* inputPath = "C:\\Users\\Administrator\\Desktop\\input.txt";
	char* outputPath = "C:\\Users\\Administrator\\Desktop\\output.txt";

	FILE* inputFile = NULL;
	FILE* outputFile = NULL;

	int flag = writeInputData(&inputFile, inputPath);
	if (!flag)
	{
		showDialog(inputPath);
	}
	else {
		fclose(inputFile);
	}

	solveProblem(&inputFile, inputPath, &outputPath, outputPath);

	system("pause");
}

int writeInputData(FILE** inputFile, char* inputPath) {
	//wģʽ����ļ�����������Զ�������Ӧ�ļ�������
	if ((*inputFile = fopen(inputPath, "w")) != NULL)
	{
		char* buffer = "3";
		/*
		sizeof�ؼ��������charָ��Ĵ�С,ָ�붼��4�ֽ�
		strlen����������������ݵĴ�С,������'\0'
		*/
		fwrite(buffer, strlen(buffer), 1, *inputFile);
		return 1;
	}
	else
	{
		return 0;
	}
}

int solveProblem(FILE** inputFile, char* inputPath, FILE** outputFile, char* outputPath) {
	if ((*inputFile = fopen(inputPath, "r")) != NULL)
	{
		char length[10] = { 0 };
		fgets(length, 10, *inputFile);
		int N = 0;
		sscanf(length, "%d", &N);
		hano(outputFile,outputPath,N,'A','C', 'B');
	}
	else {
		return 0;
	}

	return 1;
}
void hano(FILE** outputFile, char* outputPath,int n,char a,char b,char c) {
	if (n == 1) {
		char step[20] = { 0 };
		sprintf(step, "%d %c->%c\n", n, a, c);
		writeOutputResult(outputFile,outputPath,step);
	}
	else {
		hano(outputFile, outputPath, n - 1, a, c, b);
		char step[20] = { 0 };
		sprintf(step, "%d %c->%c\n", n, a, c);
		writeOutputResult(outputFile, outputPath, step);

		hano(outputFile, outputPath, n - 1, b, a, c);
	}
}
int writeOutputResult(FILE** output, char* outputPath,char *step) {
	if ((*output = fopen(outputPath, "a+")) != NULL)
	{
		fwrite(step, strlen(step), 1, *output);
	}
	else {
		return 0;
	}
	
	fclose(*output);
	return 1;
}

void showDialog(char *inputPath) {
	char tip[100] = { 0 };
	sprintf(tip, "Can't open or write on the path:%s", inputPath);
	printf("%s\n", tip);
	MessageBoxA(0, tip, "Tip", 0);
}