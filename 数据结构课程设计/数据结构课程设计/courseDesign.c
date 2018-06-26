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
		increaseEmptyLineCount(codeAnalysis, signStack);
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
			increaseCommentLineCount(codeAnalysis, signStack);

			if (lineString[index + 1] == '*')
			{
				//����ǰע�Ϳ���ʼ��ѹջ
				push(signStack, SIGN_MULTIPLE_COMMENT);
			}
		}
		return TRUE;
	}
	//�ж϶���ע�ͽ���(����ע������һ�п�ʼ�����
	else if (lineString[index] == '*') {
		if (lineString[index + 1] == '/')
		{
			//�Դ����������޸�Ҫ���ڳ�ջǰ,���⺯�������ų�ջ���˻�û�޸�,��ɺ������ڵĴ���������©��
			increaseCommentLineCount(codeAnalysis, signStack);
			
			pop(signStack);
			return TRUE;
		}
	}
	
	//���ջ���Ƕ���ע����ʼ��,����Ҫ��ʱ�жϽ�����־��
	if (getTop(signStack) == '*')
	{
		//��������ĩβ,���������жϸ���ĩβ�ַ��Ĳ���(�������ע�ͽ���������һ��ĩβ�����)
		while (lineString[index] != '\n' && lineString[index] != '\0')
		{
			index++;
		}
		//������з�'\n'ǰ�����пհ��ַ�,����ָ���Ƶ�������һ���ǿհ׷�,���һ�п���û��'\n',ֻ��һ��'\0'
		while (index >= 0 && (lineString[index] == ' ' || lineString[index] == '\t'
			|| lineString[index] == '\n' || lineString[index] == '\0')) {
			index--;
		}
		//����ע�ͽ�����
		if (lineString[index] == '/')
		{
			if (lineString[index - 1] == '*')
			{
				//�Դ����������޸�Ҫ���ڳ�ջǰ,���⺯�������ų�ջ���˻�û�޸�,��ɺ������ڵĴ���������©��
				increaseCommentLineCount(codeAnalysis, signStack);

				//����ע�ͳ�ջ
				pop(signStack);
				return TRUE;
			}
		}
		//�������ע����δ����,ֱ�Ӽ�������
		else
		{
			increaseCommentLineCount(codeAnalysis, signStack);
			return TRUE;
		}
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
	//�п���һ��while��������������ж��'('����ջ,�������м�⵽�߼��������,������������,����ջ��ƽ��.
	//����������Ҫ��¼������ջ����,�˳�ʱȫ����ջ
	int pushCount = 0;
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
		/*
			��ջ'('������'('��' ',�����һ���ǲ���')',����������в���,��Ҫ���һ�����������,�����if/while����
			��ջ�ͳ�ջ'('��ԭ���Ǳ�����������(���ʽ),��int (*p)[3]����while((a + b) > 3)
			���ﲻ��ֻͨ��while/if/for�ȹؼ�����ȷ���ǲ��Ǻ���,��Ϊ�ؼ��ֿ�������©,�ҳ���������õ�
		*/
		push(signStack,SIGN_PARENTHESES);
		pushCount++;
		index++;
		index = skipSpace(lineString,index);
		//ѭ��������������lineString[index] != ')',���Ƿ���ջ������'(',��Ŵ�������б��Ѿ���ȡ�����
		while (lineString[index] != '\n' && getTop(signStack) == '(' )
		{
			//ѭ��������ȡ�����б�ı�ʶ��,�Ա㴦��const�������
			while (lineString[index] != ',' && lineString[index] != '\n' && getTop(signStack) == '(') {
				//�����ո�,���
		  		if (copyAndCheckIdentifier(buffer, lineString, &index) == FALSE) {
					popMultiply(signStack, pushCount);
					return FALSE;
				}
				//������'('�ͼ�����ջ������
				if (lineString[index] == '(')
				{
					push(signStack, SIGN_PARENTHESES);
					pushCount++;
					index++;
					index = skipSpace(lineString, index);
				}
				//����')'�ͼ�����ջ������
				if (lineString[index] == ')')
				{
					pop(signStack);
					pushCount--;
					//������Ҫ���ݲ����б�������Ǹ�')'���жϺ�����ǲ���'{',�������һ��')'������
					if (getTop(signStack) == '(')
					{
						index++;
					}
					index = skipSpace(lineString, index);
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
		popMultiply(signStack, pushCount);
		return FALSE;
	}
	/*
		��������Ĵ���֮��,
		����Ǵ��ں����������������Ŵ�,���жϴ�����,���ھ���ջ
		û�о�����,����Ҫ�ж�ĩβ�Ƿ����';',����������ͷ
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
				popMultiply(signStack, pushCount);
				return FALSE;
			}
			index++;
		}
		//���һ�������Ľ��
		addFunctionNode(codeAnalysis,functionName);
		//ǰ��'{'�Ѿ���ջ,�޸��ļ��ͺ����д�������,����,������������ֻͳ�����洿������
		//increaseCodeCount(codeAnalysis,signStack);

		//ǰ��'{'�Ѿ���ջ, ֻ�޸��ļ������������¼,���ܵ�������ķ���,�����Ժ����ڲ����м���
		(codeAnalysis->totalLineCount)++;
		updateTotalLineCount(codeAnalysis);

		popMultiply(signStack, pushCount);
		return TRUE;
	}
	popMultiply(signStack, pushCount);
	return FALSE;
}

/*
	����ָ����push��������pop
*/
void popMultiply(Stack *signStack,int pushCount) {
	while (pushCount > 0)
	{
		pop(signStack);
		pushCount--;
	}
}

/*
	����һ���µĺ���ͳ�ƽ�㵽CodeAnalysis����
*/
void addFunctionNode(CodeAnalysis *codeAnalysis,char *functionName) {
	FunctionAnalysis *function = (FunctionAnalysis *)malloc(sizeof(FunctionAnalysis));
	function->blankLineCount = 0;
	function->commentLineCount = 0;
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
		//��������Ŀ�ͷ�����ڴ�������,�����Ǵ����������'{'����һ�е����
		increaseCodeCount(codeAnalysis, signStack);
		push(signStack, '{');
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
		//�������жϺ��������һ��'}',����Ҫ�ȳ�ջ,Ȼ��ջ�Ƿ�Ϊ��,Ϊ��˵���ղ��Ǻ���������һ��'}',������
		pop(signStack);
		//��������Ľ����������ڴ�������
		increaseCodeCount(codeAnalysis, signStack);
		return;
	}
	increaseCodeCount(codeAnalysis, signStack);
}

/*
	����Ӧ���ֵĴ���������������
*/
void increaseCodeCount(CodeAnalysis *codeAnalysis, Stack *signStack) {
	//�����������м���
	(codeAnalysis->totalLineCount)++;
	//ջ���д����ŵ�ʱ��ſ����Ǻ�����Ĵ���,�������# �� ����/�������� ��Щ������
	if (getBottom(signStack) == SIGN_BLOCK) {
		(codeAnalysis->functionAnalysis->next->codeLineCount)++;
	}
	//�����¼�����ֶ�
	updateTotalLineCount(codeAnalysis);
}

/*
	�Կ��������м���
*/
void increaseEmptyLineCount(CodeAnalysis *codeAnalysis, Stack *signStack) {
	//���������Ϳ��������м���
	(codeAnalysis->blankLineCount)++;
	(codeAnalysis->totalLineCount)++;
	//�����ǰ�ں�������ͷֱ����,�����뺯��������
	if (getBottom(signStack) == SIGN_BLOCK) {
		(codeAnalysis->functionAnalysis->next->blankLineCount)++;
	}
	//�����¼�����ֶ�
	updateTotalLineCount(codeAnalysis);
}

/*
	��ע���������м���
*/
void increaseCommentLineCount(CodeAnalysis *codeAnalysis, Stack *signStack) {
	//����������ע���������м���
	(codeAnalysis->commentLineCount)++;
	(codeAnalysis->totalLineCount)++;
	//�����ǰ�ں�������ͷֱ����,�����뺯��������
	if (getBottom(signStack) == SIGN_BLOCK) {
		(codeAnalysis->functionAnalysis->next->commentLineCount)++;
	}
	//�����¼�����ֶ�
	updateTotalLineCount(codeAnalysis);
}
/*
	�޸��ļ��еĴ�������=������-������-ע������
*/
void updateTotalLineCount(CodeAnalysis *codeAnalysis) {
	int totalLineCount = codeAnalysis->totalLineCount;
	int emptyLineCount = codeAnalysis->blankLineCount;
	int commentLineCount = codeAnalysis->commentLineCount;
	codeAnalysis->codeLineCount = totalLineCount - emptyLineCount - commentLineCount;
}