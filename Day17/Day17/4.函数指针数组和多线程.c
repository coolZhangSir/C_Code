#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#include<Windows.h>
void run1(void *p) {
	MessageBoxA(NULL, "1", "1", 0);
}
void run2(void *p) {
	MessageBoxA(NULL, "2", "2", 0);
}
void run3(void *p) {
	MessageBoxA(NULL, "3", "3", 0);
}
void function1(HANDLE *pp) {
	void (*p[])(void *) = { run1,run2,run3 };
	for (int i = 0; i < 3; i++)
	{
		//(*(p + i))(NULL);
		//�ڶ�����������0,��Ĭ�ϵ�ջ��С���ƹ�ȥ
		*(pp + i) = _beginthread((*(p + i)),0,NULL);
		//�첽�е�ͬ������
		//��һ���������ݾ��
		//�ڶ����������ݵȴ�ʱ��
		//WaitForSingleObject(*(pp + i),INFINITE);
	}
}
void main() {
	//ջ�ϵ�Handle����
	HANDLE handles[3];
	//���ϵ�Handle����
	HANDLE *p = malloc(sizeof(void *) * 3);
	function1(handles);
	//WaitForSingle/MultipleObject���������߳������˳�����
	//WaitForSingleObject(handles[0],INFINITE);
	//�ȴ��ľ��һ������,���߳��漴�˳�,false,�ȴ�һ��,�ʺ�ֻ��Ҫ�ҳ�һ�����Ľ���ĳ���
	//���Ϊtrue,��Ҫ�ȴ�ȫ��.�ʺϵȴ��������Ǹ�����ĳ���
	WaitForMultipleObjects(3,handles,FALSE,INFINITE);
	//system("pause");
}