#include<stdlib.h>
#include<stdio.h>
#include<Windows.h>
void main() {
	HWND win = FindWindowA("#32770", "MFCApplication1");
	if (win == NULL) {
		printf("�ô��岻����\n");
	}
	else {
		//���ô��ڱ���
		//SetWindowText(win, "�����");
		//Sleep(5000);
		//��ʾ/���ش���
		//ShowWindow(win, 0);
		//Sleep(5000);
		//ShowWindow(win, 1);
		//Ѱ���Ӵ���
		HWND child = FindWindowExA(win, 0, "Button", "Button1");
			//���ô���
			//EnableWindow(child, 0);
			//Sleep(5000);
			//EnableWindow(child, 1);
		//ģ�����ϵͳ��������͸�����Ϣ
		//���͹ر���Ϣ
		//SendMessageA(child,WM_CLOSE,0,0);
		//���͵����Ϣ,���Ŀ�괰��û�л�ý���,��Ҫ�������ε����Ϣ,��һ����Ϣ�ǻ�ȡ����
		//SendMessageA(child,BM_CLICK,0,0);
		//SendMessageA(child, BM_CLICK, 0, 0);

		//�ҵ��༭��ľ��,���䷢���ַ�,����Ƿ����ַ�,��һ���Ƿ��͵��ַ�,�ڶ���������
		HWND edit = FindWindowExA(win, 0, "Edit", "");
		SendMessageA(edit, WM_CHAR, 65, 2);
		SendMessageA(edit, WM_GETTEXT, 0, 0);
	}
}