#define _CRT_SECURE_NO_WARNINGS
#define WIN32
#define HAVE_REMOTE
#include <stdio.h>
#include <stdlib.h>
#include "pcap.h"

/*
	ʹ�ûص��ķ�ʽ�������ݰ�
*/

void packetHandler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);

int main1() {
	pcap_if_t *allDevices;
	pcap_if_t *device;
	pcap_t *deviceHandler;

	char errorBuffer[PCAP_ERRBUF_SIZE];

	int i = 0, number = 0;

	/*��ȡ����ӡ�б�*/
	int flag = pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &allDevices, errorBuffer);
	if (-1 == flag) {
		fprintf(stderr, "%s\n", errorBuffer);
		exit(1);
	}
	for (device = allDevices; NULL != device; device = device->next) {
		printf("%d: %s", ++i, device->name);
		if (NULL != device->description) {
			printf("(%s)\n", device->description);
		}
		else {
			printf("(No device available!)\n");
		}
	}
	if (i == 0)
	{
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
		return -1;
	}

	/*ѡ�񲢴��豸*/
	printf("Enter the interface number (1-%d):", i);
	scanf("%d", &number);

	if (number < 1 || number > i) {
		printf("\nInterface number out of range!\n");
		/*�ͷ��豸�б�*/
		pcap_freealldevs(allDevices);
		return -1;
	}
	/*��ת��ѡ�е�������*/
	for (device = allDevices, i = 0; i < number - 1; device = device->next, i++);

	/*���豸*/
	deviceHandler = pcap_open(device->name //��ĳ�豸����Դ
		,65535 //65535��֤�ܲ��񵽲�ͬ������·���ϵ�ÿ�����ݰ���ȫ������
		,PCAP_OPENFLAG_PROMISCUOUS //����Ҫ��flag������ָʾ�������Ƿ�Ҫ�����óɻ���ģʽ
		,1000 //��ȡ��ʱʱ��
		,NULL //Զ�̻�����֤
		,errorBuffer //������Ϣ��������
	);

	if (NULL == deviceHandler) {
		fprintf(stderr, "Unable to open the adapter, %s is not supported by winPcap\n", device->name);
		pcap_freealldevs(allDevices);
		return -1;
	}

	printf("\nListening on %s\n", device->description);

	/*�ͷ��豸�б�*/
	pcap_freealldevs(allDevices);

	/*
		ԭ��:int pcap_loop(pcap_t *p,
			int cnt,
			pcap_handler callback,
			u_char * user
		)
		��ʼѭ���������ݰ�
	*/
	pcap_loop(deviceHandler, 0, packetHandler, NULL);

	system("pause");
	return 0;
}

/* ÿ�β������ݰ�ʱ��libpcap�����Զ���������ص����� */
void packetHandler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data) {
	struct tm *localTime;
	char timeString[16];
	//tv = Time Value
	time_t local_tv_sec;
	/* ��ʱ���ת���ɿ�ʶ��ĸ�ʽ */
	local_tv_sec = header->ts.tv_sec;
	localTime = localtime(&local_tv_sec);
	strftime(timeString, sizeof(timeString), "%H:%M:%S", localTime);
	printf("%s, %.6d len:%d\n", timeString, header->ts.tv_usec, header->len);
}