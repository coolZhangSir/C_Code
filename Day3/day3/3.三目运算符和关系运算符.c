#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

#define ���Ҫ��ĸ� 180
#define ���Ҫ��ĸ� 10000
#define ���Ҫ���˧ 95

#define ����Ҫ��ĸ� 180
#define ����Ҫ��ĸ� 1000000
#define ����Ҫ���˧ 95
/*
	3.ʵ���ļ������������Ŀ���������ϵ�����  �÷���ҳ����������������ҳ�����
	173  10000000   96
	173  10000000   96
	173  10000000   96
	�ض����
		< ���ļ�����
		> ���ļ����
*/
int main() {
	int height = 0;
	int handsome = 0;
	int wealthy = 0;

	for (int i = 0; i < 3; i++) {
		scanf("%d,%d,%d", &height, &wealthy,&handsome);
		printf("%d,%d,%d\n", height, handsome, wealthy);
		if (height >= ���Ҫ��ĸ� && handsome >= ���Ҫ���˧ && wealthy >= ���Ҫ��ĸ�) {
			printf("�������㻹����!\n");
		}
		else {
			printf("����Щ\n");
		}

		if (height >= ����Ҫ��ĸ� || handsome >= ����Ҫ���˧ || wealthy >= ����Ҫ��ĸ�) {
			printf("�����ʾ��������!\n");
		}
		else {
			printf("һ���浰ȥ\n");
		}
	}
	return 0;
}