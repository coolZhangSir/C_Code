#include<stdio.h>
#include<stdlib.h>
void function1() {
	/*
		malloc����Ŀռ䲻���ʼ��
	*/
	int *p = malloc(sizeof(int) * 10);
	printf("%p\n",p);
	for (int i = 0; i < 10; i++)
	{
		*(p + i) = i + 1;
	}
	printf("%p\n", p);
	free(p);
}
void function2() {
	/*
	calloc����Ŀռ�ʱĬ�ϻ���������Ͷ����ʼ��Ϊ0
	*/
	double *p = calloc(10,sizeof(double));
	printf("%p\n", p);
	for (int i = 0; i < 10; i++)
	{
		*(p + i) = i + 1.0;
	}
	printf("%p\n", p);
	free(p);
}
void function3() {
	/*
		realloc������������Ŀռ��������չ�µĿռ�
		ԭ��:extern void *realloc(void *mem_address, unsigned int newsize);
		��չ���������:
			1.����ٴ���չ�Ŀռ䲻��,��С��ԭ���ռ�������ڵĿ����ڴ�
				��ô����ԭ��ʼ��ַ�϶���չ����Щ�ռ�
			2.����ٴ���չ�Ŀռ�ϴ�,������ԭ���ռ�������ڵĿ����ڴ�
				��ô�����·���һ���µĵ�ַ,���һ��ԭ����ֵ������ȥ���ͷ�ԭ�ռ�
		�ܽ�:
		1. reallocʧ�ܵ�ʱ�򣬷���NULL
		2. reallocʧ�ܵ�ʱ��ԭ�����ڴ治�ı䣬�����ͷ�Ҳ�����ƶ�
		3. ����ԭ�����ڴ���滹���㹻��ʣ���ڴ�Ļ���realloc���ڴ�=ԭ�����ڴ�+ʣ���ڴ�,realloc���Ƿ���ԭ���ڴ�ĵ�ַ; ����ԭ�����ڴ����û���㹻��ʣ���ڴ�Ļ���realloc�������µ��ڴ棬Ȼ���ԭ�����ڴ����ݿ��������ڴ��ԭ�����ڴ潫��free��,realloc�������ڴ�ĵ�ַ
		4. ���sizeΪ0��Ч����ͬ��free()��������Ҫע�����ֻ��ָ�뱾������ͷţ�����Զ�άָ��**a����a����reallocʱֻ���ͷ�һά��ʹ��ʱ�����ڴ�й¶��
		5. ���ݸ�realloc��ָ���������ǰͨ��malloc(), calloc(), ��realloc()�����
		6.���ݸ�realloc��ָ�����Ϊ�գ���ͬ��malloc��
	*/
	int *p = malloc(sizeof(int) * 10);
	for (int i = 0; i < 10; i++)
	{
		*(p + i) = i + 1;
	}
	printf("%p\n", p);
	int *newP = realloc(p,500 * sizeof(int));
	for (int i = 0; i < 520; i++)
	{
		*(newP + i) = i + 1 + 10;
	}
	printf("%p\n", newP);
	free(p);
	free(newP);
}
void function4() {
	/*
		_recalloc��realloc��������,ֻ��ǰ�߻��ʼ��.
	*/
	int *p = (int *)calloc(10,sizeof(int));
	for (int i = 0; i < 10; i++)
	{
		*(p + i) = i + 1;
	}
	printf("%p\n", p);
	int *newP = (int *)_recalloc(p,200,sizeof(int));
	printf("%p\n", newP);
}
void main() {
	//function1();
	//function2();
	//function3();
	function4();
	system("pause");
}