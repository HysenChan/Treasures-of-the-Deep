#pragma once

#include "Framework\Game.h"
#include <list>
using namespace std;

enum GSState
{
	Entrance,				//入口场景
	GameScene1,				//游戏场景1
	GameScene2,				//游戏场景2
	GameScene3,				//游戏场景3
	GameScene4,				//游戏场景4
	GameScene5,				//游戏场景5
	GameScene6,				//游戏场景6
	GameOver				//结束场景
};

enum UI
{
	Suspend,				//暂停游戏
	Continue,				//继续游戏
	Over,					//退出游戏
	Again					//再来一局
};

class CGameScene
{
public:
	CGameScene(RECT &receClient);
	~CGameScene(void);
public:
	void InitGameScene();				//初始化游戏场景
	bool HandleMouseUp(WPARAM wParam,LPARAM lParam);		//鼠标按键抬起的状态
	bool HandleMouseDown(WPARAM wParam,LPARAM lParam);		//鼠标按键按下的状态
	void MoveLeft();				//控制角色向左移动              
	void MoveRight();				//控制角色向右移动
	void MoveUp();					//控制角色向上移动
	void MoveDown();				//控制角色向下移动
	void HeroDown();				//游戏角色下沉
	void CollideWith();				//游戏碰撞检测
	bool IsTextVisible();			//判断文字提示是否可见
	void HideText();				//隐藏提示文字
	bool IsCartoonVisible();		//判断游戏故事背景是否可见
	void HideCartoon();				//隐藏游戏故事背景
	void SharkMove(CAnimationSprite *tMonster,int w);				//游戏中怪物移动
	void Shark4Move(CAnimationSprite *tMonster,int w);				//游戏中怪物移动
	void OctopusMove(CAnimationSprite *tMonster,int w,int h);		//游戏中怪物移动
	void ControlMonsterMove();		//控制游戏怪物移动
	void PutDown();					//放下道具
	bool IsGetProp();				//判断是否得到道具
	void Push(CSprite *pPush,CSprite *pBePush);		//推动道具
	void PushCar(CSprite *pPush,CSprite *pBePush);	//推动车
	void PushBox(CSprite *pPush,CSprite *pBePush);	//推动箱子	
	void PushWBox(CSprite *pPush,CSprite *pBePush); //推动水箱
	void SetGSVisible(GSState State,bool bVal);		//根据游戏状态设置场景可见性
	int GetButtonState();			//获得按钮状态
	void setButtonVisible(bool bVal);		//设置按钮可见性
	void setOverVisible(bool bVal);			//设置死亡场景可见性
	WCHAR* ReturnText();				//返回提示文字
private:
	RECT rectClient;					//端口矩形
	GSState gsState;					//游戏状态
	CAnimationSprite *pHeroWalk;		//游戏角色行走动画
	CAnimationSprite *pHeroSwim;		//游戏角色游泳动画
	CSprite *pCollideFloor;				//与地面碰撞精灵
	CSprite *pCollideWall;				//与墙壁碰撞精灵
	CSprite *pCollide;					//与其他碰撞精灵
	
	CSprite *pCartoonSprite[3];			//游戏故事背景图片
	int whichCartoon;					//用于得到那张故事背景图片显示
	int whichText;						//用于得到哪张文字提示图片显示
	
	D2D1_POINT_2F target;				//游戏角色的位置
	double xSharkSpeed, xShark4Speed,xOctopusSpeed,yOctopusSpeed;		//游戏中怪物的移动参数
	int boolHeroLF;						//判断游戏角色左右方向
	//场景1素材
	CSprite *pBg1;						//场景1背景
	CAnimationSprite *pShark;			//鲨鱼精灵
	CAnimationSprite *pOctopus;			//怪物精灵
	CSprite *pStone;					//石头
	CSprite *pCorpse;					//尸体
	CSprite *pDoor;						//门
	CSprite *pBait;						//诱饵
	CSprite *pTorpedo;					//鱼雷
	CSprite *pKey;						//钥匙
	bool IsGetKey;						//判断是否得到钥匙
	CSprite *pText[4];					//场景1提示文字精灵
	WCHAR Text[5][50];					//用于返回提示内容
	CSprite *pFloor[8];								
	CSprite *pDFloor[3];
	CSprite *pLWall[3];
	CSprite *pRWall[6];

	//场景2素材
	CSprite *pBg2;						//场景2背景
	CSprite *pBox;						//箱子
	CSprite *pDoor2;					//门
	CSprite *pRDoor2;					
	CSprite *pPlank;					
	CSprite *pBar;
	CSprite *pCrowbar;
	CSprite *pCorpse2;
	CSprite *pText2[3];					//游戏提示文字精灵
	CSprite *pBoxText2;
	CAnimationSprite *pEnter;
	CAnimationSprite *pBackEnter1;
	CSprite *pBackDoor1;
	bool IsGetCrowbar;
	CSprite *pFloor2[7];
	CSprite *pDFloor2[5];

	//场景3素材
	CSprite *pBg3;
	CSprite *pFloor3;
	CSprite *pCorpse3;
	CSprite *pText3[4];
	CSprite *pGetText3[2];
	CSprite *pBook;
	CAnimationSprite *pBackEnter2;
	CSprite *pBackDoor2;


	//场景4素材
	CSprite *pBg4;					//场景4背景
	CSprite *pCage[2];				//笼子
	CSprite *pStone4[2];			//石头
	CSprite *pCar;					//弩车
	CAnimationSprite *pShark4;		//鲨鱼
	CSprite *pTorpedo4;				//鱼雷
	bool IsLaunch;					//判断是否发射鱼雷
	CSprite *pBoom;					//爆炸效果
	CSprite *pDoor4;				//石头门
	CSprite *pText4[4];				//游戏提示文字精灵
	CSprite *pCarText1;				//文字提示碰撞体
	CSprite *pCarText2;				//文字提示碰撞体

	CSprite *pFloor4[3];
	CSprite *pLWall4[2];
	CSprite *pRWall4[2];
	CSprite *pChain[3];
	CSprite *pCageU[4];
	CSprite *pCageD[4];
	CAnimationSprite *pBackEnter3;
	CSprite *pBackDoor3;

	//场景5元素
	CSprite *pBg5;					//场景5背景
	CSprite *pWaterBox;				//水箱
	CSprite *pDoor5;				//电门
	int OPDoor5;					//判断是否开关电门
	CSprite *pPole1;				//操纵杆1，位于中间
	CSprite *pPole2;				//操纵杆2，位于左边
	CSprite *pElectric[5];			//通电效果
	CSprite *pShell[2];				//蚌
	CAnimationSprite *pFan[4];		//电扇
	CAnimationSprite *pFish[2];		//电鳗
	CSprite *pHead;					//头骨
	CSprite *pPlectrum[2];			////拨片
	int IsLFElectric;				//判断拨片接电，接哪一条电线
	CSprite *pText5[5];				//游戏提示文字精灵
	CSprite *pText5Chunk[2];		//文字提示碰撞体

	CSprite *pFloor5[5];
	CSprite *pDFloor5[2];
	CSprite *pLWall5[4];
	CSprite *pRWall5[4];

	//场景6元素		
	CSprite *pBg6;					//场景6背景

	//入口场景元素			
	CSprite *pEntranceBg;				//入口场景背景
	CAnimationSprite *pEntranceBg2;		//入口水流效果

	//其他元素
	CSprite *pOverBg;				//死亡背景
	CSpriteButton *pButtons[4];		//UI按钮
	CSprite *pBtBg;					//暂停UI背景
	int buttonState;				//用于获取UI状态					
};