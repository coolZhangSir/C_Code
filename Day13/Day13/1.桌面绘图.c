#include<stdio.h>
#include<Windows.h>
void main() {

	//��ȡ����ľ��
	HWND windowHandle = GetDesktopWindow();
	//��ȡ������ʾ�����������л���
	HDC windowDC = GetWindowDC(windowHandle);
	//��ȡ�ڴ���һ��λͼ���������л���
	HDC memoryDC = CreateCompatibleDC(0);
	HBITMAP bitmap = (HBITMAP)LoadImage(windowHandle,TEXT("1.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	SelectObject(memoryDC, bitmap);
	while (1) {
		BitBlt(windowDC, 0, 0, 500, 500, memoryDC, 0, 0, SRCCOPY);
	}
}