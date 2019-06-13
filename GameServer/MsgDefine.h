#pragma once
#pragma pack(push) //�������״̬
#pragma pack(4)//�趨Ϊ4�ֽڶ���

#define MSGID_LOGIN             1   //��¼��Ϣ
#define MSGID_CHAT              2   //������Ϣ
#define MSGID_TEST              3   //ճ��������Ϣ

#define MSGID_PLAYER_NEW        4   //����������Ϣ
#define MSGID_PLAYER_ALL        5   //�������������Ϣ
#define MSGID_PLAYER_SELF       6   //���ѵ�¼�ɹ����û���Ϣ
#define MSGID_PLAYER_DELETE     7   //ɾ�������Ϣ
#define MSGID_SCORE             8   //��ҷ�����Ϣ
#define MSGID_OB                9   //��Ϸ�Թ���Ϣ��Ϣ,��Msg_State������
#define MSGID_READY            10   //��Ϸ׼����Ϣ��Ϣ,��Msg_State������
#define MSGID_START            11   //��Ϸ��ʼ��Ϣ��Ϣ,��Msg_State������
#define MSGID_RUNNING          12   //��Ϸ������Ϣ��Ϣ,��Msg_State������
#define MSGID_FAILED           13   //��Ϸʧ����Ϣ��Ϣ,��Msg_State������
#define MSGID_SUSS             14   //��Ϸ�ɹ���Ϣ��Ϣ,��Msg_State������
#define MSGID_TIMER            15   //��Ϸ׼������ʱ��Ϣ
#define MSGID_READY_FAILED_INFO 16  //����Ϸ�Ѿ���ʼ��Ϸ׼��ʧ����Ϣ
#define MSGID_TEXT				17

enum PLAYER_STATE
{
	OB,          //�Թۣ�Ĭ�ϣ���ɫ
	READY,       //׼���ã���ɫ
	RUN,     //��Ϸ�У���ɫ
	FAILED,       //ʧ�ܣ���ɫ
	SUSS          //ʤ������ɫ
};

struct PlayerInfo
{
	int s;
	WCHAR cName[20];
	int nGrade;   //��ҵȼ�
	int nWin;     //ʤ������
	int nLost;    //ʧ�ܴ���
	int nState;   //��Ϸ��ǰ״̬�������Թۡ�׼������Ϸ�С�ʧ��
	int curScore; //��ǰ��Ϸ�ֵ÷�
	int nTotal;    //��Ϸ�ܻ���
};

struct Msg_Generic
{
	DWORD dwType;  //��Ϣ����
	int   nLen;    //��Ϣ���ȣ���ְ�ʱ��
};

struct Msg_Text :public Msg_Generic
{
	int s;
	int  nID;          //������Ϣ�˵ı��
	WCHAR Chat[50];         //������Ϣ���ȣ��200�ֽ�
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
	int nState;  //����0�Թۡ�1׼����2��Ϸ�С�3ʧ�ܡ�4��ʤ��
};


struct Msg_Chat :public Msg_Generic
{
	int s;
	int  nID;          //������Ϣ�˵ı��
	WCHAR Chat[50];         //������Ϣ���ȣ��200�ֽ�
};

struct Msg_Test :public Msg_Generic
{
	int  ID;      //��Ϣ�ı��
	WCHAR Chat[50];         //������Ϣ���ȣ��200�ֽ�
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
	WCHAR cName[20];         //�û���
	WCHAR cPwd[20];          //����
};

//���������ʾ��Ϣ
struct Msg_Game_Info :public Msg_Generic
{
	WCHAR info[50];
};

#pragma pack(pop) // �ָ���ǰ����