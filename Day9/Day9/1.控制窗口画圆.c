#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<math.h>

#define R 200
#define PI 3.1415926
#define LEFT 1
#define RIGHT 2

void main() {
	
	system("start notepad");
	Sleep(2000);

	HWND window = FindWindowA("Notepad", "�ޱ��� - ���±�");
	if (window != NULL) {
		int x = 900;
		int y = 350;
		int angle = 0;
		int flag = RIGHT;
		/*
			1.������Ҫѭ��ת360��,����������Ҫ������ת��Ϊ�Ƕ����������Ǻ���ֵ,ʹ��ת�����Բ.
			2.���ȺͽǶȵĹ�ϵ�ٶ�sin90��sin90�ȵ�����
			3.sin(90)��ָ�Ļ���,��λ��ʡ��
			4.sin(90 * PI / 180)��ָ�ĽǶ�
			5.�Ƕ� = ���� * PI / 180
			*/
		while (1) {
			printf("ת\n");
			if (angle == 180 && flag == RIGHT) {
				flag = LEFT;
				angle = 0;
				//�޸�Բ��
				x = 500;
			}
			else if(angle == 0 && flag == LEFT){
				flag = RIGHT;
				angle = 180;
				//�޸�Բ��
				x = 900;
			}

			SetWindowPos(
				window,
				0,
				x + R * cos(angle * PI / 180),
				y - R * sin(angle * PI / 180),
				100,
				100,
				0
			);
			
			angle = ((angle + 1) % 360);
			Sleep(5);
		}
	}
	else {
		printf("���ڲ�����\n");
	}
	system("pause");
}
