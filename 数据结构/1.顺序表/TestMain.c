#define _CRT_SECURE_NO_WARNINGS
#include "SqList.h"

void main(){
	int flag = 0;
	SqList *sqList = (SqList*)malloc(sizeof(SqList));
	init(sqList,10);
	int operateElement = -1;
	while (1) {
		int action = 0;
		printf("����ѡ��(�������):\n");
		printf("0.�˳� 1.���� 2.ɾ�� 3.�޸� 4.��ѯ\n");
		scanf("%d",&action);
		switch (action)
		{
		case 0:
			flag = 1;
			break;
		case 1:
			printf("�����Ԫ��:\n");
			scanf("%d", &operateElement);
			printf("ָ������λ��(-1Ĭ��Ϊ���һ��):\n");
			int insertIndex = -1;
			scanf("%d", &insertIndex);
			insert(sqList, insertIndex, operateElement);
			display(sqList);
			break;
		case 2:
			printf("1.ɾ��ָ��Ԫ��ֵ 2.ɾ��ĳһ��Χ\n");
			int deleteOption = 1;
			scanf("%d",&deleteOption);
			if (deleteOption == 1)
			{
				printf("����ָ����Ԫ��ֵ:\n");
				scanf("%d", &operateElement);
				deleteByValue(sqList, operateElement);
			}
			else {
				printf("����ָ���ķ�Χ(���ŷָ�):\n");
				int start = 0, end = 0;
				scanf("%d,%d", &start,&end);
				deleteByRange(sqList, start,end);
			}
			display(sqList);
			break;
		case 3:
			printf("���޸�Ԫ��:\n");
			scanf("%d", &operateElement);
			printf("�����޸ĵ�ֵ:\n");
			int newElement = 0;
			scanf("%d", &newElement);
			alterElement(sqList, operateElement, newElement);
			display(sqList);
			break;
		case 4:
			printf("1.��ȡָ��λ�õ�ֵ 2.��ȡָ��ֵ��λ�� 3.��ʾ��ǰ��\n");
			int queryOption = 1;
			scanf("%d", &queryOption);
			int result = 0;
			if (queryOption == 1)
			{
				printf("����ָ����λ��:\n");
				int queryIndex = 0;
				scanf("%d", &queryIndex);
				result = getElement(sqList,queryIndex);
				printf("%dλ�õ�ֵΪ:%d\n", queryIndex, result);
			}
			else if(queryOption == 2){
				printf("����ָ����ֵ:\n");
				scanf("%d", &operateElement);
				result = getIndex(sqList, operateElement);
				printf("%d���±�Ϊ:%d\n",operateElement,result);
			}
			else{
				display(sqList);
			}
			break;
		default:
			break;
		}

		if (flag == 1)
		{
			break;
		}

		printf("\n\n");
	}

	system("pause");
}