#include "LinkList.h"

LinkList* initList(){
	LinkList *linkList = (LinkList*)malloc(sizeof(LinkList));
	linkList->data = 0;
	linkList->next = NULL;
	return linkList;
}

STATUS destroyList(LinkList *linkList){
	LNode *p = linkList;
	LNode *q = linkList->next;
	if(linkList == NULL){
		return ERROR;
	}
	while(q != NULL){
		//�Ƚ�q����һ��������p��
		p = q->next;
		//ɾ����ǰqָ����Ǹ�
		free(q);
		//p�б�������һ��,���԰�p��q,����ɾ��
		q = p;
	}
	//��ͷ������һ���ÿ�
	linkList->data = 0;
	linkList->next = NULL;
	return SUCCESS;
}

STATUS clearList(LinkList *linkList){
	LNode *node = linkList->next;
	if(linkList == NULL){
		return ERROR;
	}
	
	while(node != NULL){
		node->data = 0;
		node = node->next;
	}
	return SUCCESS;
}

STATUS isEmpty(LinkList *linkList){
	LNode *node = linkList->next;
	if(linkList == NULL){
		return ERROR;
	}
	
	if(node == NULL){
		return TRUE;
	}
	return FALSE;
}

int getLength(LinkList *linkList){
	LNode *node = linkList->next;
	int length = 0;
	if(linkList == NULL){
		return ERROR;
	}
	
	while(node != NULL){
		length++;
		node = node->next;
	}
	//�����ȴ���ͷ�����
	linkList->data = length;
	return length;
}

ElemType getElement(LinkList *linkList,int index){
	int i = 0;
	LNode *node = linkList->next;
	if(linkList == NULL){
		return ERROR;
	}
	
	while(i < index){
		node = node->next;
		i++;
	}
	return node->data;
}

int locateElement(LinkList *linkList,ElemType target){
	int index = 0;
	LNode *node = linkList->next;
	if(linkList == NULL){
		return ERROR;
	}
	
	while(node != NULL){
		if(node->data == target){
			return index;
		}
		index ++;
		node = node->next;
	}
	return ERROR;
}

ElemType priorElement(LinkList *linkList,ElemType currentElement){
	LNode *node = linkList->next;
	LNode *priorNode = linkList;
	if(linkList == NULL){
		return ERROR;
	}
	
	while(node != NULL){
		if(node->data == currentElement){
			return priorNode->data;
		}
		//����������λ��
		priorNode = node;
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
	LNode *node = linkList->next;
	LNode *perviousNode = linkList;
	//��������ʼ��
	LNode *newNode = initList();
	

	if(linkList == NULL){
		return ERROR;
	}
	
	//ָ�����±곬������ֱ�ӱ���
	length = getLength(linkList);
	if (index > length) {
		return ERROR;
	}
	while (TRUE) {
		if (i == index) {
			break;
		}
		else if (index < 0 && node == NULL) {
			break;
		}
		i++;
		perviousNode = node;
		node = node->next;
	}
	
	newNode->data = element;
	//���ָ����λ���������һ������ǰһ����㸳ֵ,�������node����ɿ�ָ��
	if (node == NULL)
	{
		newNode->next = perviousNode->next;
	}
	else {
		//����������һ�������һ����������ڸ��½�����
		newNode->next = node->next;
	}
	perviousNode->next = newNode;
	return SUCCESS;
}

STATUS removeByIndex(LinkList *linkList,int index){
	int i = 0;
	LNode *node = linkList->next;
	LNode *tempNode = NULL;
	if(linkList == NULL){
		return ERROR;
	}
	
	while(i != index - 1){
		i++;
		node = node->next;
	}
	
	tempNode = node->next;
	ElemType result = tempNode->data;
	node->next = tempNode->next;
	
	free(tempNode);
	return result;
}

void show(LinkList *linkList){
	LNode *node = linkList->next;
	if(linkList->next == NULL){
		printf("�������ݣ�\n");
	}
	
	while(node != NULL){
		printf("%d,",node->data);
		node = node->next;
	}
	printf("\n");
}