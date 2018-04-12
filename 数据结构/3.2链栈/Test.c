#include "LinkStack.h"
void main() {
	//����init����Ҳ�ǽ�����ΪNULL,���ǻ����ڴ�����ʱ������NULL,����Ұָ������.
	LinkStack stack = NULL;
	init(&stack);
	int flag = 0;
	for (int i = 0; i < 5; i++)
	{
		flag = push(&stack, i);
		if (flag == SUCCESS)
		{
			printf("push %d succeeded!\n",i);
		}
		flag = getTop(stack);
		if (flag >= 0)
		{
			printf("current top element is %d !\n", flag);
		}
	}
	//����ֻ��һ��,����߲����߱����Ĳ�ͬ������
	int length = getLength(stack);
	for (int i = 0; i < length; i++)
	{
		ElemType element = pop(&stack);
		printf("pop %d succeeded!\n", element);
	}

	printf("\npush elements again!\n");
	for (int i = 10; i < 15; i++)
	{
		flag = push(&stack, i);
		if (flag == SUCCESS)
		{
			printf("push %d succeeded!\n", i);
		}
		flag = getTop(stack);
		if (flag >= 0)
		{
			printf("current top element is %d !\n", flag);
		}
	}

	printf("destroy operation:\n");
	//ͨ���ϵ�debug�鿴�ڴ�仯�۲������
	destroy(&stack);
	printf("current size after destroy:%d\n",getLength(stack));
	
	system("pause");
}