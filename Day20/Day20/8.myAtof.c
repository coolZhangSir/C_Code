#include<stdio.h>
#include<stdlib.h>
float myAtof(char *p) {
	//���п�
	if (p == NULL)
	{
		return 0.0f;
	}
	char *value = p;
	float result = 0.0f;
	int flag = 1;
	//�жϷ���λ
	if (*value == '-')
	{
		flag = -1;
		value++;
	}
	//���ȡ���ַ�����ת��,������'\0'ASCIIΪ0,���ַ�'0'ASCII��Ϊ48
	//�жϵ�ǰ�Ǵ���С�����ֻ�����������
	int isInteger = 1;
	//С����Ļ���,��һλ*0.1,�ڶ�λ*0.01
	float radix = 0.1f;
	while (*value != 0)
	{
		if ((*value < '0' || *value >'9') && *value != '.')
		{
			return 0.0f;
		}
		//����С������������ѭ��ȥ����С������
		if (*value == '.')
		{
			//����С����
			value++;
			isInteger = 0;
			continue;
		}
		if (isInteger == 1)
		{
			result *= 10.f;
			result += (*value) - '0';
		}
		else
		{
			float temp = (*value - '0') * radix;
			result += temp;
			radix *= 0.1f;
		}
		value++;
	}
	return result * flag;
}
void main() {
	char *p = "-3.1004";
	//float result = atof(p);
	float result = myAtof(p);
	printf("%f\n",result);
	system("pause");
}