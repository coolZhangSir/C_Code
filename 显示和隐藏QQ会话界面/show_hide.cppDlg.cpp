
// show_hide.cppDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "show_hide.cpp.h"
#include "show_hide.cppDlg.h"
#include "afxdialogex.h"
#include <Windows.h>

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


// Cshow_hidecppDlg �Ի���



Cshow_hidecppDlg::Cshow_hidecppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SHOW_HIDECPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cshow_hidecppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cshow_hidecppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &Cshow_hidecppDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &Cshow_hidecppDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &Cshow_hidecppDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &Cshow_hidecppDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON3, &Cshow_hidecppDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON7, &Cshow_hidecppDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON8, &Cshow_hidecppDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON9, &Cshow_hidecppDlg::OnBnClickedButton10)
END_MESSAGE_MAP()


// Cshow_hidecppDlg ��Ϣ�������

BOOL Cshow_hidecppDlg::OnInitDialog()
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

void Cshow_hidecppDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cshow_hidecppDlg::OnPaint()
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
HCURSOR Cshow_hidecppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cshow_hidecppDlg::OnBnClickedButton2()
{
	//����PanDownload����
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HWND window = FindWindowA("CMainWnd", "Pan Download");
	if (window != NULL) {
		::ShowWindow(window, 0);
	}
	else {
		MessageBoxA(0, "�ó���δ����", "��ʾ", 0);
	}
}


void Cshow_hidecppDlg::OnBnClickedButton1()
{
	//��ʾPanDownload����
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HWND window = FindWindowA("CMainWnd", "Pan Download");
	if (window != NULL) {
		::ShowWindow(window, 1);
	}
	else {
		MessageBoxA(0, "�ó���δ����", "��ʾ", 0);
	}
}


void Cshow_hidecppDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ʾQQ�Ự����
	HWND window = FindWindowA("TXGuiFoundation", "�����");
	if (window != NULL) {
		::ShowWindow(window, 1);
	}
	else {
		MessageBoxA(0, "�ó���δ����", "��ʾ", 0);
	}
}


void Cshow_hidecppDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����QQ�Ự����
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HWND window = FindWindowA("TXGuiFoundation", "�����");
	if (window != NULL) {
		::ShowWindow(window, 0);
	}
	else {
		MessageBoxA(0, "�ó���δ����", "��ʾ", 0);
	}
}


void Cshow_hidecppDlg::OnBnClickedButton7()
{
	HWND mainWindow = FindWindowA(NULL, "AnyDesk");
	if (mainWindow != NULL) {
		::ShowWindow(mainWindow, 0);
	}
	else {
		MessageBoxA(0, "�ó���δ����", "��ʾ", 0);
	}
}


void Cshow_hidecppDlg::OnBnClickedButton8()
{
	HWND mainWindow = FindWindowA(NULL, "AnyDesk");
	if (mainWindow != NULL) {
		::ShowWindow(mainWindow, 1);
	}
	else {
		MessageBoxA(0, "�ó���δ����", "��ʾ", 0);
	}
}


void Cshow_hidecppDlg::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HWND mainWindow = FindWindowA("ConsoleWindowClass", "Tomcat");
	if (mainWindow != NULL) {
		::ShowWindow(mainWindow, 0);
	}
	else {
		MessageBoxA(0, "�ó���δ����", "��ʾ", 0);
	}
}


void Cshow_hidecppDlg::OnBnClickedButton10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HWND mainWindow = FindWindowA("ConsoleWindowClass", "Tomcat");
	if (mainWindow != NULL) {
		::ShowWindow(mainWindow, 1);
	}
	else {
		MessageBoxA(0, "�ó���δ����", "��ʾ", 0);
	}
}
