#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
/*
	����:
		�Զ��������,����Զ�������������,Ȼ���Ԥ��ѡ����
*/

/*
	1.ͨ���������ָ����վ
*/
void open(char* url) {
	ShellExecuteA(0, "open", url, "", "", 1);
}

/*
	������������
	keybd_eventע��:
		1.Ӳ�����벻�����ⰴ��ֵ,���Բ�����,���˷������˺���
		2.���������������ɿ��¼�֮��,��0����,����ʹ����ϼ���������
		3.���ĸ������Ͳ�������,һ�㶼����
*/
void input() {
	//1.����Ӣ��
	keybd_event('S', 0x53, 0, 0);
	keybd_event('S', 0x53, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('U', 0x55, 0, 0);
	keybd_event('U', 0x55, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('P', 0x50, 0, 0);
	keybd_event('P', 0x50, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('A', 0x41, 0, 0);
	keybd_event('A', 0x41, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('R', 0x52, 0, 0);
	keybd_event('R', 0x52, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('C', 0x43, 0, 0);
	keybd_event('C', 0x43, KEYEVENTF_KEYUP, 0);
	//2.�л����뷨
	keybd_event(VK_LCONTROL, 0, 0, 0);
	Sleep(40);
	keybd_event(VK_SPACE, 0, 0, 0);
	Sleep(40);
	keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
	Sleep(50);
	keybd_event(VK_LCONTROL, 0, KEYEVENTF_KEYUP, 0);
	Sleep(50);
	//3.���뺺��
	keybd_event('C', 0, 0, 0);
	keybd_event('C', 0, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('F', 0, 0, 0);
	keybd_event('F', 0, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('H', 0, 0, 0);
	keybd_event('H', 0, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('K', 0, 0, 0);
	keybd_event('K', 0, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event(VK_SPACE, 0, 0, 0);
	keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('G', 0, 0, 0);
	keybd_event('G', 0, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('U', 0, 0, 0);
	keybd_event('U', 0, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('C', 0, 0, 0);
	keybd_event('C', 0, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event('K', 0, 0, 0);
	keybd_event('K', 0, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event(VK_SPACE, 0, 0, 0);
	keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
	Sleep(40);
	keybd_event(VK_RETURN, 0, 0, 0);
	keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
}

/*
	ģ��������,�򿪵�һ������
	1.���������MOUSEEVENTF_ABSOLUTE,�������ƶ�������ڵ�ǰλ��.����֮��,������Ļ�ᱻ�ָ��65536 * 65535,�����ƶ���������Ҫͨ����ʽ����
	2.�ڶ��͵��������������������ƶ��¼��Ͳ�����,����Ǿ���
	3.���ĺ͵��������
*/
void moveMouse() {
	Sleep(1000);
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, 250 * 65535 / 1920, 220 * 65535 / 1080, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}
/*
	ͨ��cmd����ر����������
*/
void close() {
	system("taskkill /f /im chrome.exe");
}
int main() {
	char* url = "http://www.baidu.com";
	
	open(url);
	Sleep(1500);
	input();
	Sleep(100);
	moveMouse();
	Sleep(5000);
	close();
	return 0;
}
