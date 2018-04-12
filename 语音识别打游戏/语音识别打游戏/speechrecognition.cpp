#include <windows.h>
#include <atlstr.h>
#include <sphelper.h>
#include <sapi.h>
#include<comutil.h>
#include<string.h>

#pragma comment(lib,"sapi.lib")
#pragma comment(lib, "comsupp.lib") 
#pragma comment(lib, "gdi32.lib")

#define GID_CMD_GR 333333
#define WM_RECOEVENT WM_USER+1

 LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

 char 	 szAppName[] = "����ɽ���µ�һ";
 BOOL b_initSR;
 BOOL b_Cmd_Grammar;
 CComPtr<ISpRecoContext>m_cpRecoCtxt;  //����ʶ�����ӿ�
 CComPtr<ISpRecoGrammar>m_cpCmdGramma; //ʶ���﷨
 CComPtr<ISpRecognizer>m_cpRecoEngine; //����ʶ������
 int speak(wchar_t *str);
 BYTE scan_code(DWORD pKey);

 int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR szCmdLine,int iCmdShow)
 {
	 HWND        hwnd;
	 MSG         msg;
	 WNDCLASS    wndclass;

	 wndclass.cbClsExtra          =0;
	 wndclass.cbWndExtra          =0;
	 wndclass.hbrBackground       =(HBRUSH)GetStockObject(WHITE_BRUSH);
	 wndclass.hCursor             =LoadCursor(NULL,IDC_ARROW);
	 wndclass.hIcon               =LoadIcon(NULL,IDI_APPLICATION);
	 wndclass.hInstance           =hInstance;
	 wndclass.lpfnWndProc         =WndProc;
	 wndclass.lpszClassName       =szAppName;
	 wndclass.lpszMenuName        =NULL;
	 wndclass.style               =CS_HREDRAW|CS_VREDRAW;

	 if(!RegisterClass(&wndclass))
	 {
		 MessageBox(NULL,TEXT("This program requires Windows NT!"),szAppName,MB_ICONERROR);
		 return 0;
	 }
	 speak(L"����ɽ���µ�һ");
	// speak(NULL);
	 hwnd=CreateWindow(szAppName,
		               TEXT("��������ɽ"),
					   WS_OVERLAPPEDWINDOW,
					   CW_USEDEFAULT,
					   CW_USEDEFAULT,
					   CW_USEDEFAULT,
					   CW_USEDEFAULT,
					   NULL,
					   NULL,
					   hInstance,
					   NULL);

	 ShowWindow(hwnd,iCmdShow);
	 UpdateWindow(hwnd);
	 
	 while(GetMessage(&msg,NULL,0,0))
	 {
		 TranslateMessage(&msg);
		 DispatchMessage(&msg);
	 }
	
	 return msg.wParam;
 }

 LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
 {
	 HDC           hdc;
	 PAINTSTRUCT   ps;

	 switch(message)
	 {
	 case WM_CREATE:
		 {
			 //��ʼ��COM�˿�
			 ::CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);
			 //����ʶ������COMʵ��Ϊ������
			 HRESULT hr=m_cpRecoEngine.CoCreateInstance(CLSID_SpSharedRecognizer);
			 //����ʶ�������Ľӿ�
			 if(SUCCEEDED(hr))
			 {
				 hr=m_cpRecoEngine->CreateRecoContext(&m_cpRecoCtxt);
			 }
			 else MessageBox(hwnd,TEXT("error1"),TEXT("error"),S_OK);
			 //����ʶ����Ϣ,ʹ�����ʱ�̼���������Ϣ
			 if(SUCCEEDED(hr))
			 {
				 hr=m_cpRecoCtxt->SetNotifyWindowMessage(hwnd,WM_RECOEVENT,0,0);
			 }
			 else MessageBox(hwnd,TEXT("error2"),TEXT("error"),S_OK);
			 //�������Ǹ���Ȥ���¼�
			 if(SUCCEEDED(hr))
			 {
				 ULONGLONG ullMyEvents=SPFEI(SPEI_SOUND_START)|SPFEI(SPEI_RECOGNITION)|SPFEI(SPEI_SOUND_END);
				 hr=m_cpRecoCtxt->SetInterest(ullMyEvents,ullMyEvents);
			 }
			 else MessageBox(hwnd,TEXT("error3"),TEXT("error"),S_OK);
			 //�����﷨����
			 b_Cmd_Grammar=TRUE;
			 if(FAILED(hr))
			 {
				 MessageBox(hwnd,TEXT("error4"),TEXT("error"),S_OK);
			 }
			 hr=m_cpRecoCtxt->CreateGrammar(GID_CMD_GR,&m_cpCmdGramma);
			 WCHAR wszXMLFile[20]=L"er.xml";
			 MultiByteToWideChar(CP_ACP,0,(LPCSTR)"er.xml",-1,wszXMLFile,256);
			 hr=m_cpCmdGramma->LoadCmdFromFile(wszXMLFile,SPLO_DYNAMIC);
			 if(FAILED(hr))
			 {
				 MessageBox(hwnd,TEXT("error5"),TEXT("error"),S_OK);
			 }
			 b_initSR=TRUE;
			 //�ڿ�ʼʶ��ʱ�������﷨����ʶ��
		     hr=m_cpCmdGramma->SetRuleState(NULL,NULL,SPRS_ACTIVE);
	    	 return 0;
		 }
	 case WM_RECOEVENT:
		 {
			 RECT rect;
             GetClientRect(hwnd,&rect);
             hdc=GetDC(hwnd);
			 USES_CONVERSION;
			 CSpEvent event;
			 while(event.GetFrom(m_cpRecoCtxt)==S_OK)
			 {
			     switch(event.eEventId)
			     {
			     case SPEI_RECOGNITION:
    				 {
            			 static const WCHAR wszUnrecognized[]=L"<Unrecognized>";
		            	 CSpDynamicString dstrText;
			    		 //ȡ��ʶ����
				    	 if(FAILED(event.RecoResult()->GetText(SP_GETWHOLEPHRASE,SP_GETWHOLEPHRASE,TRUE,&dstrText,NULL)))
					     {
						     dstrText=wszUnrecognized;
    					 }
        	    		 BSTR SRout;
	        	    	 dstrText.CopyToBSTR(&SRout);
						 char* lpszText2 = _com_util::ConvertBSTRToString(SRout);

			    		 if(b_Cmd_Grammar)
				    	 {
							 if (strcmp("װ��",lpszText2)==0)
	    				     {    
								 keybd_event('3', scan_code('3'), 0, 0);//����
								 Sleep(10);
								 keybd_event('3', scan_code('3'), 2, 0);//�ɿ�
							
					         }
							 if (strcmp("����ɽ", lpszText2) == 0)
							 {
								 //ASD ASD + I
								 keybd_event('A', scan_code('A'), 0, 0);
								 Sleep(40);
								 keybd_event('A', scan_code('A'), 2, 0);
								 Sleep(40);
								 keybd_event('S', scan_code('S'), 0, 0);
								 Sleep(40);
								 keybd_event('S', scan_code('S'), 2, 0);
								 Sleep(40);
								 keybd_event('D', scan_code('D'), 0, 0);
								 Sleep(40);
								 keybd_event('D', scan_code('D'), 2, 0);
								 Sleep(40);
								 
								 keybd_event('A', scan_code('A'), 0, 0);
								 Sleep(40);
								 keybd_event('A', scan_code('A'), 2, 0);
								 Sleep(40);
								 keybd_event('S', scan_code('S'), 0, 0);
								 Sleep(40);
								 keybd_event('S', scan_code('S'), 2, 0);
								 Sleep(40);
								 keybd_event('D', scan_code('D'), 0, 0);
								 Sleep(40);
								 keybd_event('D', scan_code('D'), 2, 0);
								 Sleep(40);

								 keybd_event('I', scan_code('I'), 0, 0);
								 Sleep(40);
								 keybd_event('I', scan_code('I'), 2, 0);
								 Sleep(40);
							 }
							 if (strcmp("��ǰǰ", lpszText2) == 0)
							 {

								 keybd_event('S', 0, 0, 0);//����
								 keybd_event('S', 0, 2, 0);//�ɿ�
								 keybd_event('W', 0, 0, 0);//����
								 keybd_event('W', 0, 2, 0);//�ɿ�
								 keybd_event('W', 0, 0, 0);//����
								 keybd_event('W', 0, 2, 0);//�ɿ�

								 mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
								 mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								 ////MapVirtualKeyӳ��
								 //keybd_event(VK_RETURN, MapVirtualKey(VK_RETURN, 0), 0, 0);//����
								 //keybd_event(VK_RETURN, MapVirtualKey(VK_RETURN, 0), 2, 0);//�ɿ�

							 }
							 if (strcmp("����ǰ", lpszText2) == 0)
							 {


								 keybd_event('A', 0, 0, 0);//����
								 keybd_event('A', 0, 2, 0);//�ɿ�
								 keybd_event('D', 0, 0, 0);//����
								 keybd_event('D', 0, 2, 0);//�ɿ�
								 keybd_event('W', 0, 0, 0);//����
								 keybd_event('W', 0, 2, 0);//�ɿ�
								 mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
								 mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								 ////MapVirtualKeyӳ��
								 //keybd_event(VK_RETURN, MapVirtualKey(VK_RETURN, 0), 0, 0);//����
								 //keybd_event(VK_RETURN, MapVirtualKey(VK_RETURN, 0), 2, 0);//�ɿ�
							 }
							 if (strcmp("��ð����", lpszText2) == 0)
							 {
								 keybd_event(VK_OEM_102, 0, 0, 0);//����
								 keybd_event(VK_OEM_102, 0, 2, 0);//�ɿ�		 \ang
								 keybd_event('A', 0, 0, 0);//����
								 keybd_event('A', 0, 2, 0);//�ɿ�
								 keybd_event('N', 0, 0, 0);//����
								 keybd_event('N', 0, 2, 0);//�ɿ�
								 keybd_event('G', 0, 0, 0);//����
								 keybd_event('G', 0, 2, 0);//�ɿ�

								 //MapVirtualKeyӳ��
								 keybd_event(VK_RETURN, MapVirtualKey(VK_RETURN,0), 0, 0);//����
								 keybd_event(VK_RETURN, MapVirtualKey(VK_RETURN, 0), 2, 0);//�ɿ�

							 }
							 if (strcmp("���絶", lpszText2) == 0)
							 {

								 keybd_event('A', 0, 0, 0);//����
								 keybd_event('A', 0, 2, 0);//�ɿ�
								 keybd_event('D', 0, 0, 0);//����
								 keybd_event('D', 0, 2, 0);//�ɿ�
								 keybd_event('S', 0, 0, 0);//����
								 keybd_event('S', 0, 2, 0);//�ɿ�
								 mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
								 mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								 
							 }
							 if (strcmp("��ǹ", lpszText2) == 0)
							 {

								 keybd_event(VK_OEM_102, 0, 0, 0);//����
								 keybd_event(VK_OEM_102, 0, 2, 0);//�ɿ�		 \ang
								 keybd_event('W', 0, 0, 0);//����
								 keybd_event('W', 0, 2, 0);//�ɿ�
								 keybd_event('E', 0, 0, 0);//����
								 keybd_event('E', 0, 2, 0);//�ɿ�
								 keybd_event('A', 0, 0, 0);//����
								 keybd_event('A', 0, 2, 0);//�ɿ�
								 keybd_event('P', 0, 0, 0);//����
								 keybd_event('P', 0, 2, 0);//�ɿ�
								 keybd_event('O', 0, 0, 0);//����
								 keybd_event('O', 0, 2, 0);//�ɿ�
								 keybd_event('N', 0, 0, 0);//����
								 keybd_event('N', 0, 2, 0);//�ɿ�

								 keybd_event(VK_SPACE, 0, 0, 0);//����
								 keybd_event(VK_SPACE, 0, 2, 0);//�ɿ�

								 keybd_event(VK_NUMPAD7, 0, 0, 0);//����
								 keybd_event(VK_NUMPAD7, 0, 2, 0);//�ɿ�

								 //MapVirtualKeyӳ��
								 keybd_event(VK_RETURN, MapVirtualKey(VK_RETURN, 0), 0, 0);//����
								 keybd_event(VK_RETURN, MapVirtualKey(VK_RETURN, 0), 2, 0);//�ɿ�

							 }
							 if (strcmp("��", lpszText2) == 0)
							 {
								 keybd_event(VK_OEM_102, 0, 0, 0);//����
								 keybd_event(VK_OEM_102, 0, 2, 0);//�ɿ�		 \ang
								 keybd_event('W', 0, 0, 0);//����
								 keybd_event('W', 0, 2, 0);//�ɿ�
								 keybd_event('E', 0, 0, 0);//����
								 keybd_event('E', 0, 2, 0);//�ɿ�
								 keybd_event('A', 0, 0, 0);//����
								 keybd_event('A', 0, 2, 0);//�ɿ�
								 keybd_event('P', 0, 0, 0);//����
								 keybd_event('P', 0, 2, 0);//�ɿ�
								 keybd_event('O', 0, 0, 0);//����
								 keybd_event('O', 0, 2, 0);//�ɿ�
								 keybd_event('N', 0, 0, 0);//����
								 keybd_event('N', 0, 2, 0);//�ɿ�

								 keybd_event(VK_SPACE, 0, 0, 0);//����
								 keybd_event(VK_SPACE, 0, 2, 0);//�ɿ�

								 keybd_event(VK_NUMPAD6, 0, 0, 0);//����
								 keybd_event(VK_NUMPAD6, 0, 2, 0);//�ɿ�

								 //MapVirtualKeyӳ��
								 keybd_event(VK_RETURN, MapVirtualKey(VK_RETURN, 0), 0, 0);//����
								 keybd_event(VK_RETURN, MapVirtualKey(VK_RETURN, 0), 2, 0);//�ɿ�
							 }
							 if (strcmp("����", lpszText2) == 0)
							 {
								 keybd_event(VK_OEM_102, 0, 0, 0);//����
								 keybd_event(VK_OEM_102, 0, 2, 0);//�ɿ�		 \ang
								 keybd_event('W', 0, 0, 0);//����
								 keybd_event('W', 0, 2, 0);//�ɿ�
								 keybd_event('E', 0, 0, 0);//����
								 keybd_event('E', 0, 2, 0);//�ɿ�
								 keybd_event('A', 0, 0, 0);//����
								 keybd_event('A', 0, 2, 0);//�ɿ�
								 keybd_event('P', 0, 0, 0);//����
								 keybd_event('P', 0, 2, 0);//�ɿ�
								 keybd_event('O', 0, 0, 0);//����
								 keybd_event('O', 0, 2, 0);//�ɿ�
								 keybd_event('N', 0, 0, 0);//����
								 keybd_event('N', 0, 2, 0);//�ɿ�

								 keybd_event(VK_SPACE, 0, 0, 0);//����
								 keybd_event(VK_SPACE, 0, 2, 0);//�ɿ�

								 keybd_event(VK_NUMPAD4, 0, 0, 0);//����
								 keybd_event(VK_NUMPAD4, 0, 2, 0);//�ɿ�

								 //MapVirtualKeyӳ��
								 keybd_event(VK_RETURN, MapVirtualKey(VK_RETURN, 0), 0, 0);//����
								 keybd_event(VK_RETURN, MapVirtualKey(VK_RETURN, 0), 2, 0);//�ɿ�
							 }
							 if (strcmp("��", lpszText2) == 0)
							 {
								 keybd_event(VK_OEM_102, 0, 0, 0);//����
								 keybd_event(VK_OEM_102, 0, 2, 0);//�ɿ�		 \ang
								 keybd_event('W', 0, 0, 0);//����
								 keybd_event('W', 0, 2, 0);//�ɿ�
								 keybd_event('E', 0, 0, 0);//����
								 keybd_event('E', 0, 2, 0);//�ɿ�
								 keybd_event('A', 0, 0, 0);//����
								 keybd_event('A', 0, 2, 0);//�ɿ�
								 keybd_event('P', 0, 0, 0);//����
								 keybd_event('P', 0, 2, 0);//�ɿ�
								 keybd_event('O', 0, 0, 0);//����
								 keybd_event('O', 0, 2, 0);//�ɿ�
								 keybd_event('N', 0, 0, 0);//����
								 keybd_event('N', 0, 2, 0);//�ɿ�

								 keybd_event(VK_SPACE, 0, 0, 0);//����
								 keybd_event(VK_SPACE, 0, 2, 0);//�ɿ�

								 keybd_event(VK_NUMPAD1, 0, 0, 0);//����
								 keybd_event(VK_NUMPAD1, 0, 2, 0);//�ɿ�
								 keybd_event(VK_NUMPAD5, 0, 0, 0);//����
								 keybd_event(VK_NUMPAD5, 0, 2, 0);//�ɿ�

								 //MapVirtualKeyӳ��
								 keybd_event(VK_RETURN, MapVirtualKey(VK_RETURN, 0), 0, 0);//����
								 keybd_event(VK_RETURN, MapVirtualKey(VK_RETURN, 0), 2, 0);//�ɿ�
							 }
							 if (strcmp("��", lpszText2) == 0)
							 {
								 keybd_event(VK_OEM_102, 0, 0, 0);//����
								 keybd_event(VK_OEM_102, 0, 2, 0);//�ɿ�		 \ang
								 keybd_event('W', 0, 0, 0);//����
								 keybd_event('W', 0, 2, 0);//�ɿ�
								 keybd_event('E', 0, 0, 0);//����
								 keybd_event('E', 0, 2, 0);//�ɿ�
								 keybd_event('A', 0, 0, 0);//����
								 keybd_event('A', 0, 2, 0);//�ɿ�
								 keybd_event('P', 0, 0, 0);//����
								 keybd_event('P', 0, 2, 0);//�ɿ�
								 keybd_event('O', 0, 0, 0);//����
								 keybd_event('O', 0, 2, 0);//�ɿ�
								 keybd_event('N', 0, 0, 0);//����
								 keybd_event('N', 0, 2, 0);//�ɿ�

								 keybd_event(VK_SPACE, 0, 0, 0);//����
								 keybd_event(VK_SPACE, 0, 2, 0);//�ɿ�

								 keybd_event(VK_NUMPAD1, 0, 0, 0);//����
								 keybd_event(VK_NUMPAD1, 0, 2, 0);//�ɿ�
								 keybd_event(VK_NUMPAD8, 0, 0, 0);//����
								 keybd_event(VK_NUMPAD8, 0, 2, 0);//�ɿ�

								 //MapVirtualKeyӳ��
								 keybd_event(VK_RETURN, MapVirtualKey(VK_RETURN, 0), 0, 0);//����
								 keybd_event(VK_RETURN, MapVirtualKey(VK_RETURN, 0), 2, 0);//�ɿ�

							 }
						
    					 }    
        			 }
	    		 }
			 }
			 return TRUE;
		 }
	 case WM_PAINT:
		 hdc=BeginPaint(hwnd,&ps);
		 EndPaint(hwnd,&ps);
		 return 0;
	 case WM_DESTROY:
		 system("taskkill /f /im ��������ɽ.exe");
		 PostQuitMessage(0);
		 return 0;
	 }
	 return DefWindowProc(hwnd,message,wParam,lParam);
 }

 BYTE scan_code(DWORD pKey)
 {
	 const DWORD result = MapVirtualKey(pKey, 0);
	 return (BYTE)(result);
 }

#pragma comment(lib, "ole32.lib") //CoInitialize CoCreateInstance��Ҫ����ole32.dll   
int speak(wchar_t *str)
{
	 ISpVoice * pVoice = NULL;
	 ::CoInitialize(NULL);
	 //��ȡISpVoice�ӿڣ�   
	 long hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
	 hr = pVoice->Speak(str, 0, NULL);
	 pVoice->Release();
	 pVoice = NULL;
	 //ǧ��Ҫ���ǣ�   
	 ::CoUninitialize();
	 return TRUE;
 }
