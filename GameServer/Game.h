#pragma once
#include "TCPServer.h"
#include "Common.h"
#include "MsgDefine.h"
#include<atlbase.h>
#include <map>
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define TIMER_READY 1
enum GAME_STATE
{
	GAME_INIT,    //游戏初始
	GAME_READY,   //游戏开始倒计时状态
	GAME_START,    //游戏开始运行状态
	GAME_OVER      //游戏结束的状态
};



class CGame :public CTCPServer
{
private:
	WCHAR bigchar[1024*128]; //显示在大文本框里的文本
	HWND hwndEdit;//只读文本框 
	std::map<int, PlayerInfo*> clientMap;  //玩家用户信息列表

	int nGameState;  //游戏状态
	int nReadyCount;
public:
	CGame(void);
	~CGame(void);
	void InitGame(HWND hwnd);
	void TimeFun(int wParam);
	int SendMsg(char* buffer, int len, int sockid); //发送给某个客户端信息
	int SendMsg(char* buffer,int len);//发送消息给所有客户
	int SendMsgExceptSelf(char *buf, int len,int s);//发送信息给除了某个客户端外的其它所有客户端
	void ShowText(WCHAR *p);

	BOOL Release();              //关闭服务器
	int GetReadyCount();  //此函数可获取准备客户端个数
	void OpenResetReadyTimer();   //打开或重设准备定时器

protected:
	// 连接完成
	void OnAccept(SOCKET sClient,struct sockaddr_in addr);
	// 一个连接关闭
	void OnClose(SOCKET s);
	// 一个连接上的读操作完成
	void OnRead(SOCKET s,char *pBuffer,int nLen);
	//添加新客户端玩家信息
	void AddPlayer(int s, struct PlayerInfo *player);
	//删除找到的客户端玩家信息
	void DeletePlayer(int s);
	//根据套接字ID获取一个用户信息
	PlayerInfo* GetPlayer(int s);
	//清空玩家用户列表
	void ClearClientMap();
};
