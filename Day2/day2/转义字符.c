#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define DATA 9

/*
����system����ͨ��ָ����·����һ��Ӧ�ó���
*/
void test1() {
	/*
	1.ת���ַ��Ĵ���,"\"��Ҫ������"\\"��ת��,˫������Ҫ��(\")����ת��
	2.���·�����пո�,����Ҫ����·����Ϊһ���ַ�����˫����������
	3.���·���д�������(),������ǰ����Ҫ���Ͽո�" "
	*/

	system("\"C:\\Program Files (x86)\\Tencent\\QQ\\Bin\\QQScLauncher.exe\"");
}

/*
	getchar()�����ַ����˳�������
*/
void test2() {
	/*
		1.vs�ж�scanf�а�ȫ�Ե�Ҫ��,��Ҫ�ڴ�����#define _CRT_SECURE_NO_WARNINGSһ�������������þ���,#define _CRT_SECURE_NO_WARNINGS���������ǰ��,�������#include����ͻ���Ч
		2.һ���#define��ǿ��Ҫ�����ǰ��
		3.getchar()����Ϊͣ������������̨�����һ�ַ�ʽ,���ǰ����scanf()����,��ô������ɺ��µĻس��ᱻgetchar()��������.
	*/
	int num1 = DATA;
	printf("\n%d",num1);
	int num = DATA;
	scanf("%d",&num);
	getchar();
}

/*
	ͨ��\aת���ַ���������
*/
void test3() {
	//��C��������,��ͼٵ�������0�ͷ�0,����0��1.
	while (-1) {
		putchar('\a');
	}
}

/*
	ͨ��printf������һ���ı���������ı���ʹ��\r��\nת���ַ�.
	'\r'�ǻس���'\n'�ǻ��У�ǰ��ʹ��굽���ף�����ʹ�������һ��
	ͨ����һ���س��������ǻس������ǻ��У�\r\n����
	Windows��ÿ�н�β�ǡ�<����><�س�>��������\n\r����
*/
void test4() {
	printf("���������ϰ���Ʈ,\r\n�������������.\n");
}

/*
	ת���ַ������8���ƺ�16����
	������Ҫ��ascii��ֵ
		0 48
		A 65
		a 97
*/
void test5() {
	putchar('\101');	// \��ͷ8����  1 * 8^2 + 0 * 8^1 + 1 * 8^0 = 65
	putchar('\x43');	// \x��ͷ16����	4 * 16^1 + 3 * 16^0 = 67
}
int main() {
	
	//test1();
	//test2();
	//test3();
	//test4();
	
	test5();

	system("pause");
	return 0;
}
