/*
	��������������������ϲ�Ϊһ����������������.
	Ҫ����������ʹ��ԭ����������Ĵ洢�ռ�,����ռ�������洢�ռ�,���в���������ظ�Ԫ��
*/
#include "LinkList.h"
//Initialize the link list with the specified elements
void init(LinkList *listA, LinkList *listB) {
	int elementsA[6] = { 0,1,2,3,4,9 };
	int elementsB[6] = { 0,4,5,7,8,10 };

	initList(listA);
	initList(listB);
	//fill the link list with specified elements
	for (int i = 0; i < 6; i++)
	{
		insertByIndex(listA, -1, elementsA[i]);
		insertByIndex(listB, -1, elementsB[i]);
	}
}
//Algorithm implement:merging the two ordered list into a list which is also ordered and its elements are unique
//˼·:��������,��B�е�ÿ��Ԫ�طŵ�A���ҵ����ʵĲ���λ��
//ԭ��:�������������list,��һ�β����λ�ñ�Ȼ�ڱ���֮��,���A��û�ҵ�����λ��,��˵��ʣ�µ�ȫ����A�д�,ֱ�����Ӽ���
LinkList mergeOrderedLists(LinkList listA, LinkList listB) {
	//inspect the list whether it is NULL point or not
	if (listA == NULL || listB == NULL) {
		return NULL;
	}
	LNode *previousA = listA;
	LNode *nodeA = listA->next;
	LNode *nodeB = listB->next;
	LNode *tempNode = NULL;

	while (nodeA != NULL && nodeB != NULL)
	{
		if (nodeB->data < nodeA->data)
		{
			tempNode = nodeB;
			nodeB = nodeB->next;
			tempNode->next = nodeA;
			previousA->next = tempNode;
			//һ����Ԫ�ز���,���ǰһ��Ԫ����Ϊ�²����Ԫ��,������ͣA�����,��Ϊ�п���B�е�ֵ��С��A�е�ǰԪ��
			previousA = tempNode;
		}
		else if(nodeB->data == nodeA->data){
			//������ͬԪ��
			nodeB = nodeB->next;
		}
		else {
			//ֻ��û�ҵ�����λ�ò����ʱ��A�ź���
			previousA = nodeA;
			nodeA = nodeA->next;
		}
		show(listA);
	}
	if (nodeB != NULL)
	{
		//��ʣ��Ԫ��ֱ�ӽӵ���󼴿�
		previousA->next = nodeB;
		show(listA);
	}
	return listA;
}
void main() {
	LinkList listA = NULL;
	LinkList listB = NULL;
	
	init(&listA,&listB);
	
	show(listA);
	show(listB);

	putchar(10);
	LinkList listC = mergeOrderedLists(listA,listB);
	putchar(10);
	show(listC);

	system("pause");
}