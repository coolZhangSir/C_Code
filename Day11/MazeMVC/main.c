/*
	����:����MVC�Ľṹ����Թ�
		M:model���ݲ�
		V:view��ʾ��
		C:controller���Ʋ�
*/
#include "controller.h"
#include "model.h"
#include "view.h"

void main() {
	int i = 0, j = 0;
	int flag = 0;
	
	display(maze);

	//flag = move(maze, i, j);
	AIFindPath(maze, i, j, &flag);

	if (flag) {
		printf("��ϲ�߳���\n");
	}

	system("pause");
}