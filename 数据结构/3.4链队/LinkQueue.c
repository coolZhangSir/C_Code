#include "LinkQueue.h"

STATUS init(LinkQueue *queue) {
	QNode *node = (QNode *)malloc(sizeof(QNode));
	node->next = NULL;
	(*queue) = (LinkQueue)malloc(sizeof(Queue));
	(*queue)->front = (*queue)->rear = node;
	return SUCCESS;
}
STATUS enQueue(LinkQueue *queue, ElemType element) {
	QNode *node = (QNode *)malloc(sizeof(QNode));
	node->data = element;
	node->next = NULL;
	(*queue)->rear->next = node;
	(*queue)->rear = node;
	return SUCCESS;
}
ElemType deQueue(LinkQueue *queue) {
	//�ж϶����Ƿ�Ϊ��
	if ((*queue)->front == (*queue)->rear)
	{
		return ERROR;
	}
	QNode *node = (*queue)->front;
	(*queue)->front = node->next;
	//�����ǰ���ӵ�Ԫ�������һ��Ԫ��,��βָ��ָ��ͷ���
	if ((*queue)->rear == node)
	{
		(*queue)->rear = (*queue)->front;
	}
	ElemType result = node->data;
	free(node);
	return result;

}
ElemType getHead(LinkQueue queue) {
	//�ж��Ƿ�Ϊ��
	if (queue->front == queue->rear)
	{
		return ERROR;
	}
	return queue->front->data;
}