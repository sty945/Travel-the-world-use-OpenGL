// OpenGLsty.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "OpenGL.h"
//////////////////////////////////////////////////////////
OpenGL* m_OpenGL;
HDC		hDC;		// GDI�豸���,���������ӵ� GDI( ͼ���豸�ӿ�)
HGLRC	hRC=NULL;	// ��Ⱦ�������,��OpenGL�������ӵ��豸������ 
HWND	hWnd=NULL;	// ���� Windows ���������Ĵ��ھ��
int		Width = 800;// ���ڿ�
int		Height= 600;// ���ڸ�
int		bits  = 16;	// ��ɫ���

void GameLoop()
{   
	MSG msg; 
	BOOL fMessage;
	PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);
	while(msg.message != WM_QUIT)	// ��Ϣѭ��
	{   
		fMessage = PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE);
		if(fMessage)				//����Ϣ
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
			m_OpenGL->Render();	//����Ϣ
	}
}
LRESULT WINAPI MsgProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam )// ��Ϣ����
{	
	switch(message)
	{
	case WM_CREATE:						// ��������
		hDC = GetDC(hWnd);				// ��ȡ��ǰ���ڵ��豸���
		m_OpenGL->SetupPixelFormat(hDC);// ������ʾģʽ��װ����
		return 0;		break;
	case WM_CLOSE:						// �رմ���
		m_OpenGL->CleanUp();			// ��������
		PostQuitMessage(0);
		return 0;		break;
	case WM_SIZE:						// ���ڳߴ�仯
		Height = HIWORD(lParam);		// ���ڵĸ�
		Width  = LOWORD(lParam);		// ���ڵĿ�
		if (Height==0)	Height=1;		// ��ֹ��0 ��
		m_OpenGL->init(Width,Height);
		return 0;		break;
	case WM_DESTROY:					// �˳���Ϣ
		PostQuitMessage(0);
		return 0;		break;
	case WM_KEYUP:						// ��ESC�˳���ȫ��ģʽ����Ҫ������˳���ʽ��
		switch (wParam)
		{ 
		case VK_ESCAPE:
			m_OpenGL->CleanUp();	// ��������
			PostQuitMessage(0);
			return 0;break;
		} 
		default:			break;
	}
	return (DefWindowProc(hWnd, message, wParam, lParam));
}

INT WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,INT )// WinMain�������
{   // ע�ᴰ����
	bool fullScreen =TRUE;
	DWORD	dwExStyle;		// Window ��չ���
	DWORD	dwStyle;		// Window ���ڷ��
	RECT	windowRect;		// ���ڳߴ�
	int		nX=0,nY=0;
	dwExStyle=WS_EX_APPWINDOW|WS_EX_WINDOWEDGE;	// ʹ���ھ���3D���
	dwStyle=WS_OVERLAPPEDWINDOW;				// ʹ�ñ�׼����
	//WS_OVERLAPPEDWINDOW���б�����,���ڲ˵�,���С����ť�Ϳɵ����ߴ�Ĵ���
	int wid=GetSystemMetrics(SM_CXSCREEN);		// ��ȡ��ǰ��Ļ��
	int hei=GetSystemMetrics(SM_CYSCREEN);		// ��ȡ��ǰ��Ļ��
	nX=(wid-Width)/2;nY=(hei-Height)/2;			// ���㴰�ھ�����
	//-------------------------------------------------------------------
	AdjustWindowRectEx(&windowRect,dwStyle,FALSE,dwExStyle);
	//���ݴ��ڷ�����������ڳߴ�ﵽҪ��Ĵ�С
	char cc[]="tml";
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, 
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		cc, NULL };
    RegisterClassEx( &wc );
	m_OpenGL=new OpenGL();//
	hWnd = CreateWindowEx(NULL,cc,"sty�ĳ���",
						  dwStyle|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
						  nX, nY,Width, Height,
						  NULL,NULL,hInst,NULL);	// ��������
	ShowWindow( hWnd, SW_SHOWDEFAULT );				// ��ʾ����
	UpdateWindow( hWnd );							// ˢ�´���
	GameLoop();										// ������Ϣѭ��
    return 0;
}

