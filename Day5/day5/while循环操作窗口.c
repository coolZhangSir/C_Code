#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
/*
	ͨ��Win32Api���������ƶ�
*/
int main() {
	//ͨ�������ͱ����ȡ���ھ��,����Ҳ����򷵻�NULL
	HWND win = FindWindowA("TXGuiFoundation", "QQ");
	//ͨ����������ô����Ƿ���ʾ
	ShowWindow(win,SW_SHOW);
	int i = 0;
	while (i <= 1080) {
		//ͨ��������ô����Ƿ���ʾ,����,�����С
		SetWindowPos(win, NULL, i * 1920 / 1080, i, 430, 333, 0);
		if (i % 2 == 0) {
			ShowWindow(win, SW_HIDE);
		}
		else {
			ShowWindow(win, SW_SHOW);
		}
		i++;
		Sleep(20);
	}
	return 0;
}