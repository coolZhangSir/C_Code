#include<Windows.h>

void onInit();
void onDestroy();
void luanzishan_1p();
void luanzishan_2p();
int getScanCode(int code);
void registerQuickPower();

int WINAPI WinMain(HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow) {

	onInit();

	MSG msg;
	while (GetMessage(&msg,NULL,0,0))
	{
		if (msg.message == WM_HOTKEY)
		{
			if (msg.wParam == 0x1)
			{
				MessageBoxA(NULL,"�����ɹ�","��ʾ",0);
				registerQuickPower();
			}

			if (msg.wParam == 0x3)
			{
				luanzishan_1p();
			}

			if (msg.wParam == 0x4)
			{
				luanzishan_2p();
			}

			if (msg.wParam == 0x2)
			{
				MessageBoxA(NULL, "�رճɹ�", "��ʾ", 0);
				onDestroy();
			}
		}
	}
}

void onInit() {
	//ע�Ὺ��һ������ɽ�ȼ�
	RegisterHotKey(NULL, 0x1, 0, VK_HOME);

	//ע���˳��ȼ�
	RegisterHotKey(NULL, 0x2, 0, VK_END);

	MessageBoxA(NULL, "����ɽ���µ�һ!", "��ʾ", 0);
}

void onDestroy() {
	//���һ������ɽ�ȼ�
	UnregisterHotKey(NULL, 0x1);

	//����˳��ȼ�
	UnregisterHotKey(NULL, 0x2);

	//�������ɽ�ȼ�
	UnregisterHotKey(NULL, 0x3);
	UnregisterHotKey(NULL, 0x4);

	exit(0);
}

void registerQuickPower() {
	//ע��һ������ɽ�ȼ�
	RegisterHotKey(NULL, 0x3, 0, 'Y');
	RegisterHotKey(NULL, 0x4, 0, 'O');
}

//һ������ɽ(1P)
//164636d+D
//ͨ��comoboMaker�۲�ó�,��һ��б�������ͣ��2֡����,4268�ĸ��������ֻ��1֡
//kwģ������һ֡������40����
void luanzishan_1p() {
	////1
	//keybd_event('A', getScanCode('A'), 0, 0);
	//keybd_event('S', getScanCode('S'), 0, 0);
	//Sleep(70);
	//keybd_event('A', getScanCode('A'), 2, 0);
	//keybd_event('S', getScanCode('S'), 2, 0);

	////6
	//keybd_event('D', getScanCode('D'), 0, 0);
	//Sleep(40);
	//keybd_event('D', getScanCode('D'), 2, 0);
	//
	////4
	//keybd_event('A', getScanCode('A'), 0, 0);
	//Sleep(40);
	//keybd_event('A', getScanCode('A'), 2, 0);
	//
	////6
	//keybd_event('D', getScanCode('D'), 0, 0);
	//Sleep(40);
	//keybd_event('D', getScanCode('D'), 2, 0);
	////3
	//keybd_event('S', getScanCode('S'), 0, 0);
	//keybd_event('D', getScanCode('D'), 0, 0);
	//Sleep(70);
	//keybd_event('S', getScanCode('S'), 2, 0);
	//keybd_event('D', getScanCode('D'), 2, 0);

	////6
	//keybd_event('D', getScanCode('D'), 0, 0);
	//Sleep(40);
	//keybd_event('D', getScanCode('D'), 2, 0);

	//keybd_event('I', getScanCode('I'), 0, 0);
	//Sleep(40);
	//keybd_event('I', getScanCode('I'), 2, 0);
}

//һ������ɽ(2P)
//346414+D
void luanzishan_2p() {
	//3
	keybd_event('D', getScanCode('D'), 0, 0);
	keybd_event('S', getScanCode('S'), 0, 0);
	Sleep(70);
	keybd_event('D', getScanCode('D'), 2, 0);
	keybd_event('S', getScanCode('S'), 2, 0);

	//4
	keybd_event('A', getScanCode('A'), 0, 0);
	Sleep(40);
	keybd_event('A', getScanCode('A'), 2, 0);

	//6
	keybd_event('D', getScanCode('D'), 0, 0);
	Sleep(40);
	keybd_event('D', getScanCode('D'), 2, 0);

	//4
	keybd_event('A', getScanCode('A'), 0, 0);
	Sleep(40);
	keybd_event('A', getScanCode('A'), 2, 0);
	//1
	keybd_event('S', getScanCode('S'), 0, 0);
	keybd_event('A', getScanCode('A'), 0, 0);
	Sleep(70);
	keybd_event('S', getScanCode('S'), 2, 0);
	keybd_event('A', getScanCode('A'), 2, 0);

	//4
	keybd_event('A', getScanCode('A'), 0, 0);
	Sleep(40);
	keybd_event('A', getScanCode('A'), 2, 0);

	keybd_event('I', getScanCode('I'), 0, 0);
	Sleep(40);
	keybd_event('I', getScanCode('I'), 2, 0);
}

/*
	���������ץ
*/
void loriLeftGrip() {
	keybd_event('D', getScanCode('D'), 2, 0);
	keybd_event('A', getScanCode('A'), 0, 0);
	Sleep(17);
	keybd_event('S', getScanCode('S'), 0, 0);
	Sleep(17);
	keybd_event('A', getScanCode('A'), 2, 0);
	Sleep(17);
	keybd_event('S', getScanCode('S'), 2, 0);

	Sleep(17);
	keybd_event('D', getScanCode('D'), 0, 0);
	Sleep(17);
	keybd_event('I', getScanCode('I'), 0, 0);
	Sleep(17);
	keybd_event('D', getScanCode('D'), 2, 0);
	Sleep(17);
	keybd_event('I', getScanCode('I'), 2, 0);
}

int getScanCode(int code) {
	return MapVirtualKey(code,MAPVK_VK_TO_VSC);
}