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
	//swapChild(&tree);

	int count = 0;
	getCountOfNodeWithOneChild(tree, &count);
	printf("\n��Ϊ1�Ľ��:%d\n",count);

	printf("\nǰ�����:\n");
	preorderTraversal(tree);
	printf("\nǰ���������:\n");
	preorderTraversal_iteration(tree);

	printf("\n�������:\n");
	inorderTraversal(tree);

	printf("\n�����������:\n");
	inorderTraversal_iteration(tree);

	printf("\n�������:\n");
	postorderTraversal(tree);

	printf("\n�����������:\n");
	postorderTraversal_iteration(tree);

	printf("\n�������:\n");
	levelTraversal(tree);

	printf("\n���:%d\n",getBinaryTreeDepth(tree));

	BTNode *node = malloc(sizeof(BTNode));
	node->data = 4;
	assignValue(&tree, node, 5);
	printf("\n�޸Ľ��4֮��:\n");
	preorderTraversal(tree);

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
	preorderTraversal(tree);

	deleteChild(&tree,node,1);
	printf("\nɾ�����֮��:\n");
	preorderTraversal(tree);

	system("pause");
}

void visit(BinaryTree pTree, Stack *stack) {
	while (pTree != NULL)
	{
		push(stack, pTree->rightChild);
		push(stack, pTree->leftChild);
		pTree = getTop(stack);
	}
}
void postorderTraversal_iteration1(BinaryTree tree) {
	Stack *stack = NULL;
	initStack(&stack);
	BTNode *pTree = tree;
	if (pTree != NULL)
	{
		push(stack, pTree);
	}
	while (TRUE)
	{
		BTNode *top = getTop(stack);
		if (top != NULL && top->leftChild != pTree && top->rightChild != pTree)
		{
			visit(top, stack);
		}
		if (isStackEmpty(stack) == TRUE)
		{
			break;
		}
		pTree = pop(stack);
		if (pTree != NULL)
		{
			printf("%d ", pTree->data);
		}
	}
}