#include<stdio.h>
#include<stdlib.h>
/*
	ʹ��λ����ʵ�ּӼ��˳�ȡģ
	�ӷ��������������������,Ȼ��ͨ���������ж����޽�λ�����,�����ֱ������һλ����
*/
int add(int a,int b){
	int sum = 0;
	sum = a ^ b;
	if(a & b != 0){
		sum += ((a & b) << 1);
	}
	return sum;
}
/*
	5 - 3 = 2
	5�Ĳ���:
		0000 0101
	
	3��ԭ��
	�Ƚ���ת���ɸ���
		0000 0011 ==>  1111 1100
	�����䷴��
		1000 0011 ==>  1111 1100
	��+1�õ�����
		1111 1100 ==>  1111 1101
	�ٽ��мӷ�
*/
void substract(int a,int b){
	int mask = 4294967295;
	int minus = 0;
	//�����õ�����
	b ^= mask;
	//��1�õ�����
	b += 1;
	minus = add(a,b);
	printf("%d\n",minus);
}
/*
	�˷����Ƕ���ӷ�
*/
void times(int a,int b){
	int i = 0;
	int sum = a;
	
	for(;i < b - 1;i++){
		sum = sum ^ a;
		if((a & a) != 0){
			sum += ((a & a) << 1);
		}
	}
	printf("%d\n",sum);
}
/*
	����:��������ȡ��+1�õ����Ӧ�ĸ����Ĳ���.
		 Ȼ����ݳ������ڱ���������������ѭ���������ټ�1
*/
void divide(int a,int b){
	int result = 1;
	int mask = 4294967295;
	int sum = 0;
	int c = b;
	while(a > c){
		b = c;

		b ^= mask;
		b += 1;
		 
		sum = a ^ b;
		
		//���������,!=�����ȴ���&������
		if((a & b) != 0){
			sum += ((a & b) << 1);
		}
		a = sum;
		result++;
	}

	printf("%d\n",result);
}

/*
	ȡ����ǽ��г���,�����С�ڱ������ĳ�����Ϊ����
*/
void remainder(int a,int b){
	int c = b;
	int mask = 4294967295;
	int sum = 0;
	while(a >= c){
		b = c;
		b  = b ^ mask;
		
		sum = b ^ 1;
		if((b & 1) != 0){
			sum += ((b & 1) << 1);
		}
		
		b = sum;

		sum = a ^ b;
		if((a & b) != 0){
			sum += ((a & b) << 1);
		}
		
		a = sum;
	}
	printf("%d\n",a);
}

void main(){
	//add(3,5);
	//substract(5,3);
	times(12,2);
	//divide(35,5);
	//remainder(33,5);
	system("pause");
}