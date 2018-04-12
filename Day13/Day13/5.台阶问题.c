#include<stdio.h>
#include<stdlib.h>

/*
	����n��̨��,ÿ��ֻ����һ����������,���ж������߷�?
	̨������˼·:
		����һ����̬�滮������.
		����n��̨��,���һ��ֻ��ѡ���n-1����n-2������,ֻ�������߷�
		������һ����һ��,��ʣ��n-1���߷�.
		������һ��������,��ʣ��n-2���߷�.
		�������п��ܵ��߷�����f(n) = f(n-1) + f(n-2);
*/

int main() {
	int n = 10;

	//��̬�滮
	int array[10] = { 0 };
	array[0] = 1;
	array[1] = 2;
	for (int i = 2; i < n; i++)
	{
		array[i] = array[i - 1] + array[i - 2];
	}

	printf("��10��̨�׹���%d���߷�\n",array[9]);
	printf("��10��̨�׹���%d���߷�\n", recursive(10));

	system("pause");
}
//�ݹ�
int recursive(int n) {
	if (n == 1) {
		return 1;
	}
	else if (n == 2) {
		return 2;
	}
	else {
		return recursive(n - 1) + recursive(n - 2);
	}
}