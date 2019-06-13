#include "DemoGame.h"
#include <time.h>

CDemoGame::CDemoGame(HINSTANCE hInstance,HWND hWnd,int nFPS )
	:CGame(hInstance,hWnd,nFPS)
{
	pStartScene = 0;
	pGameScene = 0;
	pExplainScene = 0;
}

CDemoGame::~CDemoGame(void)
{
	if(pStartScene)
	{
		delete pStartScene;
	}
	if(pGameScene)
	{
		delete pGameScene;
	}
	if(pExplainScene)
	{
		delete pExplainScene;
	}
}

void CDemoGame::InitGame()
{
	//初始化随机数种子
	srand(time(NULL));
	//加载纹理
	CResourcesPool::GetInstance()->AddTexture(L"Objects",L"RES/Objects.png");
	CResourcesPool::GetInstance()->AddTexture(L"StartBg",L"RES/StartBg.png");
	CResourcesPool::GetInstance()->AddTexture(L"EntranceBg",L"RES/EntranceBg.png");
	CResourcesPool::GetInstance()->AddTexture(L"EntranceBg2",L"RES/EntranceBg2.png");
	CResourcesPool::GetInstance()->AddTexture(L"ExplainBg",L"RES/ExplainBg.png");		
	CResourcesPool::GetInstance()->AddTexture(L"OverBg",L"RES/OverBg.png");				
	CResourcesPool::GetInstance()->AddTexture(L"GameScene1Bg",L"RES/GameScene1Bg.png");
	CResourcesPool::GetInstance()->AddTexture(L"GameScene2Bg",L"RES/GameScene2Bg.png");
	CResourcesPool::GetInstance()->AddTexture(L"GameScene3Bg",L"RES/GameScene3Bg.png");
	CResourcesPool::GetInstance()->AddTexture(L"GameScene4Bg",L"RES/GameScene4Bg.png");
	CResourcesPool::GetInstance()->AddTexture(L"GameScene5Bg",L"RES/GameScene5Bg.png");
	CResourcesPool::GetInstance()->AddTexture(L"GameScene6Bg",L"RES/GameScene6Bg.png");
	CResourcesPool::GetInstance()->AddTexture(L"StoryBg1",L"RES/StoryBg1.png");
	CResourcesPool::GetInstance()->AddTexture(L"StoryBg2",L"RES/StoryBg2.png");
	CResourcesPool::GetInstance()->AddTexture(L"StoryBg3",L"RES/StoryBg3.png");
	CResourcesPool::GetInstance()->AddTexture(L"GameUI",L"RES/GameUI.png");
	CResourcesPool::GetInstance()->AddTexture(L"HeroWalker",L"RES/HeroWalker.png");
	CResourcesPool::GetInstance()->AddTexture(L"HeroSwim",L"RES/HeroSwim.png");
	CResourcesPool::GetInstance()->AddTexture(L"Monster",L"RES/Monster.png");
	CResourcesPool::GetInstance()->AddTexture(L"Collide",L"RES/Collide.png");
	CResourcesPool::GetInstance()->AddTexture(L"Material",L"RES/Material.png");
	CResourcesPool::GetInstance()->AddTexture(L"Material2",L"RES/Material2.png");
	CResourcesPool::GetInstance()->AddTexture(L"Gs5Material",L"RES/Gs5Material.png");
	CResourcesPool::GetInstance()->AddTexture(L"Corpse",L"RES/Corpse.png");
	CResourcesPool::GetInstance()->AddTexture(L"Text",L"RES/Text.png");
	CResourcesPool::GetInstance()->AddTexture(L"game_background", L"RES/game_ui.png");


	pLoginUI=new LoginUI(hInstance,this->hWnd);
	ZeroMemory(bigchar,1024*16*2);
	//初始化游戏状态为游戏主界面状态
	/*gameState = GameStart;*/
}

void CDemoGame::HandleMouseDown(WPARAM wParam,LPARAM lParam)
{
	if (pLoginUI)
	{
		pLoginUI->btnLogin->HandleMouseDown(wParam, lParam);
	}
	if(pStartScene&&pStartScene->IsVisible())
	{
		pStartScene->HandleMouseDown(wParam,lParam);
	}
	if(pExplainScene&&pExplainScene->IsVisible())
	{
		pExplainScene->HandleMouseDown(wParam,lParam);
	}
	/*if(pGameScene)
	{
		pGameScene->HandleMouseDown(wParam,lParam);
	}*/
}

void CDemoGame::HandleMouseUp(WPARAM wParam,LPARAM lParam)
{
	if (pLoginUI)
	{
		if (pLoginUI->btnLogin->HandleMouseUp(wParam, lParam))
		{
			if (pLoginUI->btnLogin->btnState == BtnUp)
			{
				WCHAR tmp[200];
				GlobalData *globalData = GlobalData::GetInstance();
				GetWindowText(pLoginUI->hName, tmp, 200);
				wcscpy(globalData->username, tmp);
				GetWindowText(pLoginUI->hPwd, tmp, 200);
				wcscpy(globalData->password, tmp);
				InitSocket(hWnd);
				ConnectServer("127.0.0.1", 8000);
			}
			gameState=Game_START;
			///islogin = true;
		}
	}
	//游戏主界面鼠标按键抬起操作
	if(gameState == Game_START)
	{
		if(pStartScene&&pStartScene->IsVisible()&&pStartScene->HandleMouseUp(wParam,lParam))
		{
			if(pStartScene->GetButtonState()==0)
			{
				pStartScene->SetVisible(false);
				if(pGameScene == NULL)
				{
					pGameScene = new CGameScene(CGame::rectClient);
				}
				gameState = GameRun;
			}
			if (pStartScene->GetButtonState()==1)
			{
				pStartScene->SetVisible(false);
				if (pExplainScene==NULL)
				{
					pExplainScene=new CExplainScene(CGame::rectClient);
				}
				else if(pExplainScene)
				{
					pExplainScene->Reset();
				}
				gameState=GameExplain;
			}
			if (pStartScene->GetButtonState()==2)
			{
				pStartScene->SetVisible(false);
				gameState=GameClose;
			}
		}
	}
	//游戏界面中鼠标按键抬起时的操作
	else if(gameState==GameExplain)
	{
		if(pExplainScene&&pExplainScene->IsVisible()&&pExplainScene->HandleMouseUp(wParam,lParam))
		{
			if(pExplainScene->GetButtonState()==0)
			{
				pExplainScene->SetVisible(false);
				pStartScene->Reset();
				gameState=Game_START;
			}
		}	
	}
	else if(gameState==GameRun)
	{
		if(pGameScene&&pGameScene->HandleMouseUp(wParam,lParam))
		{
			if(pGameScene->GetButtonState()==0)
			{
				pGameScene->setButtonVisible(true);
			}
			if(pGameScene->GetButtonState()==1)
			{
				pGameScene->setButtonVisible(false);
			}
			if(pGameScene->GetButtonState()==2)
			{
				gameState=GameClose;
			}
			if(pGameScene->GetButtonState()==3)
			{
				pGameScene->setOverVisible(false);
				pGameScene = new CGameScene(CGame::rectClient);
			}
		}
	}
}

void CDemoGame::InitUI()
{
	pGameBackGround = CSpritesManager::GetInstance()->CreateSprite(TEXT("game_background"), D2D1::Point2F(0, 0), 1000, 680, 0, 0);
	//创建文本框子窗口
	//hEdit = CreateWindow(TEXT("EDIT"), NULL,
	//	WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE | WS_BORDER
	//	| ES_MULTILINE | ES_LEFT,
	//	680, 475, 160, 24, hWnd, (HMENU)IDB_EDIT,
	//	hInstance, NULL);

	////创建发送按钮子窗口
	//hBtnGameSend = CreateWindow(TEXT("BUTTON"),
	//	TEXT("发送猜的数字"),
	//	WS_CLIPSIBLINGS | BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
	//	850, 475, 100, 24, hWnd,
	//	(HMENU)IDB_BTNGAMESEND,
	//	hInstance,
	//	NULL);
	hChat = CreateWindow(TEXT("EDIT"), NULL, WS_CLIPSIBLINGS | WS_CHILD |
		WS_VISIBLE | ES_MULTILINE | WS_BORDER | ES_READONLY | ES_AUTOVSCROLL | WS_VSCROLL,
		1005, 40, 235, 660, hWnd, (HMENU)IDB_EDIT, hInstance, NULL);
	//ShowWindow(hChat, SW_NORMAL);
	//创建由列表框和静态控件组成的组合框
	hComBoxInput = CreateWindow(TEXT("COMBOBOX"), NULL,
		WS_CLIPSIBLINGS | CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | CBS_AUTOHSCROLL,
		1005, 10, 185, 400, hWnd, (HMENU)IDB_COMBOXINPUT, hInstance, NULL);
	//创建发送按钮子窗口
	hBtnChat = CreateWindow(TEXT("BUTTON"),
		TEXT("发送"),
		WS_CLIPSIBLINGS | BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		1195, 10, 45, 24, hWnd,
		(HMENU)IDB_BTNCHAT,
		hInstance,
		NULL);

	for (int i = 0; i < 5; i++)
	{
		SendMessage(hComBoxInput, CB_ADDSTRING, 0, (LPARAM)DefaultTextArray[i]);
	}
	SendMessage(hComBoxInput, CB_DELETESTRING, (WPARAM)"", 0);

	CSprite *pReadyUp = CSpritesManager::GetInstance()->CreateSprite(TEXT("game_ui"), D2D1::Point2F(0, 0), 150, 50, 0, 50);
	CSprite *pReadyDown = CSpritesManager::GetInstance()->CreateSprite(TEXT("game_ui"), D2D1::Point2F(0, 0), 150, 50, 150, 50);

	pReadyButton = new CSpriteButton(1, D2D1::Point2F(418, 372), pReadyUp, pReadyDown);
	WCHAR* pTimerString = new WCHAR[4];

	timerTextSprite = TextSpriteManager::GetInstance()->CreateTextSprite(pTimerString, D2D1::RectF(400, 200, 600, 400), D2D1::ColorF::Orange, 200);
	timerTextSprite->SetVisible(false);
	nGameState = GAME_STATE::GAME_INIT;

	pGameScene = new CGameScene(rectClient);
	pGameScene->InitGameScene();
}

void CDemoGame::OnConnect(LPARAM lParam)
{
	if (WSAGETSELECTERROR(lParam) != 0)
	{
		bConnected = false;
		MessageBox(NULL, TEXT("服务器末开放"), TEXT("OK"), 0);
	}
	else
	{

		InitUI();
		delete(pLoginUI);
		pLoginUI = NULL;
		bConnected = true;

		//MessageBox(NULL, TEXT("连接成功"), TEXT("OK"), 0);
		Msg_Login myLogin;
		myLogin.dwType = MSGID_LOGIN;
		myLogin.nLen = sizeof(myLogin);
		GlobalData *globalData = GlobalData::GetInstance();

		wcscpy(myLogin.cName, globalData->username);
		wcscpy(myLogin.cPwd, globalData->password);
		SendMsg((char*)&myLogin, myLogin.nLen);

	}
}

void CDemoGame::OnClose(SOCKET s)
{

	WCHAR tchar[MSG_SIZE];
	wsprintf(tchar, TEXT("服务端关闭或主动断开了与我们的连接。"), s);
	closesocket(s);
	ClearClientMap();
	ShowText(tchar);
}

// 一个连接上的读操作完成
void CDemoGame::OnRead(SOCKET s, char *pBuffer, int nLen)
{
	WCHAR tmp[200];
	Msg_Generic* pGenericMsg = (Msg_Generic*)pBuffer;
	switch (pGenericMsg->dwType) // 判断收到的消息类型
	{
	case MSGID_FAILED:
		{
			Msg_State* pFailed = (Msg_State*)pBuffer;
			PlayerInfo *player = GetPlayer(pFailed->s);
			player->nState = pFailed->nState; //改变对应玩家状态

			ModifyPlayerText(player); //更新玩家状态信息
		}
		break;
	case MSGID_SCORE:
		{
			Msg_Score *pScore = (Msg_Score*)pBuffer;
			PlayerInfo *player = GetPlayer(pScore->s);
			player->curScore = pScore->nScore;
			ModifyPlayerText(player);
		}
		break;
	case MSGID_READY_FAILED_INFO:
		{
			Msg_Game_Info* pInfo = (Msg_Game_Info*)pBuffer;
			ShowText(pInfo->info);
			pReadyButton->SetVisible(true);

		}
		break;
	case MSGID_START:
		{
			Msg_State* pState = (Msg_State*)pBuffer;

			PlayerInfo *player = GetPlayer(pState->s);
			player->nState = PLAYER_STATE::RUN;
			ModifyPlayerText(player);

			if (player->s == myID) //当自己收到游戏开始消息，则创建游戏对象并开始游戏
			{

				pGameScene->InitGameScene();
				nScore = 0;

				nGameState = GAME_STATE::Game_START;
				timerTextSprite->SetVisible(false);

			}

		}
		break;
	case MSGID_TIMER:
		{
			Msg_Timer *pTimer = (Msg_Timer*)pBuffer;
			timerTextSprite->SetVisible(true);
			ZeroMemory(timerTextSprite->pText, 4 * 2);
			wsprintf(timerTextSprite->pText, TEXT("%d"), pTimer->nReadyCount);
			timerTextSprite->SetVisible(true);
		}
		break;
	case MSGID_READY:
		{
			Msg_State *pReady = (Msg_State*)pBuffer;
			PlayerInfo *player = GetPlayer(pReady->s);
			player->nState = PLAYER_STATE::READY;

			ModifyPlayerText(player);
		}
		break;
	case MSGID_PLAYER_SELF:  //登录成功时收到自己的用户信息
		{
			struct Msg_Player* pSelf = (struct Msg_Player*)pBuffer;

			wsprintf(tmp, TEXT("你登录游戏成功，用户名是%s。"), pSelf->player.cName);
			ShowText(tmp);
			myID = pSelf->player.s;
			if (!clientMap.empty()) //当服务器有其它用户，则输出
			{

				WCHAR* pOutString = MakePlayerInfoOutString();
				ShowText(pOutString);

				delete[] pOutString;
			}
			//将自己的信息存入到玩家信息列表
			AddPlayer(pSelf->player.s, &pSelf->player);

			//创建自己的显示信息文本
			AddPlayerText(pSelf->player.s, &pSelf->player);


		}
		break;
	case MSGID_PLAYER_ALL: //玩家收到当前服务器在线用户信息
		{
			struct Msg_Player* pAll = (struct Msg_Player*)pBuffer;
			AddPlayer(pAll->player.s, &pAll->player);

			//新登录时创建其它在线玩家的显示信息文本
			AddPlayerText(pAll->player.s, &pAll->player);

		}
		break;
	case MSGID_PLAYER_NEW://用户在线时收到新玩家登录时消息
		{
			ZeroMemory(tmp, 400);
			struct Msg_Player* pNew = (struct Msg_Player*)pBuffer;
			wsprintf(tmp, TEXT("有新用户登录游戏成功，用户名是%s。"), pNew->player.cName);
			AddPlayer(pNew->player.s, &pNew->player);
			ShowText(tmp);

			//用户在线时收到新玩家时创建该玩家信息文本
			AddPlayerText(pNew->player.s, &pNew->player);



		}
		break;
	case MSGID_PLAYER_DELETE:  //用户在线时收到玩家退出消息
		{
			ZeroMemory(tmp, 400);
			struct Msg_Player_Delete* pDel = (struct Msg_Player_Delete*)pBuffer;

			struct PlayerInfo* player = GetPlayer(pDel->s);
			wsprintf(tmp, TEXT("用户%s离开了游戏。"), player->cName);

			ShowText(tmp);
			DeletePlayer(pDel->s);

			//用户在线时收到玩家退出消息删除该玩家信息文本
			DeletePlayerText(pDel->s);

		}
		break;
	case MSGID_CHAT:
		{
			Msg_Chat* pChat = (Msg_Chat*)pBuffer;
			PlayerInfo *player = GetPlayer(pChat->s);
			WCHAR tchar[MSG_SIZE];
			ZeroMemory(tchar, MSG_SIZE * 2);
			wsprintf(tchar, TEXT("%s说:%s"), player->cName, pChat->Chat);
			ShowText(tchar);
		}
		break;
	case MSGID_TEXT:
		{
			Msg_Text* pChat = (Msg_Text*)pBuffer;
			PlayerInfo *player = GetPlayer(pChat->s);
			WCHAR tchar[MSG_SIZE];
			ZeroMemory(tchar, MSG_SIZE * 2);
			wsprintf(tchar, TEXT("%s %s"), player->cName, pChat->Chat);
			ShowText(tchar);
		}
		break;
	}
}

void CDemoGame::Update(float fDeltaTime)
{
	CGame::Update(fDeltaTime);
	switch(gameState)
	{
	case Game_START:
		if(pStartScene == NULL)
			pStartScene=new CStartScene(CGame::rectClient);
		break;
	case GameExplain:
		if(pExplainScene == NULL)
			pExplainScene=new CExplainScene(CGame::rectClient);
		break;
	case GameRun:
		if(pGameScene)
		{
			if(pGameScene->IsCartoonVisible())
			{
				if(IsKeyUp(DIK_SPACE))
				{
					pGameScene->HideCartoon();
				}
			}
			else if(pGameScene->IsTextVisible())
			{
				if (IsKeyUp(DIK_SPACE))
				{
					pGameScene->HideText();
					WCHAR* Text=new WCHAR[50];
					Text=pGameScene->ReturnText();
					this->ModifyText(Text);
				}			
			}
			else if(pGameScene->GetButtonState()==0)
			{
				if(pGameScene->GetButtonState()==1)
				{
					break;
				}
			}
			else
			{
				pGameScene->HeroDown();
				pGameScene->CollideWith();
				pGameScene->ControlMonsterMove();
				if(pGameScene->IsGetProp())
				{
					if(IsKeyUp(DIK_SPACE))
					{
						pGameScene->PutDown();
					}
				}
				if (IsKeyPressed(DIK_LEFT))
				{
					pGameScene->MoveLeft();
				}
				if (IsKeyPressed(DIK_RIGHT))
				{
					pGameScene->MoveRight();
				}
				if (IsKeyPressed(DIK_UP))
				{
					pGameScene->MoveUp();
				}
				if (IsKeyPressed(DIK_DOWN))
				{
					pGameScene->MoveDown();
				}
			}
		}
		break;
	case GameClose:
		exit(0);
		break;
	}
	CGame::Update(fDeltaTime);
}

void CDemoGame::ShowText(WCHAR *p)
{

	wcscat(bigchar, p);
	wcscat(bigchar, TEXT("\r\n"));
	SetWindowTextW(hChat, bigchar);//显示聊天字符串
	int ChatEditLineCount = SendMessage(hChat, EM_GETLINECOUNT, 0, 0);	//得到一共多少行
	SendMessage(hChat, EM_LINESCROLL, 0, ChatEditLineCount);     //实现滚动到最后一行
}


void CDemoGame::OnCommand(int cmd)
{

	switch (cmd)
	{
	case IDB_BTNCHAT:
		{
			Msg_Chat MyChat;//定义当前用户登录
			MyChat.dwType = MSGID_CHAT;//新用户登录类型赋值
			MyChat.nLen = sizeof(struct Msg_Chat);
			WCHAR c1[MSG_SIZE];
			GetWindowTextW(hComBoxInput, c1, MSG_SIZE);

			wcscpy(MyChat.Chat, c1);
			char* p = (char*)&MyChat;//将新牌结构体强转化为字符串指针
			SendMsg(p, sizeof(struct Msg_Chat));//通过MyGame的MySocket的Send方法发送
		}
		break;
	case IDB_BTNGAMESEND:
		{
			Msg_Test MyTest;//定义当前用户登录
			MyTest.dwType = MSGID_TEST;//新用户登录类型赋值
			MyTest.nLen = sizeof(struct Msg_Test);

			for (int i = 1; i <= 100; i++)
			{
				//memset(MyTest.Chat, 0, 50);
				ZeroMemory(MyTest.Chat, 50 * 2);
				wsprintf(MyTest.Chat, TEXT("数据包%d"), i);
				MyTest.ID = i;
				char* p = (char*)&MyTest;//将新牌结构体强转化为字符串指针
				SendMsg(p, MyTest.nLen);//通过MyGame的MySocket的Send方法发送


			}
		}
		break;

	}

}


//添加新客户端玩家信息
void CDemoGame::AddPlayer(int s, struct PlayerInfo *player)
{
	PlayerInfo *playerAdd = new  PlayerInfo();  //因需要长期存入用户信息列表，所以需要通过创建用户信息堆
	memcpy(playerAdd, player, sizeof(struct PlayerInfo));//将收到缓冲区中的用户信息复制到用户信息堆
	clientMap.insert(std::make_pair(s, playerAdd));
}

//删除找到的客户端玩家信息
void CDemoGame::DeletePlayer(int s)
{
	std::map<int, PlayerInfo*>::iterator iter = clientMap.begin();
	iter = clientMap.find(s);
	if (iter != clientMap.end()) {
		SAFE_DELETE(iter->second);
		clientMap.erase(iter);
	}
}

//根据套接字ID获取一个用户信息
PlayerInfo* CDemoGame::GetPlayer(int s)
{
	std::map<int, PlayerInfo*>::iterator iter = clientMap.begin();
	iter = clientMap.find(s);
	if (iter != clientMap.end())
	{
		return iter->second;
	}
	else
	{
		return NULL;
	}
}


//清空玩家用户列表
void CDemoGame::ClearClientMap()
{
	std::map<int, PlayerInfo*>::iterator iter = clientMap.begin();
	for (iter = clientMap.begin(); iter != clientMap.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	clientMap.clear();
	if (clientMap.empty()) {
		printf("clientMap清空了\n");
	}
}


//生成当前所有玩家列表的输出字符串
WCHAR* CDemoGame::MakePlayerInfoOutString()
{
	WCHAR* tmp = new WCHAR[200];
	ZeroMemory(tmp, 400);
	if (clientMap.size() >= 1) {
		wcscat(tmp, TEXT("当前服务器的用户还有"));

		std::map<int, PlayerInfo*>::iterator iter;
		int i = 0;
		for (iter = clientMap.begin(); iter != clientMap.end(); ++iter)
		{
			//send(iter->first, buf, len, 0);
			wcscat(tmp, iter->second->cName);
			if (i < clientMap.size() - 1) {
				wcscat(tmp, TEXT(","));

			}
			i++;
		}

		wcscat(tmp, TEXT("。"));
	}

	return tmp;
}


//添加新客户端玩家信息
void CDemoGame::AddPlayerText(int s, struct PlayerInfo *player)
{
	//PlayerInfo *playerAdd = new  PlayerInfo();  //因需要长期存入用户信息列表，所以需要通过创建用户信息堆
	WCHAR *playerText = new WCHAR[100];

	TextSprite *textSprite = TextSpriteManager::GetInstance()->CreateTextSprite(playerText, D2D1::RectF(0, 0, 180, 24), D2D1::ColorF::Yellow,12);
	//memcpy(playerAdd, player, sizeof(struct PlayerInfo));//将收到缓冲区中的用户信息复制到用户信息堆
	//clientMap.insert(std::make_pair(s, playerAdd));
	playerTextSpriteMap.insert(std::make_pair(s,textSprite));
	ReDrawAllPlayerText();
}
//删除找到的客户端玩家信息
void CDemoGame::DeletePlayerText(int s)
{
	std::map<int, TextSprite*>::iterator iter = playerTextSpriteMap.begin();
	iter = playerTextSpriteMap.find(s);
	if (iter != playerTextSpriteMap.end()) {
		//SAFE_DELETE(iter->second);
		TextSpriteManager::GetInstance()->DeleteTextSprite(iter->second);
		playerTextSpriteMap.erase(iter);
	}
	ReDrawAllPlayerText();

}
//根据套接字ID获取一个用户信息
TextSprite* CDemoGame::GetPlayerText(int s)
{
	std::map<int, TextSprite*>::iterator iter = playerTextSpriteMap.begin();
	iter = playerTextSpriteMap.find(s);
	if (iter != playerTextSpriteMap.end())
	{
		return iter->second;
	}
	else
	{
		return NULL;
	}

}
//清空玩家用户列表
void CDemoGame::ClearPlayerTextMap()
{
	std::map<int, TextSprite*>::iterator iter = playerTextSpriteMap.begin();
	for (iter = playerTextSpriteMap.begin(); iter != playerTextSpriteMap.end(); ++iter)
	{
		//SAFE_DELETE(iter->second);
		TextSpriteManager::GetInstance()->DeleteTextSprite(iter->second);
	}
	playerTextSpriteMap.clear();
}

//修改某个玩家信息文本
void  CDemoGame::ModifyPlayerText(struct PlayerInfo *player)
{

	TextSprite* pTextSprite = GetPlayerText(player->s);
	ZeroMemory(pTextSprite->pText, 100 * 2);

	/*WCHAR *tmp = new WCHAR[20];
	ZeroMemory(tmp, 20 * 2);
	wcscpy(tmp, player->cName);
	InsertSpace(tmp);
	wcscat(pTextSprite->pText, tmp);*/

	/*wsprintf(tmp, TEXT("%d"), player->nTotal);
	InsertSpace(tmp);
	wcscat(pTextSprite->pText, tmp);

	ZeroMemory(tmp, 20 * 2);
	wsprintf(tmp, TEXT("%d"), player->curScore);
	InsertSpace(tmp);
	wcscat(pTextSprite->pText, tmp);
	delete[]tmp;*/
	pTextSprite->SetColor(fontColorArray[player->nState]);
}

void  CDemoGame::ModifyText(WCHAR MyText[50])
{
	//Msg_Text *pText;
	//pText->dwType=MSGID_TEXT;
	//pText->nLen = sizeof(struct Msg_Text);		
	//wcscpy(pText->Chat, Chat);
	//char* p = (char*)&pText;//将新牌结构体强转化为字符串指针
	//SendMsg(p, sizeof(struct Msg_Text));
	Msg_Text MyChat;//定义当前用户登录
	MyChat.dwType = MSGID_TEXT;//新用户登录类型赋值
	MyChat.nLen = sizeof(struct Msg_Chat);
	wcscpy(MyChat.Chat, MyText);
	char* p = (char*)&MyChat;//将新牌结构体强转化为字符串指针
	SendMsg(p, sizeof(struct Msg_Chat));//通过MyGame的MySocket的Send方法发送
}

//重绘玩家用户列表
void CDemoGame::ReDrawAllPlayerText() //重设所有玩家信息，当有新用户登录或有人离开时
{
	std::map<int, TextSprite*>::iterator iter = playerTextSpriteMap.begin();
	int i = 0;
	for (iter = playerTextSpriteMap.begin(); iter != playerTextSpriteMap.end(); ++iter)
	{
		PlayerInfo *player = GetPlayer(iter->first);
		ModifyPlayerText(player);
		TextSprite *pTextSprite;
		pTextSprite = GetPlayerText(iter->first);
		pTextSprite->SetRect(D2D1::RectF(46, 215 + i * 36, 294, 215+i * 36 + 36));

		i++;
	}
}

void CDemoGame::InsertSpace(WCHAR* pText)
{
	int nSpaceNumber = 10 - wcslen(pText);

	for (int j = 0; j < nSpaceNumber; j++)
	{
		wcscat(pText, TEXT(" "));
	}
}
