#include<stdio.h>
#include<stdlib.h>

#define ElemType int
#define STATUS int

#define ERROR -1
#define SUCCESS 1

#define TRUE 1
#define FALSE 0
/*
	�����Դ�ͷ����ѭ�������ʾ����,����ֻ��һ��ָ��ָ���βԪ�ؽ��
	�Ա�д��Ӧ���ÿն���,�ж϶����Ƿ�Ϊ��,��Ӻͳ����㷨
*/

typedef struct {
	ElemType data;
	struct LNode *next;
}QNode,*QueuePtr;
typedef struct {
	QueuePtr front;
	QueuePtr rear;
}Queue,*LinkQueue;

STATUS init(LinkQueue *queue);
STATUS enQueue(LinkQueue *queue,ElemType element);
ElemType deQueue(LinkQueue *queue);
ElemType getHead(LinkQueue queue);


