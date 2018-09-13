#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define ElemType int
#define SIZE 10

typedef struct LinkedListNodeStruct {
	int child;
	struct LinkedListNodeStruct *next;
}*LinkedListNode;

typedef struct ChildTreeNodeStruct {
	//���ϼ�Ϊ����˫�ױ�ʾ��,������Ҹ����,�Ǻ��ӱ�ʾ���ĸĽ�
	//int parent;
	ElemType data;
	LinkedListNode list;
}*ChildTreeNode;

typedef struct ChildTreeStruct {
	ChildTreeNode nodes;
}*ChildTree;

void ct_init(ChildTree *tree);
void ct_create(ChildTree tree);
void ct_show(ChildTree tree);
void ct_queryChild(ChildTree tree);
void ct_queryParent(ChildTree tree);
void ct_destroy(ChildTree tree);