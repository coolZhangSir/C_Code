#define _CRT_SECURE_NO_WARNINGS
#define WIN32
#define HAVE_REMOTE
#include <stdio.h>
#include <stdlib.h>
#include "pcap.h"

/*����ԭ��*/
void ifPrint(pcap_if_t *device);
char* ipToString(u_long in);
char* ip6ToString(struct sockaddr *socketAddress, char *address, int addressLength);

int main() {
	pcap_if_t *allDevices;
	pcap_if_t *device;
	char errorBuffer[PCAP_ERRBUF_SIZE + 1];
	char sourceBuffer[PCAP_ERRBUF_SIZE + 1];
	int i = 0;

	printf("Enter the device you want to list:\n"
		"rpcap://              ==> lists interfaces in the local machine\n"
		"rpcap://hostname:port ==> lists interfaces in a remote machine\n"
		"                          (rpcapd daemon must be up and running\n"
		"                           and it must accept 'null' authentication)\n"
		"file://foldername     ==> lists all pcap files in the give folder\n\n"
		"Enter your choice: ");
	fgets(sourceBuffer, PCAP_ERRBUF_SIZE, stdin);
	sourceBuffer[PCAP_ERRBUF_SIZE] = '\0';


	/*��ȡ�豸�б�*/
	int flag = pcap_findalldevs_ex(sourceBuffer, NULL, &allDevices, errorBuffer);

	if (-1 == flag) {
		fprintf(stderr, "%s", errorBuffer);
	}
	/*ɨ�貢��ӡÿһ��*/
	for (device = allDevices; NULL != device; device = device->next)
	{
		ifPrint(device);
	}

	pcap_freealldevs(allDevices);
	system("pause");
	return 0;
}

void ifPrint(pcap_if_t *device) {
	pcap_addr_t *address;
	char ip6String[128];

	/*�豸��(Name)*/
	printf("%s\n", device->name);

	/*�豸����*/
	if (NULL != device->description) {
		printf("%s\n", device->description);
	}

	/*LoopBack Address*/
	printf("\tLoopback: %s\n", (device->flags & PCAP_IF_LOOPBACK) ? "yes" : "no");

	/*IP Address*/
	for (address = device->addresses; NULL != address; address = address->next)
	{
		printf("Address Family: #%d\n", address->addr->sa_family);

		switch (address->addr->sa_family)
		{
		case AF_INET:
			printf("\tAddress Family Name: AF_INET\n");
			if (NULL != address->addr) {
				printf("\tAddress:%s\n", ipToString(((struct sockaddr_in *)address->addr)->sin_addr.s_addr));
			}
			if (NULL != address->netmask) {
				printf("\tNetmask:%s\n", ipToString(((struct sockaddr_in *)address->netmask)->sin_addr.s_addr));
			}
			if (NULL != address->broadaddr) {
				printf("\tBroadcast:%s\n", ipToString(((struct sockaddr_in *)address->broadaddr)->sin_addr.s_addr));
			}
			if (NULL != address->dstaddr) {
				printf("\tDestination:%s\n", ipToString(((struct sockaddr_in *)address->dstaddr)->sin_addr.s_addr));
			}
			break;
		case AF_INET6:
			printf("\tAddress Family Name: AF_INET6\n");
			if (NULL != address->addr)
			{
				printf("\tAddress: %s\n", ip6ToString(address->addr, ip6String, sizeof(ip6String)));
			}
			break;
		default:
			printf("\tAddress Family Name: Unknown\n");
			break;
		}
	}
	printf("\n");
}

/* 
	���������͵�IP��ַת�����ַ������͵� 
	����������32λ������IP��ַ��Ӧ�ĳ�����,����ת�����ַ�ָ��,ֻ��Ҫ������ǰȡ4���ֽڼ���
*/
#define IP_TO_STRING_BUFFERS_LENGTH 12
char *ipToString(u_long in) {
	/*
	3 * 4 + 3 + 1(���ʮ����) : ���3λ(0 - 255) * 4�� + 3��"." + 1��'\0'
	*/
	static char output[IP_TO_STRING_BUFFERS_LENGTH][3 * 4 + 3 + 1];
	static short which;
	u_char *p;
	p = (u_char*)&in;

	which = (which + 1 == IP_TO_STRING_BUFFERS_LENGTH ? 0 : which + 1);
	//�ȼ���which = (which + 1) % IP_TO_STRING_BUFFERS_LENGTH;
	sprintf(output[which], "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
	return output[which];
}
char* ip6ToString(struct sockaddr *socketAddress, char *address, int addressLength) {
	socklen_t sockaddrlen;

#ifdef WIN32
	sockaddrlen = sizeof(struct sockaddr_in6);
#else
	sockaddrlen = sizeof(struct sockaddr_storage);
#endif


	if (getnameinfo(socketAddress,
		sockaddrlen,
		address,
		addressLength,
		NULL,
		0,
		NI_NUMERICHOST) != 0) {
		address = NULL;
	}

	return address;
}