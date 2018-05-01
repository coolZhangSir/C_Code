#include "LinkStack.h"
/*
	����ջ����������Ƿ�ƥ�������,���ݼ����֮��stack�Ƿ�Ϊ�����жϸ��ַ����Ƿ���ȷ
*/
void verify(char *signal,LinkStack *stack) {
	char *p = signal;
	while (*p != '\0')
	{
		switch (*p)
		{
		case ')':
			if ((*stack) == NULL || getTop(*stack) != '(')
			{
				push(stack, *p);
			}
			else {
				pop(stack);
			}
			break;
		case ']':
			if ((*stack) == NULL || getTop(*stack) != '[')
			{
				push(stack, *p);
			}
			else {
				pop(stack);
			}
			break;
		default:
			push(stack, *p);
			break;
		}
		
		p++;
	}
}
/*
	����һ����־����,��⵽����ֱ�ӽ�������,����ȴ�ȫ�������
*/
int verifyImprove(char *signal, LinkStack *stack) {
	int errorFlag = 0;
	char *p = signal;
	while (*p != '\0' && errorFlag != 1) {
		switch (*p)
		{
		case '(':
		case '[':
			//�����⵽������ֱ����ջ
			push(stack, *p);
			break;
		case ')':
			if ((*stack) != NULL && getTop(*stack) == '(')
			{
				pop(stack);
			}
			else {
				push(stack, *p);
				errorFlag = 1;
			}
			break;
		case ']':
			if ((*stack) != NULL && getTop(*stack) == '[')
			{
				pop(stack);
			}
			else {
				push(stack, *p);
				errorFlag = 1;
			}
			break;
		}
		p++;
	}
	return errorFlag;
}
void main() {
	char *signal = "([]))(";
	LinkStack stack = NULL;
	init(&stack);

	/*verify(signal, &stack);
	if (stack != NULL)
	{
		printf("\"%s\"��ʽ����\n",signal);
	}
	else {
		printf("\"%s\"��ʽ��ȷ\n", signal);
	}*/

	int flag = verifyImprove(signal, &stack);
	if (flag)
	{
		printf("\"%s\"��ʽ����\n", signal);
	}
	else {
		printf("\"%s\"��ʽ��ȷ\n", signal);
	}
	system("pause");
}