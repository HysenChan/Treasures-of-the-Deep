#pragma once

#include "Framework\Game.h"
#include <list>
using namespace std;

enum GSState
{
	Entrance,				//��ڳ���
	GameScene1,				//��Ϸ����1
	GameScene2,				//��Ϸ����2
	GameScene3,				//��Ϸ����3
	GameScene4,				//��Ϸ����4
	GameScene5,				//��Ϸ����5
	GameScene6,				//��Ϸ����6
	GameOver				//��������
};

enum UI
{
	Suspend,				//��ͣ��Ϸ
	Continue,				//������Ϸ
	Over,					//�˳���Ϸ
	Again					//����һ��
};

class CGameScene
{
public:
	CGameScene(RECT &receClient);
	~CGameScene(void);
public:
	void InitGameScene();				//��ʼ����Ϸ����
	bool HandleMouseUp(WPARAM wParam,LPARAM lParam);		//��갴��̧���״̬
	bool HandleMouseDown(WPARAM wParam,LPARAM lParam);		//��갴�����µ�״̬
	void MoveLeft();				//���ƽ�ɫ�����ƶ�              
	void MoveRight();				//���ƽ�ɫ�����ƶ�
	void MoveUp();					//���ƽ�ɫ�����ƶ�
	void MoveDown();				//���ƽ�ɫ�����ƶ�
	void HeroDown();				//��Ϸ��ɫ�³�
	void CollideWith();				//��Ϸ��ײ���
	bool IsTextVisible();			//�ж�������ʾ�Ƿ�ɼ�
	void HideText();				//������ʾ����
	bool IsCartoonVisible();		//�ж���Ϸ���±����Ƿ�ɼ�
	void HideCartoon();				//������Ϸ���±���
	void SharkMove(CAnimationSprite *tMonster,int w);				//��Ϸ�й����ƶ�
	void Shark4Move(CAnimationSprite *tMonster,int w);				//��Ϸ�й����ƶ�
	void OctopusMove(CAnimationSprite *tMonster,int w,int h);		//��Ϸ�й����ƶ�
	void ControlMonsterMove();		//������Ϸ�����ƶ�
	void PutDown();					//���µ���
	bool IsGetProp();				//�ж��Ƿ�õ�����
	void Push(CSprite *pPush,CSprite *pBePush);		//�ƶ�����
	void PushCar(CSprite *pPush,CSprite *pBePush);	//�ƶ���
	void PushBox(CSprite *pPush,CSprite *pBePush);	//�ƶ�����	
	void PushWBox(CSprite *pPush,CSprite *pBePush); //�ƶ�ˮ��
	void SetGSVisible(GSState State,bool bVal);		//������Ϸ״̬���ó����ɼ���
	int GetButtonState();			//��ð�ť״̬
	void setButtonVisible(bool bVal);		//���ð�ť�ɼ���
	void setOverVisible(bool bVal);			//�������������ɼ���
	WCHAR* ReturnText();				//������ʾ����
private:
	RECT rectClient;					//�˿ھ���
	GSState gsState;					//��Ϸ״̬
	CAnimationSprite *pHeroWalk;		//��Ϸ��ɫ���߶���
	CAnimationSprite *pHeroSwim;		//��Ϸ��ɫ��Ӿ����
	CSprite *pCollideFloor;				//�������ײ����
	CSprite *pCollideWall;				//��ǽ����ײ����
	CSprite *pCollide;					//��������ײ����
	
	CSprite *pCartoonSprite[3];			//��Ϸ���±���ͼƬ
	int whichCartoon;					//���ڵõ����Ź��±���ͼƬ��ʾ
	int whichText;						//���ڵõ�����������ʾͼƬ��ʾ
	
	D2D1_POINT_2F target;				//��Ϸ��ɫ��λ��
	double xSharkSpeed, xShark4Speed,xOctopusSpeed,yOctopusSpeed;		//��Ϸ�й�����ƶ�����
	int boolHeroLF;						//�ж���Ϸ��ɫ���ҷ���
	//����1�ز�
	CSprite *pBg1;						//����1����
	CAnimationSprite *pShark;			//���㾫��
	CAnimationSprite *pOctopus;			//���ﾫ��
	CSprite *pStone;					//ʯͷ
	CSprite *pCorpse;					//ʬ��
	CSprite *pDoor;						//��
	CSprite *pBait;						//�ն�
	CSprite *pTorpedo;					//����
	CSprite *pKey;						//Կ��
	bool IsGetKey;						//�ж��Ƿ�õ�Կ��
	CSprite *pText[4];					//����1��ʾ���־���
	WCHAR Text[5][50];					//���ڷ�����ʾ����
	CSprite *pFloor[8];								
	CSprite *pDFloor[3];
	CSprite *pLWall[3];
	CSprite *pRWall[6];

	//����2�ز�
	CSprite *pBg2;						//����2����
	CSprite *pBox;						//����
	CSprite *pDoor2;					//��
	CSprite *pRDoor2;					
	CSprite *pPlank;					
	CSprite *pBar;
	CSprite *pCrowbar;
	CSprite *pCorpse2;
	CSprite *pText2[3];					//��Ϸ��ʾ���־���
	CSprite *pBoxText2;
	CAnimationSprite *pEnter;
	CAnimationSprite *pBackEnter1;
	CSprite *pBackDoor1;
	bool IsGetCrowbar;
	CSprite *pFloor2[7];
	CSprite *pDFloor2[5];

	//����3�ز�
	CSprite *pBg3;
	CSprite *pFloor3;
	CSprite *pCorpse3;
	CSprite *pText3[4];
	CSprite *pGetText3[2];
	CSprite *pBook;
	CAnimationSprite *pBackEnter2;
	CSprite *pBackDoor2;


	//����4�ز�
	CSprite *pBg4;					//����4����
	CSprite *pCage[2];				//����
	CSprite *pStone4[2];			//ʯͷ
	CSprite *pCar;					//��
	CAnimationSprite *pShark4;		//����
	CSprite *pTorpedo4;				//����
	bool IsLaunch;					//�ж��Ƿ�������
	CSprite *pBoom;					//��ըЧ��
	CSprite *pDoor4;				//ʯͷ��
	CSprite *pText4[4];				//��Ϸ��ʾ���־���
	CSprite *pCarText1;				//������ʾ��ײ��
	CSprite *pCarText2;				//������ʾ��ײ��

	CSprite *pFloor4[3];
	CSprite *pLWall4[2];
	CSprite *pRWall4[2];
	CSprite *pChain[3];
	CSprite *pCageU[4];
	CSprite *pCageD[4];
	CAnimationSprite *pBackEnter3;
	CSprite *pBackDoor3;

	//����5Ԫ��
	CSprite *pBg5;					//����5����
	CSprite *pWaterBox;				//ˮ��
	CSprite *pDoor5;				//����
	int OPDoor5;					//�ж��Ƿ񿪹ص���
	CSprite *pPole1;				//���ݸ�1��λ���м�
	CSprite *pPole2;				//���ݸ�2��λ�����
	CSprite *pElectric[5];			//ͨ��Ч��
	CSprite *pShell[2];				//��
	CAnimationSprite *pFan[4];		//����
	CAnimationSprite *pFish[2];		//����
	CSprite *pHead;					//ͷ��
	CSprite *pPlectrum[2];			////��Ƭ
	int IsLFElectric;				//�жϲ�Ƭ�ӵ磬����һ������
	CSprite *pText5[5];				//��Ϸ��ʾ���־���
	CSprite *pText5Chunk[2];		//������ʾ��ײ��

	CSprite *pFloor5[5];
	CSprite *pDFloor5[2];
	CSprite *pLWall5[4];
	CSprite *pRWall5[4];

	//����6Ԫ��		
	CSprite *pBg6;					//����6����

	//��ڳ���Ԫ��			
	CSprite *pEntranceBg;				//��ڳ�������
	CAnimationSprite *pEntranceBg2;		//���ˮ��Ч��

	//����Ԫ��
	CSprite *pOverBg;				//��������
	CSpriteButton *pButtons[4];		//UI��ť
	CSprite *pBtBg;					//��ͣUI����
	int buttonState;				//���ڻ�ȡUI״̬					
};