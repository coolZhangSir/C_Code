#include "controller.h"
/*
	����ߵ�99�����ͷ���1,��ʾ�߳�����
*/
int move(int maze[N][N], int i, int j) {
	int flag = 0;
	while (1) {
		char direction = 'd';
		direction = getchar();

		getchar();//�Ե��س�

		switch (direction) {
		case 'w':
		case 'W':
			flag = up(maze, &i, &j);
			if (flag) {
				return 1;
			}
			break;
		case 'a':
		case 'A':
			flag = left(maze, &i, &j);
			if (flag) {
				return 1;
			}
			break;
		case 's':
		case 'S':
			flag = down(maze, &i, &j);
			if (flag) {
				return 1;
			}
			break;
		case 'd':
		case 'D':
			flag = right(maze, &i, &j);
			if (flag) {
				return 1;
			}
			break;
		}

		display(maze);
	}
}

/*
	�Զ�Ѱ·
*/
void AIFindPath(int maze[N][N], int i, int j,int* flag)
{
	if (i == N - 1 && j == N - 1) {
		*flag = 1;
		maze[i][j] = 1;
		display(maze);
	}

	if (*flag == 1) {
		return;
	}

	maze[i][j] = 1;
	display(maze);
	
	maze[i][j] = 3;

	if (j < N - 1 && maze[i][j + 1] < 2)
	{
		AIFindPath(maze,i,j + 1,flag);
	}

	if (i < N - 1 && maze[i + 1][j] < 2)
	{
		AIFindPath(maze, i + 1, j, flag);
	}

	if (j > 0 && maze[i][j - 1] < 2)
	{
		AIFindPath(maze, i, j - 1, flag);
	}

	if (i > 0 && maze[i - 1][j] < 2)
	{
		AIFindPath(maze, i - 1, j, flag);
	}

	maze[i][j] = 4;
}

/*
�����ƶ�
*/
int left(int maze[N][N], int* i, int* j) {
	if (*j > 0 && maze[*i][*j - 1] < 2) {
		int temp = maze[*i][*j];
		maze[*i][*j] = maze[*i][*j - 1];
		maze[*i][*j - 1] = temp;

		*j = *j - 1;
	}
	
	if ((*i == N - 1) && (*j - 1 == N - 1)) {
		return 1;
	}
	else {
		return 0;
	}
}
/*
	�����ƶ�
*/
int right(int maze[N][N], int* i, int* j) {
	if (*j < (N - 1) && maze[*i][*j + 1] < 2) {
		int temp = maze[*i][*j];
		maze[*i][*j] = maze[*i][*j + 1];
		maze[*i][*j + 1] = temp;

		*j = *j + 1;
	}

	if ((*i == N - 1) && (*j + 1 == N - 1)) {
		return 1;
	}
	else {
		return 0;
	}
}
/*
�����ƶ�
*/
int up(int maze[N][N], int* i, int* j) {
	if (*i > 0 && maze[*i - 1][*j] < 2) {
		int temp = maze[*i][*j];
		maze[*i][*j] = maze[*i - 1][*j];
		maze[*i - 1][*j] = temp;

		*i = *i - 1;
	}

	if ((*i - 1 == N - 1) && (*j == N - 1)) {
		return 1;
	}
	else {
		return 0;
	}
}
/*
�����ƶ�
*/
int down(int maze[N][N], int* i, int* j) {
	if (*i < N - 1 && maze[*i + 1][*j] < 2) {
		int temp = maze[*i][*j];
		maze[*i][*j] = maze[*i + 1][*j];
		maze[*i + 1][*j] = temp;

		*i = *i + 1;
	}

	if ((*i + 1 == N - 1) && (*j == N - 1)) {
		return 1;
	}
	else {
		return 0;
	}
}
