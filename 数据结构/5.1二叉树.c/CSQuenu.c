#include "StackAndQueue.h"

/*
	ѭ������Լ��:�ճ�һ�������Ϊ����ӿպͶ���������,��ͷָ��ָ��ͷԪ��,��βָ��ָ��βԪ�ص���һ��λ��
*/
STATUS initQueue(CSQueue *queue){
	//û�ö���ָ��,����ǿ��ת�������Ϊ����
	(*queue) = (CSQueue )malloc(sizeof(struct TagCSQueue));
	for (int i = 0; i < SIZE; i++)
	{
		(*queue)->base[i]= NULL;
	}
	(*queue)->front = 0;
	(*queue)->rear = 0;
	return SUCCESS;
}
BOOL isQueueEmpty(CSQueue queue){
	if (queue == NULL)
	{
		return ERROR;
	}
	if(queue->front == queue->rear){
		return TRUE;
	}else{
		return FALSE;
	}
}
BOOL isQueueFull(CSQueue queue){
	if (queue == NULL)
	{
		return ERROR;
	}
	if((queue->rear + 1) % SIZE == queue->front){
		return TRUE;
	}else{
		return FALSE;
	}
}
int getQueueLength(CSQueue queue){
	if (queue == NULL || queue->base == NULL)
	{
		return 0;
	}
	else{
		//%SIZEΪ�˷�ֹ����ĵ�ǰ���ȳ�����󳤶�
		return (queue->rear + SIZE - queue->front) % SIZE;
	}
}

ElemType getHead(CSQueue queue){
	if (queue == NULL)
	{
		return NULL;
	}
	else{
		return queue->base[queue->front];
	}
}
STATUS enQueue(CSQueue queue,ElemType element){
	if (queue == NULL)
	{
		return ERROR;
	}
	if(isQueueFull(queue) == TRUE){
		printf("��ǰ��������!\n");
		return ERROR;
	}else{
		queue->base[queue->rear] = element;
		queue->rear = (queue->rear + 1) % SIZE;
		return SUCCESS;
	}
}
ElemType deQueue(CSQueue queue){
	if (queue == NULL)
	{
		return NULL;
	}
	if(isQueueEmpty(queue)){
		printf("��ǰ����Ϊ��!\n");
		return NULL;
	}else{
		ElemType result = queue->base[queue->front];
		queue->front = (queue->front + 1) % SIZE;
		return result;
	}
}

STATUS clearQueue(CSQueue queue){
	if(queue->front == queue->rear){
		return SUCCESS;
	}else{
		queue->front = 0;
		queue->rear = queue->front;
		return SUCCESS;
	}
}
STATUS destroyQueue(CSQueue queue){
	if(queue == NULL){
		return SUCCESS;
	}else{
		free(queue);
		queue = NULL;
		return SUCCESS;
	}

}

