//�������⣺��m����Ʒ��һ������Ϊt�ı�������i����Ʒ��������w[i]����ֵ��v[i]�� 

//��⽫��Щ��Ʒװ�뱳����ʹ��Щ��Ʒ�������ܺͲ���������������t���Ҽ�ֵ�ܺ���� 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <conio.h> 

#include <string.h> 



int f[1010], w[1010], v[1010];//f��¼��ͬ�������������ܼ�ֵ��w��¼��ͬ��Ʒ��������v��¼��ͬ��Ʒ�ļ�ֵ 



int getMax(int x, int y) {//����x,y�����ֵ 

	if (x>y) return x;

	return y;

}



int main() {

	int t, m, i, j;

	memset(f, 0, sizeof(f));  //�ܼ�ֵ��ʼ��Ϊ0 

	printf("���뱳��������t����Ʒ����Ŀm:\n");
	scanf("%d %d", &t, &m);  //���뱳��������t����Ʒ����Ŀm 

	printf("����m����Ʒ������w[i]�ͼ�ֵv[i]:\n");
	for (i = 1; i <= m; i++)
		scanf("%d%d", &w[i], &v[i]);  //����m����Ʒ������w[i]�ͼ�ֵv[i] 

	for (i = 1; i <= m; i++) {  //���Է���ÿһ����Ʒ 

		for (j = t; j >= w[i]; j--) {

			f[j] = getMax(f[j - w[i]] + v[i], f[j]);

			//�ڷ����i����Ʒǰ�󣬼��鲻ͬj�������������ܼ�ֵ����������i����Ʒ��ȷ���ǰ�ļ�ֵ����ˣ����޸�j�����������ļ�ֵ�����򲻱� 

		}

	}


	printf("����ֵ:%d\n", f[t]);  //���������Ϊt�ı������ܼ�ֵ 

	system("pause");

	return 0;

}