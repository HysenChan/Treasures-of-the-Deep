#include "Game.h"
CSpritesManager *CSpritesManager::instance = NULL;
CResourcesPool *CResourcesPool::instance = NULL;
TextSpriteManager *TextSpriteManager::instance=NULL;
CGame::CGame(HINSTANCE hInstance,HWND hWnd,int nFps)
{
	pRenderTarget = NULL;
	pWICFactory = NULL;
	this->nFps = nFps;
	this->hWnd = hWnd;
	this->hInstance = hInstance;
	if (nFps > 0)
	{
		nFixedDeltaTime = 1000 / nFps;
	}
	else
	{
		nFixedDeltaTime = 0;
	}


	Init(hWnd);
	
	pInput = new CInput();						//创建封装DirectInput的对象
	pInput->CreateInput(hInstance,hWnd);

	t=0;
	nFrames = 0;

	t0 = GetTickCount();


}

CGame::~CGame(void)												//在析构函数中释放资源
{

	Cleanup();

}


HRESULT CGame::CreateDeviceIndependentResources()
{
	static const WCHAR msc_fontName[] = L"Comic Sans MS";
	static const FLOAT msc_fontSize = 18;

	// Create a Direct2D factory.

	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);


	if (SUCCEEDED(hr))
	{
		// Create WIC factory.
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&pWICFactory)
			);
	}

	if (SUCCEEDED(hr))
	{

		// Create a DirectWrite factory.
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(pDWriteFactory),
			reinterpret_cast<IUnknown **>(&pDWriteFactory)
			);
	}
	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = pDWriteFactory->CreateTextFormat(
			L"Comic Sans MS",
			NULL,
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"", //locale
			&pTextFormat
			);
	}
	if (SUCCEEDED(hr))
	{
		// Center the text horizontally and vertically.
		pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

		pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	}

	return hr;
}

HRESULT CGame::CreateDeviceResources()
{
	HRESULT hr = !S_OK;

	if (!pRenderTarget)
	{

		D2D1_SIZE_U size = D2D1::SizeU(
			rectClient.right - rectClient.left,
			rectClient.bottom - rectClient.top
			);

		// Create a Direct2D render target.
		hr = pD2DFactory->CreateHwndRenderTarget(			
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&pRenderTarget
			);
		if (FAILED(hr))
		{
			return hr;
		}
		hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White),&pTextBrush);


	}
	return hr;
}

HRESULT CGame::Init(HWND hWnd)
{

	GetClientRect(hWnd,&rectClient);					//得到屏幕绘图区域矩形
	HRESULT hr = CreateDeviceIndependentResources();	//创建设备无关资源
	if (SUCCEEDED(hr))
	{
		hr = CreateDeviceResources();					//创建设备相关资源
	}
	CResourcesPool::GetInstance()->init(pWICFactory,pRenderTarget);
	CSpritesManager::GetInstance()->SetRenderTarget(pRenderTarget);
	TextSpriteManager::GetInstance()->init(pRenderTarget,pDWriteFactory);
	return hr;
}



//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
void CGame::Cleanup()
{
	if(CResourcesPool::GetInstance())
	{
		delete CResourcesPool::GetInstance();
	}
	if (CSpritesManager::GetInstance())
	{
		delete CSpritesManager::GetInstance();
	}
	if(pInput)
	{
		delete pInput;
	}
	if (TextSpriteManager::GetInstance())
	{
		delete TextSpriteManager::GetInstance();
	}
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
void CGame::Render()
{
	if( NULL == pRenderTarget )
		return;


	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(D2D1::ColorF(0x0,1.0f));

	pSpritesManager = CSpritesManager::GetInstance();
	pTextSpriteManager=TextSpriteManager::GetInstance();

	if (pSpritesManager)
	{
		pSpritesManager->Render();
	}
	if (pTextSpriteManager)
	{
		pTextSpriteManager->Render();
	}
	if (pRenderTarget==NULL)
	{
		pRenderTarget->EndDraw();
		return;
	}
	if (t > 0)
	{
		int nfps =  nFrames / t;
		wsprintf(szBuf,TEXT("%d"),nfps);
		D2D1_RECT_F rect = {0,0,50,20};
		pRenderTarget->DrawText(
			szBuf,           // Text to render
			wcslen(szBuf),       // Text length
			pTextFormat,     // Text format
			rect,    // The region of the window where the text will be rendered
			pTextBrush      // The brush used to draw the text
			);

	}

	
	pRenderTarget->EndDraw();


}
void CGame::GameFunc()
{
	DWORD dt = 0;

	do 
	{ 
		dt=GetTickCount() - t0; 
	} while(dt < 1);									//保证最小间隔时间大于等于1毫秒
	if (dt >= nFixedDeltaTime)							//如果大于固定的间隔时间
	{

		t0 = GetTickCount();								//记录本帧调用的时刻



		Update(dt / 1000.0);							//调用帧函数更新
		t += dt / 1000.0;
		Render();										//渲染
		if (t > 1)
		{
			t = 0;
			nFrames = 0;
		}
		nFrames++;
	}
	else
	{
		Sleep(1);										//否则休眠1毫秒
	}
	

}
void CGame::Update(float fDeltaTime)
{

	CSpritesManager::GetInstance()->Update(fDeltaTime);					//帧函数，根据系统流逝的时间更新链表里的精灵，可以在子类重载，写游戏规则

}
