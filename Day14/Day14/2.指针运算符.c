#include<stdio.h>
#include<stdlib.h>
/*
	����:ָ���++/--��ַƫ�Ƶĳ���ȡ������������,intΪ4�ȵ�
*/
void main() {
	int intArr[] = { 0,1,2,3,4 };
	char charArr[] = { 'A','B','C','D' };
	float floatArr[] = { 1.0f,2.0f,3.0f,4.0f };
	double doubleArr[] = { 1.0,2.0,3.0,4.0 };
	//��ʼ��ָ��
	int *pInt = intArr;
	int *pInt1 = &intArr[3];
	char *pChar = charArr;
	float *pFloat = floatArr;
	double *pDouble = doubleArr;

	//����ָ���������,ʵ���Ͼ������м�����Ԫ�ظ���:(��ַ-��ַ)/sizeof(����)
	printf("ָ�����:%d\n",pInt1 - pInt);

	//����ָ������
	*pInt++;
	printf("intָ��++:%d\n",*pInt);

	*pChar++;
	printf("charָ��++:%c\n", *pChar);

	*pFloat++;
	printf("floatָ��++:%f\n", *pFloat);

	*pDouble++;
	printf("doubleָ��++:%lf\n", *pDouble);

	system("pause");
}