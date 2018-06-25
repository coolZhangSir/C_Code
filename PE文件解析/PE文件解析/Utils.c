#include "PeParser.h"

void showString(char *string) {
	printf("%s\n", string);
}

/*
	����ȡ��������ת�����Զ�Ӧ��WORD/DWORD��ʽ
	int isCharacter:�Ƿ�Ϊ��־���ַ�,��:"MZ"/"PE"
	�����漰����С�˴洢����,��������ַ�����Ҫ���ߵ�ַ������ת��Ϊ���ֽ�
*/
DWORD charToDWORD(char *buffer, int size, int isCharacter) {
	if (buffer == NULL) {
		return FAILURE;
	}
	DWORD result = 0;
	if (size == sizeof(WORD))
	{
		//WORD MAKEWORD(BYTE bLow,	BYTE bHigh);
		//0x4D5A
		if (isCharacter == CHARACTER) {
			result = MAKEWORD(buffer[1], buffer[0]);
		}
		else
		{
			result = MAKEWORD(buffer[0], buffer[1]);
		}
	}
	else if (size == sizeof(DWORD)) {
		//DWORD MAKELONG( WORD wLow, WORD wHigh );
		if (isCharacter == CHARACTER)
		{
			WORD low = MAKEWORD(buffer[1], buffer[0]);
			WORD high = MAKEWORD(buffer[3], buffer[2]);
			result = MAKELONG(high, low);
		}
		else
		{
			WORD low = MAKEWORD(buffer[0], buffer[1]);
			WORD high = MAKEWORD(buffer[2], buffer[3]);
			result = MAKELONG(low, high);
		}
	}
	else {
		return FAILURE;
	}
	return result;
}

//��ȡĳ���ֶε�ͨ�÷���
STATUS seekAndReadFile(FILE *file, int size, int offset, void *result, int isCharacter) {
	//2.����PEͷ,��������Ӧ�ֶε�ƫ��
	int flag = fseek(file, offset, SEEK_CUR);
	if (flag == FSEEK_ERROR)
	{
		return FAILURE;
	}

	char buffer[5] = { 0 };
	flag = fread(buffer, size, 1, file);
	if (flag == FREAD_ERROR)
	{
		return FAILURE;
	}

	//���꽫��ַƫ�ƻ���,�����ղŶ�ȡ�ĳ���
	fseek(file, 0 - (offset + size), SEEK_CUR);

	if (size == sizeof(WORD))
	{
		*((WORD *)result) = (WORD)charToDWORD(buffer, size, isCharacter);
	}
	else
	{
		*((DWORD *)result) = charToDWORD(buffer, size, isCharacter);
	}
	return SUCCESS;
}