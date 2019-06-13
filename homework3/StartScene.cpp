#include "StartScene.h"

CStartScene::CStartScene(RECT &rectClient)
{
	this->rectClient = rectClient;
	InitStartScene();
}

CStartScene::~CStartScene(void)
{
}

void CStartScene::InitStartScene()
{
	int left = rectClient.left;
	int top = rectClient.top;

	CSpritesManager *pSpritesManager = CSpritesManager::GetInstance();
	//创建开始界面背景
	pBg = pSpritesManager->CreateSprite(L"StartBg",D2D1::Point2F(0,0));
	//创建第开始游戏UI
	CSprite *pStartUp = pSpritesManager->CreateSprite(L"GameUI",D2D1::Point2F(0,0),170,75,10,25);
	CSprite *pStartDown= pSpritesManager->CreateSprite(L"GameUI",D2D1::Point2F(0,0),170,75,10,25);
	pStartDown->SetScaleFactor(1.05f,1.05f);
	pButtons[0] = new CSpriteButton(Start,D2D1::Point2F(left + 290,top + 420),pStartUp,pStartDown);	
	//创建游戏说明UI
	CSprite *pExplainUp = pSpritesManager->CreateSprite(L"GameUI",D2D1::Point2F(0,0),175,75,20,160);
	CSprite *pExplainDown= pSpritesManager->CreateSprite(L"GameUI",D2D1::Point2F(0,0),175,75,20,160);
	pExplainDown->SetScaleFactor(1.05f,1.05f);
	pButtons[1] = new CSpriteButton(Explain,D2D1::Point2F(left + 550,top + 420),pExplainUp,pExplainDown);
	//创建游戏结束UI
	CSprite *pCloseUp = pSpritesManager->CreateSprite(L"GameUI",D2D1::Point2F(0,0),170,75,18,420);
	CSprite *pCloseDown = pSpritesManager->CreateSprite(L"GameUI",D2D1::Point2F(0,0),170,75,18,420);
	pCloseDown->SetScaleFactor(1.05f,1.05f);
	pButtons[2] = new CSpriteButton(Close,D2D1::Point2F(left + 420,top + 520),pCloseUp,pCloseDown);
}

bool CStartScene::HandleMouseUp(WPARAM wParam,LPARAM lParam)
{
	bool bRet = false;
	for(int i=0;i<3;i++)
	{
		if (pButtons[i]->HandleMouseUp(wParam,lParam))
		{
			bRet = true;
			if (pButtons[i]->btnState == BtnUp)
			{
				buttonState=i;
				break;
			}
		}
	}
	return bRet;
}

bool CStartScene::HandleMouseDown(WPARAM wParam,LPARAM lParam)
{
	bool bRet = false;
	for(int i=0;i<3;i++)
	{
		if (pButtons[i]->HandleMouseDown(wParam,lParam))
		{
			bRet = true;
		}
	}
	return bRet;
}

void CStartScene::Reset()
{
	for(int i=0;i<3;i++)
	{
		pButtons[i]->Reset();
	}
	pBg->SetVisible(true);
}

void CStartScene::SetVisible(bool bVal)
{
	for(int i=0;i<3;i++)
	{
		pButtons[i]->SetVisible(bVal);
	}
	pBg->SetVisible(bVal);
}

bool CStartScene::IsVisible()
{
	return bVisible;
}
int CStartScene::GetButtonState()
{
	return buttonState;
}