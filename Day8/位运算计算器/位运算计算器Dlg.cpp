
// λ���������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "λ���������.h"
#include "λ���������Dlg.h"
#include "afxdialogex.h"

#include<stdio.h>
#include<stdlib.h>
/*
ʹ��λ����ʵ�ּӼ��˳�ȡģ
�ӷ��������������������,Ȼ��ͨ���������ж����޽�λ�����,�����ֱ������һλ����
*/
int add(int a, int b) {
	int sum = 0;
	sum = a ^ b;
	if ((a & b) != 0) {
		sum += ((a & b) << 1);
	}
	return sum;
}
/*
5 - 3 = 2
5�Ĳ���:
0000 0101

3��ԭ��
�Ƚ���ת���ɸ���
0000 0011 ==>  1111 1100
�����䷴��
1000 0011 ==>  1111 1100
��+1�õ�����
1111 1100 ==>  1111 1101
�ٽ��мӷ�
*/
int substract(int a, int b) {
	int mask = 4294967295;
	int minus = 0;
	//�����õ�����
	b ^= mask;
	//��1�õ�����
	b += 1;
	minus = add(a, b);
	
	return minus;
}
/*
�˷����Ƕ���ӷ�
*/
int times(int a, int b) {
	int i = 0;
	int sum = a;

	for (; i < b - 1; i++) {
		sum = sum ^ a;
		if ((a & a) != 0) {
			sum += ((a & a) << 1);
		}
	}
	
	return sum;
}
/*
����:��������ȡ��+1�õ����Ӧ�ĸ����Ĳ���.
Ȼ����ݳ������ڱ���������������ѭ���������ټ�1
*/
int divide(int a, int b) {
	int result = 1;
	int mask = 4294967295;
	int sum = 0;
	int c = b;
	while (a > c) {
		b = c;

		b ^= mask;
		b += 1;

		sum = a ^ b;

		//���������,!=�����ȴ���&������
		if ((a & b) != 0) {
			sum += ((a & b) << 1);
		}
		a = sum;
		result++;
	}

	return result;
}

/*
ȡ����ǽ��г���,�����С�ڱ������ĳ�����Ϊ����
*/
int remainder(int a, int b) {
	int c = b;
	int mask = 4294967295;
	int sum = 0;
	while (a >= c) {
		b = c;
		b = b ^ mask;

		sum = b ^ 1;
		if ((b & 1) != 0) {
			sum += ((b & 1) << 1);
		}

		b = sum;

		sum = a ^ b;
		if ((a & b) != 0) {
			sum += ((a & b) << 1);
		}

		a = sum;
	}
	
	return a;
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


// Cλ���������Dlg �Ի���



Cλ���������Dlg::Cλ���������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cλ���������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, parameter1Edit);
	DDX_Control(pDX, IDC_EDIT2, parameter2Edit);
	DDX_Control(pDX, IDC_EDIT3, resultEdit);
	DDX_Control(pDX, IDC_BUTTON1, addButton);
	DDX_Control(pDX, IDC_BUTTON2, substractButton);
	DDX_Control(pDX, IDC_BUTTON3, multiplyButton);
	DDX_Control(pDX, IDC_BUTTON4, divisionButton);
	DDX_Control(pDX, IDC_BUTTON5, remainderButton);
}

BEGIN_MESSAGE_MAP(Cλ���������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cλ���������Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Cλ���������Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Cλ���������Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Cλ���������Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &Cλ���������Dlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// Cλ���������Dlg ��Ϣ�������

BOOL Cλ���������Dlg::OnInitDialog()
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

void Cλ���������Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cλ���������Dlg::OnPaint()
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
HCURSOR Cλ���������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//�ӷ�����
void Cλ���������Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString parameter1;
	CString parameter2;
	char resultString[100] = { 0 };
	
	int parameter1Number = 0;
	int parameter2Number = 0;
	int result = 0;

	parameter1Edit.GetWindowTextA(parameter1);
	parameter2Edit.GetWindowTextA(parameter2);

	sscanf(parameter1, "%d", &parameter1Number);
	sscanf(parameter2, "%d", &parameter2Number);

	result = add(parameter1Number, parameter2Number);
	sprintf(resultString, "%d", result);

	resultEdit.SetWindowTextA(resultString);
}

//����
void Cλ���������Dlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString parameter1;
	CString parameter2;
	char resultString[100] = { 0 };

	int parameter1Number = 0;
	int parameter2Number = 0;
	int result = 0;

	parameter1Edit.GetWindowTextA(parameter1);
	parameter2Edit.GetWindowTextA(parameter2);

	sscanf(parameter1, "%d", &parameter1Number);
	sscanf(parameter2, "%d", &parameter2Number);

	result = substract(parameter1Number, parameter2Number);
	sprintf(resultString, "%d", result);

	resultEdit.SetWindowTextA(resultString);
}

//�˷�
void Cλ���������Dlg::OnBnClickedButton3()
{
	CString parameter1;
	CString parameter2;
	char resultString[100] = { 0 };

	int parameter1Number = 0;
	int parameter2Number = 0;
	int result = 0;

	parameter1Edit.GetWindowTextA(parameter1);
	parameter2Edit.GetWindowTextA(parameter2);

	sscanf(parameter1, "%d", &parameter1Number);
	sscanf(parameter2, "%d", &parameter2Number);

	result = times(parameter1Number, parameter2Number);
	sprintf(resultString, "%d", result);

	resultEdit.SetWindowTextA(resultString);
}

//����
void Cλ���������Dlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString parameter1;
	CString parameter2;
	char resultString[100] = { 0 };

	int parameter1Number = 0;
	int parameter2Number = 0;
	int result = 0;

	parameter1Edit.GetWindowTextA(parameter1);
	parameter2Edit.GetWindowTextA(parameter2);

	sscanf(parameter1, "%d", &parameter1Number);
	sscanf(parameter2, "%d", &parameter2Number);

	result = divide(parameter1Number, parameter2Number);
	sprintf(resultString, "%d", result);

	resultEdit.SetWindowTextA(resultString);
}

//����
void Cλ���������Dlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString parameter1;
	CString parameter2;
	char resultString[100] = { 0 };

	int parameter1Number = 0;
	int parameter2Number = 0;
	int result = 0;

	parameter1Edit.GetWindowTextA(parameter1);
	parameter2Edit.GetWindowTextA(parameter2);

	sscanf(parameter1, "%d", &parameter1Number);
	sscanf(parameter2, "%d", &parameter2Number);

	result = remainder(parameter1Number, parameter2Number);
	sprintf(resultString, "%d", result);

	resultEdit.SetWindowTextA(resultString);
}
