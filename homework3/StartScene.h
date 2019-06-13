#pragma once

#include "Framework\Game.h"

enum MenuButtons					//菜单状态
{
	Start,		//开始游戏
	Explain,	//排行榜
	Close		//关闭游戏
};

class CStartScene					//选择菜单类
{
public:
	CStartScene(RECT &rectClient);	//构造函数
	~CStartScene(void);
public :
	bool HandleMouseUp(WPARAM wParam,LPARAM lParam);					//鼠标按键抬起的状态
	bool HandleMouseDown(WPARAM wParam,LPARAM lParam);					//鼠标按键按下的状态
	void Reset();														//重设按钮
	void SetVisible(bool bVal);											//设置按钮可见性
	bool IsVisible();													//是否可见			
	int GetButtonState();												//获取按钮状态
private :
	void InitStartScene();												//初始化菜单，加载资源

	CSprite *pBg;														//背景
	CSpriteButton *pButtons[3];											//3个按钮		
	RECT rectClient;													//窗口矩形
	bool bVisible;														//判断场景是否可见
	int buttonState;													//按钮状态
};
