#include "Huffman.h"
/*
	���ݴ����ֵ��ʼ����ù�������,�ܵĽ����Ϊ2N-1
	��ʼ��һ����HuffmanTreeָ�������,������ÿ�������Ϣ
*/
void initTree(HuffmanTree *tree, int *weights) {
	//�����������뵥�����ż������,3*2*2+1��3*(2*2+1)����ǲ���ͬ��
	//������ֵ�malloc�Ͼͻ���ֶ��ѱ��ƻ�
	*tree = (HuffmanTree)malloc(sizeof(HuffmanNode) * (2 * N + 1));
	for (int i = 0; i < 2 * N + 1; i++)
	{
		if (i < N)
		{
			((*tree) + i)->weight = *(weights + i);
		}
		else {
			((*tree) + i)->weight = 0;
		}
		((*tree) + i)->leftChild = NULL;
		((*tree) + i)->rightChild = NULL;
		((*tree) + i)->parent = -1;
	}
}
/*
	�ܽ��2N-1,��ȥN��Ҷ���,ʣ��N-1����������
	ÿ���ҳ�����Ȩֵ��С�Ľ��,����Ȩֵ��Ӳ�����һ���µĽ�㴦��,ͬʱ��������Ϊ���������ĸ����
*/
void createTree(HuffmanTree *tree) {
	int firstIndex = 0;
	int secondIndex = 0;
	for (int i = 0; i < N - 1; i++)
	{
		if (i == N - 2) {
			printf("");
		}
		selectMinimum(*tree, &firstIndex, &secondIndex);
		printf("first=%d,second=%d\n",(*tree + firstIndex)->weight, (*tree + secondIndex)->weight);
		(*tree + firstIndex)->parent = N + i;
		(*tree + secondIndex)->parent = N + i;
		(*tree + N + i)->weight = (*tree + firstIndex)->weight + (*tree + secondIndex)->weight;
		(*tree + N + i)->leftChild = (*tree + firstIndex);
		(*tree + N + i)->rightChild = (*tree + secondIndex);
	}
}
/*
	�ҳ������Ϊ�յ�������С�����±�
*/
void selectMinimum(HuffmanTree tree,int *firstIndex,int *secondIndex) {
	*firstIndex = 0;
	*secondIndex = 0;
	int isInit = 0;
	for (int i = 0; i < 2 * N - 1; i++)
	{
		if ((tree + i)->parent != -1)
		{
			continue;
		}
		else {
			if (0 == isInit) {
				*firstIndex = i;
				isInit++;
			}
			else if (1 == isInit) {
				*secondIndex = i;
				isInit++;
			}
			if ((tree + i)->weight != 0) {
				//�����õ���,����½��Ȩֵ��֮ǰ���Ȩֵ��Ȼ����ǰ��һ�����ᱻ�½�㸲��
				if ((tree + i)->weight < (tree + *firstIndex)->weight)
				{
					//��ʱ������һ���ȵ�һС������С����,����ԭ����һС�����ڱ���˵ڶ�С
					*secondIndex = *firstIndex;
					*firstIndex = i;
				}else if((tree + i)->weight < (tree + *secondIndex)->weight){
					//�����С�ڵ�һС,������С�ڵ�ǰ�ڶ�С��,��Ҫ�����ж�
					*secondIndex = i;
				}
			}
		}
	}
}
void prefix(HuffmanTree tree) {
	if (tree == NULL)
	{
		return;
	}
	else {
		printf("%d ",tree->weight);
		prefix(tree->leftChild);
		prefix(tree->rightChild);
	}
}
/*
	������0��1����
	code:����һ��ָ������,ÿ��Ԫ�ض���Ŷ�Ӧ���ı�����Ϣ
	ÿ���ڵ�ı��볤�ȱض�С��n(�������С��n),ԭ��:
		����������û�з�֧(�������ֻ��һ�����ӽ������),n��Ҷ�ӽ�������n-1����Ҷ�ӽ��,
		����ÿ����ѡ����Ȩֵ��С�Ľ��,ceil((2n - 1) / 2)����ȡ�����Ϊn
	tree:�����Ļ�׼��ַ,ÿ�����ĸ�����±궼�Ӹõ�ַ����ƫ��
	currentNode:��ǰ�Ľ��,�ý���ȡ���ĸ���㲻��ֱ�������������ƫ��
	code:��ǰ�����ŵĵ�Ԫ��ַ
*/
void encodeRecursive(HuffmanTree tree, HuffmanTree currentNode, char *code) {
	if (currentNode == NULL || currentNode->parent == -1) {
		return;
	}
	else {
		//tree�ĵ�ַÿ�ζ�����Ա仯,���������±�û�����ű仯,ֱ�ӼӺ���ᵼ��Խ��
		HuffmanTree parent = tree + currentNode->parent;
		//���ܱ�Ȩֵ,�������Һ���Ȩֵ��Ⱦ�������,ֱ�ӱȵ�ַ��
		if (parent->leftChild == currentNode) {
			*code = LEFT;
		}
		else {
			*code = RIGHT;
		}
		code--;
		encodeRecursive(tree,parent,code);
	}
}
