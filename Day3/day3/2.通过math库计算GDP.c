#include<stdio.h>
/*
2.����GDP��10 ->  1.07     50->1.02   �й�GDP��������Դﵽ����30%  math
*/
int main() {
	float china = 10.0f;
	float chinaIncrease = 1.07f;
	float world = 50.0f;
	float worldIncrease = 1.02f;
	int i = 1;
	while (china - world * 0.3f <= 0) {
		china = china * (chinaIncrease * i);
		world = world * (worldIncrease * i);
		i++;
		printf("%f,%f\n", china, world);
	}

	printf("%d���,�쳯�ﵽ�����30%\n", i);

	getchar();
	return 0;
}