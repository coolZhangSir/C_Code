#include "StackAndQueue.h"

//����ʹ��ָ����Ը��ݵ�ַ������в���
STATUS initStack(Stack **stack){
	(*stack) = (Stack *)malloc(sizeof(Stack));
	(*stack)->maxSize = SIZE;
	(*stack)->top = 0;
	for (int i = 0; i < SIZE; i++)
	{
		(*stack)->base[i] = NULL;
	}
	return SUCCESS;
}
STATUS destroyStack(Stack **stack){
	int i = 0;
	if((*stack) == NULL){
		return ERROR;
	}
	
	//�ռ���ͷ�ֻ�ܴ�����ĵ�ַ��ʼ�ͷ�,���ܴ�������ַ�ͷ�
	free((*stack));
	return SUCCESS;
}
STATUS clearStack(Stack **stack){
	if((*stack) == NULL){
		return ERROR;
	}
	(*stack)->top = 0;
	return SUCCESS;
}

//�ṹ��Ϊ������������ʹ��ָ�������в������ݣ������������ķ���
BOOL isStackEmpty(Stack *stack){
	if(stack == NULL){
		return ERROR;
	}
	if(stack->top == 0){
		return TRUE;
	}else{
		return FALSE;
	}
}

BOOL isStackFull(Stack *stack) {
	if (stack == NULL) {
		return ERROR;
	}

	if (stack->top == SIZE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int getStackLength(Stack *stack){
	return stack->top;
}

ElemType getTop(Stack *stack){
	//�±��0��ʼ,���1
	return *(stack->base + stack->top - 1);
}
STATUS push(Stack *stack,ElemType element){
	if(stack == NULL || element == NULL){
		return ERROR;
	}
	if (isStackFull(stack) == TRUE)
	{
		return FALSE;
	}
	stack->base[stack->top] = element;
	stack->top++;
	return SUCCESS;
}
ElemType pop(Stack *stack){
	if(stack == NULL){
		return NULL;
	}
	if (isStackEmpty(stack) == TRUE)
	{
		return NULL;
	}
	//��ջ��topҪ�Լ�1,�����дҪ������ʱ����,�鷳
	return stack->base[(stack->top--) - 1];
}

//������ջ,��ʾջ�ڵ�ǰԪ��
STATUS traverseStack(Stack *stack){
	if(stack == NULL){
		return ERROR;
	}
	printf("��ǰջ��Ԫ��:\n");
	for (int i = 0; i < stack->top; i++) {
		printf("%d, ",(*(stack->base + i))->data);
	}
	printf("\n");
	return SUCCESS;
}

