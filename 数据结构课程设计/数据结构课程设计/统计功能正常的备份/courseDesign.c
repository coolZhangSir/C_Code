#include "courseDesign.h"

void inputFileName(char *fileName) {
	printf("�����ļ�·�����ļ���(���ֱ���Ͻ���):\n");
	scanf("%s", fileName);
}
void output(char *content) {
	printf("%s\n", content);
}

BOOL isEmptyLine(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack) {
	int index = skipSpace(lineString,0);
	if (lineString[index] == '\n') {
		//���������Ϳ��������м���
		(codeAnalysis->emptyLineCount)++;
		increaseCodeCount(codeAnalysis, signStack);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
BOOL isComment(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack) {
	int index = skipSpace(lineString,0);
	//�жϵ���ע�ͺͶ���ע����ʼ
	if (lineString[index] == '/') {
		if (lineString[index + 1] == '/' || lineString[index + 1] == '*') {
			(codeAnalysis->commentLineCount)++;
			increaseCodeCount(codeAnalysis, signStack);
			if (lineString[index + 1] == '*')
			{
				//����ǰע�Ϳ���ʼ��ѹջ
				push(signStack, SIGN_MULTIPLE_COMMENT);
			}
		}
		return TRUE;
	}
	//�ж϶���ע�ͽ���
	else if (lineString[index] == '*') {
		if (lineString[index + 1] == '/')
		{
			increaseCodeCount(codeAnalysis, signStack);
			(codeAnalysis->commentLineCount)++;
			pop(signStack);
		}
		return TRUE;
	}
	return FALSE;
}
/*
����ǩ��Ӧ�����������([]��ʾ��ѡ):
[XX] YY([ZZ]){
����
[XX] YY([ZZ])
{
�ص��ж�'YY(){',���������Ǳ�Ҫ����
*/
BOOL isFunction(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack) {
	int index = skipSpace(lineString,0);
	char buffer[NAME_SIZE] = { 0 };
	char functionName[NAME_SIZE] = { 0 };
	//���������ʹ���buffer��
	if (copyAndCheckIdentifier(buffer, lineString, &index) == FALSE) {
		return FALSE;
	}

	if (lineString[index] == ' ') {
		index = skipSpace(lineString,index);
	}

	//�������'(',��˵�����к�����,֮ǰ���Ƿ�������
	if (lineString[index] != '\n' && lineString[index] != '(') {
		//������������buffer��
		if (copyAndCheckIdentifier(buffer, lineString, &index) == FALSE) {
			return FALSE;
		}
		else
		{
			strcpy(functionName, buffer);
		}
	}
	//�����ո�Ӧ������'('��
	if (lineString[index] == ' ') {
		index = skipSpace(lineString,index);
	}

	//�����һ����'(',������ǲ���
	if (lineString[index] == '(')
	{
		//����'('��' ',�����һ���ǲ���')',����������в���,��Ҫ���һ�����������,�����if/while����
		index++;
		index = skipSpace(lineString,index);
		while (lineString[index] != '\n' && lineString[index] != ')')
		{
			//ѭ������,�Ա㴦��const�������
			while (lineString[index] != ',' && lineString[index] != '\n' && lineString[index] != ')') {
				//�����ո�,���
				if (copyAndCheckIdentifier(buffer, lineString, &index) == FALSE) {
					return FALSE;
				}
				index = skipSpace(lineString,index);
			}
			if (lineString[index] == ',')
			{
				index++;
			}
			index = skipSpace(lineString, index);
		}
	}
	else
	{
		return FALSE;
	}
	/*
	��������Ĵ���֮��,
	Ҫô�Ǵ��ں������������Ŵ�,
	�жϴ�����,���ھ���ջ
	û�о�����,����Ҫ�ж��Ƿ����';',����������ͷ
	*/
	if (lineString[index] == ')')
	{
		index++;
		//���')'�����н����м���������ַ��Ϳ�����Ϊ��ʽ������
		while (lineString[index] != '\n')
		{
			if (lineString[index] == '{')
			{
				push(signStack, '{');
				break;
			}
			if (lineString[index] == ';')
			{
				return FALSE;
			}
			index++;
		}
		FunctionAnalysis *function = (FunctionAnalysis *)malloc(sizeof(FunctionAnalysis));
		function->codeLineCount = 0;
		strcpy(function->functionName, functionName);
		//��ͷ�巨������뵽��һ��λ��
		function->next = codeAnalysis->functionAnalysis->next;
		codeAnalysis->functionAnalysis->next = function;
		//ͷ���ͳ�ƺ�������
		codeAnalysis->functionAnalysis->codeLineCount++;
		//���Ӵ���
		(codeAnalysis->codeLineCount)++;
		//���Ӻ��������
		(codeAnalysis->functionAnalysis->next->codeLineCount)++;
		return TRUE;
	}
	return FALSE;
}

/*
	�������,���ŵ���ջ�ͳ�ջ,����ͳһ�����
*/
void isBlock(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack) {
	int index = skipSpace(lineString,0);
	//if��while�ȵĵ�'{'Ϊ��һ�е�һ���ǿհ��ַ������
	if (lineString[index] == '{')
	{
		push(signStack, '{');
		increaseCodeCount(codeAnalysis, signStack);
		return;
	}

	while (lineString[index] != '\n' && lineString[index] != '\0')
	{
		index++;
	}
	//������з�'\n'ǰ�����пհ��ַ�,����ָ���Ƶ�������һ���ǿհ׷�,���һ�п���û��'\n',ֻ��һ��'\0'
	while (index >= 0 && (lineString[index] == ' ' || lineString[index] == '\t'
		|| lineString[index] == '\n' || lineString[index] == '\0')){
		index--;
	}
	//if��while�ȵĵ�'{'Ϊͬһ��ĩβ�����,������λ��'\n'ǰ��ΨһԪ��
	if (lineString[index] == '{') {
		push(signStack, SIGN_BLOCK);
		increaseCodeCount(codeAnalysis, signStack);
		return;
	}
	//������'}'������λ��'\n'ǰ��ΨһԪ��,������������,�������ֺ�';'
	if (lineString[index] == '}') {
		increaseCodeCount(codeAnalysis, signStack);
		pop(signStack);
		return;
	}
	increaseCodeCount(codeAnalysis, signStack);
}
void handleLineString(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack) {
	//����->ע��->����->�Ĳ���
	if (isEmptyLine(lineString, codeAnalysis, signStack) == FALSE) {
		if (isComment(lineString, codeAnalysis, signStack) == FALSE) {
			if (isFunction(lineString, codeAnalysis, signStack) == FALSE) {
				isBlock(lineString, codeAnalysis, signStack);
			}
		}
	}
}
/*
�������п��ַ�,�ҵ���һ����Ϊ' '��λ��
*/
int skipSpace(char *lineString,int index) {
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

void increaseCodeCount(CodeAnalysis *codeAnalysis, Stack *signStack) {
	(codeAnalysis->codeLineCount)++;
	//ջ�������ŵ�ʱ��ſ����Ǻ�����Ĵ���,�������# �� ����/�������� ��Щ������
	if (isStackEmpty(signStack) == FALSE)
	{
		(codeAnalysis->functionAnalysis->next->codeLineCount)++;
	}
}

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