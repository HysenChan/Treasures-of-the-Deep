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
	GAME_INIT,    //��Ϸ��ʼ
	GAME_READY,   //��Ϸ��ʼ����ʱ״̬
	GAME_START,    //��Ϸ��ʼ����״̬
	GAME_OVER      //��Ϸ������״̬
};



class CGame :public CTCPServer
{
private:
	WCHAR bigchar[1024*128]; //��ʾ�ڴ��ı�������ı�
	HWND hwndEdit;//ֻ���ı��� 
	std::map<int, PlayerInfo*> clientMap;  //����û���Ϣ�б�

	int nGameState;  //��Ϸ״̬
	int nReadyCount;
public:
	CGame(void);
	~CGame(void);
	void InitGame(HWND hwnd);
	void TimeFun(int wParam);
	int SendMsg(char* buffer, int len, int sockid); //���͸�ĳ���ͻ�����Ϣ
	int SendMsg(char* buffer,int len);//������Ϣ�����пͻ�
	int SendMsgExceptSelf(char *buf, int len,int s);//������Ϣ������ĳ���ͻ�������������пͻ���
	void ShowText(WCHAR *p);

	BOOL Release();              //�رշ�����
	int GetReadyCount();  //�˺����ɻ�ȡ׼���ͻ��˸���
	void OpenResetReadyTimer();   //�򿪻�����׼����ʱ��

protected:
	// �������
	void OnAccept(SOCKET sClient,struct sockaddr_in addr);
	// һ�����ӹر�
	void OnClose(SOCKET s);
	// һ�������ϵĶ��������
	void OnRead(SOCKET s,char *pBuffer,int nLen);
	//����¿ͻ��������Ϣ
	void AddPlayer(int s, struct PlayerInfo *player);
	//ɾ���ҵ��Ŀͻ��������Ϣ
	void DeletePlayer(int s);
	//�����׽���ID��ȡһ���û���Ϣ
	PlayerInfo* GetPlayer(int s);
	//�������û��б�
	void ClearClientMap();
};
