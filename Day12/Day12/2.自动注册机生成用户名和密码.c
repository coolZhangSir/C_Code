#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<locale.h>

#define N 6
/*
	�Զ�ע����������һ���û���������
*/
void generateUsername() {
	wchar_t username[N] = { L'��', L'��', L'ΰ', L'��', L'��', L'��'};
	for (int i = 0; i < 2; i++)
	{
		wprintf(L"%c",username[rand() % 6]);
	}
	printf("\n");
}
void generatePassword() {
	char password[N] = { 's', 'a', 'd', 'w', 'g', 'h' };
	for (int i = 0; i < 6; i++)
	{
		putchar(password[rand() % 6]);
	}
	printf("\n");
}
void main() {
	setlocale(LC_ALL, "zh-CN");
	srand(time(NULL));
	generateUsername();
	generatePassword();

	system("pause");
}