//���ļ��洢��Ҫ�ķ���ʵ��ϸ��
#include "CourseDesign.h"

/*
	��Ҫ���ж��߼�
*/
void handleLineString(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack) {
	//�ж�˳��:����->ע��->����->�Ĳ���
	if (isEmptyLine(lineString, codeAnalysis, signStack) == FALSE) {
		if (isComment(lineString, codeAnalysis, signStack) == FALSE) {
			if (isFunction(lineString, codeAnalysis, signStack) == FALSE) {
				isBlock(lineString, codeAnalysis, signStack);
			}
		}
	}
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
			//�Դ����������޸�Ҫ���ڳ�ջǰ,���⺯�������ų�ջ���˻�û�޸�,��ɺ������ڵĴ���������©��
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
	�ص��ж�'YY(){',�������߲��ֻ���Ҫ������,��Ȼ���Ǳ�Ҫ����
*/
BOOL isFunction(char *lineString, CodeAnalysis *codeAnalysis, Stack *signStack) {
	int index = skipSpace(lineString,0);
	char buffer[NAME_SIZE] = { 0 };
	char functionName[NAME_SIZE] = { 0 };
	//���������ʹ���buffer��
	if (copyAndCheckIdentifier(buffer, lineString, &index) == FALSE) {
		return FALSE;
	}

	index = skipSpace(lineString,index);

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
	index = skipSpace(lineString,index);

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
		//���һ�������Ľ��
		addFunctionNode(codeAnalysis,functionName);
		//�޸Ĵ�������
		increaseCodeCount(codeAnalysis,signStack);
		return TRUE;
	}
	return FALSE;
}

/*
	����һ���µĺ���ͳ�ƽ�㵽CodeAnalysis����
*/
void addFunctionNode(CodeAnalysis *codeAnalysis,char *functionName) {
	FunctionAnalysis *function = (FunctionAnalysis *)malloc(sizeof(FunctionAnalysis));
	function->codeLineCount = 0;
	strcpy(function->functionName, functionName);
	//��ͷ�巨������뵽��һ��λ��
	function->next = codeAnalysis->functionAnalysis->next;
	codeAnalysis->functionAnalysis->next = function;
	//ͷ���ͳ�ƺ�������
	codeAnalysis->functionAnalysis->codeLineCount++;
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
	//��������ĩβ,���������жϸ���ĩβ�ַ��Ĳ���
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

/*
	����Ӧ���ֵĴ���������������
*/
void increaseCodeCount(CodeAnalysis *codeAnalysis, Stack *signStack) {
	(codeAnalysis->codeLineCount)++;
	//ջ�������ŵ�ʱ��ſ����Ǻ�����Ĵ���,�������# �� ����/�������� ��Щ������
	if (isStackEmpty(signStack) == FALSE)
	{
		(codeAnalysis->functionAnalysis->next->codeLineCount)++;
	}
}
