#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>

#define TRUE 1
#define FALSE 0
#define HOST_NUMBER "hostNumber"
#define ATTACK_COUNT "attackCount"
#define INDICATOR_IP 1
#define INDICATOR_MAC 2

int hostNumber;//��Ҫ��������������
int attackCount;//��Ҫ�����Ĵ���
unsigned long gatewayIP; //����IP
unsigned char gatewayMac[6]; //����MAC
unsigned long *fakeIps; //Ҫαװ�ɵ�IP��ַ�б�
//��Ҫ����������MAC��ַ�б�,������δ֪,��ʱ������ָ���ʾ
unsigned char(*attackHostMacs)[6];

void loadConfig();
int isSpaceLine(char *buffer);
void init();
int loadIPOrMac(char *buffer, int contentIndicator, unsigned long *ip, unsigned char *mac, int hostId);

int main() {
	loadConfig();
	system("pause");
	return 0;
}
/*
���������ļ�����ʼ��������
���� : ��õ�ǰ����Ŀ¼.
char* _getcwd(char *buffer, int maxlen);
*/
void loadConfig() {
	char buffer[300] = { 0 };

	FILE *config = fopen("./config.txt", "r");
	if (config == NULL)
	{
		fprintf(stderr, "��ǰ·���в�����config.txt�����ļ�,����!\n");
		free(config);
		config = NULL;
		exit(-1);
	}
	//ָ�������ݵ����Ǵ�ŵ�IP����MAC,1��ʾIP,2��ʾMAC
	int contentIndicator = 0;
	//��ǰ��ȡ���������
	int hostId = 0;
	int i = 0;
	while (!feof(config))
	{
		fgets(buffer, 300, config);

		if (buffer[0] == '#')
		{
			continue;
		}
		else if (TRUE == isSpaceLine(buffer)) {
			//�ڿ���ʱ,������ΪIP
			contentIndicator = INDICATOR_IP;
			continue;
		}
		else if (strstr(buffer, HOST_NUMBER) != NULL)
		{
			sscanf(buffer, "hostNumber=%d", &hostNumber);
			//��ȡ�����������Ϳ��Կ�ʼ��ʼ����
			init();
		}
		else if (strstr(buffer, ATTACK_COUNT) != NULL)
		{
			//��ȡ��������
			sscanf(buffer, "attackCount=%d", &attackCount);
		}
		else
		{
			//��ȡ���ص�IP��MAC
			if (hostId == 0)
			{
				hostId = loadIPOrMac(buffer, contentIndicator, &gatewayIP, gatewayMac, hostId);
			}
			else {
				hostId = loadIPOrMac(buffer, contentIndicator, &fakeIps[hostId - 1], attackHostMacs[hostId - 1], hostId);
			}
			contentIndicator++;
		}
	}

	fclose(config);
	config = NULL;
}

/*
��ʼ������
*/
void init() {
	fakeIps = (unsigned long *)calloc(hostNumber, sizeof(unsigned long));
	attackHostMacs = (unsigned char(*)[6])calloc(hostNumber, sizeof(char) * 6);
}

/*
��ȡIP��MAC
*/
int loadIPOrMac(char *buffer, int contentIndicator, unsigned long *ip, unsigned char *mac, int hostId) {
	if (contentIndicator == INDICATOR_IP)
	{
		(*ip) = inet_addr(buffer);
	}
	else if (contentIndicator == INDICATOR_MAC) {
		sscanf(buffer, "%hhX-%hhX-%hhX-%hhX-%hhX-%hhX",
			&mac[0], &mac[1], &mac[2],
			&mac[3], &mac[4], &mac[5]);
		//��ȡ��MAC֮��������������ݲ����ȡ���
		hostId++;
	}
	return hostId;
}

/*
�жϵ�ǰ���Ƿ�Ϊ����,fgets��ȡ���л᷵��'\n',�����жϷ�������:
1.�����'\n'��ʼ,���ǿ���
2.�������'\n'֮ǰ�������ַ���Ϊ' '�ո�,Ҳ�ǿ���
*/
int isSpaceLine(char *buffer) {
	if (buffer == NULL)
	{
		return TRUE;
	}
	if (buffer[0] == '\n') {
		return TRUE;
	}
	for (int i = 0; buffer[i] != '\n'; i++)
	{
		if (buffer[i] != ' ')
		{
			return FALSE;
		}
	}
	return TRUE;
}