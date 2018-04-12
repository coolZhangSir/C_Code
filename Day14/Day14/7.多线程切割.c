#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<process.h>

#define N 100
#define THREAD_COUNT 8

typedef struct SearchInfo {
	int *startPoint;
	int count;
	int target;
	int threadId;
}SearchInfo;

void init(int *array) {
	time_t t;
	srand(time(&t));
	for (int i = 0; i < N; i++)
	{
		*(array + i) = rand() % 100;
	}
}
void show(int *array) {
	for (int i = 0; i < N; i++)
	{
		printf("%2d ", *(array + i));
		if ((i + 1) % THREAD_COUNT == 0) {
			printf("\n");
		}
	}
	printf("\n");
}
void work(void *p) {
	SearchInfo *info = (SearchInfo *)p;
	//printf("�߳�%d��ʼ��������\n", info->threadId);
	for (int i = 0; i < info->count; i++)
	{
		if (*(info->startPoint + i) == info->target)
		{
			printf("�߳�%d���ҵ�����%d\n", info->threadId, *(info->startPoint + i));
			return;
		}
	}
	printf("�߳�%d��������\n", info->threadId);
}
void main() {
	int array[N];
	init(array);
	show(array);

	int target = 0;
	printf("����Ŀ������:\n");
	scanf("%d", &target);

	//��ý�����cpu���������ɱ������߳���,�����Ч��
	SearchInfo info[THREAD_COUNT];
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		int *startIndex = array + THREAD_COUNT * i;
		//���ﲻ�ô���һ������,��Ϊ����������ܵ���ָ������,���������������ĵ�ַ��ȥ,��ôÿһ���߳���ʹ�õĲ���ȫ����һ����.
		//SearchInfo info;
		info[i].startPoint = startIndex;
		//�Ƚ����ҵĻ���,93���ܳ���,��Ҫ���⴦��
		if ((N - THREAD_COUNT * i) % THREAD_COUNT == 0)
		{
			info[i].count = N - THREAD_COUNT * i % THREAD_COUNT;
		}
		else {
			info[i].count = THREAD_COUNT;
		}
		info[i].target = target;
		info[i].threadId = i + 1;
		
		_beginthread(work, 0, &info[i]);
	}

	system("pause");
}