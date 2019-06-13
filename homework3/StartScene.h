#pragma once

#include "Framework\Game.h"

enum MenuButtons					//�˵�״̬
{
	Start,		//��ʼ��Ϸ
	Explain,	//���а�
	Close		//�ر���Ϸ
};

class CStartScene					//ѡ��˵���
{
public:
	CStartScene(RECT &rectClient);	//���캯��
	~CStartScene(void);
public :
	bool HandleMouseUp(WPARAM wParam,LPARAM lParam);					//��갴��̧���״̬
	bool HandleMouseDown(WPARAM wParam,LPARAM lParam);					//��갴�����µ�״̬
	void Reset();														//���谴ť
	void SetVisible(bool bVal);											//���ð�ť�ɼ���
	bool IsVisible();													//�Ƿ�ɼ�			
	int GetButtonState();												//��ȡ��ť״̬
private :
	void InitStartScene();												//��ʼ���˵���������Դ

	CSprite *pBg;														//����
	CSpriteButton *pButtons[3];											//3����ť		
	RECT rectClient;													//���ھ���
	bool bVisible;														//�жϳ����Ƿ�ɼ�
	int buttonState;													//��ť״̬
};
