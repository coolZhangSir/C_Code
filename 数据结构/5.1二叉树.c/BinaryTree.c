#include "BinaryTree.h"

/*��ʼ������Ķ�����*/
STATUS initBinaryTree(BinaryTree *tree){
	(*tree) = (BinaryTree)malloc(sizeof(BTNode));
	(*tree)->data = -1;
	(*tree)->leftChild = NULL;
	(*tree)->rightChild = NULL;
	return SUCCESS;
}
/*
	���ٵ�ǰ������
	�²⵱ǰֻ���ú�������ķ�ʽ���ɾ�����ռ䣬�������ֿ��ܻᵼ����ɾ������㣬����Ľ��ز���
*/
STATUS destroyBinaryTree(BinaryTree *tree){
	if((*tree)->leftChild != NULL || (*tree)->rightChild != NULL){
		destroyBinaryTree(&(*tree)->leftChild);
		destroyBinaryTree(&(*tree)->rightChild);
		free(*tree);
		return SUCCESS;
	}else{
		return SUCCESS;
	}
}
/*
	���ݸ�����Ԫ�أ���-1�Ž����������򴴽���������ʹ��X�򶼿��Դ���
*/
STATUS createBinaryTree(BinaryTree *tree,int **elements){
	if(**elements == -1){
		(*tree) = NULL;
	}else{
		(*tree) = malloc(sizeof(BTNode));
		(*tree)->data = **elements;
		*elements = *elements + 1;
		createBinaryTree(&(*tree)->leftChild,elements);
		*elements = *elements + 1;
		createBinaryTree(&(*tree)->rightChild, elements);
	}
	return SUCCESS;
}
/*
	������Ϊһ���ն�����
*/
STATUS clearBinaryTree(BinaryTree *tree){
	destroyBinaryTree(tree);
	initBinaryTree(tree);
	return SUCCESS;
}
/*
	�ж����Ƿ�Ϊһ������
*/
int isBinaryTreeEmpty(BinaryTree tree){
	if(tree->leftChild != NULL || tree->rightChild != NULL){
		return 0;
	}else{
		return 1;
	}
}
/*
	��ȡ�������
*/
int getBinaryTreeDepth(BinaryTree tree){
	if(tree == NULL){
		return 0;
	}else{
		int leftDepth = getBinaryTreeDepth(tree->leftChild);
		int rightDepth = getBinaryTreeDepth(tree->rightChild);
		if(leftDepth > rightDepth){
			return leftDepth + 1;
		}else{
			return rightDepth + 1;
		}
	}
}
STATUS assignValue(BinaryTree *tree,BTNode *node,ELEMENT_TYPE value){
	if (*tree == NULL)
	{
		return ERROR;
	}
	else {
		if ((*tree)->data == node->data)
		{
			(*tree)->data = value;
			return SUCCESS;
		}
		int leftFlag = assignValue(&(*tree)->leftChild, node, value);
		if (leftFlag == 1)
		{
			return leftFlag;
		}
		int rightFlag = assignValue(&(*tree)->rightChild, node, value);
		return rightFlag;
	}
}
ELEMENT_TYPE getRoot(BinaryTree tree) {
	if (tree == NULL)
	{
		return -1;
	}
	else {
		return tree->data;
	}
}
ELEMENT_TYPE getParent(BinaryTree tree, BTNode *node) {
	if (tree == NULL)
	{
		return ERROR;
	}
	else {
		//����������ڸ�����ֵ,����-1
		if (tree->data == node->data)
		{
			return -1;
		}
		if (tree->leftChild != NULL)
		{
			if (tree->leftChild->data != node->data)
			{
				return tree->leftChild->data;
			}
		}
		if (tree->rightChild != NULL)
		{
			if (tree->rightChild->data != node->data)
			{
				return tree->rightChild->data;
			}
		}
		int left = getParent(tree->leftChild, node);
		if (left != 0)
		{
			return left;
		}
		int right = getParent(tree->rightChild, node);
		return right;
	}
}
ELEMENT_TYPE getLeftChild(BinaryTree tree, BTNode *node) {
	if (tree == NULL)
	{
		return ERROR;
	}
	else {
		if (tree->data == node->data)
		{
			if (tree->leftChild != NULL)
			{
				return tree->leftChild->data;
			}
		}
		ELEMENT_TYPE left = getLeftChild(tree->leftChild, node);
		if (left != ERROR)
		{
			return left;
		}
		ELEMENT_TYPE right = getLeftChild(tree->rightChild,node);
		return right;
	}
}
ELEMENT_TYPE getRightChild(BinaryTree tree, BTNode *node) {
	if (tree == NULL)
	{
		return ERROR;
	}
	else {
		if (tree->data == node->data)
		{
			if (tree->rightChild != NULL)
			{
				return tree->rightChild->data;
			}
		}
		ELEMENT_TYPE left = getRightChild(tree->leftChild, node);
		if (left != ERROR)
		{
			return left;
		}
		ELEMENT_TYPE right = getRightChild(tree->rightChild, node);
		return right;
	}
}
/*
	�Ӹ���㿪ʼ����ĳ�����ӽ��,������ӽ�����ָ�����
		�жϵ�ǰ����Ƿ�Ϊ���ӽ��,��ָ�����û�����ֵ�
		�жϵ�ǰ����Ƿ�Ϊ���ӽ��,�򷵻��丸�������ӽ��
*/
ELEMENT_TYPE getLeftSibling(BinaryTree tree, BTNode *node) {
	if (tree == NULL)
	{
		return ERROR;
	}
	else {
		if (tree->leftChild->data == node->data)
		{
			return ERROR;
		}
		if (tree->rightChild->data == node->data)
		{
			return tree->leftChild->data;
		}

		int left = getLeftSibling(tree->leftChild, node);
		if (left != ERROR)
		{
			return left;
		}
		int right = getLeftSibling(tree->rightChild, node);
		return right;
	}

	return ERROR;
}
ELEMENT_TYPE getRightSibling(BinaryTree tree, BTNode *node) {
	if (tree == NULL)
	{
		return ERROR;
	}
	else {
		if (tree->leftChild->data == node->data)
		{
			return ERROR;
		}
		if (tree->rightChild->data == node->data)
		{
			return tree->leftChild->data;
		}

		int left = getLeftSibling(tree->leftChild, node);
		if (left != ERROR)
		{
			return left;
		}
		int right = getLeftSibling(tree->rightChild, node);
		return right;
	}

	return ERROR;
}
/*
	parentNodeָ��ԭ��tree��ĳһ���
	isLeftChild��������parentNode�����ӽ�㻹�����ӽ��
	newChildΪ����������ӽ�������ӽ��ǿ�
	��newChild�����Ӧ�Ľ��,parentԭ�е����ӽ������ӽ���ΪnewChild�����ӽ��
*/
STATUS insertChild(BinaryTree *tree, BTNode *parentNode, int isLeftChild, BinaryTree *newChild) {
	if (*tree == NULL)
	{
		return ERROR;
	}
	else {
		if ((*tree)->data == parentNode->data)
		{
			if (isLeftChild == 1)
			{
				(*newChild)->rightChild = (*tree)->leftChild;
				(*tree)->leftChild = *newChild;
			}else if (isLeftChild == 0)
			{
				(*newChild)->rightChild = (*tree)->rightChild;
				(*tree)->rightChild = *newChild;
			}
			return SUCCESS;
		}
		STATUS left = insertChild(&(*tree)->leftChild, parentNode, isLeftChild, newChild);
		if (left == SUCCESS)
		{
			return left;
		}
		STATUS right = insertChild(&(*tree)->rightChild, parentNode, isLeftChild, newChild);
		return right;
	}
}
STATUS deleteChild(BinaryTree *tree, BTNode *parentNode, int isLeftChild) {
	if (*tree == NULL)
	{
		return ERROR;
	}
	else {
		if ((*tree)->data == parentNode->data)
		{
			if (isLeftChild == 1)
			{
				(*tree)->leftChild = NULL;
				return SUCCESS;
			}
			else if (isLeftChild == 0)
			{
				(*tree)->rightChild = NULL;
				return SUCCESS;
			}
		}
		int left = deleteChild(&(*tree)->leftChild, parentNode, isLeftChild);
		if (left != ERROR)
		{
			return left;
		}
		int right = deleteChild(&(*tree)->rightChild, parentNode, isLeftChild);
		return right;
	}
}
void prefixTraverse(BinaryTree tree){
	if(tree == NULL){
		return;
	}else{
		printf("%d ",tree->data);
		prefixTraverse(tree->leftChild);
		prefixTraverse(tree->rightChild);
	}
}
void infixTraverse(BinaryTree tree) {
	if (tree == NULL) {
		return;
	}
	else {
		infixTraverse(tree->leftChild);
		printf("%d ", tree->data);
		infixTraverse(tree->rightChild);
	}
}
void postfixTraverse(BinaryTree tree) {
	if (tree == NULL) {
		return;
	}
	else {
		postfixTraverse(tree->leftChild);
		postfixTraverse(tree->rightChild);
		printf("%d ", tree->data);
	}
}
void levelTraverse(BinaryTree tree) {
	if (tree == NULL)
	{
		return;
	}
	else {
		printf("%d ",tree->data);

	}
}
/*
	1������㷨������������ÿ���������Ҷ��ӡ�
	˼·:���������,ֱ��ʹ��ǰ��������в���
		����������,���Խ������ӽ���Ѻ���Ľ��һ�𽻻���
*/
void swapChild(BinaryTree *tree) {
	if (NULL == (*tree))
	{
		return;
	}
	else 
	{
		//��ȡ���Ҷ���,����ֻ�ǽ���������ֵ,����ֻ��Ҫȡһ����һ����ʱ���漴��
		BTNode *rightChild = (*tree)->rightChild;
		(*tree)->rightChild = (*tree)->leftChild;
		(*tree)->leftChild = rightChild;
		//�ݹ����������Ӻ��Ҷ���
		swapChild(&(*tree)->leftChild);
		swapChild(&(*tree)->rightChild);
	}
}
/*
	��������,ͬʱ��ֻ��һ���ӽ���������м���
	�ݹ���Ϊ�˱��ⷴ��������������,ֱ�Ӵ�����������ָ�뼴��
*/
void getCountOfNodeWithOneChild(BinaryTree tree,int *count) {
	if (NULL == tree)
	{
		return;
	}
	else 
	{
		if ((NULL != tree->leftChild && NULL == tree->rightChild) ||
			(NULL == tree->leftChild && NULL != tree->rightChild))
		{
			*count = *count + 1;
		}
		//�����ӽ��
		getCountOfNodeWithOneChild(tree->leftChild, count);
		getCountOfNodeWithOneChild(tree->rightChild, count);
	}
}