#include "MatricGraph.h"
/*
	malloc����һ����ά��������ַ�ʽ:(3��2��)
		һ.�ö���ָ��(�Ƽ�����,���������)
			1.������һ��ָ������(����int *p[3],��д��int **p)
			int **a = (int **)malloc(sizeof(int *) * 3);
			2.����ÿһ��ָ������Ԫ������ռ�
			for(int i = 0;i < 2;i++){
				a[i] = (int *)malloc(sizeof(int) * 2);
			}
		��.������ָ��
			int (*a)[2] = (int (*)[2])malloc(sizeof(int) * 3 * 2);
		��.��һά��������ά����
			int *a = (int *)malloc(sizeof(int) * 3 * 2);
			1.���ʵ�ʱ����Ҫ�ֶ����㻻����Ҫ��λ��,��a[3][2]�ķ���:
			*(a + 3 * 2 + 1)
*/
void initMatricGraph(MatricGraph *graph,int vexCount, int arcCount){
	//1.�ȳ�ʼ��ͼ
	(*graph) = (MatricGraph)malloc(sizeof(Matric));
	//2.��ʼ������ĳ�Ա
	(*graph)->matric = (ELEM_TYPE **)malloc(sizeof(int *) * vexCount);
	for (int i = 0; i < vexCount; i++)
	{
		(*graph)->matric[i] = (int *)malloc(sizeof(int) * vexCount);
	}
	
	(*graph)->arcCount = arcCount;
	(*graph)->vexCount = vexCount;

	(*graph)->vexs = (ELEM_TYPE *)malloc(sizeof(ELEM_TYPE) * vexCount);
	for(int i = 0;i < (*graph)->vexCount;i++){
		(*graph)->vexs[i] = 0;
	}

	(*graph)->positions = (ELEM_TYPE *)calloc(sizeof(ELEM_TYPE),vexCount);

	for(int i = 0;i < (*graph)->vexCount;i++){
		for(int j = 0;j < (*graph)->vexCount;j++){
			(*graph)->matric[i][j] = MAX_ELEMENT;
		}
	}
}
/*
	graph:�ڽӾ���ĵ�ַ
	vexs:�������Ķ��㼯
	arcs:����Ϣ����
	arcInfoLength:ÿ������Ϣ��ռ����
*/
void createMatricGraph(MatricGraph *graph,int *vexs,int (*arcs)[3],int arcInfoLength){
	for(int i = 0;i < (*graph)->vexCount;i++){
		(*graph)->vexs[i] = vexs[i];
	}
	for(int i = 0;i < (*graph)->arcCount;i++){
		int start = arcs[i][0];
		int end = arcs[i][1];
		int weight = arcs[i][2];
		(*graph)->matric[start][end] = weight;
	}
}
void output(MatricGraph graph){
	printf("\n���㼯��\n");
	for(int i = 0;i < graph->vexCount;i++){
		printf("%d ",graph->vexs[i]);
	}
	printf("\n����\n");
	for(int i = 0;i < graph->vexCount;i++){
		for(int j = 0;j < graph->vexCount;j++){
			printf("%-10d ",graph->matric[i][j]);
		}
		printf("\n");
	}

}