
// ChildView.cpp : CChildView ���ʵ��
//

#include "stdafx.h"
#include "HookTest.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

HMODULE hDllLib;
CChildView::CChildView()
{
	
}

CChildView::~CChildView()
{
	
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_APP_EXIT, &CChildView::OnAppExit)
	ON_COMMAND(ID_EDIT_UNDO, &CChildView::OnEditUndo)
END_MESSAGE_MAP()



// CChildView ��Ϣ�������

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	
	// TODO: �ڴ˴������Ϣ����������
	
	// ��ҪΪ������Ϣ������ CWnd::OnPaint()
}



void CChildView::OnAppExit()
{
	// TODO: �ڴ���������������
	hDllLib = LoadLibrary(L"./����.dll");
	FARPROC initHook = GetProcAddress(hDllLib, "initHook");
	(*initHook)();
}


void CChildView::OnEditUndo()
{
	// TODO: �ڴ���������������
	FARPROC endHook = GetProcAddress(hDllLib, "endHook");
	(*endHook)();
	FreeLibrary(hDllLib);
}
