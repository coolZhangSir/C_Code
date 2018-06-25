#include<stdio.h>
#include<stdlib.h>
#define ELEM_TYPE int
#define MAX_ELEMENT 2000
#define LEFT 0
#define RIGHT 1

typedef struct Matric{
	ELEM_TYPE *vexs;	//������Ϣ
	ELEM_TYPE **matric;	//�ڽӾ���,�ض���һ������
	int vexCount,arcCount;	//��ǰ�������ͱ���
	int *positions;	//��ǰ�������߻����ұ�
}*MatricGraph;
void initMatricGraph(MatricGraph *graph,int vexCount, int arcCount);
void createMatricGraph(MatricGraph *graph,int *vexs,int (*arcs)[3],int arcInfoLength);
void output(MatricGraph graph);