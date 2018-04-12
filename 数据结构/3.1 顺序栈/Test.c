#include "Stack.h"
#include <time.h>
void main(){
	Stack *stack = NULL;
	int i = 0;
	initStack(&stack);

	srand(time(NULL));

	printf("��ջ����:\n");
	for(i = 0;i < stack->maxSize;i++){
		push(stack,rand() % 100 + 1);

		stackTraverse(stack);
	}

	printf("ջ��Ԫ���Ƿ�Ϊ��:%s\n",isStackEmpty(stack)?"��":"�ǿ�");

	printf("ջ��Ԫ�س���:%d\n",getLength(stack));

	printf("��ǰջ��topԪ��:%d\n",getTop(stack));


	printf("\n��ջ����:\n");
	while(stack->top != stack->base){
		printf("��ǰ��ջԪ��:%d\n",pop(stack));
		stackTraverse(stack);
		printf("\n");
	}

	printf("ջ��Ԫ���Ƿ�Ϊ��:%s\n",isStackEmpty(stack)?"��":"�ǿ�");
	printf("ջ��Ԫ�س���:%d\n",getLength(stack));

	printf("\n�ٴν�����ջ����:\n");
	for(i = 0;i < stack->maxSize;i++){
		push(stack,rand() % 100 + 1);

		stackTraverse(stack);
	}

	printf("\nջ��ղ���:\n");
	clearStack(&stack);
	printf("ջ��Ԫ�س���:%d\n",getLength(stack));
	stackTraverse(stack);

	printf("\n�ٴν�����ջ����:\n");
	for(i = 0;i < stack->maxSize;i++){
		push(stack,rand() % 100 + 1);

		stackTraverse(stack);
	}
	printf("����ջ����\n");
	destroyStack(&stack);
	printf("ջ��Ԫ�س���:%d\n",getLength(stack));

	system("pause");
}
