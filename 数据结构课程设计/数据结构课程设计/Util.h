//���ļ��洢һЩ������ͨ�����߷���

//��������
#define FILE_PATH "C:\\Users\\ZhangHao\\Desktop\\test.c"
//#define FILE_PATH "F:\\Code_Sets\\C_Code\\���������ϰ��\\���������ϰ��"
#define OPEN_FILE_ERROR "�ļ���ʧ��!"
#define FUNCTION_COUNT "��������"

#define BOOL int
#define SIGN_MULTIPLE_COMMENT '*'
#define SIGN_BLOCK '{'
#define NAME_SIZE 80
#define BUFFER_SIZE 150

//ͨ�ù��߷���
void inputFileName(char *fileName);
void output(char *content);
int skipSpace(char *lineString, int index);
BOOL isLegalIdentifier(char *identifier);
BOOL isLegalFirstCharacter(char character);
BOOL isLegalCharacter(char character);
BOOL copyAndCheckIdentifier(char *buffer, char *source, int *sourceIndex);
BOOL isOperator(char character);

