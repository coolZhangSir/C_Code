#include<stdio.h>
#include<stdlib.h>
void test1(){
	char data[500] = "131610	��С��	Ů	20	165	����	δ��	����	˫����	��Уѧ��	��ͨ��	����	����Ԫ/��	�й�����	ѧ������	�崿Ư�� ���ſɰ����Ҷ��ڱ�����ѧ.���������ļ���ż����������Ѱ���ҵ���Ե��.Ը���ǵ���������������������õĻ���!	10:00��23:00		2264938779@qq.com		226493870779";

	char name[20] = {0};
	int age = 0;
	int tall = 0;
	sscanf(data,"%*s%s%*s%d%d%*s",name,&age,&tall);
	printf("name=%s\nage=%d\ntall=%d\n",name,age,tall);

}
void test2(){
	//�����Ƕ��ŷָ�,����scanf��Ѳ���ѷǿհ��ַ������ָ���,�������仰����scanf������һ���ַ���
	char data[500] = "420111197203024016,13600477059,nixiaodong@vip.sina.com";
	char id[100] = {0};
	char telphone[100] = {0};
	char email[200] = {0};
	int i = 0;
	for(;i < 500;i++){
		if(data[i] == ','){
			data[i] = ' ';
		}
	}
	sscanf(data,"%s%s%s",id,telphone,email);
	printf("id=%s\ntelphone=%s\nemail=%s\n",id,telphone,email);
}
/*
	sprintf():������ƴ�ӳ��ַ���
	sscanf():���ַ����ָ�ɱ���

	�����ַ���ʱ,',','#'��Щ���Ƿָ���,������Ҫ����ת�ɿո�������
*/
int main(){
	//test1();
	test2();
	return 0;
}
