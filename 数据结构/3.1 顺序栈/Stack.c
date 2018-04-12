#include "Stack.h"
//����ʹ��ָ����Ը��ݵ�ַ������в���
STATUS initStack(Stack **stack){
	(*stack) = (Stack *)malloc(sizeof(Stack));
	(*stack)->maxSize = SIZE;
	(*stack)->base = (ElemType *)malloc(sizeof(ElemType) * (*stack)->maxSize);
	(*stack)->top = (*stack)->base;

	return SUCCESS;
}
STATUS destroyStack(Stack **stack){
	int i = 0;
	if((*stack) == NULL){
		return ERROR;
	}
	
	//�ռ���ͷ�ֻ�ܴ�����ĵ�ַ��ʼ�ͷ�,���ܴ�������ַ�ͷ�
	free((*stack)->base);
	free((*stack));
	return SUCCESS;
}
STATUS clearStack(Stack **stack){
	if((*stack) == NULL){
		return ERROR;
	}
	(*stack)->top = (*stack)->base;
	return SUCCESS;
}

//�ṹ��Ϊ������������ʹ��ָ�������в������ݣ������������ķ���
int isStackEmpty(Stack *stack){
	if(stack == NULL){
		return ERROR;
	}
	if(stack->top == stack->base){
		return TRUE;
	}else{
		return FALSE;
	}
}
int getLength(Stack *stack){
	return stack->top - stack->base;
}

ElemType getTop(Stack *stack){
	return *(stack->top - 1);
}
STATUS push(Stack *stack,ElemType element){
	if(stack == NULL){
		return ERROR;
	}
	*(stack->top++) = element;
	return SUCCESS;
}
ElemType pop(Stack *stack){
	if(stack == NULL){
		return ERROR;
	}
	return *((stack->top--) - 1);
}

//������ջ,��ʾջ�ڵ�ǰԪ��
STATUS stackTraverse(Stack *stack){
	int i = 0;
	if(stack == NULL){
		return ERROR;
	}
	printf("��ǰջ��Ԫ��:\n");
	for(;(stack->base + i) != stack->top;i++){
		printf("%d, ",*(stack->base + i));
	}
	printf("\n");
	return SUCCESS;
}