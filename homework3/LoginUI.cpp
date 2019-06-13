#include "LoginUI.h"

GlobalData *GlobalData::instance = NULL;
//TextSpriteManager *TextSpriteManager::instance=NULL;
LoginUI::LoginUI( HINSTANCE hInstance, HWND hWnd)
{
	this->hInstance = hInstance;
	this->hWnd = hWnd;

	Init();
}


LoginUI::~LoginUI()
{

	TextSpriteManager::GetInstance()->DeleteTextSprite(textTitle);
	TextSpriteManager::GetInstance()->DeleteTextSprite(textName);
	TextSpriteManager::GetInstance()->DeleteTextSprite(textPwd);
	CSpritesManager::GetInstance()->DeleteSprite(loginUIBg);
	DestroyWindow(hName);
	DestroyWindow(hPwd);
	delete(btnLogin);

}



void LoginUI::Init()
{
	CResourcesPool::GetInstance()->AddTexture(L"loginUIBg", L"RES/LoginBg.png");
	CResourcesPool::GetInstance()->AddTexture(L"game_ui", L"RES/game_ui.png");
	loginUIBg = CSpritesManager::GetInstance()->CreateSprite(L"loginUIBg", D2D1::Point2F(0, 0));

	textTitle = TextSpriteManager::GetInstance()->CreateTextSprite(L"登录", D2D1::RectF(450, 250, 680, 300), D2D1::ColorF::Yellow, 58);

	textName = TextSpriteManager::GetInstance()->CreateTextSprite(L"用户名:", D2D1::RectF(320, 375, 530, 470), D2D1::ColorF::White, 30);
	textPwd = TextSpriteManager::GetInstance()->CreateTextSprite(L"密  码:", D2D1::RectF(320, 435, 530, 530), D2D1::ColorF::White, 30);
	//创建文本框子窗口

	hName = CreateWindow(TEXT("EDIT"), NULL,
		 WS_CHILD | WS_VISIBLE | WS_BORDER
		| ES_MULTILINE | ES_LEFT,
		430, 385, 200, 25, hWnd, (HMENU)IDB_EDIT_NAME,
		hInstance, NULL);

	hPwd = CreateWindow(TEXT("EDIT"), NULL,
		WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE | WS_BORDER
		| ES_MULTILINE | ES_LEFT,
		430, 445, 200, 25, hWnd, (HMENU)IDB_EDIT_PWD,
		hInstance, NULL);
	CSprite *pLoginUp = CSpritesManager::GetInstance()->CreateSprite(L"game_ui", D2D1::Point2F(0, 0), 150, 50, 0, 0);
	CSprite *pLoginDown = CSpritesManager::GetInstance()->CreateSprite(L"game_ui", D2D1::Point2F(0, 0), 150, 50, 150, 0);

	btnLogin = new CSpriteButton(1, D2D1::Point2F(445, 550), pLoginUp, pLoginDown);
}

