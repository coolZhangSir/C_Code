
// show_hide.cpp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cshow_hidecppApp: 
// �йش����ʵ�֣������ show_hide.cpp.cpp
//

class Cshow_hidecppApp : public CWinApp
{
public:
	Cshow_hidecppApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cshow_hidecppApp theApp;