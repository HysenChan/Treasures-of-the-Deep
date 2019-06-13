#pragma once

#include "Framework/Game.h"

enum ExplainMenu			//�˵�״̬
{
	ReturnStartScene        //�������˵�
};

class CExplainScene
{
public:
	CExplainScene(RECT &rectClient);
	~CExplainScene(void);
public:
	bool HandleMouseUp(WPARAM wParam,LPARAM lParam);		//��갴��̧���״̬
	bool HandleMouseDown(WPARAM wParam,LPARAM lParam);		//��갴�����µ�״̬
	void Reset();											//���ó���
	void SetVisible(bool bVal);								//���ð�ť�ɼ���
	bool IsVisible();										//�Ƿ�ɼ�			
	int GetButtonState();									//�õ���ť״̬���жϰ��µ����ĸ���ť
private:
	void InitExplainScene();			//��ʼ������
	RECT rectClient;					//�˿ھ���
	CSprite *pBg;						//��������
	CSpriteButton *pButtons[1];			//��ť
	bool bVisible;						//�жϳ����ɼ���
	int buttonState;					//��ť״̬
};