#define WIN32
/*
	pcap_findalldevs_ex���������Ը�ͷ�ļ��е�,�ĵ���������Ӹ�ͷ�ļ�.
	#include <remote-ext.h>
	���Ǹ�ͷ�ļ����Ѿ�ָ������ֱ�ӵ����ͷ�ļ�,ֻ��Ҫ���� HAVE_REMOTE ����,������pcap.h����
*/
#define HAVE_REMOTE
#include <stdio.h>
#include <stdlib.h>
#include "pcap.h"

int main() {
	pcap_if_t *allDevices;
	pcap_if_t *device;
	char errorBuffer[PCAP_ERRBUF_SIZE];

	int i = 0;
	/* ��ȡ���ػ����豸�б� */
	int flag = pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &allDevices, errorBuffer);
	if (flag == -1) {
		fprintf(stdout, "%s" ,errorBuffer);
		exit(1);
	}

	/*��ӡ�б�*/
	for (device = allDevices; device != NULL; device = device->next)
	{
		printf("%d: %s", ++i, device->name);
		if (device->description != NULL) {
			printf("(%s)\n", device->description);
		}
		else {
			printf("(No device available!)\n");
		}
	}

	if (i == 0) {
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
	}

	pcap_freealldevs(allDevices);
	system("pause");
	return 0;
}