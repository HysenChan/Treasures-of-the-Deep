#pragma once
#pragma pack(push) //保存对齐状态
#pragma pack(4)//设定为4字节对齐

#define MSGID_LOGIN             1   //登录消息
#define MSGID_CHAT              2   //聊天消息
#define MSGID_TEST              3   //粘包测试消息

#define MSGID_PLAYER_NEW        4   //添加新玩家消息
#define MSGID_PLAYER_ALL        5   //所有其它玩家消息
#define MSGID_PLAYER_SELF       6   //自已登录成功的用户消息
#define MSGID_PLAYER_DELETE     7   //删除玩家消息
#define MSGID_SCORE             8   //玩家分数信息
#define MSGID_OB                9   //游戏旁观消息信息,用Msg_State传数据
#define MSGID_READY            10   //游戏准备消息信息,用Msg_State传数据
#define MSGID_START            11   //游戏开始消息信息,用Msg_State传数据
#define MSGID_RUNNING          12   //游戏运行消息信息,用Msg_State传数据
#define MSGID_FAILED           13   //游戏失败消息信息,用Msg_State传数据
#define MSGID_SUSS             14   //游戏成功消息信息,用Msg_State传数据
#define MSGID_TIMER            15   //游戏准备倒计时消息
#define MSGID_READY_FAILED_INFO 16  //当游戏已经开始游戏准备失败消息
#define MSGID_TEXT				17

enum PLAYER_STATE
{
	OB,          //旁观，默认，白色
	READY,       //准备好，绿色
	RUN,     //游戏中，黄色
	FAILED,       //失败，灰色
	SUSS          //胜利，红色
};

struct PlayerInfo
{
	int s;
	WCHAR cName[20];
	int nGrade;   //玩家等级
	int nWin;     //胜利次数
	int nLost;    //失败次数
	int nState;   //游戏当前状态，包括旁观、准备、游戏中、失败
	int curScore; //当前游戏局得分
	int nTotal;    //游戏总积分
};

struct Msg_Generic
{
	DWORD dwType;  //消息类型
	int   nLen;    //消息长度，需分包时用
};

struct Msg_Text :public Msg_Generic
{
	int s;
	int  nID;          //发送消息人的编号
	WCHAR Chat[50];         //聊天信息长度，最长200字节
};

struct Msg_Timer :public Msg_Generic
{
	int nReadyCount;
};

struct Msg_Score :public Msg_Generic
{
	int s;
	int nScore;
};

struct Msg_State :public Msg_Generic
{
	int s;
	int nState;  //包括0旁观、1准备、2游戏中、3失败、4、胜利
};


struct Msg_Chat :public Msg_Generic
{
	int s;
	int  nID;          //发送消息人的编号
	WCHAR Chat[50];         //聊天信息长度，最长200字节
};

struct Msg_Test :public Msg_Generic
{
	int  ID;      //消息的编号
	WCHAR Chat[50];         //聊天信息长度，最长200字节
};

struct Msg_Player :public Msg_Generic
{

	struct PlayerInfo player;
};

struct Msg_Player_Delete :public Msg_Generic
{
	int s;
};

struct Msg_Login :public Msg_Generic
{
	WCHAR cName[20];         //用户名
	WCHAR cPwd[20];          //密码
};

//用于输出提示信息
struct Msg_Game_Info :public Msg_Generic
{
	WCHAR info[50];
};

#pragma pack(pop) // 恢复先前设置