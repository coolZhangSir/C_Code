#include "CyclicLinkedList.h"
/*
	��������:�˴�n=8,k=3ʱ,���ʣ��7
	n����Χ��һ��Ȧ��Ȼ���1���α���������k���Ǹ����˳�Ȧ������һ���˼�����1��ʼ������ֱ��ʣ�����һ���ˣ������ʣ�µ��˵ı��
	����:
		1.������
		ÿ��Ԫ������һ����־λ,ÿ����һ���ͽ���flagλ��Ϊ0,����ʱ������Щ�Ѿ����ֵ�Ԫ��,ѭ����ȥ��ok
		2.��ѭ������
		�ҵ�һ��ɾ��һ��,ע��Ҫ����ͷ���
*/

//number of person
#define NUMBER 8
//the interval of numbering each round
#define INTERVAL 3
#define EXIST 1
#define NOT_EXIST 0

typedef struct TagPerson {
	CyclicLinkedListNode *next;
	int index;
	int isExist;
}Person;

void useArray();

void print(CyclicLinkedListNode *node) {
	Person *person = (Person *)node;
	printf("%d ", person->index);
}

int comparator(CyclicLinkedListNode *currentValue, CyclicLinkedListNode *targetValue) {
	Person *current = (Person *)currentValue;
	Person *target = (Person *)targetValue;

	if (current->index == target->index)
	{
		return CYCLIC_LINKED_LIST_TRUE;
	}
	else
	{
		return CYCLIC_LINKED_LIST_FALSE;
	}
}

int main() {

	CyclicLinkedList list = create_CyclicLinkedList();

	for (int i = 0; i < NUMBER; i++)
	{
		Person *person = (Person *)malloc(sizeof(Person));
		person->index = i + 1;
		insert_CyclicLinkedList(list, i, (CyclicLinkedListNode *)person);
	}

	printf("�������:\n");
	traverse_CyclicLinkedList(list, print);

	int interval = 1;
	int i = 0;
	CyclicLinkedListNode *p = list->node->next;
	CyclicLinkedListNode *pTemp = NULL;

	while (getSize_CyclicLinkedList(list) > 1)
	{
		if (interval == INTERVAL)
		{
			interval = 1;
			i++;
			printf("��%d�γ���:%d\n", i, ((Person *)p)->index);

			pTemp = p;
			p = p->next;
			removeByValue_CyclicLinkedLIst(list,pTemp,comparator);

			//����ͷ���
			if (p == list->node)
			{
				p = p->next;
			}
		}
		else
		{
			p = p->next;
			//����ͷ���
			if (p == list->node)
			{
				p = p->next;
			}
			interval++;
		}
	}

	printf("���˶���:%d\n", ((Person *)p)->index);

	system("pause");
	return 0;
}

void useArray() {
	Person persons[NUMBER] = { NULL };


	for (int i = 0; i < NUMBER; i++)
	{
		persons[i].index = i + 1;
		persons[i].isExist = EXIST;
	}

	int currentInterval = 1;
	int size = NUMBER;

	for (int i = 0, j = 0; size != 1; i = (i + 1) % NUMBER)
	{
		if (persons[i].isExist == EXIST)
		{
			if (currentInterval == INTERVAL)
			{
				printf("��%d�γ���:%d\n", j, persons[i].index);
				persons[i].isExist = NOT_EXIST;
				currentInterval = 0;
				j++;
				size--;
			}
			currentInterval++;
		}

	}

	for (int i = 0; i < NUMBER; i++)
	{
		if (persons[i].isExist == EXIST)
		{
			printf("���˶���:%d\n", persons[i].index);
		}
	}
}