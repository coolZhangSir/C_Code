#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
void function1()
{
	/*
		����һ����������ڴ�
		����:һ����������ڴ�Ϊ2GB
	*/
	while (1) {
		malloc(10 * 1024 * 1024);
		Sleep(500);
	}
}
void function2() {
	/*
		malloc(��̬�ڴ�)���������������Ҫ��̬�����ڴ������.
		int array[10] = { 0 };
		C�����в��ܶ�̬�������鳤��,�����ж�����������ھ�̬�ڴ�,�������й����в����޸����С.
		����ջ�Ĵ�СĬ��1MB,�����޸�,����̫��Ӱ��Ч��.
	*/
	//������������鶯̬�Ĵ���һ��ָ�����ȵ�����
	int length = 0;
	printf("�������鳤��:\n");
	scanf("%d", &length);
	int *p = (int *)malloc(length * sizeof(int));
	for (int i = 0; i < length; i++)
	{
		*(p + i) = i + 1;
	}
	for (int i = 0; i < length; i++)
	{
		printf("%d ",*(p + i));
	}
	printf("\n");
	free(p);
}
void function3() {
	/*
		malloc
		ԭ��:void* malloc(size_t size);
			1.1 ����ָ���Ƭ�ڴ���׵�ַ,�������ʧ��,����0x00000000
			1.2 size_t ��unsigned int,�������-1,���Ӧ��ֵΪint�����ֵ,��ɷ���ʧ��
			1.3 malloc�ķ���ֵ������һά����������,Ҳ�����������ṹ������,��Ҫȡ��������
			1.4 malloc���Է���0,����û������
	*/
	//1.1
	//int length = 4123456789;
	
	//1.2
	//int length = -1;//��ʱ-1Ϊ����

	//1.3
	int length = 30 * sizeof(int);
	int (*p)[6] = malloc(length);
	printf("%p\n",p);
}
void function4() {
	/*
		2.free
			ԭ�� : void free(void *block);
			2.1 malloc����Ķ�̬�ڴ��ڳ����˳�ǰ�����Զ��ͷ�, �����ֶ��ͷ�,���ͷŻ�����ڴ�й¶.
			2.2 freeֻ���ͷ�һ��,���������ͷ�,�ᴥ���ϵ�
			2.3 free�ͷ�֮���ٴβ������ڴ���ܻ���������,
				����free�ͷ�֮����ý���ָ��ָ��NULL,������ָ��ᱨ��,�������δ֪����	
			2.4 �ͷ�֮��δָ��NULL��ָ���Ϊ"��;ָ��"
	*/
	int length = 30;
	int *p = (int *)malloc(length);
	printf("%p\n",p);
	free(p);
	//2.3
	//*p = 123;
	p = NULL;
	//2.2
	//free(p);
}
void main() {
	//function1();
	//function2();
	//function3();
	function4();
	system("pause");
}