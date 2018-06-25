//���ļ��洢һЩ���õĹ��߷���,���ǲ�ֱ���漰���޸ĳ���ؼ����ݵķ���������������
#include "CourseDesign.h"

void inputFileName(char *fileName) {
	printf("�����ļ�·�����ļ���(���ֱ���Ͻ���):\n");
	scanf("%s", fileName);
}

void output(char *content) {
	printf("%s\n", content);
}

/*
�������п��ַ�,�ҵ���һ����Ϊ' '��λ��
*/
int skipSpace(char *lineString, int index) {
	while (lineString[index] != '\n' && (lineString[index] == ' ' || lineString[index] == '\t'))
	{
		index++;
	}
	return index;
}
/*
�жϱ�ʶ��
����:ֻ��������,��ĸ,�»�����������ֲ���ͷ
*/
BOOL isLegalIdentifier(char *identifier) {
	int startIndex = 0;
	int endIndex = 0;
	//����ǰ��Ŀո�
	while (identifier[startIndex] != '\0' && (identifier[startIndex] == ' ' || identifier[startIndex] == '\t'))
	{
		startIndex++;
		//ͬʱ�ѽ�βָ��������
		endIndex++;
	}
	//����ָ������ [int] *p
	if (identifier[startIndex] != '\0')
	{
		if (identifier[startIndex] == '*' || identifier[startIndex] == '&')
		{
			startIndex++;
		}
	}
	//���˺���Ŀո��ٿ���ָ������� int* 
	while (identifier[startIndex] != '\0' && (identifier[startIndex] == ' ' || identifier[startIndex] == '\t'))
	{
		endIndex++;
	}
	if (identifier[endIndex] != '\0')
	{
		if (identifier[startIndex] == '*' || identifier[startIndex] == '&')
		{
			endIndex--;
		}
	}
	//��ʶ���жϹ���:�������ֿ�ͷ,�������»��ߺ���ĸ,�����
	if (isLegalFirstCharacter(identifier[startIndex]) != TRUE)
	{
		return FALSE;
	}
	startIndex++;
	while (startIndex < endIndex)
	{
		if (isLegalCharacter(identifier[startIndex]) != TRUE)
		{
			return FALSE;
		}
		startIndex++;
	}
	return TRUE;
}

//�жϱ�ʶ���е�һ���ַ��Ƿ�Ϸ�
BOOL isLegalFirstCharacter(char character) {
	if ((character >= 'a' && character <= 'z')
		|| (character >= 'A' || character <= 'Z')
		|| (character == '_'))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//�жϱ�ʶ���г���һ�������ÿ���ַ��Ƿ�Ϸ�
BOOL isLegalCharacter(char character) {
	if ((character >= 'a' && character <= 'z')
		|| (character >= 'A' && character <= 'Z')
		|| (character >= '0' && character <= '9')
		|| (character == '_'))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//�ж��߼������
BOOL isOperator(char character) {
	if (character == '&' || character == '|' || character == '^'
		|| character == '!' || character == '='
		|| character == '<' || character == '>')
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL copyAndCheckIdentifier(char *buffer, char *source, int *sourceIndex) {
	int bufferIndex = 0;
	while (source[*sourceIndex] != '\n' && source[*sourceIndex] != '\0' && (source[*sourceIndex] != '\t' && source[*sourceIndex] != ' ' && source[*sourceIndex] != '(') && source[*sourceIndex] != ')')
	{
		//ͬʱ������������Ϊ���������
		if (source[*sourceIndex] != '[') {
			if (isLegalCharacter(source[*sourceIndex]) == TRUE)
			{
				buffer[bufferIndex] = source[*sourceIndex];
				bufferIndex++;
			}
			//����ַ����Ϸ���Ϊ�����,�Ǿ�GG
			else
			{
				if (isOperator(source[*sourceIndex]) == TRUE) {
					return FALSE;
				}
			}
			(*sourceIndex)++;
		}
		//ֻҪ��������'[',��һֱ����Ѱ��']'
		else
		{
			while (source[*sourceIndex] != '\n' && source[*sourceIndex] != ']')
			{
				(*sourceIndex)++;
			}
			break;
		}
	}
	buffer[bufferIndex] = '\0';
	if (isLegalIdentifier(buffer) != TRUE)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}