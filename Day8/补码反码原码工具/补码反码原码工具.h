
// ���뷴��ԭ�빤��.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C���뷴��ԭ�빤��App: 
// �йش����ʵ�֣������ ���뷴��ԭ�빤��.cpp
//

class C���뷴��ԭ�빤��App : public CWinApp
{
public:
	C���뷴��ԭ�빤��App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C���뷴��ԭ�빤��App theApp;