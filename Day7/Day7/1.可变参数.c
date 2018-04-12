#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
/*
	�ɱ������Ҫ�����׼����(stdarg.h)ͷ�ļ�,�����ֱ������������ķ���
		1.����һ��������Ϊ��ʶ��������
		2.�����һ��������Ϊ���������ı�־
	va_start(list,start)�ǲ����ȡstart������,ֻ������ĺ��濪ʼ��
*/
//��һ����ʶ�������� ...�ǿɱ�����ı�ʶ
void test1(int count,...){
	va_list list;//��Ų�������ʼ��ַ
	int i = 0;
	int result = 0;
	va_start(list,count);//���������ʼ��ַ�Ͳ�������,���׵�ַ��ʼ��ȡcount������
	for(i = 0;i < count;i++){
		result += va_arg(list,int);//����ʼ��ַ��ʼ��ȡ����,����ȡ��ÿ������ת��Ϊint����
	}
	va_end(list);
	printf("%d\n",result);
}
//��ĳһ��ֵ��Ϊ���������ı�־
void test2(int start,...){
	va_list list;
	int i = 0;
	int result = 0;
	int arg = start;
	
	va_start(list,start);
	
	do{
		printf("%d ",arg);	
		arg = va_arg(list,int);
		result += arg;
	}while(arg != -1);
	
	va_end(list);
	printf("\n%d\n",result);
}
void main(){
	test1(3,2,1,4);
	test2(5,3,5,2,-1);
	system("pause");
}