#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
void showDialog() {
	MessageBoxA(NULL,"����ָ����ú���","����ָ����;",0);
}
int add(int a, int b) {
	return a + b;
}
int sub(int a, int b) {
	return a - b;
}
void operate(int(*p)(int, int), int a, int b) {
	/*
		��Ϊһ���ӿ�,�������һ������ָ��.
		�����ƾ������ĸ�����,������չ��
	*/
	printf("%d\n",p(a,b));
}
void function1() {
	/*
		����ָ�������:�Ѻ���������(*ָ����)
			int (*)(int,int)=add
			�洢һ�������ĵ�ַ.
			����д��:
				int (*)(int,int) = add(1,2);
				add(1,2)��һ����������,����Ѻ����ķ���ֵ��Ϊ��ַ��ֵ������ָ��,��ɷ��ʳ�ͻ
		����:
			1.ͨ������ָ�����һ������:����ָ��(����);
			2.ͨ��dllע��Ƿ�������һ�����̵ĺ���
			3.������ָ����Ϊһ�������������ݸ���������(ʵ��һ���ӿڵĹ���)
	*/
	void (*p)() = showDialog;
	p();
}
void function2() {
	/*
		&showDialog,showDialog,*showDialog:
			��������ȫ�ȼ�
		&showDialog = showDialog
		*showDialog = *(&showDialog) = showDialog
		���ڴ�������˵,����ָ��������,��û������,*showDialog,&showDialog��û�ж������
	*/
	printf("%p,%p,%p\n", &showDialog, showDialog, *showDialog);
	//����,��3����������Ӽ�����,�������������޸�(������Ӧ�ò�)
	//printf("%p,%p,%p\n", &showDialog + 1, showDialog + 1, *showDialog+1);
}
void function3() {
	/*
		����3:������ָ����Ϊһ�������������ݸ���������
	*/
	//operate(add,10,7);
	operate(sub, 10, 7);
}
/*
	����ָ����Ϊ����ֵ
		 int (*ff(int))(int *, int);
		������������ܵķ�������һ�£�ff���������ġ�()����ϣ�����
		int (*(ff(int)))(int *, int); // �����Ž�ff(int)��������Ҳ����ζ�ţ�ff��һ��������
		������ǰ��ġ�*����ϣ�˵��ff�����ķ���ֵ��һ��ָ�롣
		Ȼ���������ġ�()����ϣ�Ҳ����˵����ָ��ָ�����һ��������
		����д��ȷʵ���˷ǳ��Ѷ���������һЩ��ѧ�߲�����⣬��Ϊд�����˿������Ĵ��������ʾ�Լ�ˮƽ�ߡ�
		����ʵ��ǡ���෴���ܷ�д��ͨ���׶��Ĵ����Ǻ�������Ա�Ƿ�����ı�׼��
		һ����˵����typedef�ؼ��ֻ�ʹ�����������׶�����ǰ�������Ѿ�������
		int (*PF)(int *, int);
		Ҳ����˵��PF��һ������ָ�롰��������
		��ʹ��typedef��������PF�ͳ�Ϊ��һ������ָ�롰���͡�������
			 typedef int (*PF)(int *, int);
		�����Ͷ����˷���ֵ�����͡�Ȼ������PF��Ϊ����ֵ����������:
			PF ff(int);
*/
int (*function4(int a, int b))(int, int) {
	return add;
}
/*
	ʹ��typedef�򻯷���ֵΪ����ָ��Ķ���
*/
typedef int (*p)(int, int);
p function5() {
	return sub;
}
void main() {
	//function1();
	//function2();
	//function3();
	//printf("function4=%d\n", function4(3, 4)(1, 2));
	printf("function5=%d\n", function5()(3, 2));
	system("pause");
}