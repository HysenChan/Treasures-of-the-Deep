#include "ExplainScene.h"


CExplainScene::CExplainScene(RECT &rectClient)
{
	this->rectClient=rectClient;
	InitExplainScene();
}


CExplainScene::~CExplainScene(void)
{
}

void CExplainScene::InitExplainScene()
{
	int left = rectClient.left;
	int top = rectClient.top;

	CSpritesManager *pSpritesManager = CSpritesManager::GetInstance();

	pBg=pSpritesManager->CreateSprite(L"ExplainBg",D2D1::Point2F(0,0));

	CSprite *pReturnUp = pSpritesManager->CreateSprite(L"GameUI",D2D1::Point2F(0,0),85,85,718,154);
	CSprite *pReturnDown= pSpritesManager->CreateSprite(L"GameUI",D2D1::Point2F(0,0),85,85,718,154);
	pReturnUp->SetScaleFactor(0.7f,0.7f);
	pReturnDown->SetScaleFactor(0.8f,0.8f);
	pButtons[0] = new CSpriteButton(ReturnStartScene,D2D1::Point2F(left + 10,top + 10),pReturnUp,pReturnDown);	
}

bool CExplainScene::HandleMouseUp(WPARAM wParam,LPARAM lParam)
{
	bool bRet = false;
	for(int i=0;i<1;i++)
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
bool CExplainScene::HandleMouseDown(WPARAM wParam,LPARAM lParam)
{
	bool bRet = false;
	for(int i=0;i<1;i++)
	{
		if (pButtons[i]->HandleMouseDown(wParam,lParam))
		{
			bRet = true;
		}
	}
	return bRet;
}
void CExplainScene::Reset()
{
	for(int i=0;i<1;i++)
	{
		pButtons[i]->Reset();
	}
	pBg->SetVisible(true);
}

void CExplainScene::SetVisible(bool bVal)
{
	for(int i=0;i<1;i++)
	{
		pButtons[i]->SetVisible(bVal);
	}
	pBg->SetVisible(bVal);
}
bool CExplainScene::IsVisible()
{
	return bVisible;
}
int CExplainScene::GetButtonState()
{
	return buttonState;
}