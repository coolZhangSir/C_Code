#include "CyclicLinkedList.h"

CyclicLinkedList create_CyclicLinkedList() {
	CyclicLinkedList list = malloc(sizeof(struct TagCyclicLinkedList));
	list->node = malloc(sizeof(struct TagCyclicLinkedListNode));
	list->size = 0;
	//������ѭ������,�������Ľ��ָ��ͷ��㱾��
	list->node->next = list->node;

	return list;
}

void insert_CyclicLinkedList(CyclicLinkedList list, int position, CyclicLinkedListNode *node) {
	if (list == NULL || node == NULL)
	{
		return;
	}

	//�Բ���λ�ý�������
	if (position < 0)
	{
		position = 0;
	}

	if (position > list->size)
	{
		position = list->size;
	}

	int i = 0;
	CyclicLinkedListNode *p = list->node;
	while (i < position)
	{
		p = p->next;
		i++;
	}

	node->next = p->next;
	p->next = node;
	list->size++;
}

void removeByPosition_CyclicLinkedList(CyclicLinkedList list, int position) {
	if (list == NULL)
	{
		return;
	}

	if (position < 0 || position > list->size)
	{
		return;
	}

	int i = 0;
	CyclicLinkedListNode *p = list->node;
	while (i < position - 1)
	{
		p = p->next;
		i++;
	}
	CyclicLinkedListNode *removedNode = p->next;
	p->next = removedNode->next;
	free(removedNode);
}

//����������Ҫ�Ƚ��û�ָ����ֵ�����Ǳ�������Ԫ��ֵ,���������ֲ�֪���û�����ʹ�õ���������,������Ҫ�û�����һ���Զ���ıȽϺ���ָ��(������java�ıȽ���(comparator))
void removeByValue_CyclicLinkedLIst(CyclicLinkedList list, CyclicLinkedListNode *targetValue, COMPARATOR comparator) {
	if (list == NULL)
	{
		return;
	}
	
	if (targetValue == NULL)
	{
		return;
	}

	CyclicLinkedListNode *pPrevious = list->node;
	CyclicLinkedListNode *pCurrent = list->node->next;
	int flag = CYCLIC_LINKED_LIST_FALSE;
	
	while (pCurrent != list->node)
	{
		flag = (*comparator)(pCurrent,targetValue);
		if (flag == CYCLIC_LINKED_LIST_TRUE)
		{
			break;
		}
		pPrevious = pCurrent;
		pCurrent = pCurrent->next;
	}
	if (flag == CYCLIC_LINKED_LIST_TRUE)
	{
		pPrevious->next = pCurrent->next;
	}

	free(pCurrent);
}

CyclicLinkedListNode* getNodeByPosition_CyclicLinkedList(CyclicLinkedList list, int position) {
	if (list == NULL)
	{
		return;
	}

	if (position < 0 || position > list->size)
	{
		return;
	}

	int i = 0;
	CyclicLinkedListNode *pCurrent = list->node;
	while (i < position)
	{
		pCurrent = pCurrent->next;
		i++;
	}

	return pCurrent;
}

CyclicLinkedListNode* getNodeByValue_CyclicLinkedList(CyclicLinkedList list, CyclicLinkedListNode *targetValue, COMPARATOR comparator) {
	if (list == NULL)
	{
		return;
	}

	if (targetValue == NULL)
	{
		return;
	}

	if (comparator == NULL)
	{
		return;
	}

	CyclicLinkedListNode *pCurrent = list->node->next;
	int flag = CYCLIC_LINKED_LIST_FALSE;
	while (pCurrent != list->node)
	{
		flag = (*comparator)(pCurrent,targetValue);
		if (flag == CYCLIC_LINKED_LIST_TRUE)
		{
			break;
		}
		pCurrent = pCurrent->next;
	}

	if (flag == CYCLIC_LINKED_LIST_TRUE)
	{
		return pCurrent;
	}
	else
	{
		return NULL;
	}
}

CyclicLinkedListNode* getFirstNode_CyclicLinkedList(CyclicLinkedList list) {
	if (list == NULL)
	{
		return NULL;
	}
	return list->node->next;
}

int getSize_CyclicLinkedList(CyclicLinkedList list) {
	if (list == NULL)
	{
		return -1;
	}
	return list->size;
}

//���ڲ�֪����������,��ӡ����Ҳֻ�����û����ж���,����һ������ָ������ǵ��ü���
void traverse_CyclicLinkedList(CyclicLinkedList list, PRINT print) {
	if (list == NULL)
	{
		return;
	}

	if (print == NULL)
	{
		return;
	}

	CyclicLinkedListNode *pCurrent = list->node->next;
	while (pCurrent != list->node)
	{
		(*print)(pCurrent);
		pCurrent = pCurrent->next;
	}
}

void releaseMemory(CyclicLinkedList list) {
	if (list == NULL)
	{
		return;
	}

	CyclicLinkedListNode *pCurrent = list->node->next;
	CyclicLinkedListNode *pNext = pCurrent->next;

	while (pNext != list->node)
	{
		free(pCurrent);
		pCurrent = pNext;
		pNext = pNext->next;
	}

	//���remove������Ľ�㶼�ͷ����,��ô�����ĵ�ַ������ȵ�,�����ظ��ͷ�
	if (pCurrent != list->node)
	{
		free(list->node);
	}
	free(pCurrent);
	free(list);
}