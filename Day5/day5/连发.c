#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
void killQQ() {
	system("taskkill /f /im QQ.exe");
	MessageBoxA(0, "���ϵ���,��������,��,���ǿ���־����վ", "�黨�ڿ�����:", 0);
	ShellExecuteA(0, "open", "http://www.hh99.me", 0, 0, 0);
}
int main() {
	killQQ();
	return 0;
}