//����Ĵ������´�С˳��ĺ�ŵ��,��ӡ��5��İᷨ,Ҫ���ӡ��ÿһ���ƶ������ӱ��
#include<stdio.h>
#include<stdlib.h>

void reverseTower(int layers, char from, char temp, char to);
void tower(int layers, char from, char temp, char to);
void showMove(int layer, char from, char to);

int stepCount = 0;
void main() {
	int layers = 5;

	printf("��ԭ˳��İᷨ:\n");
	tower(layers, 'A', 'B', 'C');

	stepCount = 0;

	printf("�ߵ�˳��İᷨ:\n");
	reverseTower(layers, 'A', 'B', 'C');

	system("pause");
}

/*
	������ĺ�ŵ��˳��ߵ�����(��ʼ�Ǵ�����������,���ȥ��������С��)
	Ҫ��:����3������,��2��������Ҫ��A���ᵽC��,�Ұ��ȥ����������С��
	˼·:
		1.�Ƚ���(n-1)����A�ᵽC
		2.�ٽ���n����A�ᵽB
*/
void reverseTower(int layers,char from,char temp,char to) {
	if (layers > 0) {
		reverseTower(layers - 1, from, temp, to);
		showMove(layers, from, to);
	}
}

/*
	����ĺ�ŵ��(��ʼ�Ǵ�����������,���ȥ���滹������)
	Ҫ��:����3������,��2��������Ҫ��A���ᵽC��,�Ұ��ȥ��˳�򲻱�
	˼·:
		1.����(n - 1)��A�ᵽB
		2.����n����A�ᵽC
		3.����(n - 1)����B�ᵽC
*/
void tower(int layers,char from,char temp,char to) {
	if (layers > 0) {
		tower(layers - 1, from, to, temp);
		showMove(layers, from, to);
		tower(layers - 1, temp, from,to);
	}
}
/*
��ʾÿһ�����ƶ������ӱ�ź��ƶ��ķ���
*/
void showMove(int layer, char from, char to) {
	printf("��%02d��:%d������%c--->%c\n", ++stepCount, layer, from, to);
}