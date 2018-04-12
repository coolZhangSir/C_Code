//�����Ϊ��
#include "SqList.h"
int isLegal(SqList *sqList){
	if(sqList->list == NULL){
		return FALSE;
	}else if(sqList->size <= 0){
		return FALSE;
	}

	return TRUE;
}

//�ж������Ƿ�����
int isFull(SqList *sqList){
	if(sqList->length >= sqList->size){
		return TRUE;
	}
	return FALSE;
}

//����һ��ָ����С�����Ա�,����ʼ������������Ϊ0,����ֵΪ������������Ա�,ѡ���ԵĽ��ܷ��ؽ��
SqList* init(SqList *sqList,int size){
	sqList->list = (ElemType *)calloc(size,sizeof(ElemType));
	sqList->length = 0;
	sqList->size = size;
	return sqList;
}

//��������Ԫ�ز����ô�С
SqList* clear(SqList *sqList){
	int i = 0;
	for(;i < sqList->length;i++){
		*(sqList->list + i) = 0;
	}
	sqList->length = 0;
	return sqList;
}

//���ٱ�,�������ַ,ͨ���ж��Ƿ�ΪNULL,ΪNULL�ɹ�����
SqList* destroy(SqList *sqList){
	free(sqList->list);
	sqList->list = NULL;
	sqList->length = 0;
	sqList->size = 0;
	free(sqList);
	sqList = NULL;
	return sqList;
}

//��ָ�����±�,����ָ����ֵ,Ĭ�ϲ嵽���,����ʧ�ܷ���-1,�ɹ��������±�
int insert(SqList *sqList,int index,ElemType element){
	//�Ϸ��Լ��
	if(!isLegal(sqList)){
		return ERROR;
	}
	if(isFull(sqList)){
		return ERROR;
	}

	if(index >= 0 && index < sqList->length){
		int i = sqList->length - 1;
		for(;i >= index;i--){
			*(sqList->list + i + 1) = *(sqList->list + i);
		}
		*(sqList->list + index) = element;
		sqList->length++;
		return index;
	}else{
		*(sqList->list + sqList->length) = element;
		sqList->length++;
		return sqList->length - 1;
	}
}

//ɾ��ָ�������ڵ�����,ʧ�ܷ���-1
int deleteByRange(SqList *sqList,int lowIndex,int highIndex){
	//�Ϸ����ж�
	if(lowIndex < 0 || lowIndex > sqList->length || highIndex < 0 || highIndex > sqList->length){
		return FALSE;
	}
	if(!isLegal(sqList)){
		return FALSE;
	}
	while(highIndex < sqList->length){
		*(sqList->list + lowIndex) = *(sqList->list + highIndex);
		lowIndex++;
		highIndex++;
	}
	sqList->length -= highIndex - lowIndex;
	return TRUE;
}
//ɾ������ָ��Ԫ�ص�ֵ
int deleteByValue(SqList *sqList,ElemType element){
	int i = 0;
	int j = i + 1;
	int count = 0;
	if(!isLegal(sqList)){
		return ERROR;
	}
	for(i = 0;i < sqList->length;i++){
		if(*(sqList->list + i) == element){
			for(j = i + 1;j < sqList->length - 1;j++){
				*(sqList->list + j - 1) = *(sqList->list + j);
			}
			count++;
		}
	}
	sqList->length -= count;
	return TRUE;
}

//����ָ��Ԫ���±�,δ�ҵ�����-1
int getIndex(SqList *sqList,ElemType element){
	int i = 0;
	if(!isLegal(sqList)){
		return FALSE;
	}
	
	for(i = 0;i < sqList->length;i++){
		if(*(sqList->list + i) == element){
			return i;
		}
	}
	return -1;
}
//ͨ�������±��ȡԪ��ֵ,�Ҳ�������-1
int getElement(SqList *sqList,int index){
	if(!isLegal(sqList)){
		return FALSE;
	}
	if(index < 0){
		return FALSE;
	}
	return *(sqList->list + index);
}
//���ر�ĳ���
int getLength(SqList *sqList){
	if(!isLegal(sqList)){
		return FALSE;
	}
	return sqList->length;
}

//�޸�ָ��Ԫ�ص�ֵ,ʧ�ܷ���-1,�ɹ�������ԭ����ֵ
int alterElement(SqList *sqList,int oldElement,ElemType newElement){
	if(!isLegal(sqList)){
		return FALSE;
	}

	for (int i = 0; i < sqList->length; i++)
	{
		if (*(sqList->list + i) == oldElement) {
			*(sqList->list + i) = newElement;
		}
	}
	return oldElement;
}

void display(SqList *sqList){
	int i = 0;
	printf("��ǰ��ĳ���:%d\n",getLength(sqList));
	printf("��ǰ����״̬:\n");
	for(i = 0; i < sqList->length;i++){
		printf("%d,",*(sqList->list + i));
	}
	printf("\n");
}