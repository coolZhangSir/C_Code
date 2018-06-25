#include "PeParser.h"

void inputFileName(char *fileName) {
	showString(TIPS_INPUT_FILE_PATH);
	gets(fileName);
}

STATUS openFile(FILE **file,char *fileName) {
	*file = fopen(fileName,"r");
	if (*file != NULL)
	{
		return SUCCESS;
	}
	else {
		return FAILURE;
	}
}

STATUS parseDosHeaderStruct(IMAGE_DOS_HEADER_STRUCT *dosHeader,FILE *file) {
	if (dosHeader == NULL) {
		return FAILURE;
	}

	char buffer[5] = { 0 };
	int size = fread(buffer, sizeof(WORD), 1, file);
	if (size != 0)
	{
		//showString(buffer);
		dosHeader->e_magic = (WORD)charToDWORD(buffer, sizeof(WORD), CHARACTER);
		fseek(file, 0 - sizeof(WORD), SEEK_CUR);

		int result = seekAndReadFile(file, sizeof(DWORD), OFFSET_ELFANEW, &(dosHeader->e_lfanew), NOT_CHARACTER);
		if (result == FSEEK_ERROR)
		{
			return FAILURE;
		}
		else
		{
			return SUCCESS;
		}
	}
	else {
		return FAILURE;
	}
}

STATUS parseNTHeadersStruct(IMAGE_NT_HEADERS_STRUCT *ntHeaders, FILE *file) {
	//1.PE�ļ���ʶ
	STATUS status = parsePESignature(ntHeaders, file);
	if (status == FAILURE) {
		showString(ERROR_ON_PARSE_PE_SIGNATURE);
		return FAILURE;
	}

	//2.�ļ�ͷ
	ntHeaders->fileHeader = (IMAGE_FILE_HEADER_STRUCT *)malloc(sizeof(IMAGE_FILE_HEADER_STRUCT));
	status = parseFileHeaderStruct(ntHeaders->fileHeader, file);
	if (status == FAILURE) {
		showString(ERROR_ON_PARSE_FILE_HEADER);
		return FAILURE;
	}

	//3.��ѡͷ
	ntHeaders->optionalHeader = (IMAGE_OPTIONAL_HEADER32_STRUCT *)malloc(sizeof(IMAGE_OPTIONAL_HEADER32_STRUCT));
	status = parseOptionalHeaderStruct(ntHeaders->optionalHeader, file);
	if (status == FAILURE) {
		showString(ERROR_ON_PARSE_OTPIONAL_HEADER);
		return FAILURE;
	}
	return SUCCESS;
}

STATUS parsePESignature(IMAGE_NT_HEADERS_STRUCT *ntHeader, FILE *file) {
	if (file == NULL || ntHeader == NULL) {
		return FAILURE;
	}
	int result = seekAndReadFile(file, sizeof(DWORD), OFFSET_NT_HEADERS, &(ntHeader->signature), CHARACTER);
	if (result == FSEEK_ERROR)
	{
		return FAILURE;
	}
	return SUCCESS;
}

STATUS parseFileHeaderStruct(IMAGE_FILE_HEADER_STRUCT *fileHeaders, FILE *file) {
	if (file == NULL || fileHeaders == NULL) {
		return FAILURE;
	}
	//1.�ȴ��ļ���ʼ��ַ����PEͷ��λ��
	int flag = fseek(file, OFFSET_NT_HEADERS, SEEK_SET);
	if (flag == FSEEK_ERROR)
	{
		return FAILURE;
	}

	//2.����PEͷ,��ȡMachine�ֶ�
	flag = seekAndReadFile(file, sizeof(WORD), OFFSET_MACHINE, &(fileHeaders->machine), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}

	//3.����PEͷ,��ȡNumberOfSections�ֶ�
	flag = seekAndReadFile(file, sizeof(WORD), OFFSET_NUMBER_OF_SECTIONS, &(fileHeaders->numberOfSections), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}

	//4.����PEͷ,��ȡSizeOfOptionalHeader�ֶ�
	flag = seekAndReadFile(file, sizeof(WORD), OFFSET_SIZE_OF_OPTIONAL_HEADER, &(fileHeaders->sizeOfOptionalHeader), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	
	//5.����PEͷ,��ȡCharacteristics�ֶ�
	flag = seekAndReadFile(file, sizeof(WORD), OFFSET_CHARACTERISTICS, &(fileHeaders->characteristics), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}

	//6.������,��ָ����ƫ�ƻ��ļ���ʼ��ַ
	fseek(file, 0 - OFFSET_NT_HEADERS, SEEK_CUR);
	return SUCCESS;
}
STATUS parseOptionalHeaderStruct(IMAGE_OPTIONAL_HEADER32_STRUCT *optionalHeaders, FILE *file) {
	if (file == NULL || optionalHeaders == NULL) {
		return FAILURE;
	}
	//1.��ָ��ƫ�Ƶ�PEͷ��
	int flag = fseek(file, OFFSET_NT_HEADERS, SEEK_SET);
	if (flag == FSEEK_ERROR)
	{
		return FAILURE;
	}
	//2.����PEͷ,��ȡMagic�ֶ�
	flag = seekAndReadFile(file, sizeof(WORD), OFFSET_MAGIC, &(optionalHeaders->magic), CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//3.����PEͷ,��ȡSizeOfCode�ֶ�
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_MAGIC, &(optionalHeaders->sizeOfCode), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//4.����PEͷ,��ȡAddressOfEntryPoint�ֶ�
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_ADDRESS_OF_ENTRY_POINT, &(optionalHeaders->addressOfEntryPoint), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//5.����PEͷ,��ȡBaseOfCode�ֶ�
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_BASE_OF_CODE, &(optionalHeaders->baseOfCode), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//6.����PEͷ,��ȡBaseOfData�ֶ�
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_BASE_OF_DATA, &(optionalHeaders->baseOfData), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//7.����PEͷ,��ȡImageBase�ֶ�
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_IMAGE_BASE, &(optionalHeaders->imageBase), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//8.����PEͷ,��ȡSectionAlignment�ֶ�
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_SECTION_ALIGNMENT, &(optionalHeaders->sectionAlignment), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//9.����PEͷ,��ȡFileAlignment�ֶ�
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_FILE_ALIGNMENT, &(optionalHeaders->fileAlignment), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//10.����PEͷ,��ȡSizeOfImage�ֶ�
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_SIZE_OF_IMAGE, &(optionalHeaders->sizeOfImage), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//11.����PEͷ,��ȡSizeOfHeader�ֶ�
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_SIZE_OF_HEADERS, &(optionalHeaders->sizeOfHeaders), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//12.����PEͷ,��ȡSubsystem�ֶ�
	flag = seekAndReadFile(file, sizeof(WORD), OFFSET_SUBSYSTEM, &(optionalHeaders->subsystem), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//13.����PEͷ,��ȡnumberOfRvaAndSizes�ֶ�
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_NUMBER_OF_RVA_AND_SIZE, &(optionalHeaders->numberOfRvaAndSizes), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}

	//14.��ȡ����Ŀ¼��2���͵�13��Ԫ��(�±��0��)
	optionalHeaders->dataDirectories = (IMAGE_DATA_DIRECTORY_STRUCT *)malloc((sizeof(DWORD) * 2 + sizeof(int)) * 2);
	//1.������2��Ԫ��
	optionalHeaders->dataDirectories[0].id = 2;
	parseDataDirectoryStruct(&(optionalHeaders->dataDirectories[0]), file, 1);
	//2.������13��Ԫ��
	optionalHeaders->dataDirectories[1].id = 13;
	parseDataDirectoryStruct(&(optionalHeaders->dataDirectories[1]), file, 12);
	//����ָ��
	fseek(file, 0 - OFFSET_NT_HEADERS, SEEK_CUR);
	return SUCCESS;
}
STATUS parseDataDirectoryStruct(IMAGE_DATA_DIRECTORY_STRUCT *dataDirectoryHeaders, FILE *file, int directoryIndex) {
	if (file == NULL || dataDirectoryHeaders == NULL) {
		return FAILURE;
	}
	//����NT_HEADER,ƫ�Ƶ�����Ŀ¼
	int flag = fseek(file, OFFSET_DATA_DIRECTORY, SEEK_CUR);
	if (flag == FSEEK_ERROR)
	{
		return FAILURE;
	}
	
	//��ȡ��directoryIndex��DATA_DIRECTORY,����DATA_DIRECTORY��СΪsizeof(DWORD) * 2
	//1.��ȡVIRTUAL_ADDRESS
	flag = seekAndReadFile(file, sizeof(DWORD), (sizeof(DWORD) * 2) * directoryIndex, &(dataDirectoryHeaders->virtualAddress), NOT_CHARACTER);
	if (flag == FSEEK_ERROR)
	{
		return FAILURE;
	}

	//2.��ȡiSize
	flag = seekAndReadFile(file, sizeof(DWORD), (sizeof(DWORD) * 2) * directoryIndex + sizeof(DWORD), &(dataDirectoryHeaders->iSize), NOT_CHARACTER);
	if (flag == FSEEK_ERROR)
	{
		return FAILURE;
	}

	//���˵�NT_HEADER
	fseek(file, 0 - OFFSET_DATA_DIRECTORY, SEEK_CUR);
	return SUCCESS;
}

/*
	����ָ����ĳ��Section_Header
*/
STATUS parseSectionStruct(IMAGE_SECTION_HEADER_STRUCT *sectionHeader, FILE *file ,int index) {
	if (file == NULL || sectionHeader == NULL) {
		return FAILURE;
	}
	//ƫ�Ƶ��ڱ�λ��
	int flag = fseek(file, OFFSET_IMAGE_SECTION_HEADER, SEEK_SET);
	if (flag == FSEEK_ERROR)
	{
		return FAILURE;
	}

	//1.�ֶ���������
	flag = fseek(file, SIZE_OF_SECTION * index, SEEK_CUR);
	if (flag == FSEEK_ERROR)
	{
		return FAILURE;
	}
	flag = fread(sectionHeader->Name, IMAGE_SIZEOF_SHORT_NAME, 1, file);
	if (flag == FREAD_ERROR)
	{
		return FAILURE;
	}
	flag = fseek(file, 0 - (SIZE_OF_SECTION * index + IMAGE_SIZEOF_SHORT_NAME), SEEK_CUR);
	if (flag == FSEEK_ERROR)
	{
		return FAILURE;
	}

	//2.����Union�е�VirtualSize
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_UNION_MISC + SIZE_OF_SECTION * index, &(sectionHeader->Misc.VirtualSize), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//3.����VirtualAddress
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_VIRTUAL_ADDRESS + SIZE_OF_SECTION * index, &(sectionHeader->VirtualAddress), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//4.����SIZE_OF_RAW_DATA
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_SIZE_OF_RAW_DATA + SIZE_OF_SECTION * index, &(sectionHeader->SizeOfRawData), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//4.����POINT_TO_RAW_DATA
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_POINT_TO_RAW_DATA + SIZE_OF_SECTION * index, &(sectionHeader->PointerToRawData), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}
	//5.����characteristics
	flag = seekAndReadFile(file, sizeof(DWORD), OFFSET_SECTION_CHARACTERISTICS + SIZE_OF_SECTION * index, &(sectionHeader->Characteristics), NOT_CHARACTER);
	if (flag == FAILURE)
	{
		return FAILURE;
	}

	fseek(file, 0 - OFFSET_IMAGE_SECTION_HEADER, SEEK_CUR);
	return SUCCESS;
}