#include "LinkStack.h"
/*
	����:����ջ����ÿ�����������,����֮�����γ�ջ���ɵõ���ȷ���
		��ջ�Ļ����Ա��⿼�Ǵ����ȡ��ʱ������±�֮�䴦��
*/
void decimalToOctal(LinkStack *stack,int number) {
	while (number != 0) {
		int remainder = 0;
		remainder = number % 8;
		push(stack, remainder);
		number = number / 8;
	}
}
void main() {
	LinkStack stack = NULL;
	init(&stack);

	int number = 127;
	decimalToOctal(&stack, number);
	while (stack != NULL) {
		printf("%d",pop(&stack));
	}
	printf("\n");
	system("pause");
}