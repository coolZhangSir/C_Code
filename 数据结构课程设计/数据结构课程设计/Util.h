//���ļ��洢һЩ������ͨ�����߷���

//��������
#define FILE_PATH "C:\\Users\\ZhangHao\\Desktop\\test2.c"
#define OPEN_FILE_ERROR "�ļ���ʧ��!\n"
#define FUNCTION_COUNT "��������"

#define BOOL int
#define SIGN_MULTIPLE_COMMENT '*'
#define SIGN_BLOCK '{'
#define SIGN_PARENTHESES '('
#define NAME_SIZE 80
#define BUFFER_SIZE 150

#define EVALUATE_EXCELLENT "Excellent"
#define EVALUATE_AWSOME "Awsome"
#define EVALUATE_GREATE "Great"
#define EVALUATE_GOOD "Good"

//ͨ�ù��߷���
void inputFileName(char *fileName);
void output(char *content);
int skipSpace(char *lineString, int index);
BOOL isLegalIdentifier(char *identifier);
BOOL isLegalFirstCharacter(char character);
BOOL isLegalCharacter(char character);
BOOL copyAndCheckIdentifier(char *buffer, char *source, int *sourceIndex);
BOOL isOperator(char character);


