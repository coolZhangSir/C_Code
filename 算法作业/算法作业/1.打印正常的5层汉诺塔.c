//�����Ĵ������ϴ�С˳��ĺ�ŵ��,��ӡ��5��İᷨ,Ҫ���ӡ��ÿһ���ƶ������ӱ��
#include<stdio.h>
#include<stdlib.h>

void tower(int layers, char from, char temp, char to);
void showMove(int layer, char from, char to);

int stepCount = 0;
void main() {
	int layers = 5;
	tower(layers, 'A', 'B', 'C');
	system("pause");
}
/*
	layers:�����ܲ���
	from:��ʼ������
	temp:��ת������
	to:Ŀ������
	Ҫ��:����3������,��2��������Ҫ��A���ᵽC��,�Ұ��ȥ��˳���ܱ�
	˼·:
		1.�Ƚ�(n - 1)�����Ӵ�A�ᵽB
		2.�ٽ���n�����Ӵ�A�ᵽC
		3.�ٽ�(n - 1)�����Ӵ�B�ᵽC
*/
void tower(int layers,char from,char temp,char to) {
	if (layers > 0) {
		tower(layers - 1, from, to, temp);
		showMove(layers,from,to);
		tower(layers - 1, temp, from, to);
	}
}
/*
	��ʾÿһ�����ƶ������ӱ�ź��ƶ��ķ���
*/
void showMove(int layer,char from,char to) {
	printf("��%02d��:%d������%c--->%c\n",++stepCount,layer,from,to);
}