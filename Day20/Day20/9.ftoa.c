#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
void* ftoa(float value,void *buffer,int size) {
	//�п�
	if (buffer == NULL || size == 0)
	{
		return NULL;
	}
	char *buffer_temp = buffer;
	//ǰ�������λ��ҪС��ָ���������ַ����ĳ���
	int currentIndex = 0;
	//�и�
	if (value < 0)
	{
		*buffer_temp = '-';
		buffer_temp++;
		currentIndex++;
	}
	//��ȡ�������ֳ���
	int integer = (int)value;
	int int_length = 0;
	while (integer > 0)
	{
		integer /= 10;
		int_length++;
	}
	//�ɻ�,��ת��������
	//�ٴ������������ֵ�ֵ
	integer = (int)value;
	//���ݳ���,����Ҫ��
	int  length_backup = int_length;
	while (length_backup > 0)
	{
		//�����ǰ�Ѿ������ٽ�λ��,�������һλ���'\0'������,�����Ǵ�0��ʼ���±�,����ʵ���±�ͳ������1
		if (currentIndex == size - 1)
		{
			*buffer_temp = '\0';
			return buffer;
		}
		*(buffer_temp + length_backup - 1) = integer % 10 + '0';
		integer /= 10;
		length_backup--;
		currentIndex++;
	}
	//Խ���������ֲ����С����
	buffer_temp += int_length;
	*buffer_temp = '.';
	buffer_temp++;
	currentIndex++;
	//����С����
	//�Ȼ�ȡС��
	float decimal = value - (int)value;
	while (decimal > 0)
	{
		//�����ǰ�Ѿ������ٽ�λ��,�������һλ���'\0'������,�����Ǵ�0��ʼ���±�,����ʵ���±�ͳ������1
		if (currentIndex == size - 1)
		{
			*buffer_temp = '\0';
			return buffer;
		}
		//С��ÿ�γ���10��ȡ�������Ի�ȡһλ����
		decimal *= 10;
		int int_decimal = (int)decimal;
		//���õ����Ǹ���������ת��
		*buffer_temp = int_decimal + '0';
		buffer_temp++;
		//С����ȥǰ��������͵õ����µ�С��
		decimal -= int_decimal;
		currentIndex++;
	}
	return buffer;
}
void main() {
	float number = 3.14f;
	char buffer[8] = { 0 };
	//ʵ��ת�ַ���ʵ�������п�����sprintf�����
	//sprintf(buffer, "%f", number);
	ftoa(number,buffer,4);
	printf("%s\n",buffer);
	system("pause");
}