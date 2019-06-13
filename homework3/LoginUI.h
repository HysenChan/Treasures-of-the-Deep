#pragma once
#include <windows.h>
#include "Framework\SpritesManager.h"
#include "Framework\ResourcesPool.h"
#include "Framework\Game.h"
#include "Framework\TextSpriteManager.h"
#include "Framework\SpriteButton.h"

#include "GlobalData.h"
const int IDC_LOGINUI_LABEL = 1;
const int IDB_EDIT_NAME = 2;
const int IDB_EDIT_PWD = 3;
const int IDB_BUTTON_LOGIN = 4;


class LoginUI
{
private:
	CSprite *loginUIBg;
	TextSprite *textTitle;
	TextSprite *textName;
	TextSprite *textPwd;

	HINSTANCE hInstance;
	HWND hWnd;


public:
	CSpriteButton *btnLogin;
	HWND hName;
	HWND hPwd;
	LoginUI(HINSTANCE hInstance, HWND hWnd);
	~LoginUI();
	void Init();


};

