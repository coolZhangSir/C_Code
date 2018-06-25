#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Stack.h"

#define BUFFER_SIZE 150

#define FILE_PATH "C:\\Users\\ZhangHao\\Desktop\\test.c"
//#define FILE_PATH "F:\\Code_Sets\\C_Code\\���������ϰ��\\���������ϰ��"
#define OPEN_FILE_ERROR "�ļ���ʧ��!"
#define FUNCTION_COUNT "��������"

#define BOOL int
#define SIGN_MULTIPLE_COMMENT '*'
#define SIGN_BLOCK '{'
#define NAME_SIZE 80

typedef struct FunctionAnalysis {
	char functionName[NAME_SIZE];
	int codeLineCount;//��������,����ע�ͺͿ���
	struct FunctionAnalysis *next;
}FunctionAnalysis;

typedef struct CodeAnalysis {
	char fileName[NAME_SIZE];
	int codeLineCount;//����������
	int commentLineCount;//ע��������
	int emptyLineCount;//����������
	FunctionAnalysis *functionAnalysis;
}CodeAnalysis;

void inputFileName(char *fileName);
void output(char *content);
BOOL isEmptyLine(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
BOOL isComment(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
BOOL isFunction(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
void isBlock(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
void handleLineString(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);

int skipSpace(char *lineString, int index);
BOOL isLegalIdentifier(char *identifier);
BOOL isLegalFirstCharacter(char character);
BOOL isLegalCharacter(char character);
BOOL copyAndCheckIdentifier(char *buffer,char *source,int *sourceIndex);
BOOL isOperator(char character);
void increaseCodeCount(CodeAnalysis *codeAnalysis, Stack *signStack);