#include<stdio.h>
#include<stdlib.h>

//length of pattern
#define N 5
//length of text
#define M 11

void buildNext(char *pattern, int *next);
int KMP_Match(char *text, char *pattern);

void main() {
	char *text = "abcaddabcaba";
	char *pattern = "abcab";
	
	int index = KMP_Match(text, pattern);

	if (index == -1)
	{
		printf("ƥ��ʧ��!\n");
	}
	else
	{
		printf("ƥ���±�:%d\n", index);
	}

	//for (int i = 0; i < N; i++)
	//{
	//	printf("%d ", next[i]);
	//}
	//printf("\n");

	system("pause");
}

void buildNext(char *pattern, int *next) {
	int i = -1, j = 0;
	next[0] = -1;

	while (j < N) {
		if (i == -1 || pattern[i] == pattern[j])
		{
			i++;
			j++;
			//û�ö��ڵĿռ�,���Է�ֹԽ��
			if (j < N)
			{
				next[j] = i;
			}
		}
		else
		{
			i = next[i];
		}
	}
}

/*
	�ҵ������±�,δ�ҵ�����-1
*/
int KMP_Match(char *text, char *pattern) {
	int i = 0, j = 0;
	int next[N] = { 0 };
	buildNext(pattern, next);

	while (i < M && j < N)
	{
		if (j == -1 || text[i] == pattern[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
		}
	}

	//abcaddabcab

	if (j >= N - 1)
	{
		return i - j;
	}
	else
	{
		return -1;
	}
}