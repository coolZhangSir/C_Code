#include "Stack.h"
//����ʹ��ָ����Ը��ݵ�ַ������в���
STATUS initStack(Stack **stack){
	(*stack) = (Stack *)malloc(sizeof(Stack));
	(*stack)->maxSize = SIZE;
	(*stack)->top = 0;
	(*stack)->base = (ElemType *)malloc(sizeof(ElemType) * (*stack)->maxSize);
	memset((*stack)->base,0, (*stack)->maxSize);

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
	(*stack)->top = 0;
	return SUCCESS;
}

//�ṹ��Ϊ������������ʹ��ָ�������в������ݣ������������ķ���
int isStackEmpty(Stack *stack){
	if(stack == NULL){
		return ERROR;
	}
	if(stack->top == 0){
		return TRUE;
	}else{
		return FALSE;
	}
}
int getLength(Stack *stack){
	return stack->top - 0;
}

ElemType getTop(Stack *stack){
	return *(stack->base + stack->top - 1);
}
STATUS push(Stack *stack,ElemType element){
	if (stack == NULL) {
		return ERROR;
	}
	if (stack->top > SIZE) {
		printf("Խ����\n");
		return ERROR;
	}
	*(stack->base + stack->top) = element;
	(stack->top)++;
	return SUCCESS;
}
ElemType pop(Stack *stack){
	if(stack == NULL){
		return ERROR;
	}
	if (stack->top <= 0)
	{
		return ERROR;
	}
	(stack->top)--;
	int pop =  *(stack->base + stack->top);
	*(stack->base + stack->top) = '\0';
	return pop;
}

//ȡ��ջ��Ԫ��,�����һ����������,������־��Ȼ��ջ��,���������ж���'{'��'/*'
ElemType getBottom(Stack *stack) {
	if (stack == NULL) {
		return ERROR;
	}
	if (stack->top <= 0)
	{
		return ERROR;
	}
	return stack->base [0];
}

//������ջ,��ʾջ�ڵ�ǰԪ��
STATUS stackTraverse(Stack *stack){
	int i = 0;
	if(stack == NULL){
		return ERROR;
	}
	printf("��ǰջ��Ԫ��:\n");
	for(int i = 0;i != stack->top;i++){
		printf("%d, ",*(stack->base + i));
	}
	printf("\n");
	return SUCCESS;
}