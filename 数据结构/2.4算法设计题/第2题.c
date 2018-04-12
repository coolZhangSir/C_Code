/*
	�������ǵݼ�����������ϲ���һ���ǵ�������������.
	Ҫ����������ʹ��ԭ����������Ĵ洢�ռ�,������ռ�������Ĵ洢�ռ�,�����������ظ�������.
*/
#include "LinkList.h"
void initialize(LinkList *list,int *elements,int length) {
	initList(list);
	for (int i = 0; i < length; i++)
	{
		insertByIndex(list,-1,*(elements + i));
	}
}
/*
	����:�ϲ������ǵݼ�����Ϊһ���ǵ���������
	˼·:����Ƚ�,Ȼ�󽫴�Ĳ��뵽ǰ��
	����:�޷���,�����listAΪ�µ�����ͷ���
*/
void merge(LinkList *listA,LinkList *listB) {
	LinkList a = (*listA)->next;
	LinkList b = (*listB)->next;
	LinkList tempNode = NULL;
	LinkList newHead = *listA;
	//�Ͽ���̵Ľ��
	newHead->next = NULL;
	//�ͷŵ�B�ı�ͷ���
	free(*listB);

	while (a != NULL && b != NULL) {
		if (a->data <= b->data)
		{
			tempNode = a;
			a = a->next;
		}
		else {
			tempNode = b;
			b = b->next;
		}

		tempNode->next = newHead->next;
		newHead->next = tempNode;
	}

	while (a != NULL) {
		tempNode = a;
		a = a->next;
		tempNode->next = newHead->next;
		newHead->next = tempNode;
	}

	while (b != NULL) {
		tempNode = b;
		b = b->next;
		tempNode->next = newHead->next;
		newHead->next = tempNode;
	}
}
void main() {
	//��ʼ����������
	LinkList listA;
	int arrayA[] = { 2,4,5,6,7 }; 
	initialize(&listA,arrayA,5);

	LinkList listB;
	int arrayB[] = { 1,2,2,8,9 };
	initialize(&listB,arrayB,5);

	show(listA);
	show(listB);

	printf("after merge:\n");
	merge(&listA,&listB);
	show(listA);

	system("pause");
}