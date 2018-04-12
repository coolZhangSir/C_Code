#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int myAtoi(const char *p) {
	if (p == NULL)
	{
		return NULL;
	}
	int result = 0;
	int flag = 1;
	//�ж��ǲ��Ǹ���,�ǵĻ��ѷ���λ��Ϊ-1,�����ٳ�����
	if (*p == '-') {
		flag = -1;
		*p++;
	}
	//���ȡ��ÿһλȥ��,�õ������,ѭ������������'\0'(0),�������ַ�'0'(48)
	while (*p)
	{
		if (*p < '0' || *p > '9')
		{
			return -1;
		}
		int per = *p - 48;
		p++;
		result *= 10;
		result += per;
	}
	return result * flag;
}
char *myItoa(int value,void *buffer,int radix) {
	char *buffer_temp = buffer;
	if (value == 0)
	{
		*buffer_temp = '0';
		return buffer;
	}
	//�ж��Ƿ���,��Ӹ���
	if (value < 0)
	{
		*buffer_temp = '-';
		buffer_temp++;
	}
	//��ȡ����λ��
	int length = 0;
	int value_temp = abs(value);
	while (value_temp > 0)
	{
		value_temp /= 10;
		length++;
	}
	//ָ��Ӻ�����ǰ��
	value_temp = abs(value);
	while (length > 0) {
		//�±��ʵ����1
		*(buffer_temp + length - 1) = value_temp % 10 + '0';
		value_temp /= 10;
		length--;
	}
	return buffer;
}
void main() {
	char *p = "-1203";
	//int result = atoi(p);
	int result = myAtoi(p);
	printf("%d\n",result);

	int number = -45;
	char buffer[4] = { 0 };
	_itoa_s(number, buffer, 4, 10);
	//myItoa(number, buffer, 10);
	printf("%s\n", buffer);
	
	system("pause");
}