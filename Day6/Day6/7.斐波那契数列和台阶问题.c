#include<stdio.h>
/*
	���쳲���������
*/
void method1(){
	int a = 1;
	int b = 1;
	int c = 0;
	int i = 0;
	printf("��1���µ�������:%d\n",1);
	printf("��2���µ�������:%d\n",1);
	for(i = 3;i <= 10;i++){
		c = a + b;
		a = b;
		b = c;
		printf("��%d���µ�������:%d\n",i,c);
	}
}
int recursive(int month){
	if(month == 1){
		return 1;
	}else if(month == 2){
		return 1;
	}else{
		return recursive(month - 1) + recursive(month - 2);
	}
}
void main(){
	int result = 0;
	int i = 0;
	printf("��1���µ�������:%d\n",1);
	printf("��2���µ�������:%d\n",1);
	for(i = 3;i <= 4;i++){
		result = recursive(i);
		printf("��%d���µ�������:%d\n",i,result);
	}
}