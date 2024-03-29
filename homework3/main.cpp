

#include <windows.h>
#include "Net/TCPClient.h"
#include "DemoGame.h"
HWND		hWnd ;


LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;	


CDemoGame		*pGame = NULL;
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT ("Demo") ;
	MSG			msg ;
	WNDCLASS	wc ;
	wc.style			= CS_HREDRAW | CS_VREDRAW ;
	wc.lpfnWndProc		= WndProc ;
	wc.cbClsExtra		= 0 ;
	wc.cbWndExtra		= 0 ;
	wc.hInstance		= hInstance ;
	wc.hIcon			= LoadIcon (NULL, IDI_APPLICATION) ;
	wc.hCursor			= LoadCursor (NULL, IDC_ARROW) ;
	wc.hbrBackground	= (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wc.lpszMenuName		= NULL ;
	wc.lpszClassName	= szAppName ;

	if (!RegisterClass (&wc))
	{
		MessageBox (	NULL, TEXT ("This program requires Windows NT!"), 
			szAppName, MB_ICONERROR) ;
		return 0 ;
	}
	hWnd = CreateWindow(szAppName,	// window class name
		TEXT("The Demo Game"),	// window caption
		WS_OVERLAPPEDWINDOW^WS_THICKFRAME |WS_SYSMENU|WS_CLIPCHILDREN,	// window style
		//WS_POPUP | WS_VISIBLE,
		0,	// initial x position
		0,	// initial y position
		1250,	// initial x size
		730,	// initial y size
		NULL,			// parent window handle
		NULL,	        // window menu handle
		hInstance,	    // program instance handle
		NULL) ; 	    // creation parameters

	ShowWindow (hWnd, SW_SHOW) ;
	UpdateWindow (hWnd) ;

	
	if (SUCCEEDED(CoInitialize(NULL)))				//如果初始化Com组件成功
	{
		pGame = new  CDemoGame(hInstance,hWnd,60);
		pGame->InitGame();
		//if (SUCCEEDED(init()))						//初始化
		{
			BOOL  bMessage;
			PeekMessage(&msg, NULL, 0, 0,PM_NOREMOVE);
			while(msg.message != WM_QUIT)			//进入消息循环
			{
				bMessage = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
				if(bMessage)
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				//Render();							//渲染
				pGame->GameFunc();
			} 
		}
		
		if (pGame)
		{
			delete pGame;
		}
		CoUninitialize();							//释放Com组件

	}

	return 0 ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC			hdc ;
	PAINTSTRUCT ps ;
	RECT		rect ;
	int wmId, wmEvent;

	switch (message)
	{
	case WM_SOCKET:
		pGame->WndProc(hwnd,message,wParam,lParam);

		break;
	case WM_CREATE: 

		break;
	case WM_KEYUP:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0) ;
		}	
		return 0;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		switch (wmId)
		{
		default:
			pGame->OnCommand(wmId);
		}
		break;
	case WM_LBUTTONUP:												//拦截WM_KEYDWON
			pGame->HandleMouseUp(wParam,lParam);						//调用HandleKeyDown函数处理键盘消息
			return 0;
	case WM_LBUTTONDOWN:
		pGame->HandleMouseDown(wParam,lParam);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0) ;
		return 0 ;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}
