#include "LinkList.h"

void createListWithHead(LinkList *list,int n){
	//��������ʼ��ͷ���
	(*list) = (LinkList)malloc(sizeof(LNode));
	(*list)->data = 0;
	(*list)->next = (*list);
	(*list)->previous = (*list);
	//��ʾ��ǰԪ��,��������next��previousԪ��,�������������֮�����Ԫ��
	LNode *p = (*list);
	//ÿ�β������ʱ���
	LNode *tempNode = NULL;
	for (int i = 0; i < n; i++)
	{
		//�ȸ㶨��Ԫ�ص�ǰ���ͺ��
		tempNode = malloc(sizeof(LNode));
		tempNode->data = i;
		tempNode->next = p->next;
		tempNode->previous = p;
		//�㶨p->next->previous
		p->next->previous = tempNode;
		//���㶨p->next,ȷ��֮ǰ�����ù�ϵ������
		p->next = tempNode;
		p = tempNode;
	}
}

void initList(LinkList *list){
	(*list) = (LinkList)malloc(sizeof(LNode));
	(*list)->data = 0;
	(*list)->next = (*list);
	(*list)->previous = (*list);
}

STATUS destroyList(LinkList *linkList){
	LNode *p = (*linkList);
	LNode *q = (*linkList)->next;
	if((*linkList) == NULL){
		return ERROR;
	}
	while(q != (*linkList)){
		//�Ƚ�q����һ��������p��
		p = q->next;
		//ɾ����ǰqָ����Ǹ�
		free(q);
		//p�б�������һ��,���԰�p��q,����ɾ��
		q = p;
	}
	//��ͷ������һ����Ϊͷ���
	(*linkList)->data = 0;
	(*linkList)->next = (*linkList);
	return SUCCESS;
}

STATUS clearList(LinkList *linkList){
	LNode *node = (*linkList)->next;
	if((*linkList) == NULL){
		return ERROR;
	}
	
	while(node != (*linkList)){
		node->data = 0;
		node = node->next;
	}
	return SUCCESS;
}

STATUS isEmpty(LinkList linkList){
	LNode *node = linkList->next;
	if(linkList == NULL){
		return ERROR;
	}
	
	if(node == linkList){
		return TRUE;
	}
	return FALSE;
}

int getLength(LinkList linkList){
	LNode *node = linkList->next;
	int length = 0;
	if(linkList == NULL){
		return ERROR;
	}
	
	while(node != linkList){
		length++;
		node = node->next;
	}
	//�����ȴ���ͷ�����
	linkList->data = length;
	return length;
}

ElemType getElement(LinkList linkList,int index){
	int i = 0;
	LNode *node = linkList->next;
	if(linkList == NULL){
		return ERROR;
	}
	
	while(i < index && node != linkList){
		node = node->next;
		i++;
	}
	return node->data;
}

int locateElement(LinkList linkList,ElemType target){
	int index = 0;
	LNode *node = linkList->next;
	if(linkList == NULL){
		return ERROR;
	}
	
	while(node != linkList){
		if(node->data == target){
			return index;
		}
		index ++;
		node = node->next;
	}
	return ERROR;
}

/*
	β�����룬ָ���±�ʱ���뵽ָ���±�ĺ��棬ָ���±꣨-1��ʱ�����������һ��λ�ò���
*/
STATUS insertByIndex(LinkList *linkList,int index,ElemType element){
	int i = 0;
	int length = 0;
	LNode *node = (*linkList)->next;
	LNode *previousNode = (*linkList);
	//��������ʼ��
	LNode *newNode = NULL;
	initList(&newNode);
	

	if((*linkList) == NULL){
		return ERROR;
	}
	
	//ָ�����±곬������ֱ�ӱ���
	length = getLength((*linkList));
	if (index > length) {
		return ERROR;
	}
	while (TRUE) {
		if (i == index) {
			break;
		}
		else if (index < 0 && node == (*linkList)) {
			break;
		}
		i++;
		previousNode = node;
		node = node->next;
	}
	
	newNode->data = element;
	//���ָ����λ���������һ������ǰһ����㸳ֵ,�������node����ɿ�ָ��
	if (node == (*linkList))
	{
		newNode->next = previousNode->next;
		newNode->previous = previousNode;
	}
	else {
		//����������һ�������һ����������ڸ��½�����
		newNode->next = node->next;
		newNode->previous = node;
	}
	previousNode->next->previous = newNode;
	previousNode->next = newNode;
	return SUCCESS;
}

STATUS removeByIndex(LinkList *linkList,int index){
	int i = 0;
	LNode *node = (*linkList)->next;
	LNode *tempNode = NULL;
	if(linkList == NULL){
		return ERROR;
	}
	
	while(i != index - 1){
		i++;
		node = node->next;
	}
	
	tempNode = node->next;
	tempNode->next->previous = node;
	ElemType result = tempNode->data;
	node->next = tempNode->next;
	
	free(tempNode);
	return result;
}

void show(LinkList linkList){
	LNode *node = linkList->next;
	if(linkList->next == NULL){
		printf("�������ݣ�\n");
	}
	
	while(node != linkList){
		printf("%d,",node->data);
		node = node->next;
	}
	printf("\n");
}