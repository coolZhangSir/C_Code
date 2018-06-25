#include "Huffman.h"
void main() {
	int weights[N] = { 5,29,7,8,14,23,3,11 };
	HuffmanTree tree = NULL;
	initTree(&tree,weights);
	createTree(&tree);
	for (int i = 0; i < 2 * N - 1; i++)
	{
		if ((tree + i)->parent == 0)
		{
			prefix(tree + i);
		}
		//printf("%d:weight=%d,parent=%d\n",i + 1,(tree + i)->weight, (tree + i)->parent);
	}
	char **codes = NULL;
	codes = malloc(sizeof(char *) * N);
	for (int i = 0; i < N; i++)
	{
		//������'\0'�Ĵ���,��Ҫ����һ��
		codes[i] = malloc(sizeof(char) * (N + 1));
		//����ʹ�õ�calloc,���Բ��ó�ʼ�����N��
		for (int j = 0; j < N + 1; j++)
		{
			codes[i][j] = '\0';
		}
		encodeRecursive(tree,tree + i,codes[i] + N);
	}
	for (int i = 0; i < N; i++)
	{
		printf("%d:", (tree + i)->weight);
		for (int j = 0; j < N + 1; j++)
		{
			//��Ҫ��ͼ��%c��ӡ0('\0'),������ʾ�ַ���ӡ����滷����cmd���벻ͬ����ͬ,���ı����cmd�»����'a'
			if (codes[i][j] != '\0') {
				printf("%c ",codes[i][j]);
			}
		}
		printf("\n");
	}
	system("pause");
}