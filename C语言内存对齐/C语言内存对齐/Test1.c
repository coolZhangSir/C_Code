//�ο�����:https://blog.csdn.net/tic_yx/article/details/9718971
/*
	�ص�����:
		1.�ṹ���е�һ����Ա��ַʼ����ṹ�������ַ��ͬ
		2�������ԭ��
		ԭ��1�����ݳ�Ա������򣺽ṹ��struct������union�������ݳ�Ա����һ�����ݳ�Ա����offsetΪ0�ĵط����Ժ�ÿ�����ݳ�Ա�洢����ʼλ��Ҫ�Ӹó�Ա��С����������ʼ������int��32λ��Ϊ���ֽڣ���Ҫ��4����������ַ��ʼ�洢����

		ԭ��2���ṹ����Ϊ��Ա�����һ���ṹ����ĳЩ�ṹ���Ա����ṹ���ԱҪ�����ڲ����Ԫ�ش�С����������ַ��ʼ�洢����struct a�����struct b��b����char��int��double��Ԫ�أ���bӦ�ô�8����������ʼ�洢����

		ԭ��3����β�������ṹ����ܴ�С��Ҳ����sizeof�Ľ�������������ڲ�����Ա���������������Ҫ���롣

*/
#include<stdio.h>
#include<stdlib.h>

struct A {
	char a;
	char b;
};

struct B {
	int a;
	char b;
};

void main() {
	
	printf("sizeof(A):%d\n", sizeof(struct A));
	printf("sizeof(B):%d\n", sizeof(struct B));

	system("pause");
}