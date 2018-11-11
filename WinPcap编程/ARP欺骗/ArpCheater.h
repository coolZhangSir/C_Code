#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define WIN32
#define HAVE_REMOTE

#define TRUE 1
#define FALSE 0
#define HOST_NUMBER "hostNumber"
#define ATTACK_COUNT "attackCount"
#define INDICATOR_IP 1
#define INDICATOR_MAC 2

#include "direct.h"
#include <stdio.h>
#include <stdlib.h>
#include "pcap.h"
#include <packet32.h>
#include <ntddndis.h>
#include <process.h>

//�ֽڶ��������1 
#pragma pack (1) 
typedef struct ArpDatagramHeader {
	unsigned short hardwareType; //Ӳ�����ͣ���ʾӲ����ַ�����ͣ�ֵΪ1��ʾ��̫����ַ
	unsigned short protocolType; //Э�����ͣ���ʾҪӳ���Э���ַ���͡�����ֵΪ0x0800��ʾIP��ַ����
	unsigned char hardwareAddressLength; //Ӳ����ַ���Ⱥ�Э���ַ�������ֽ�Ϊ��λ��������̫���ϵ�IP��ַ��ARP�����Ӧ����˵�����ǵ�ֵ�ֱ�Ϊ6��4��
	unsigned char protocolAddressLength;
	unsigned short operationType; //�������ͣ�op��:1��ʾARP����2��ʾARPӦ��
	unsigned char senderMac[6]; //���Ͷ�MAC��ַ�����ͷ��豸��Ӳ����ַ��
	unsigned long senderIP; //���Ͷ�IP��ַ�����ͷ��豸��IP��ַ��
	unsigned char receiverMac[6]; //Ŀ��MAC��ַ�����շ��豸��Ӳ����ַ��
	unsigned long receiverIP; //Ŀ��IP��ַ�����շ��豸��IP��ַ��
	//������ʱΪ�˱�֤��̫��֡����С֡��Ϊ64 bytes�����ڱ��������һ��padding�ֶΣ�����������ݰ���С��
	//��̫�������ݲ��ִ�С��������46 - 1500֮�䣬��ARP��ֻ��28���ֽڣ�������Ҫ���18���ֽڲ�������Ҫ��
	unsigned char padding[18]; 
}ArpDatagramHeader;

typedef struct EthnetFrameHander {
	unsigned char destinationMac[6];
	unsigned char sourceMAC[6];
	//֡����:ARP:0X806 RARP:0X8035
	unsigned short frameType;
}EthnetFrameHander;

/*������ARP��*/
typedef struct ArpDatagram {
	EthnetFrameHander ethnetFrame;
	ArpDatagramHeader arpDatagram;
}ArpDatagram;

/*��װ��������*/
typedef struct AttackHost {
	unsigned long ip; //Ҫαװ�ɵ�IP��ַ�б�
	unsigned char *mac; //����MAC
}AttackHost;

/*
	���������ļ�
*/
void loadConfig();

/*��������������������������*/
void sendPacketToAllHost(int hostSize, unsigned long net);
/*�ֱ���Ŀ��������·�ɷ���ARPӦ���ʹ�����*/
void sendAttackPacket(void *p);

/*
	��ȡ����MAC
*/
unsigned char* getLocalMac(char* deviceName);

/*
	��װARPЭ�������
	@param sourceMac ԴMAC
	@param sourceIP ԴIP
	@param destinationIP Ŀ��IP
	@return  ARPЭ�������
*/
unsigned char* buildArpRequestDatagram(unsigned char* sourceMac, unsigned long sourceIP,
	unsigned long destinationIP);

/*
	��װARPЭ��Ӧ���
	@param packet ��Ҫ�����Ӧ���
	@param sourceMac ԴMAC
	@param sourceIP ԴIP
	@param destinationIP Ŀ��IP
*/
void buildArpReplyDatagram(ArpDatagram *packet, unsigned char* sourceMac, unsigned long sourceIP,
	unsigned long destinationIP, unsigned char* destinationMac);

/*
	�жϵ�ǰ���Ƿ�Ϊ����,fgets��ȡ���л᷵��'\n',�����жϷ�������:
	1.�����'\n'��ʼ,���ǿ���
	2.�������'\n'֮ǰ�������ַ���Ϊ' '�ո�,Ҳ�ǿ���
*/
int isSpaceLine(char *buffer);

/*
	��ʼ������
*/
void init();

/*
	��ȡIP��MAC
*/
int loadIPOrMac(char *buffer, int contentIndicator, unsigned long *ip, unsigned char *mac, int hostId);

/*
	��ʾ��ȡ�������غ�������IP��MAC
*/
void showConfig();

/*
��ʾ���
*/
void showResult(int sendResult, unsigned long *IPs, unsigned char **Macs, int i, int j);