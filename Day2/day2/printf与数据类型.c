#include<stdio.h>
int main() {
	/*
		��ͬ���͵�����:
		��С��ͬ,�����ķ�ʽ��ͬ.
		�����С����ʹ��sizeof�ؼ���(���Ǻ���)�鿴���ʹ�С

		printf()�������ᰴ�������Զ�ת��
		�������%dȥ��ӡһ��������,��ô�ͻ���ִ���.
		�����Ҫ���������ո�������ӡ��ô��Ҫ��ӡ��ʱ�����ǿ������ת��
	*/
	int number = 10;
	//printf("%f\n",number); ����
	printf("%f\n",(float)number);
	
	float number1 = 10.0f;
	//printf("%d\n", number1);����
	printf("%d\n", (int)number1);

	getchar();
	return 0;
}