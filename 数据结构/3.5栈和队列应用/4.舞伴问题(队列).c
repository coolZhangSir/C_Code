#include "CSQueue.h"
/*
	��ʿ��Ůʿ���ų�һ��,���迪ʼʱ,���δ��к�Ů��ͷ����һ�����,
	�����ӳ�ʼ������һ��,�򳤵���һ����δ����ߵȴ���һֻ����.
	дһ�㷨ģ����������������
*/
void show(Participant participant) {
	printf("����:%-6s,�Ա�:%c\n",participant->name,participant->gender);
}
void showPartner(Participant MParticipant, Participant FParticipant,int group) {
	printf("��%d��:��ʿ:%-6s,Ůʿ:%-6s\n", group,MParticipant->name, FParticipant->name);
}
void main() {
	Participant participants[10] = {NULL};
	char *names[10] = {"ר��","����","����","����","СȪ��","����","��å","��ү","����","Ԭ����"};
	char genders[10] = { 'M', 'M', 'M', 'M', 'M', 'M', 'F', 'F', 'F', 'F' };
	for (int i = 0; i < 10; i++)
	{
		participants[i] = malloc(sizeof(struct Person));
		participants[i]->gender = genders[i];
		participants[i]->name = names[i];
	}
	
	CSQueue MQueue;
	init(&MQueue);
	CSQueue FQueue;
	init(&FQueue);

	for (int i = 0; i < 10; i++)
	{
		if (participants[i]->gender == 'F') {
			enQueue(&FQueue, participants[i]);
		}
		else {
			enQueue(&MQueue, participants[i]);
		}
	}

	printf("������ʼ:\n");
	for (int i = 0;!isEmpty(MQueue) && !isEmpty(FQueue);i++)
	{
		showPartner(deQueue(&MQueue), deQueue(&FQueue),i+1);
	}
	if (!isEmpty(MQueue))
	{
		printf("��һ������ƥ�����ʿ��:%s\n",getHead(MQueue)->name);
	}
	if (!isEmpty(FQueue))
	{
		printf("��һ������ƥ���Ůʿ��:%s\n", getHead(FQueue)->name);
	}
	system("pause");
}
