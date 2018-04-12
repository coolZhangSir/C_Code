/*��������
	��������:��������N��Ԫ�صĶ��ؼ���S,ÿ��Ԫ����S�г��ֵĴ�����Ϊ��Ԫ�ص�����.
			���ؼ�S����������Ԫ�س�Ϊ����
	�㷨���:���ڸ�������N����Ȼ����ɵĶ��ؼ�S,����S������������
	��������:�����������ļ���Ϊinput.txt���ı��ļ��ṩ.�ļ��ĵ�һ��Ϊ���ؼ���Ԫ�ظ���n
			�ڽ�������n����,ÿ����һ����Ȼ��
	������:��������������ļ�output.txt.����ļ�������,��1��������,��2��������
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>

int writeInputData(FILE** inputFile, char* inputPath);
int solveProblem(FILE** inputFile, char* inputPath, int* max, int* count);
int writeOutputResult(FILE** output, char* outputPath, int max, int count);
void showDialog(char *inputPath);
void showArr(int *arr, int n);

void main() {
	char* inputPath = "C:\\Users\\Administrator\\Desktop\\input.txt";
	char* outputPath = "C:\\Users\\Administrator\\Desktop\\output.txt";
	
	FILE* inputFile = NULL;
	FILE* outputFile = NULL;
	
	int max = 0;
	int count = 0;

	int flag = writeInputData(&inputFile, inputPath);
	if (!flag)
	{
		showDialog(inputPath);
	}
	else {
		fclose(inputFile);
	}

	flag = solveProblem(&inputFile,inputPath,&max,&count);
	if (!flag)
	{
		showDialog(inputPath);
	}
	else {
		fclose(inputFile);
	}

	flag = writeOutputResult(&outputFile, outputPath, max, count);
	if (!flag)
	{
		showDialog(outputPath);
	}
	else {
		fclose(outputFile);
	}
	system("pause");
}

int writeInputData(FILE** inputFile,char* inputPath) {
	//wģʽ����ļ�����������Զ�������Ӧ�ļ�������
	if ((*inputFile = fopen(inputPath, "w")) != NULL)
	{
		char* buffer = "6\n1\n2\n2\n2\n3\n5\n";
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
/*
	max:�����
	count:���ֵ�������
*/
int solveProblem(FILE** inputFile,char* inputPath,int* max,int* count) {
	if ((*inputFile = fopen(inputPath,"r")) != NULL)
	{
		char length[10] = { 0 };
		fgets(length, 10, *inputFile);
		int N = 0;
		sscanf(length,"%d",&N);
		int* data = (int*)(malloc(sizeof(int) * N));
		char c = 0;
		for(int i = 0;(c = fgetc(*inputFile)) != EOF;)
		{
			if (c != '\n') {
				data[i] = c - 48;
				i++;
			}
		}
		//��һ��Ԫ�������ݸ���,����ͳ��
		int* statistical = (int*)(malloc(sizeof(int) * (N - 1)));
		for (int i = 1; i < N; i++)
		{
			int count = 0;
			for (int j = 1; j < N; j++)
			{
				if (data[i] == data[j])
				{
					count++;
				}
			}
			statistical[i - 1] = count;
		}
		int maxIndex = 0;
		for (int i = 0; i < N - 1; i++)
		{
			if (statistical[i] >= *count)
			{
				*count = statistical[i];
				maxIndex = i;
			}
		}
		//����statistical��data������һ��Ԫ�ظ���,������Ҫ��1
		*max = data[maxIndex + 1];
		
		free(data);
		free(statistical);
	}
	else {
		return 0;
	}

	return 1;
}

int writeOutputResult(FILE** output,char* outputPath,int max,int count) {
	if ((*output = fopen(outputPath,"w")) != NULL)
	{
		char result[10] = { 0 };
		sprintf(result,"%d\n%d\n",max,count);
		fwrite(result,strlen(result),1,*output);
	}
	else {
		return 0;
	}
	return 1;
}

void showDialog(char *inputPath) {
	char tip[100] = { 0 };
	sprintf(tip, "Can't open or write on the path:%s", inputPath);
	printf("%s\n", tip);
	MessageBoxA(0, tip, "Tip", 0);
}

void showArr(int *arr,int n) {
	for (int i = 0; i < n; i++)
	{
		printf("%d ",*(arr + i));
	}
	putchar(10);
}