#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
/*
	ͨ��getCursorPos��ȡ��ǰ���λ�ò�������Point�ṹ����.
	Ȼ��ͨ��setWindowPosition()�����ô���λ��
*/
void main() {
	POINT point;
	
	HWND win = FindWindowA("TXGuiFoundation", "QQ");
	if (win == NULL) {
		printf("�ô��ڲ�����\n");
	}else{
		while (1) {
			GetCursorPos(&point);
			SetWindowPos(win, 0, point.x + 200, point.y + 200, 300, 300, 1);
		}
	}
	system("pause");
}