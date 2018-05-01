#include "LinkStack.h"
#define N 100
#define BOOL int
/*
	���ú�׺���ʽ����ֵ
	1.����׺���ʽת���ɺ�׺���ʽ
	2.���ú�׺���ʽ����
*/
/*
	�Ƚϱ��ʽ�е��������ջ������������ȼ�, �����������ŵ����,��Ϊ������ֻ�ܱ�����������
*/
BOOL isPrior(char currentOperator, char stackOpeator) {
	if (currentOperator == '*' || currentOperator == '/')
	{
		if (stackOpeator == '+' || stackOpeator == '-' || stackOpeator == '(')
		{
			return 1;
		}
	}
	else if (currentOperator == '+' || currentOperator == '-') 
	{
		if (stackOpeator == '(')
		{
			return 1;
		}
	}
	return 0;
}
/*
	����:
		1.����ǲ�����ֱ�����
		2.�����������"("ֱ�ӽ������ջ
		3.�����������")",�������ջ����������γ�ջ,ֱ����������"("��ջ
		4.�����"+ - * /",���������ջ��Ԫ�رȽ�(���������������������)
			4.1�����ǰ��������ȼ�С�ڻ��ߵ���ջ�������,�����ν����ջ,����󽫸��������ջ
			4.2�����ǰ��������ȼ�����ջ�������,��ֱ�ӽ�ջ
*/
char* infixToPostfix(char *expression) {
	char *p = expression;
	char *postfix = calloc(N, sizeof(char));
	int postfixIndex = 0;
	
	LinkStack operatorStack = NULL;//�����ջ
	init(&operatorStack);

	while (*p != '\0')
	{
		if (*p >= '0' && *p <= '9')
		{
			postfix[postfixIndex++] = *p;
		}
		else if (*p == '(') 
		{
			push(&operatorStack, *p);
		}
		else if (*p == ')')
		{
			while (getTop(operatorStack) != '(')
			{
				char operator = pop(&operatorStack);
				postfix[postfixIndex++] = ' ';
				postfix[postfixIndex++] = operator;
			}
			pop(&operatorStack);//����ջ�е�������
		}
		else if (*p == '+' || *p == '-' || *p == '*' || *p == '/') 
		{
			while (operatorStack != NULL && isPrior(*p,getTop(operatorStack)) == 0)
			{
				postfix[postfixIndex++] = ' ';
				postfix[postfixIndex++] = pop(&operatorStack);
			}
			push(&operatorStack, *p);
		}

		//�������ʱ��һ���ո�����������,�������ƴ�ն�λ�������
		if (*p < '0' || *p > '9')
		{
			if (*p != '(' && *p != ')') {
				postfix[postfixIndex++] = ' ';
			}
		}
		p++;
	}
	while (operatorStack != NULL)
	{
		postfix[postfixIndex++] = ' ';
		postfix[postfixIndex++] = pop(&operatorStack);
	}
	free(operatorStack);
	postfix[postfixIndex] = '\0';
	return postfix;
}
int calculate(LinkStack *stack,char operator) {
	int operandA = 0, operandB = 0,result = 0;
	switch (operator)
	{
	case '+':
		operandB = pop(stack);
		operandA = pop(stack);
		result = operandA + operandB;
		break;
	case '-':
		operandB = pop(stack);
		operandA = pop(stack);
		result = operandA - operandB;
		break;
	case '*':
		operandB = pop(stack);
		operandA = pop(stack);
		result = operandA * operandB;
		break;
	case '/':
		operandB = pop(stack);
		operandA = pop(stack);
		result = operandA / operandB;
		break;
	}
	return result;
}
/*
	����:
		�������Ҷ�ȡ�ַ���,���������ֱ����ջ,����������ֱ��ȡ��ջ��������������������,����������ջ
*/
int parseExpression(char *postfixExpression) {
	char *p = postfixExpression;
	int result = 0;
	LinkStack operandStack = NULL;
	init(&operandStack);
	int operand = 0;

	while (*p != '\0')
	{
		if (*p >= '0' && *p <= '9')
		{
			//��ԭ������
			operand = operand * 10 + *p - '0';
		}
		else if (*p == ' ') {
			//���֮ǰ���ڻ�ԭ������,�����ڽ�����ջ������
			if (operand > 0)
			{
				push(&operandStack, operand);
				operand = 0;
			}
		}
		else if (*p == '+' || *p == '-' || *p == '*' || *p == '/') {
			push(&operandStack, calculate(&operandStack, *p));
		}
		p++;
	}
	result = pop(&operandStack);
	free(operandStack);
	return result;
}
void main() {
	char *expression = "9+(2*3-1)*3+10/2";
	char *postfix = infixToPostfix(expression);
	printf("%s\n",postfix);

	int result = parseExpression(postfix);
	printf("%d\n",result);

	free(postfix);
	system("pause");
}