#include "PeParser.h"
void main() {
	FILE *file = NULL;
	char fileName[100] = { 0 };
	//char fileName[100] = "C:\\Users\\ZhangHao\\Desktop\\PE\\HelloWorld.exe";
	STATUS status = 0;

	while (1) {
		inputFileName(fileName);
		status = openFile(&file,fileName);
		if (status != SUCCESS)
		{
			showString(ERROR_ON_OPEN_FILE);
		}
		else {
			break;
		}
	}
	//����Dos�����õ������ֶ�
	IMAGE_DOS_HEADER_STRUCT *dosHeader = (IMAGE_DOS_HEADER_STRUCT *)malloc(sizeof(IMAGE_DOS_HEADER_STRUCT));
	status = parseDosHeaderStruct(dosHeader,file);
	if (status == FAILURE) {
		showString(ERROR_ON_PARSE_DOS);
	}

	//����PEͷ
	IMAGE_NT_HEADERS_STRUCT *ntHeaders = (IMAGE_NT_HEADERS_STRUCT *)malloc(sizeof(IMAGE_NT_HEADERS_STRUCT));
	parseNTHeadersStruct(ntHeaders, file);

	//�����α�
	int sectionCount = ntHeaders->fileHeader->numberOfSections;
	IMAGE_SECTION_HEADER_STRUCT *sectionHeader = (IMAGE_SECTION_HEADER_STRUCT *)malloc(sizeof(IMAGE_SECTION_HEADER_STRUCT) * sectionCount);
	for (int i = 0; i < sectionCount; i++)
	{
		status = parseSectionStruct(&(sectionHeader[i]), file, i);
		if (status == FAILURE) {
			showString(ERROR_ON_PARSE_SECTION_HEADER);
		}
	}

	showDosHeader(dosHeader);
	printf("\n");
	showNTHeader(ntHeaders);
	printf("\n");
	showSectionHeader(sectionHeader,sectionCount);

	/*
		ͨ�����ǻ᷸���ͷ��ڴ������������¼��֣�
		1.�ڴ��ظ��ͷţ�����double freeʱ��ͨ������������������¡�
		2.�ڴ�й¶��������ڴ������ͷš�
		3.�ڴ�Խ��ʹ�ã�ʹ���˲���ʹ�õ��ڴ档(�������)
		4.ʹ������Чָ�롣
		5.��ָ�룬��һ����ָ����в�����
	*/
	free(dosHeader);
	free(ntHeaders->fileHeader);
	free(ntHeaders->optionalHeader->dataDirectories);
	free(ntHeaders->optionalHeader);
	free(ntHeaders);
	free(sectionHeader);
	fclose(file);
	system("pause");
}