#include<stdio.h>
#include<stdlib.h>
//sprintf()���ַ����д���ֵ
void test1(){
	char input[100] = {0};
	char command[100] = {0};
	scanf("%s",input);
	
	//sprintf()�������ַ����в���ɱ�ֵ
	//ͨ����.s��ȡ�ַ���Ӧ����sprintf()������ַ���
	sprintf(command,"color %.2s",input);
	system(command);
}
/*
	printf��ʽ���������ʽ
	-:printfĬ�����Ҷ���,�������-��,���ʾ�����,�ұ߲�0��ո�
	0:��ʾ����Ŀո���0���
	m:����ַ��Ŀ������,���ʵ�ʿ�ȴ��ڸ������,��ʵ�ʿ����ʾ,���ʵ�ʿ��С�ڸ������,����ո����0
	.n:�����ʵ��,���ʾ�����ӡ��С��λ��,������ַ���,���ʾ��ȡ�ĳ���
	l:��ʾ������.��lf/ld
*/
void test2(){
	printf("%10d\n",1340);
	printf("%010d\n",234);
	printf("%-010d\n",1242);
	printf("%.2f\n",1234.235432);
	printf("%.3s\n","sldfjio");
}
/*
	ͨ����ʽ���ַ���ƴ���ַ���(C���Բ�֧��java�ַ�����ֱ�����)
*/
void test3(){
	char command1[100] = "task";
	char command2[100] = "123list";//ֻ�ܴ���߿�ʼ��ȡ,'-'��ֻ�ܱ�ʾ�����,���ܱ�ʾ���ұ߿�ʼ��ȡ
	char command[100] = {0};
	sprintf(command,"%s%.4s",command1,command2+3);
	system(command);
}
/*
	�����������:hd/hu
	�����������:ld/lu
	long long���������:lld/llu
*/
void test4(){
	unsigned short int number1 = 65535;
	short int number2 = 65535;

	//32�����ϵ�ϵͳ��,long�ȼ���int
	long number3 = 234124;
	int number4 = 234124;

	//�����qq��/�ֻ�����Щ,��Ҫ�õ�long long,��ʹ���ַ���,��������
	//long long telphone = 18523482416;


	printf("%hu,%hd\n",number1+1,number2);//hu�ķ�Χ��2��16�η�,u��int�ķ�Χ2��32�η�,��������ͻᷢ���������.
	printf("%u,%d\n",number1+1,number2);

	
	printf("%ld\n",number3);

	
	//printf("%lld\n",telphone);

}
/*
	��ӡ���Ʊ�ʶ��:#
	�����ڴ�ӡ�˽��ƻ���ʮ�����Ƶ�ʱ�����0����0x�ı�ʶ��
*/
void test5(){
	int number1 = 0123;
	int number2 = 0x123;
	printf("%#o\n",number1);
	
	printf("%#x\n",number2);
}
/*
	��ʽ���Ʒ���Сд������
	�����������ݿ��Դ����ַ���һ����Դ�д,����%o
*/
void test6(){
	printf("%o\n",0123);
	printf("%O\n",0123);
	printf("%#X\n",0x123);
	printf("%E\n",123.0);//ָ����ʽ��ʾС��,���ﲻ�ܴ�����,printf�����������ת��.

	//��ʾת���ַ�
	printf("\"%d\"\n",123);
	//����%%��ʾһ��%%��,�Ҷ��%��ʱ�򲻻��ظ��ϲ�,%%%%%%���ʾ��3��,����һֱ�ϲ���1��
	printf("%d%%\n",12);
	//printf("%d\%\n",12); %����ͨ��ת���ʾ
}
/*
	printf��ʽ���Ʒ��Ͳ���������Ӧ������
	1.�����ʽ���Ʒ��ĸ���С��ʵ�ʲ�����ʱ��,����Ĳ����������
	2.�����ʽ���Ʒ��ĸ�������ʵ�ʲ�����ʱ��,������ֵ����,����������ֵ,Ҳ������0
*/
void test7(){
	printf("%d,%d\n",1,2,3,4);
	printf("%d,%d,%d,%d\n",1,2);
	
}
/*
	printf��Ⱥ�С����λ���Ŀɱ�ֵ

*/
void test8(){
	int i = 1;
	char str[100] = "120938sjdfoa;u3wqj4023ujsoifadj";
	
	for(;i <= 20;i++){
	//	printf("%*d\n",i,i);
	}

	for(i = 1;i <= 20;i++){
		printf("%.*s\n",i,str);
	}
}
int main(){
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	//test7();
	test8();
	return 0;
}