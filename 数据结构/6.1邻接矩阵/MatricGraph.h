#include<stdio.h>
#include<stdlib.h>
#define ELEM_TYPE int
#define MAX_ELEMENT INT_MAX
typedef struct Matric{
	ELEM_TYPE *vexs;	//������Ϣ
	ELEM_TYPE **matric;	//�ڽӾ���,�ض���һ������
	int vexCount,arcCount;	//��ǰ�������ͱ���
}*MatricGraph;
void initMatricGraph(MatricGraph *graph,int vexCount, int arcCount);
void createMatricGraph(MatricGraph *graph,int *vexs,int (*arcs)[3],int arcInfoLength);
void output(MatricGraph graph);