#include "Game.h"

CGame::CGame(void)
{
	
}

CGame::~CGame(void)
{
}

void CGame::InitGame(HWND h)
{
	this->hwndEdit=h;
	nGameState = GAME_STATE::GAME_INIT;
	nReadyCount = 5;   //30秒倒计时


}
void CGame::ShowText(WCHAR *p)
{
	//wsprintf(bigchar,TEXT("%s%s%s"),bigchar,p,TEXT("\r\n"));//连接字符串
	wcscat(bigchar, p);
	wcscat(bigchar, TEXT("\r\n"));
	SetWindowTextW(hwndEdit,bigchar);//显示聊天字符串
	int ChatEditLineCount=SendMessage(hwndEdit,EM_GETLINECOUNT,0,0);	//得到一共多少行
	SendMessage(hwndEdit,EM_LINESCROLL,0,ChatEditLineCount);     //实现滚动到最后一行
}

void CGame::OnAccept(SOCKET sClient,struct sockaddr_in addr)
{
		//sClientList.push_back(sClient);
		WCHAR tchar[MSG_SIZE];
		wsprintf(tchar, TEXT("IP%S连接成功,套按字为:%d"), inet_ntoa(addr.sin_addr), sClient);
		ShowText(tchar);
}

void CGame::OnClose(SOCKET s)
{
	PlayerInfo *player = GetPlayer(s);
	WCHAR tchar[MSG_SIZE];
	wsprintf(tchar, TEXT("用户%s退出了游戏。"), player->cName);
	
	Msg_Player_Delete playerDelete;
	playerDelete.dwType = MSGID_PLAYER_DELETE;
	playerDelete.nLen = sizeof(playerDelete);
	playerDelete.s = player->s;
	SendMsg((char*)&playerDelete, sizeof(playerDelete));

	DeletePlayer(s);
}



void CGame::OnRead(SOCKET s, char *pBuffer, int nLen)
{
	Msg_Generic *pGenericMsg = (Msg_Generic *)pBuffer;
	switch (pGenericMsg->dwType)//判断消息包类型
	{
	case MSGID_FAILED:
	{
		Msg_State* pFailed = (Msg_State*)pBuffer;
		PlayerInfo *player = GetPlayer(pFailed->s);
		player->nState = pFailed->nState; //服务器存储用户状态

		//转化给所有在线用户
		SendMsg(pBuffer, nLen);

	}
		break;
	case MSGID_SCORE:
	{
		Msg_Score *pScore = (Msg_Score*)pBuffer;
		PlayerInfo *player = GetPlayer(pScore->s);
		player->curScore = pScore->nScore;
		//转化给所有用户
		SendMsg(pBuffer, nLen);

	}
		break;
	case MSGID_READY: //收到玩家准备消息，更新玩家信息并转化给所有用户
	{
		Msg_State* pReady = (Msg_State*)pBuffer;
		PlayerInfo *player = GetPlayer(pReady->s);
		if (nGameState != GAME_STATE::GAME_START)
		{
			player->nState = pReady->nState;
			SendMsg(pBuffer, nLen);
			int nReady = GetReadyCount();
			if (nReady >= 2)
			{
				nGameState = GAME_STATE::GAME_READY;
				OpenResetReadyTimer();
			}
		}
		else  //准备失败
		{
			Msg_Game_Info gameInfo;
			gameInfo.dwType = MSGID_READY_FAILED_INFO;
			gameInfo.nLen = sizeof(struct Msg_Game_Info);
			wcscpy(gameInfo.info,TEXT("游戏运行中，暂时无法准备，请等本局游戏结束再重试"));
			SendMsg((char*)&gameInfo, gameInfo.nLen, s);

		}

	

	}
		break;
	case MSGID_CHAT:
	{
					   Msg_Chat* pChat = (Msg_Chat*)pBuffer;
					   pChat->s = s;
					   PlayerInfo *player = GetPlayer(s);
					   WCHAR tchar[MSG_SIZE];
					   wsprintf(tchar,TEXT("%s说:%s"), player->cName,pChat->Chat);
					   ShowText(tchar);
					   SendMsg(pBuffer, sizeof(struct Msg_Chat));
	}
		break;
	case MSGID_TEXT:
	{
					   Msg_Text* pChat = (Msg_Text*)pBuffer;
					   pChat->s = s;
					   PlayerInfo *player = GetPlayer(s);
					   WCHAR tchar[MSG_SIZE];
					   wsprintf(tchar,TEXT("%s %s"), player->cName,pChat->Chat);
					   ShowText(tchar);
					   SendMsg(pBuffer, sizeof(struct Msg_Chat));
	}
		break;
	case MSGID_TEST:
	{
					   Msg_Test* pTest = (Msg_Test*)pBuffer;
					   WCHAR tchar[MSG_SIZE];
					   ZeroMemory(tchar, MSG_SIZE);
					   wsprintf(tchar, TEXT("这是%s，长度%d"), pTest->Chat, sizeof(struct Msg_Test));
					   ShowText(tchar);
	}
		break;
	case MSGID_LOGIN:
	{
			struct Msg_Login *pLogin = (struct Msg_Login*)pBuffer;
			
			WCHAR tchar[MSG_SIZE];
			ZeroMemory(tchar, MSG_SIZE);
			wsprintf(tchar, TEXT("用户%s登录了游戏。\n"), pLogin->cName);
			//创建一个玩家信息对象存储玩家信息
			PlayerInfo *playerInfo = new PlayerInfo();
			wcscpy(playerInfo->cName, pLogin->cName);
			playerInfo->s = s;


			//向当前用户发送所有在线用户信息
			Msg_Player allPlayer;
			allPlayer.dwType = MSGID_PLAYER_ALL;
			allPlayer.nLen = sizeof(allPlayer);
			std::map<int, PlayerInfo*>::iterator iter;
			for (iter = clientMap.begin(); iter != clientMap.end(); ++iter)
			{
				memcpy(&allPlayer.player, iter->second, sizeof(struct PlayerInfo));
				SendMsg((char *)&allPlayer, allPlayer.nLen, s);
			}


			//向服务器其它玩家发送有新用户登录的用户信息
			Msg_Player newPlayer;
			newPlayer.dwType = MSGID_PLAYER_NEW;
			newPlayer.nLen = sizeof(newPlayer);
			memcpy(&newPlayer.player, playerInfo, sizeof(struct PlayerInfo));
			SendMsgExceptSelf((char*)&newPlayer, newPlayer.nLen, s);

			//向当前玩家发送当前玩家自己的用户信息
			newPlayer.dwType = MSGID_PLAYER_SELF;
			SendMsg((char*)&newPlayer, newPlayer.nLen,s);

			//将当前用户信息存入用户信息列表
			AddPlayer(s, playerInfo);


	}
		break;
	}
}

//发送信息给在线所有用户
int CGame::SendMsg(char* buf, int len)
{
	std::map<int, PlayerInfo*>::iterator iter;
	for (iter = clientMap.begin(); iter != clientMap.end(); ++iter)
	{
		send(iter->first, buf, len, 0);
	}
	return 0;
}

//发送信息给某个客户端
int CGame::SendMsg(char* buffer, int len, int sockid)
{
	int n = send(sockid, buffer, len, 0);
	return n;
}

//发送信息给除了某个客户端外的其它所有客户端
int CGame::SendMsgExceptSelf(char *buf, int len, int s)
{
	std::map<int, PlayerInfo*>::iterator iter;
	for (iter = clientMap.begin(); iter != clientMap.end(); ++iter)
	{
		if (iter->first != s) {
			send(iter->first, buf, len, 0);
		}
	}
	return 0;
}

BOOL  CGame::Release()         //关闭服务器
{
	std::map<int, PlayerInfo*>::iterator iter = clientMap.begin();
	for (iter = clientMap.begin(); iter != clientMap.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	clientMap.clear();
	CTCPServer::Release();
	return true;
}

//添加新客户端玩家信息
void CGame::AddPlayer(int s, struct PlayerInfo *player)
{
	clientMap.insert(std::make_pair(s, player));
}

//删除找到的客户端玩家信息
void CGame::DeletePlayer(int s)
{
	std::map<int, PlayerInfo*>::iterator iter = clientMap.begin();
	iter = clientMap.find(s);
	if (iter != clientMap.end()) {
		SAFE_DELETE(iter->second);
		clientMap.erase(iter);
	}
}

//根据套接字ID获取一个用户信息
PlayerInfo* CGame::GetPlayer(int s)
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
void CGame::ClearClientMap()
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


void  CGame::TimeFun(int wParam)
{
	switch (wParam)
	{
	case TIMER_READY://每秒一次的处理 
	{
		//通过循环判断只有准备的用户才会接收定时器消息和开始消息
		std::map<int, PlayerInfo*>::iterator iter;
		
		for (iter = clientMap.begin(); iter != clientMap.end(); ++iter)
		{
			if (iter->second->nState == PLAYER_STATE::READY ) {
				
				//每一秒发一条倒计时数据给每个客户端
				Msg_Timer timer;
				timer.dwType = MSGID_TIMER;
				timer.nLen = sizeof(struct Msg_Timer);
				timer.nReadyCount = nReadyCount;
				SendMsg((char*)&timer, timer.nLen,iter->first);

			
			}
		}

		if (nReadyCount == 0)
		{

			for (iter = clientMap.begin(); iter != clientMap.end(); ++iter)
			{
				
				//循环判断当玩家的状态是运行状态时，才把这个状态转化给所有在线用户，用于通知有哪些玩家进入游戏状态
				if (iter->second->nState = PLAYER_STATE::RUN) {
					
					Msg_State stateStart;
					stateStart.dwType = MSGID_START;
					stateStart.nLen = sizeof(struct Msg_State);
					stateStart.nState = PLAYER_STATE::RUN;
					stateStart.s = iter->first;
					SendMsg((char*)&stateStart, stateStart.nLen);
				}
				
			}
			//游戏开始时，更改游戏状态为开始状态
			nGameState = GAME_STATE::GAME_START;
			KillTimer(hwndWin, TIMER_READY);  //先关闭之前的定义器
		}
		nReadyCount--;
			

	}
		break;

	}
}

int CGame::GetReadyCount()  //此函数可获取准备客户端个数及根据情况打开或重设定时器
{
	int nReady = 0;
	std::map<int, PlayerInfo*>::iterator iter = clientMap.begin();
	for (iter = clientMap.begin(); iter != clientMap.end(); ++iter)
	{
		if (iter->second->nState == PLAYER_STATE::READY)
		{
			nReady++;
		}

	}
	return nReady;
}

void CGame::OpenResetReadyTimer()   //打开或重设准备定时器
{
	KillTimer(hwndWin, TIMER_READY);  //先关闭之前的定义器
	nReadyCount = 30;
	SetTimer(hwndWin, TIMER_READY, 1000, NULL);  //再重新打开新的定时器
}