#include<Windows.h>
#include<stdlib.h>
/*
	Win32�еĶ��̴߳���
*/
DWORD WINAPI myMessage(LPVOID lp) {
	MessageBoxA(0, "�Ի���", "test", 0);
}
void main() {
	HANDLE handle;
	DWORD threadId = 0;
	for (int i = 0; i < 5; i++)
	{
		handle = CreateThread(
					NULL,//��ȫ����
					NULL,//��ջ��С
					myMessage,//������ڵ�
					NULL,//�����Ĳ���
					0,//����ִ��
					&threadId//�߳�ID
		);

		//���߳��е�ͬ��
		WaitForSingleObject(handle,INFINITE);
	}
	system("pause");
}