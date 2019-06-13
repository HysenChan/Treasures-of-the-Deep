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
	nReadyCount = 5;   //30�뵹��ʱ


}
void CGame::ShowText(WCHAR *p)
{
	//wsprintf(bigchar,TEXT("%s%s%s"),bigchar,p,TEXT("\r\n"));//�����ַ���
	wcscat(bigchar, p);
	wcscat(bigchar, TEXT("\r\n"));
	SetWindowTextW(hwndEdit,bigchar);//��ʾ�����ַ���
	int ChatEditLineCount=SendMessage(hwndEdit,EM_GETLINECOUNT,0,0);	//�õ�һ��������
	SendMessage(hwndEdit,EM_LINESCROLL,0,ChatEditLineCount);     //ʵ�ֹ��������һ��
}

void CGame::OnAccept(SOCKET sClient,struct sockaddr_in addr)
{
		//sClientList.push_back(sClient);
		WCHAR tchar[MSG_SIZE];
		wsprintf(tchar, TEXT("IP%S���ӳɹ�,�װ���Ϊ:%d"), inet_ntoa(addr.sin_addr), sClient);
		ShowText(tchar);
}

void CGame::OnClose(SOCKET s)
{
	PlayerInfo *player = GetPlayer(s);
	WCHAR tchar[MSG_SIZE];
	wsprintf(tchar, TEXT("�û�%s�˳�����Ϸ��"), player->cName);
	
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
	switch (pGenericMsg->dwType)//�ж���Ϣ������
	{
	case MSGID_FAILED:
	{
		Msg_State* pFailed = (Msg_State*)pBuffer;
		PlayerInfo *player = GetPlayer(pFailed->s);
		player->nState = pFailed->nState; //�������洢�û�״̬

		//ת�������������û�
		SendMsg(pBuffer, nLen);

	}
		break;
	case MSGID_SCORE:
	{
		Msg_Score *pScore = (Msg_Score*)pBuffer;
		PlayerInfo *player = GetPlayer(pScore->s);
		player->curScore = pScore->nScore;
		//ת���������û�
		SendMsg(pBuffer, nLen);

	}
		break;
	case MSGID_READY: //�յ����׼����Ϣ�����������Ϣ��ת���������û�
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
		else  //׼��ʧ��
		{
			Msg_Game_Info gameInfo;
			gameInfo.dwType = MSGID_READY_FAILED_INFO;
			gameInfo.nLen = sizeof(struct Msg_Game_Info);
			wcscpy(gameInfo.info,TEXT("��Ϸ�����У���ʱ�޷�׼������ȱ�����Ϸ����������"));
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
					   wsprintf(tchar,TEXT("%s˵:%s"), player->cName,pChat->Chat);
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
					   wsprintf(tchar, TEXT("����%s������%d"), pTest->Chat, sizeof(struct Msg_Test));
					   ShowText(tchar);
	}
		break;
	case MSGID_LOGIN:
	{
			struct Msg_Login *pLogin = (struct Msg_Login*)pBuffer;
			
			WCHAR tchar[MSG_SIZE];
			ZeroMemory(tchar, MSG_SIZE);
			wsprintf(tchar, TEXT("�û�%s��¼����Ϸ��\n"), pLogin->cName);
			//����һ�������Ϣ����洢�����Ϣ
			PlayerInfo *playerInfo = new PlayerInfo();
			wcscpy(playerInfo->cName, pLogin->cName);
			playerInfo->s = s;


			//��ǰ�û��������������û���Ϣ
			Msg_Player allPlayer;
			allPlayer.dwType = MSGID_PLAYER_ALL;
			allPlayer.nLen = sizeof(allPlayer);
			std::map<int, PlayerInfo*>::iterator iter;
			for (iter = clientMap.begin(); iter != clientMap.end(); ++iter)
			{
				memcpy(&allPlayer.player, iter->second, sizeof(struct PlayerInfo));
				SendMsg((char *)&allPlayer, allPlayer.nLen, s);
			}


			//�������������ҷ��������û���¼���û���Ϣ
			Msg_Player newPlayer;
			newPlayer.dwType = MSGID_PLAYER_NEW;
			newPlayer.nLen = sizeof(newPlayer);
			memcpy(&newPlayer.player, playerInfo, sizeof(struct PlayerInfo));
			SendMsgExceptSelf((char*)&newPlayer, newPlayer.nLen, s);

			//��ǰ��ҷ��͵�ǰ����Լ����û���Ϣ
			newPlayer.dwType = MSGID_PLAYER_SELF;
			SendMsg((char*)&newPlayer, newPlayer.nLen,s);

			//����ǰ�û���Ϣ�����û���Ϣ�б�
			AddPlayer(s, playerInfo);


	}
		break;
	}
}

//������Ϣ�����������û�
int CGame::SendMsg(char* buf, int len)
{
	std::map<int, PlayerInfo*>::iterator iter;
	for (iter = clientMap.begin(); iter != clientMap.end(); ++iter)
	{
		send(iter->first, buf, len, 0);
	}
	return 0;
}

//������Ϣ��ĳ���ͻ���
int CGame::SendMsg(char* buffer, int len, int sockid)
{
	int n = send(sockid, buffer, len, 0);
	return n;
}

//������Ϣ������ĳ���ͻ�������������пͻ���
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

BOOL  CGame::Release()         //�رշ�����
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

//����¿ͻ��������Ϣ
void CGame::AddPlayer(int s, struct PlayerInfo *player)
{
	clientMap.insert(std::make_pair(s, player));
}

//ɾ���ҵ��Ŀͻ��������Ϣ
void CGame::DeletePlayer(int s)
{
	std::map<int, PlayerInfo*>::iterator iter = clientMap.begin();
	iter = clientMap.find(s);
	if (iter != clientMap.end()) {
		SAFE_DELETE(iter->second);
		clientMap.erase(iter);
	}
}

//�����׽���ID��ȡһ���û���Ϣ
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


//�������û��б�
void CGame::ClearClientMap()
{
	std::map<int, PlayerInfo*>::iterator iter = clientMap.begin();
	for (iter = clientMap.begin(); iter != clientMap.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	clientMap.clear();
	if (clientMap.empty()) {
		printf("clientMap�����\n");
	}
}


void  CGame::TimeFun(int wParam)
{
	switch (wParam)
	{
	case TIMER_READY://ÿ��һ�εĴ��� 
	{
		//ͨ��ѭ���ж�ֻ��׼�����û��Ż���ն�ʱ����Ϣ�Ϳ�ʼ��Ϣ
		std::map<int, PlayerInfo*>::iterator iter;
		
		for (iter = clientMap.begin(); iter != clientMap.end(); ++iter)
		{
			if (iter->second->nState == PLAYER_STATE::READY ) {
				
				//ÿһ�뷢һ������ʱ���ݸ�ÿ���ͻ���
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
				
				//ѭ���жϵ���ҵ�״̬������״̬ʱ���Ű����״̬ת�������������û�������֪ͨ����Щ��ҽ�����Ϸ״̬
				if (iter->second->nState = PLAYER_STATE::RUN) {
					
					Msg_State stateStart;
					stateStart.dwType = MSGID_START;
					stateStart.nLen = sizeof(struct Msg_State);
					stateStart.nState = PLAYER_STATE::RUN;
					stateStart.s = iter->first;
					SendMsg((char*)&stateStart, stateStart.nLen);
				}
				
			}
			//��Ϸ��ʼʱ��������Ϸ״̬Ϊ��ʼ״̬
			nGameState = GAME_STATE::GAME_START;
			KillTimer(hwndWin, TIMER_READY);  //�ȹر�֮ǰ�Ķ�����
		}
		nReadyCount--;
			

	}
		break;

	}
}

int CGame::GetReadyCount()  //�˺����ɻ�ȡ׼���ͻ��˸�������������򿪻����趨ʱ��
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

void CGame::OpenResetReadyTimer()   //�򿪻�����׼����ʱ��
{
	KillTimer(hwndWin, TIMER_READY);  //�ȹر�֮ǰ�Ķ�����
	nReadyCount = 30;
	SetTimer(hwndWin, TIMER_READY, 1000, NULL);  //�����´��µĶ�ʱ��
}