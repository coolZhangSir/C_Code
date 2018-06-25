#include <WINDEF.H>

typedef struct IMAGE_DOS_HEADER_STRUCT {
	WORD e_magic;//MZǩ��
	DWORD e_lfanew;//PE�ļ�ͷƫ��,ָ����PE�ļ�ͷ��λ��
}IMAGE_DOS_HEADER_STRUCT;

typedef struct IMAGE_FILE_HEADER_STRUCT {
	WORD machine;//����ƽ̨
	WORD numberOfSections;//PE�еĽ���
	WORD sizeOfOptionalHeader;//��չͷ�Ĵ�С
	WORD characteristics;//�ļ�����
}IMAGE_FILE_HEADER_STRUCT;

typedef struct IMAGE_DATA_DIRECTORY_STRUCT {
	int id;//��ǰ�����
	DWORD virtualAddress;//���ݵ���ʼRVA
	DWORD iSize;//���ݿ�ĳ���
}IMAGE_DATA_DIRECTORY_STRUCT;

typedef struct IMAGE_OPTIONAL_HEADER32_STRUCT {
	WORD magic;//��־��,��ͨ��ִ���ļ�Ϊ(0x010BH)
	DWORD sizeOfCode;//���к�����Ľڵ��ܴ�С
	DWORD addressOfEntryPoint;//����ִ�����RVA
	DWORD baseOfCode;//����Ľڵ���ʼRVA
	DWORD baseOfData;//���ݵĽڵ���ʼRVA
	DWORD imageBase;//������װ�ص�ַ(EXEͨ��Ϊ40000H)
	DWORD sectionAlignment;//�ڴ��е������������(ͨ��Ϊ0x1000H)
	DWORD fileAlignment;//�ļ��е������������(ͨ��Ϊ0x20000H)
	DWORD sizeOfImage;//�ڴ�������PE�ļ���ӳ��ߴ�
	DWORD sizeOfHeaders;//����ͷ+�ڱ�Ĵ�С
	WORD subsystem;//�ļ�����ϵͳ(Windowsͼ�γ���ͨ��Ϊ0x0002)
	DWORD numberOfRvaAndSizes;//DataDirectory��Ŀ����,ͨ��Ϊ16��
	IMAGE_DATA_DIRECTORY_STRUCT *dataDirectories;//����Ŀ¼����,ͨ��ֻ���ĵ�2��Ԫ��(����Ŀ¼)�͵�13��Ŀ¼(���뺯����ַĿ¼)
}IMAGE_OPTIONAL_HEADER32_STRUCT;

typedef struct IMAGE_NT_HEADERS_STRUCT {
	DWORD signature;//PE�ļ���ʶ
	IMAGE_FILE_HEADER_STRUCT *fileHeader;//�ļ�ͷ�ṹ
	IMAGE_OPTIONAL_HEADER32_STRUCT *optionalHeader;//��չͷ�ṹ
}IMAGE_NT_HEADERS_STRUCT;

//������FILE_HEADER�е�NumberOfSection + 1���յĽ������α����
typedef struct IMAGE_SECTION_HEADER_STRUCT {
	BYTE    Name[IMAGE_SIZEOF_SHORT_NAME];
	union {
		DWORD   PhysicalAddress;
		DWORD   VirtualSize;
	} Misc;
	DWORD   VirtualAddress;
	DWORD   SizeOfRawData;
	DWORD   PointerToRawData;
	DWORD   Characteristics;
}IMAGE_SECTION_HEADER_STRUCT;

