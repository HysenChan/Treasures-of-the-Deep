#pragma once

#include "Framework/Game.h"

enum ExplainMenu			//菜单状态
{
	ReturnStartScene        //返回主菜单
};

class CExplainScene
{
public:
	CExplainScene(RECT &rectClient);
	~CExplainScene(void);
public:
	bool HandleMouseUp(WPARAM wParam,LPARAM lParam);		//鼠标按键抬起的状态
	bool HandleMouseDown(WPARAM wParam,LPARAM lParam);		//鼠标按键按下的状态
	void Reset();											//重置场景
	void SetVisible(bool bVal);								//设置按钮可见性
	bool IsVisible();										//是否可见			
	int GetButtonState();									//得到按钮状态，判断按下的是哪个按钮
private:
	void InitExplainScene();			//初始化场景
	RECT rectClient;					//端口矩形
	CSprite *pBg;						//场景背景
	CSpriteButton *pButtons[1];			//按钮
	bool bVisible;						//判断场景可见性
	int buttonState;					//按钮状态
};