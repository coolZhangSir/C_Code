#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<process.h>//ʹ���̱߳���Ҫ�����ͷ�ļ�
/*
	ʹ�ö��߳���Ҫע�������:
		1.�̱߳�����һ������,������������,���ǲ���������void*����
		2.�����̵߳ķ�ʽΪ_beginthread(������ַ,��ջ��С�� 0,������NULL);
		3.������߳��˳�,�����߳�Ҳ����֮�ҵ�
		
*/
void testThread(void *p) {
	MessageBoxA(0, "����", "����", 0);
}
void main() {
	//���̴߳�5���Ի���
	/*for (int i = 0; i < 5; i++)
	{
		MessageBoxA(0, "����", "����", 0);
	}*/
	for (int i = 0; i < 5; i++)
	{
		_beginthread(testThread, 0, NULL);
	}

	system("pause");//��֤���̲߳���,�������߳�Ҳ���������
}