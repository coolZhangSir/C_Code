/*
	��֪��������A��B�ֱ��ʾ��������,��Ԫ�ص�������.����㷨,�������A��B�Ľ���,������A������
*/
#include "LinkList.h"
#define N 5
void merge(LinkList *listA, LinkList *listB) {
	LinkList listC = (*listA)->next;
	initList(listA);
	while (listC != NULL) {
		LNode *nodeB = (*listB)->next;
		while (nodeB != NULL) {
			if (listC->data == nodeB->data)
			{
				insertByIndex(listA, -1, nodeB->data);
				(*listB) = nodeB;
				break;
			}
			else if (nodeB->data > listC->data) {//��Ϊ�ǵ���,ֻҪ��һ������A�е�Ԫ�ؼ��������ô�Ѱ��
				break;
			}
			nodeB = nodeB->next;
		}
		listC = listC->next;
	}
}
void main() {
	LinkList listA = NULL;
	initList(&listA);
	for (int i = 0; i < N; i++)
	{
		int element = i + 1;
		insertByIndex(&listA,-1,element);
	}
	show(listA);

	LinkList listB = NULL;
	initList(&listB);
	for (int i = 0; i < N; i++)
	{
		int element = i + 2;
		insertByIndex(&listB, -1, element);
	}
	show(listB);

	merge(&listA, &listB);
	show(listA);

	system("pause");
}