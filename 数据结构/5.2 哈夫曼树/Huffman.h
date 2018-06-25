#include <stdio.h>
#include <stdlib.h>
#define ELEMENT_TYPE int
#define STATUS int
#define N 8
#define LEFT '0'
#define RIGHT '1'

typedef struct HuffmanNode {
	int parent;
	int weight;//Ȩ��
	struct HuffmanNode *leftChild;//������
	struct HuffmanNode *rightChild;//������
}HuffmanNode, *HuffmanTree;

void initTree(HuffmanTree *tree, int *weights);
void createTree(HuffmanTree *tree);
void selectMinimum(HuffmanTree tree, int *firstIndex, int *secondIndex);
void prefix(HuffmanTree tree);
void encodeRecursive(HuffmanTree tree, HuffmanTree currentNode, char *code);
