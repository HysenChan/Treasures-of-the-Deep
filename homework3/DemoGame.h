#pragma once
#include "framework\game.h"
#include "StartScene.h"
#include "GameScene.h"
#include "ExplainScene.h"

#include "Net/TCPClient.h"
#include "LoginUI.h"
#include "GlobalData.h"
using namespace std;

const int IDB_EDIT = 11;       //�����ı���
const int IDB_BTNCHAT = 12;
const int IDB_BTNGAMESEND = 13;
const int IDB_COMBOXINPUT = 14;
const WCHAR DefaultTextArray[5][50] = { TEXT("�ܸ�����ʶ���!"),
	TEXT("��Ҫ�ߣ���ս������!"),
	TEXT("��Ҫ���ˣ��һ����ҵ�!"),
	TEXT("����������̫�����!"),
	TEXT("���ɣ��ҵȵĻ�����л��!")
};

enum GAME_STATE					//��Ϸ״̬
{
	GAME_INIT,					//��Ϸ��ʼ
	Game_READY,				//��Ϸ��ʼ����ʱ״̬
	Game_START,					//��Ϸ���ڿ�ʼ����״̬
	GameRun,					//��Ϸ������Ϸ��״̬
	GameClose,					//��Ϸ���ڽ���״̬
	GameExplain					//��Ϸ����˵������״̬
};

const int fontColorArray[4] = 
{
	D2D1::ColorF::Black,
	D2D1::ColorF::Green,
	D2D1::ColorF::Red,
	D2D1::ColorF::Gray
};

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }

class CDemoGame :
	public CGame,public CTCPClient
{
public:
	CDemoGame(HINSTANCE hInstance,HWND hWnd,int nFPS = 0);
	virtual ~CDemoGame(void);
public:
	void InitGame();											//��ʼ����Ϸ
	void HandleMouseUp(WPARAM wParam,LPARAM lParam);			//���������Ϣ��mouseup
	void HandleMouseDown(WPARAM wParam,LPARAM lParam);			//���������Ϣ��mousedown
	void Update(float fDeltaTime);

	void InitUI();//��ʼ����ϷUI��ʵ�ִ����ؼ���ִ��InitSocket��
	void OnCommand(int cmd);//���յ���ť���������
	void ShowText(WCHAR *p); //�Զ���ֻ����ʾ�ı���������ʾ��������

	//����¿ͻ��������Ϣ
	void AddPlayer(int s, struct PlayerInfo *player);
	//ɾ���ҵ��Ŀͻ��������Ϣ
	void DeletePlayer(int s);
	//�����׽���ID��ȡһ���û���Ϣ
	PlayerInfo* GetPlayer(int s);
	//�������û��б�
	void ClearClientMap();


	//����¿ͻ��������Ϣ
	void AddPlayerText(int s, struct PlayerInfo *player);
	//ɾ���ҵ��Ŀͻ��������Ϣ
	void DeletePlayerText(int s);
	//�����׽���ID��ȡһ���û���Ϣ
	TextSprite* GetPlayerText(int s);
	//�������û��б�
	void ClearPlayerTextMap();
	//�ػ�����û��б�
	void ReDrawAllPlayerText(); //�������������Ϣ���������û���¼�������뿪ʱ

	//�޸�ĳ�������Ϣ�ı�
	void ModifyPlayerText(struct PlayerInfo *player);

	void ModifyText(WCHAR Text[50]);

	WCHAR* MakePlayerInfoOutString();//���ɵ�ǰ��������б������ַ���

	void InsertSpace(WCHAR* pText);
private:
	CStartScene *pStartScene;
	CGameScene *pGameScene;
	CExplainScene *pExplainScene;
	GAME_STATE gameState;
protected:
	// �������
	void OnConnect(LPARAM lParam);
	// һ�����ӹر�
	void OnClose(SOCKET s);
	// һ�������ϵĶ��������
	void OnRead(SOCKET s, char *pBuffer, int nLen);
	LoginUI *pLoginUI;
private:
	std::map<int, PlayerInfo*> clientMap; //�����Ϣ����

	std::map<int, TextSprite*> playerTextSpriteMap;
	SOCKET myID;       //��ǰ�û��׽���ID

	CSpriteButton *pReadyButton;
	CSprite* pGameBackGround;
	TextSprite *timerTextSprite;
	int nGameState;
	int nScore;//�÷�
	int nTotal;//�ܻ���
private:
	WCHAR bigchar[1024 * 16]; //��ʾ�ڴ��ı�������ı�
	HWND hEdit; //���뼸�����ı���
	HWND hChat;		//ֻ���ı�����ʾ
	HWND hBtnChat;  //����������Ϣ�İ�ť
	HWND hBtnGameSend;
	HWND hBtnKai;
	HWND hComBoxInput;
};

