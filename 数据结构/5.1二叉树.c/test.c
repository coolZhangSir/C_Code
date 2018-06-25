#include "BinaryTree.h"
void main() {
	BinaryTree tree = NULL;
	int elements[9] = { 1,2,-1,3,-1,-1,4,-1,-1 };
	int *p = elements;
	initBinaryTree(&tree);
	printf("�Ƿ�Ϊ����:%s\n",isBinaryTreeEmpty(tree)?"��":"�ǿ�");
	createBinaryTree(&tree, &p);
	printf("�Ƿ�Ϊ����:%s\n", isBinaryTreeEmpty(tree) ? "��" : "�ǿ�");
	
	//�����¹���
	swapChild(&tree);

	int count = 0;
	getCountOfNodeWithOneChild(tree, &count);
	printf("\n��Ϊ1�Ľ��:%d\n",count);

	printf("\nǰ�����:\n");
	prefixTraverse(tree);
	printf("\n�������:\n");
	infixTraverse(tree);
	printf("\n�������:\n");
	postfixTraverse(tree);

	printf("\n���:%d\n",getBinaryTreeDepth(tree));

	BTNode *node = malloc(sizeof(BTNode));
	node->data = 4;
	assignValue(&tree, node, 5);
	printf("\n�޸Ľ��4֮��:\n");
	prefixTraverse(tree);

	printf("\nroot:%d\n", getRoot(tree));
	
	node->data = 3;
	printf("\n���3�ĸ����:%d\n", getParent(tree,node));

	node->data = 1;
	printf("\n���1�����ӽ��:%d\n", getLeftChild(tree, node));

	node->data = 1;
	printf("\n���1�����ӽ��:%d\n", getRightChild(tree, node));

	int elements2[9] = { 1,2,-1,3,-1,-1,-1 };
	int *pp = elements2;
	BinaryTree tree2 = NULL;
	initBinaryTree(&tree2);
	createBinaryTree(&tree2, &pp);

	node->data = 2;
	insertChild(&tree,node,1,&tree2);
	printf("\n������֮��:\n");
	prefixTraverse(tree);

	deleteChild(&tree,node,1);
	printf("\nɾ�����֮��:\n");
	prefixTraverse(tree);

	system("pause");
}