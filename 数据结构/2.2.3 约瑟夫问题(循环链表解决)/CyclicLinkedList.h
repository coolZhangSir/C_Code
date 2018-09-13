#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CYCLIC_LINKED_LIST_TRUE 1
#define CYCLIC_LINKED_LIST_FALSE 0

/*
	ǰ��:
		���ݽṹ�����ԭ��,��Ϊ�������next������ڵ�һ����Ա������λ��,��ֹ�ڽṹ��ָ��֮��ǿת�������ݽ����Ĵ���.
		ԭ��:�ṹ���һ����Ա������λ������ṹ��������.
			�������е�next���û�����Ľṹ������node�����ڵ�һ����Ա������λ����,�ڽṹ������ǿת�������,ȷ��ÿ�β����Ķ���ͬһ�ڴ��ַ
			��Person����ǿתΪ��CyclicLinkedListNode,ֻҪ����next,���۴�ʱ�ṹ��������ʲô,���Ƕ����ڲ���ͬһ���ڴ�.

	�Ľ��Ĺؼ�������������:
		1.����ṹ�����Ϊ�����,�����������û��Լ�����,ֻ�ṩһ��ָ��.��֮ǰ���ṹ������д�����,����д���������.�����������ڶ�̬������
			�����������nextָ�������ʲô�����Ѿ�����ν��,�û�ֻ��Ҫ�Լ�����һ���ṹ��,����һ��CyclicLinkedListNode�ṹ��ĳ�Ա���������漴��,�ھ���ʹ�õ�ʱ�����ʹ������ǿת:
			(1).������ɾ�ȶ���ʱ,������ǿתΪCyclicLinkedListNode,ֱ�ӽ�������������
			(2).һ���漰Ԫ�صĶ�ȡʱ,���û�����ǿתΪ�Զ��������,ͨ�������ʵ�ֵĺ�������ɲ���,����ֻ��Ҫ��ȡ�ú���ָ�뼴��
		2.�����˺���ָ���ʹ��,���û��������Ͳ�ȷ���������,ʹ�ú���ָ�����û��Լ�ʵ�־���ĺ�������,�������
*/
typedef struct TagCyclicLinkedListNode {//���Լ���һ��Tag��������ʱ���ֺ�typedef�ı�����
	/*
		һ���ṹ�����治�������ýṹ�屾�����,��������Ϊ����Ƕ�׶�����,ֻ����ָ��.
		ԭ��:�ýṹ����δ�������,��������֪��Ϊ���������ڴ�,��ָ��Ĵ�С����֪�ҹ̶���(4Byte)
	*/
	struct TagCyclicLinkedListNode *next;
}CyclicLinkedListNode;

typedef struct TagCyclicLinkedList {
	//��������ʹ��һ��������Ϊ����,��malloc��ListʱҲ���node���з����ڴ�,�����ٴ��ֶ�malloc.���ǽṹ����ռ���ڴ�϶���һ��ָ���,���Ի��ǲ�Ҫ͵��,����ʵʵ����ָ��
	CyclicLinkedListNode *node;
	int size;
}*CyclicLinkedList;

//�Ƚ����ĺ���ָ��,����ıȽϹ������û����ж���
typedef int(*COMPARATOR)(CyclicLinkedListNode *currentValue,CyclicLinkedListNode *targetValue);

//��ӡ������ݵĺ���ָ��,����Ĵ�ӡ�������û����ж���
typedef void(*PRINT)(CyclicLinkedListNode *node);

CyclicLinkedList create_CyclicLinkedList();

void insert_CyclicLinkedList(CyclicLinkedList list, int position, CyclicLinkedListNode *node);

void removeByPosition_CyclicLinkedList(CyclicLinkedList list, int position);

//����������Ҫ�Ƚ��û�ָ����ֵ�����Ǳ�������Ԫ��ֵ,���������ֲ�֪���û�����ʹ�õ���������,������Ҫ�û�����һ���Զ���ıȽϺ���ָ��(������java�ıȽ���(comparator))
void removeByValue_CyclicLinkedLIst(CyclicLinkedList list, CyclicLinkedListNode *targetValue,COMPARATOR comparator);

CyclicLinkedListNode* getNodeByPosition_CyclicLinkedList(CyclicLinkedList list, int position);

CyclicLinkedListNode* getNodeByValue_CyclicLinkedList(CyclicLinkedList list, CyclicLinkedListNode *targetValue,COMPARATOR comparator);

CyclicLinkedListNode* getFirstNode_CyclicLinkedList(CyclicLinkedList list);

int getSize_CyclicLinkedList(CyclicLinkedList list);

//���ڲ�֪����������,��ӡ����Ҳֻ�����û����ж���,����һ������ָ������ǵ��ü���
void traverse_CyclicLinkedList(CyclicLinkedList list,PRINT print);

void releaseMemory(CyclicLinkedList list);