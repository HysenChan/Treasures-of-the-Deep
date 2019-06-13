#pragma once
#include "framework\game.h"
#include "StartScene.h"
#include "GameScene.h"
#include "ExplainScene.h"

#include "Net/TCPClient.h"
#include "LoginUI.h"
#include "GlobalData.h"
using namespace std;

const int IDB_EDIT = 11;       //定义文本框
const int IDB_BTNCHAT = 12;
const int IDB_BTNGAMESEND = 13;
const int IDB_COMBOXINPUT = 14;
const WCHAR DefaultTextArray[5][50] = { TEXT("很高兴认识大家!"),
	TEXT("不要走，决战到天亮!"),
	TEXT("我要走了，我会想大家的!"),
	TEXT("和你合作真的太愉快了!"),
	TEXT("快点吧，我等的花儿都谢了!")
};

enum GAME_STATE					//游戏状态
{
	GAME_INIT,					//游戏初始
	Game_READY,				//游戏开始倒计时状态
	Game_START,					//游戏处于开始界面状态
	GameRun,					//游戏处于游戏中状态
	GameClose,					//游戏处于结束状态
	GameExplain					//游戏处于说明界面状态
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
	void InitGame();											//初始化游戏
	void HandleMouseUp(WPARAM wParam,LPARAM lParam);			//处理鼠标消息：mouseup
	void HandleMouseDown(WPARAM wParam,LPARAM lParam);			//处理鼠标消息：mousedown
	void Update(float fDeltaTime);

	void InitUI();//初始化游戏UI，实现创建控件及执行InitSocket。
	void OnCommand(int cmd);//在收到按钮点击的命令
	void ShowText(WCHAR *p); //自定义只读显示文本框内容显示函数定义

	//添加新客户端玩家信息
	void AddPlayer(int s, struct PlayerInfo *player);
	//删除找到的客户端玩家信息
	void DeletePlayer(int s);
	//根据套接字ID获取一个用户信息
	PlayerInfo* GetPlayer(int s);
	//清空玩家用户列表
	void ClearClientMap();


	//添加新客户端玩家信息
	void AddPlayerText(int s, struct PlayerInfo *player);
	//删除找到的客户端玩家信息
	void DeletePlayerText(int s);
	//根据套接字ID获取一个用户信息
	TextSprite* GetPlayerText(int s);
	//清空玩家用户列表
	void ClearPlayerTextMap();
	//重绘玩家用户列表
	void ReDrawAllPlayerText(); //重设所有玩家信息，当有新用户登录或有人离开时

	//修改某个玩家信息文本
	void ModifyPlayerText(struct PlayerInfo *player);

	void ModifyText(WCHAR Text[50]);

	WCHAR* MakePlayerInfoOutString();//生成当前所有玩家列表的输出字符串

	void InsertSpace(WCHAR* pText);
private:
	CStartScene *pStartScene;
	CGameScene *pGameScene;
	CExplainScene *pExplainScene;
	GAME_STATE gameState;
protected:
	// 连接完成
	void OnConnect(LPARAM lParam);
	// 一个连接关闭
	void OnClose(SOCKET s);
	// 一个连接上的读操作完成
	void OnRead(SOCKET s, char *pBuffer, int nLen);
	LoginUI *pLoginUI;
private:
	std::map<int, PlayerInfo*> clientMap; //玩家信息集合

	std::map<int, TextSprite*> playerTextSpriteMap;
	SOCKET myID;       //当前用户套接字ID

	CSpriteButton *pReadyButton;
	CSprite* pGameBackGround;
	TextSprite *timerTextSprite;
	int nGameState;
	int nScore;//得分
	int nTotal;//总积分
private:
	WCHAR bigchar[1024 * 16]; //显示在大文本框里的文本
	HWND hEdit; //输入几个的文本框
	HWND hChat;		//只读文本框显示
	HWND hBtnChat;  //发送聊天信息的按钮
	HWND hBtnGameSend;
	HWND hBtnKai;
	HWND hComBoxInput;
};

