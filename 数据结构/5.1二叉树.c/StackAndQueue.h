#include<stdio.h>
#include<stdlib.h>

#define ElemType BTNode*
#define STATUS int
#define BOOL int
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define SUCCESS -2
#define SIZE 10

typedef struct Tree {
	int data;
	struct Tree *leftChild;
	struct Tree *rightChild;
}BTNode, *BinaryTree;

/*
	������Խ����������ͳһ�޸�,������������,ֻ�����ַ����(��ָ������)
*/
typedef struct {
	int maxSize;
	int top;
	ElemType base[SIZE];
}Stack;

//����ʹ��ָ����Ը��ݵ�ַ������в���
STATUS initStack(Stack **stack);
STATUS destroyStack(Stack **stack);
STATUS clearStack(Stack **stack);

//�ṹ��Ϊ������������ʹ��ָ�������в������ݣ������������ķ���
BOOL isStackEmpty(Stack *stack);
BOOL isStackFull(Stack *stack);
int getStackLength(Stack *stack);

ElemType getTop(Stack *stack);
STATUS push(Stack *stack,ElemType element);
ElemType pop(Stack *stack);

STATUS traverseStack(Stack *stack);


//ѭ��˳�����
typedef struct TagCSQueue{
	ElemType base[SIZE];
	//��¼��ǰ��ͷ�Ͷ�βλ��
	int rear;
	int front;
}*CSQueue;

STATUS initQueue(CSQueue *queue);
BOOL isQueueEmpty(CSQueue queue);
BOOL isQueueFull(CSQueue queue);
int getQueueLength(CSQueue queue);
ElemType getHead(CSQueue queue);
STATUS enQueue(CSQueue queue, ElemType element);
ElemType deQueue(CSQueue queue);
STATUS clearQueue(CSQueue queue);
STATUS destroyQueue(CSQueue queue);