//2������һ���ַ����ж��������Сд��ĸ������Ӧ��д��ĸ������Ǵ�д��ĸ������ӦСд��ĸ�����������������ֱ�������ǿո������space�������������������������other����
#include<stdio.h>
#include<stdlib.h>

int main() {
	char ch = getchar();
	if (ch >= 65 && ch <= 90) {
		printf("%c\n",ch + 32);
	}
	else if (ch >= 97 && ch <= 122) {
		printf("%c\n", ch - 32);
	}
	else if (ch >= 48 && ch <= 57) {
		printf("%c\n", ch);
	}
	else if (ch == 32) {
		printf("%s\n", "space");
	}
	else {
		printf("%s\n", "other");
	}
	system("pause");
	return 0;
}