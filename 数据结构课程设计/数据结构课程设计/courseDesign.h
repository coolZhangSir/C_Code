//���ļ��洢��Ҫ�Ľṹ��ͷ�������
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Stack.h"
#include "Util.h"

typedef struct FunctionAnalysis {
	//����,������������������ע�ͺͿ���,��������.
	//��������,����ע�ͺͿ���
	int codeLineCount;//��������
	int commentLineCount;//ע��������
	int blankLineCount;//����������
	char functionName[NAME_SIZE];
	struct FunctionAnalysis *next;
}FunctionAnalysis;

typedef struct CodeAnalysis {
	char fileName[NAME_SIZE];
	//����,����������,�ļ����ܵ�����.ԭ���Ĵ���������������ע�ͺͿ���,��¼�����ݵķ����Ͳ��ٸ��Ĵ���,��Ϊ��������=������-������-ע������
	int totalLineCount;//������
	int codeLineCount;//����������
	int commentLineCount;//ע��������
	int blankLineCount;//����������
	FunctionAnalysis *functionAnalysis;
}CodeAnalysis;

//��Ҫ�߼�����
BOOL isEmptyLine(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
BOOL isComment(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
BOOL isFunction(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
void isBlock(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
void handleLineString(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack);
void increaseCodeCount(CodeAnalysis *codeAnalysis, Stack *signStack);
void increaseEmptyLineCount(CodeAnalysis *codeAnalysis, Stack *signStack);
void increaseCommentLineCount(CodeAnalysis *codeAnalysis, Stack *signStack);
void addFunctionNode(CodeAnalysis *codeAnalysis, char *functionName);
void popMultiply(Stack *signStack, int pushCount);
void updateTotalLineCount(CodeAnalysis *codeAnalysis);