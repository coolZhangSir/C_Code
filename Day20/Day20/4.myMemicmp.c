#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<math.h>
int myMemicmp(const void *buffer1, const void *buffer2,int size) {
	char *buffer_1 = buffer1;
	char *buffer_2 = buffer2;

	for (int i = 0; i < size; i++)
	{
		//��ΪҪ���Դ�Сд,���ж��Ƿ�Ϊ�ַ���
		if ((*(buffer_1 + i) >='a' && *(buffer_1 + i) <= 'z') ||
			(*(buffer_1 + i) >= 'A' && *(buffer_1 + i) <= 'Z')) {
			if (*(buffer_2 + i) >= 'a' && *(buffer_2 + i) <= 'z' ||
				(*(buffer_2 + i) >= 'A' && *(buffer_2 + i) <= 'Z')) {
				//�������������0����32,��˵����ͬһ���ַ����ߴ�Сд
				int difference = abs(*(buffer_1 + i) - *(buffer_2 + i));
				if (difference == 0 || difference == 32)
				{
					//ͬһ�ַ�ֱ������,������һ��,��ͬ��ֱ���������жϴ�С
					continue;
				}
			}
		}
		if (*(buffer_1 + i) > *(buffer_2 + i)) {
			return 1;
		}
		else if (*(buffer_1 + i) < *(buffer_2 + i)) {
			return -1;
		}
	}
	return 0;
}
void main() {
	//_memicmp:�Ƚ������ַ���ǰN���ֽ��Ƿ���ͬ(���Դ�Сд)
	char *a = "abcd";
	char *b = "ABCD";
	//int result = _memicmp(a, b, 4);
	int result = myMemicmp(a, b, 4);
	printf("%d\n",result);
	int c[] = { 1,2,5,4 };
	int d[] = { 1,2,5,3 };
	//���ıȷ�Ҳ��һ���ֽ�һ���ֽڵıȽ�,���������������ֽ���ȫ��ͬ��������ͬ�����õ��ý���
	//result = _memicmp(c, d, 9);
	result = myMemicmp(c, d, 12);
	printf("%d\n", result);
	system("pause");
}