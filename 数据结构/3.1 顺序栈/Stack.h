#include<stdio.h>
#include<stdlib.h>

#define ElemType int
#define SIZE 10
#define STATUS int
#define SUCCESS 2
#define ERROR -1
#define TRUE 1
#define FALSE 0

typedef struct {
	int maxSize;
	ElemType *top;
	ElemType *base;
}Stack;

//����ʹ��ָ����Ը��ݵ�ַ������в���
STATUS initStack(Stack **stack);
STATUS destroyStack(Stack **stack);
STATUS clearStack(Stack **stack);

//�ṹ��Ϊ������������ʹ��ָ�������в������ݣ������������ķ���
int isStackEmpty(Stack *stack);
int getLength(Stack *stack);

ElemType getTop(Stack *stack);
STATUS push(Stack *stack,ElemType element);
ElemType pop(Stack *stack);

STATUS stackTraverse(Stack *stack);