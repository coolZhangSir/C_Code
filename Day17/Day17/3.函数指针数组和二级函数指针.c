#include<stdio.h>
#include<stdlib.h>
int add(int a,int b) {
	return a + b;
}
int subtract(int a, int b) {
	return a - b;
}
int multiply(int a, int b) {
	return a * b;
}
void function1() {
	/*
		����ָ������
			����:���� (*[])(�β�����);
			����:������������ַ,���������ö����ַ
			����:(*(p + i))(����)
	*/
	int(*p[])(int, int) = { add,subtract,multiply };
	for (int i = 0; i < 3; i++)
	{
		int result = (*(p + i))(100,10);
		printf("%d\n",result);
	}
}
void function2(){
	/*
		��������ָ��
		����:int (**pp)(int,int);
			�ɺ���ָ�������Ƶ�����
			int (*p[])(int,int),��[]�滻��һ��*
			p�Ǻ���ָ��������,�ȼ��ڶ�������ָ��pp
		����:1.���Բ���ָ������,ֱ��ͨ������ָ��ļӼ�����
	*/
	int (*p[])(int, int) = { add,subtract,multiply };
	int (**pp)(int, int) = p;
	for (pp = p; pp < p + 3; pp++)
	{
		//*û()���ȼ���,������Ҫ*pp����()
		printf("%d\n",(*pp)(100,10));
	}
	pp = p;
	for (int i = 0; i < 3; i++)
	{
		printf("%d\n",(*(pp + i))(100,10));
	}
}
void function3() {
	/*
		malloc��������ָ��
			����ָ�뼴ָ������,��malloc�����������ָ��Ŀռ伴��
			int(**pp)(int, int) = malloc(sizeof(int (*)(int, int)) * 4);
	*/
	int(**pp)(int, int) = malloc(sizeof(int (*)(int, int)) * 4);
	*(pp + 0) = add;
	*(pp + 1) = subtract;
	*(pp + 2) = multiply;
	for (int i = 0; i < 3; i++)
	{
		printf("%d\n",(*(pp + i))(100,10));
	}
}
void main() {
	//function1();
	//function2();
	function3();
	system("pause");
}