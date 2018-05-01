#include "LinkStack.h"
/*
	����:��������ջ,ֱ�ӽ�ͷ�����Ϊջ��,��ȥͷ���
*/

/*
	Note:�����stack���ֻ��Ϊһ��ջ��ָ��Ĵ���,����Ҫ������ռ�,�����˷�һ��ջ�׽��
		���ڼ�ֵ����
*/
STATUS init(LinkStack *stack) {
	(*stack) = NULL;
	return SUCCESS;
}

/*
	Note:
		1.��һ��pushʱ,�����stackֻ��Ϊһ��ָ�����һ�����,����ֱ�ӽ��丳ֵ���½���next
		ѭ����������
		2.��������ջ,�����ж�ջ��
*/
STATUS push(LinkStack *stack, ElemType element) {
	LinkStack newNode = (LinkStack)malloc(sizeof(StackNode));
	newNode->element = element;
	newNode->next = (*stack);
	(*stack) = newNode;
	return SUCCESS;
}

/*
	������ջ����Ҫ�ж������,������Ҫ�п�
*/
ElemType pop(LinkStack *stack) {
	if ((*stack) == NULL)
	{
		printf("The stack is empty!");
		return ERROR;
	}
	else {
		LinkStack topNode = (*stack);
		ElemType result = topNode->element;
		(*stack) = (*stack)->next;
		free(topNode);
		return result;
	}
}
/*
	Note:�п�
*/
ElemType getTop(LinkStack stack) {
	if (stack == NULL)
	{
		printf("The stack is empty!");
		return ERROR;
	}
	else {
		return stack->element;
	}
}
/*
	���ڸýṹ������ʾ����ջ��ͷ���,���ñ��泤����һ����.
	�Լ�������ĳ���Ҳ��O(n)�ĸ��Ӷ�,��ֱ�ӱ�����ȡ��.
*/
int getLength(LinkStack stack) {
	int length = 0;
	while (stack != NULL) {
		length++;
		stack = stack->next;
	}
	return length;
}

/*
	����:��ջ�ڽ������ͷ�,��ջ��ָ��Ϊ��ʱ�����ͷ�
*/
STATUS destroy(LinkStack *stack) {
	if ((*stack) == NULL)
	{
		return SUCCESS;
	}
	else {
		LinkStack tempNode = NULL;
		while ((*stack) != NULL)
		{
			tempNode = (*stack);
			(*stack) = (*stack)->next;
			free(tempNode);
		}
	}
	return SUCCESS;
}