
// ����ת������Dlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "����ת������.h"
#include "����ת������Dlg.h"
#include "afxdialogex.h"

#include<stdio.h>
#include<stdlib.h>
/*
ͨ��ģ�����һ�����Ķ�����,�˽���,ʮ������
*/
/*
10 % 2 = 0	10 / 2 = 5

5  % 2 = 1	5  / 2 = 2

2  % 2 = 0	2 / 2 = 1
1  % 2 = 1	1 / 2 = 0
*/
void binary(int number, char *arr) {
	int i = 31;
	arr[32] = '\0';
	for (; i >= 0; i--) {
		if (number > 0) {
			arr[i] = number % 2 + '0';
		}
		else {
			arr[i] = '0';
		}
		number /= 2;
	}
}
void octal(int number, char* arr) {
	int i = 10;
	arr[11] = '\0';
	for (; i >= 0; i--) {
		if (number > 0) {
			arr[i] = number % 8 + '0';
		}
		else {
			arr[i] = '0';
		}
		number /= 8;
	}
}
void hex(int number, char *arr) {
	int i = 7;
	arr[8] = '\0';
	for (; i >= 0; i--) {
		if (number % 16 >= 10) {
			arr[i] = number % 16 - 10 + 'A';
		}
		else {
			arr[i] = number % 16 + '0';
		}

		number /= 16;
	}
}

void recursiveBinary(int number, char *arr, int index) {
	if (number == 0) {
		return;
	}
	else {
		recursiveBinary(number /= 2, arr, index - 1);
		arr[index] = number % 2 + '0';
	}
}

void recursiveOctal(int number, char *arr, int index) {
	if (number == 0) {
		return;
	}
	else {
		recursiveBinary(number /= 8, arr, index - 1);
		arr[index] = number % 8 + '0';
	}
}

void recursiveHex(int number, char *arr, int index) {
	if (number == 0) {
		return;
	}
	else {
		recursiveBinary(number /= 16, arr, index - 1);
		if (number % 16 >= 10) {
			arr[index] = number % 16 - 10 + 'A';
		}
		arr[index] = number % 16 + '0';
	}
}

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C����ת������Dlg �Ի���



C����ת������Dlg::C����ת������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C����ת������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT4, numberEdit);
	DDX_Control(pDX, IDC_EDIT1, binaryEdit);
	DDX_Control(pDX, IDC_EDIT2, octalEdit);
	DDX_Control(pDX, IDC_EDIT3, hexEdit);
}

BEGIN_MESSAGE_MAP(C����ת������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C����ת������Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// C����ת������Dlg ��Ϣ�������

BOOL C����ת������Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C����ת������Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C����ת������Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C����ת������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C����ת������Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�Ȼ�ȡ����������е�ֵ
	CString numberString;

	int number = 0;
	char binaryArray[33] = { 0 };
	char octalArray[12] = { 0 };
	char hexArray[9] = { 0 };

	numberEdit.GetWindowTextA(numberString);
	sscanf(numberString,"%d",&number);

	binary(number, binaryArray);
	octal(number, octalArray);
	hex(number, hexArray);



	binaryEdit.SetWindowTextA(binaryArray);
	octalEdit.SetWindowTextA(octalArray);
	hexEdit.SetWindowTextA(hexArray);
}
