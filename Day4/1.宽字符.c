#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<locale.h>
void test1() {
	char ch = '��';
	printf("%c\n", ch);
	printf("%d\n", sizeof(ch));
	printf("%d\n", sizeof(L'��'));
	//wchar_t���ַ����ڽ����ֵ����ַ�����ȴ���,һ��ռ2���ֽ�
	wchar_t wch = L'��';
	printf("%d\n", sizeof(wch));
	//������ַ����ı������ñ�������
	setlocale(LC_ALL, "zh-CN");
	putwchar(wch);
}
/*
	���ַ����������Ӧ����wscanf/wprintf
	�������ʱ����Ҫ����locale.hͷ�ļ�,�����������ǰʹ��setLocale()�������ñ�������
*/
void test2() {
	wchar_t wch[100] = { '0' };
	setlocale(LC_ALL, "zh-CN");
	wscanf(L"%ls",wch);
	wprintf(L"%ls\n", wch);
}
/*
	wprintf()������ַ�
	printf()���խ�ַ�
	���߲��ܸ㷴
*/
void test3() {
	printf("%s\n",L"��������");	//��ƥ��
	setlocale(LC_ALL, "zh-CN");
	wprintf(L"%s\n", "��������");	//��ƥ��
}
int main() {
	//MessageBox������ַ������������й�,�����unicode���ǿ��ַ�,����Ƕ��ֽ��ַ�������խ�ַ�
	//MessageBox(0, L"�����ı�", L"���Ǳ���", 0);
	//MessageBoxA�����խ�ַ���
	//MessageBoxA(0, "�����ı�", "���Ǳ���", 0);
	//MessageBoxA��������ַ���,������ַ���Ҫ����L
	//MessageBoxW(0, L"�����ı�", L"���Ǳ���", 0);
	//Ҳ����ʹ��TEXT()�����Զ�ת����խ�ַ�����
	//MessageBox(0, TEXT("�����ı�"), TEXT("���Ǳ���"), 0);
	//test1();
	//test2();
	test3();
	system("pause");
	return 0;
}
