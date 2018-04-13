#include "CSQueue.h"

/*
	ѭ������Լ��:�ճ�һ�������Ϊ����ӿպͶ���������,��ͷָ��ָ��ͷԪ��,��βָ��ָ��βԪ�ص���һ��λ��
*/
STATUS init(CSQueue *queue){
	//û�ö���ָ��,����ǿ��ת�������Ϊ����
	(*queue) = *((CSQueue *)malloc(sizeof(CSQueue)));
	queue->base = (ElemType *)malloc(sizeof(ElemType) * MAXSIZE);
	queue->front = 0;
	queue->rear = 0;
	return SUCCESS;
}
BOOL isEmpty(CSQueue queue){
	if(queue.base == NULL || queue.front == queue.rear){
		return TRUE;
	}else{
		return FALSE;
	}
}
BOOL isFull(CSQueue queue){
	if(queue.base != NULL && 
		(queue.rear + 1) % MAXSIZE == queue.front){
		return TRUE;
	}else{
		return FALSE;
	}
}
int getLength(CSQueue queue){
	if(isEmpty(queue)){
		return 0;
	}else{
		//%MAXSIZEΪ�˷�ֹ����ĵ�ǰ���ȳ�����󳤶�
		return (queue.rear + MAXSIZE - queue.front) % MAXSIZE;
	}
}

ElemType getHead(CSQueue queue){
	if(isEmpty(queue)){
		return ERROR;
	}else{
		return *(queue.base + queue.front);
	}
}
STATUS enQueue(CSQueue *queue,ElemType element){
	if(isFull(*queue)){
		printf("��ǰ��������!\n");
		return ERROR;
	}else{
		*(queue->base + queue->rear) = element;
		queue->rear = (queue->rear + 1) % MAXSIZE;
		return SUCCESS;
	}
}
ElemType deQueue(CSQueue *queue){
	if(isEmpty(*queue)){
		printf("��ǰ����Ϊ��!\n");
		return ERROR;
	}else{
		ElemType result = *(queue->base + queue->front);
		queue->front = (queue->front + 1) % MAXSIZE;
		return result;
	}
}

STATUS clear(CSQueue *queue){
	if(queue->base == NULL || queue->front == queue->rear){
		return SUCCESS;
	}else{
		queue->front = 0;
		queue->rear = queue->front;
		return SUCCESS;
	}
}
STATUS destroy(CSQueue *queue){
	if(queue->base == NULL || queue->front == queue->rear){
		return SUCCESS;
	}else{
		free(queue->base);
		free(queue);
		return SUCCESS;
	}

}

