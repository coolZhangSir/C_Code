#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<process.h>

#define N 93

//ȫ�ֱ���,�����߳�֮��ͨ��,�����һ���߳��ҵ���Ӧ��ֵ,���޸���ֵ,�����߳�ÿ���ж���ֵ�Ƿ����ı�
int isFind = 0;

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
		if ((i + 1) % 10 == 0) {
			printf("\n");
		}
	}
	printf("\n");
}
void work(void *p) {
	SearchInfo *info = (SearchInfo *)p;
	for (int i = 0; i < info->count; i++)
	{
		if (isFind) {
			printf("�����߳����ҵ�,�߳�%d�˳�\n",info->threadId);
			return;
		}
		if (*(info->startPoint + i) == info->target)
		{
			printf("�߳�%d���ҵ�����%d\n",info->threadId,*(info->startPoint + i));
			isFind = 1;
			return;
		}
	}
}
void main() {
	int array[N];
	init(array);
	show(array);

	int target = 0;
	printf("����Ŀ������:\n");
	scanf("%d",&target);

	//��ý�����cpu���������ɱ������߳���,�����Ч��
	SearchInfo info[10];
	for (int i = 0; i < 10; i++)
	{
		int *startIndex = array + 10 * i;
		//���ﲻ�ô���һ������,��Ϊ����������ܵ���ָ������,���������������ĵ�ַ��ȥ,��ôÿһ���߳���ʹ�õĲ���ȫ����һ����.
		//SearchInfo info[i];
		info[i].startPoint = startIndex;
		//�����ڱȽϹ��ɵĻ���,���Գ����Ļ��Ͳ������⴦��
		info[i].target = target;
		info[i].threadId = i + 1;
		_beginthread(work, 0, &info[i]);
	}

	system("pause");
}