
// λ���������Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// Cλ���������Dlg �Ի���
class Cλ���������Dlg : public CDialogEx
{
// ����
public:
	Cλ���������Dlg(CWnd* pParent = NULL);	// ��׼���캯��

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
	CEdit parameter1Edit;
	CEdit parameter2Edit;
	CEdit resultEdit;
	CButton addButton;
	CButton substractButton;
	CButton multiplyButton;
	CButton divisionButton;
	CButton remainderButton;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
