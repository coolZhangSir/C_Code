
// ����ת������Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// C����ת������Dlg �Ի���
class C����ת������Dlg : public CDialogEx
{
// ����
public:
	C����ת������Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit numberEdit;
	CEdit binaryEdit;
	CEdit octalEdit;
	CEdit hexEdit;
	afx_msg void OnBnClickedButton1();
};
