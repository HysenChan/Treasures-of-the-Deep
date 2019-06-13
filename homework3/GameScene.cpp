#include"GameScene.h"
#include <time.h>

CGameScene::CGameScene(RECT &rectClient)
{
	this->rectClient=rectClient;
	InitGameScene();
}

CGameScene::~CGameScene(void)
{
}

void CGameScene::InitGameScene()
{
	/*int left = ((rectClient.right - rectClient.left) - 272 ) / 2;
	int top =((rectClient.bottom - rectClient.top) - 300) / 2;*/
	int left = rectClient.left;
	int top = rectClient.top;

	CSpritesManager *pSpritesManager = CSpritesManager::GetInstance();

	//GameScene6
	pBg6=pSpritesManager->CreateSprite(L"GameScene6Bg",D2D1::Point2F(0,0));
	//GameScene6

	//GameScene5
	OPDoor5=2;
	IsLFElectric=2;
	pBg5=pSpritesManager->CreateSprite(L"GameScene5Bg",D2D1::Point2F(0,0));//场景五背景

	pDoor5 = pSpritesManager->CreateSprite(L"Gs5Material",D2D1::Point2F(330,315),40,155,320,415);//电门
	pElectric[0] = pSpritesManager->CreateSprite(L"Gs5Material",D2D1::Point2F(20,460),20,140,20,460);//左一电
	pElectric[1] = pSpritesManager->CreateSprite(L"Gs5Material",D2D1::Point2F(50,460),20,90,50,460);//左二电
	pElectric[1]->SetVisible(false);
	pElectric[2] = pSpritesManager->CreateSprite(L"Gs5Material",D2D1::Point2F(130,615),600,45,130,615);//底部电
	pElectric[3] = pSpritesManager->CreateSprite(L"Gs5Material",D2D1::Point2F(410,540),150,60,410,540);//中间电
	pElectric[3]->SetVisible(false);
	pElectric[4] = pSpritesManager->CreateSprite(L"Gs5Material",D2D1::Point2F(570,265),40,30,570,265);//活板门电
	pElectric[4]->SetVisible(false);
	pShell[0] = pSpritesManager->CreateSprite(L"Monster",D2D1::Point2F(860,100),137,140,130,360);
	pShell[0]->SetScaleFactor(-0.75,0.75);
	pShell[1] = pSpritesManager->CreateSprite(L"Monster",D2D1::Point2F(860,100),130,140,0,360);
	pShell[1]->SetScaleFactor(-0.75,0.75);
	pShell[1]->SetVisible(false);
	pPole1 = pSpritesManager->CreateSprite(L"Gs5Material",D2D1::Point2F(570,200),20,40,560,160);
	pPole1->SetHotSpot(D2D1::Point2F(10,40));
	pPole1->SetRotationAngle(-30);
	pPole2 = pSpritesManager->CreateSprite(L"Gs5Material",D2D1::Point2F(780,70),20,40,560,160);
	pPole2->SetHotSpot(D2D1::Point2F(10,40));
	pPole2->SetRotationAngle(30);
	pPole2->SetVisible(false);
	pWaterBox = pSpritesManager->CreateSprite(L"Gs5Material",D2D1::Point2F(800,530),45,70,800,530);
	pFan[0] = pSpritesManager->CreateAnimationSprite(L"Gs5Material",2,30,D2D1::Point2F(96,590),90,35,0,15);//左侧横风扇
	pFan[0]->Play();
	pFan[1] = pSpritesManager->CreateAnimationSprite(L"Gs5Material",2,30,D2D1::Point2F(665,618),90,35,0,15);//右侧横风扇
	pFan[1]->Play();
	pFan[2] = pSpritesManager->CreateAnimationSprite(L"Gs5Material",2,30,D2D1::Point2F(65,540),90,35,0,15,D2D1::Point2F(45,35));//左侧立风扇
	pFan[2]->SetRotationAngle(90);
	pFan[2]->Play();
	pFan[2]->Stop();
	pFan[3] = pSpritesManager->CreateAnimationSprite(L"Gs5Material",2,30,D2D1::Point2F(545,555),90,35,0,15,D2D1::Point2F(45,35));//中间风扇
	pFan[3]->SetScaleFactor(0.7,0.7);
	pFan[3]->SetRotationAngle(-90);
	pFan[3]->Play();	
	pFan[3]->Stop();	
	pHead = pSpritesManager->CreateSprite(L"Gs5Material",D2D1::Point2F(265,565),70,70,625,20);
	pHead->SetScaleFactor(0.4,0.4);
	pFish[0] = pSpritesManager->CreateAnimationSprite(L"Gs5Material",2,2,D2D1::Point2F(230,530),105,60,360,20);//中间鱼
	pFish[0]->Play();
	pFish[1] = pSpritesManager->CreateAnimationSprite(L"Gs5Material",2,2,D2D1::Point2F(70,228),105,60,360,20);//被困鱼
	pFish[1]->SetScaleFactor(0.4,0.5);
	pFish[1]->SetRotationAngle(90);
	pFish[1]->Play();
	pPlectrum[0] = pSpritesManager->CreateSprite(L"Gs5Material",D2D1::Point2F(25,445),20,25,105,310);//左拨片
	pPlectrum[1] = pSpritesManager->CreateSprite(L"Gs5Material",D2D1::Point2F(30,465),20,25,105,310);//右拨片
	pPlectrum[1]->SetRotationAngle(-80);
	pPlectrum[1]->SetVisible(false);

	for(int i=0;i<5;i++)
	{
		pText5[i] = pSpritesManager->CreateSprite(L"Text",D2D1::Point2F(300,200),400,200,i*403,800);
		pText5[i]->SetVisible(false);
	}
	pText5Chunk[0] = pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(795,525),55,80);
	pText5Chunk[1] = pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(0,190),80,20);
	for(int i=0;i<2;i++)
	{
		pText5Chunk[i]->SetVisible(false);
	}

	for(int i=0;i<5;i++)
	{
		pFloor5[i]=pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(0,0),50,10);
		pFloor5[i]->SetVisible(false);
	}
	for(int i=0;i<2;i++)
	{
		pDFloor5[i]=pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(0,0),50,10);
		pDFloor5[i]->SetVisible(false);
	}
	pFloor5[0]->SetScaleFactor(1.8,1.0);
	pFloor5[0]->SetPos(D2D1::Point2F(0,200));
	pFloor5[1]->SetScaleFactor(9.5,1.0);
	pFloor5[1]->SetPos(D2D1::Point2F(200,210));
	pFloor5[2]->SetScaleFactor(2.0,1.0);
	pFloor5[2]->SetPos(D2D1::Point2F(765,200));
	pFloor5[3]->SetPos(D2D1::Point2F(960,280));
	pFloor5[4]->SetScaleFactor(20.0,1.0);
	pFloor5[4]->SetPos(D2D1::Point2F(0,600));
	pDFloor5[0]->SetScaleFactor(9.5,1.0);
	pDFloor5[0]->SetPos(D2D1::Point2F(200,420));
	pDFloor5[1]->SetScaleFactor(2.0,1.0);
	pDFloor5[1]->SetPos(D2D1::Point2F(770,420));

	for(int i=0;i<4;i++)
	{
		pLWall5[i]=pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(300,100),10,50);
		pLWall5[i]->SetVisible(false);
		pRWall5[i]=pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(300,100),10,50);
		pRWall5[i]->SetVisible(false);
	}
	pLWall5[0]->SetScaleFactor(1.0,4.5);
	pLWall5[0]->SetPos(D2D1::Point2F(200,215));
	pLWall5[1]->SetScaleFactor(1.0,4.5);
	pLWall5[1]->SetPos(D2D1::Point2F(530,430));
	pLWall5[2]->SetScaleFactor(1.0,4.5);
	pLWall5[2]->SetPos(D2D1::Point2F(765,200));
	pLWall5[3]->SetScaleFactor(1.0,8.0);
	pLWall5[3]->SetPos(D2D1::Point2F(956,280));
	pRWall5[0]->SetScaleFactor(1.0,10.0);
	pRWall5[0]->SetPos(D2D1::Point2F(75,200));
	pRWall5[1]->SetScaleFactor(1.0,4.5);
	pRWall5[1]->SetPos(D2D1::Point2F(570,430));
	pRWall5[2]->SetScaleFactor(1.0,4.5);
	pRWall5[2]->SetPos(D2D1::Point2F(660,210));
	pRWall5[3]->SetScaleFactor(1.0,4.5);
	pRWall5[3]->SetPos(D2D1::Point2F(860,200));
	//GameScene5

	//GameScene4
	xShark4Speed=1;
	IsLaunch=false;

	pBg4=pSpritesManager->CreateSprite(L"GameScene4Bg",D2D1::Point2F(0,0));

	pDoor4 = pSpritesManager->CreateSprite(L"Material",D2D1::Point2F(930,0),80,310,700,390);
	pBoom = pSpritesManager->CreateSprite(L"Material",D2D1::Point2F(890,70),115,198,800,450);
	pBoom->SetVisible(false);

	pBackDoor3 = pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(5,0),15,100);
	pBackDoor3->SetVisible(false);
	pBackEnter3 = pSpritesManager->CreateAnimationSprite(L"EntranceBg2",2,2,D2D1::Point2F(80,0),115,120);	
	pBackEnter3->Play();
	pBackEnter3->SetScaleFactor(-1.0f,1.0f);

	for(int i=0;i<3;i++)
	{
		pChain[i] = pSpritesManager->CreateSprite(L"Material",D2D1::Point2F(0,0),17,320,670,380);
	}
	pChain[0]->SetRotationAngle(-90);
	pChain[0]->SetScaleFactor(1.0,1.1);
	pChain[0]->SetPos(D2D1::Point2F(230,55));
	pChain[1]->SetScaleFactor(1.0,1.7);
	pChain[1]->SetPos(D2D1::Point2F(195,72));
	pChain[2]->SetScaleFactor(1.0,1.7);
	pChain[2]->SetPos(D2D1::Point2F(600,72));

	pTorpedo4 = pSpritesManager->CreateSprite(L"Material",D2D1::Point2F(360,225),250,120,30,380);
	pTorpedo4->SetScaleFactor(0.3f,0.3f);
	pTorpedo4->SetRotationAngle(-15);
	pTorpedo4->SetVisible(false);

	pCar = pSpritesManager->CreateSprite(L"Material2",D2D1::Point2F(580,660),470,265,0,680);
	//pCar = pSpritesManager->CreateSprite(L"Material2",D2D1::Point2F(700,300),470,265,0,680);
	pCar->SetHotSpot(D2D1::Point2F(pCar->GetWidth()/2,pCar->GetHeight()/2));
	pCar->SetScaleFactor(0.2f,0.3f);

	pShark4 = pSpritesManager->CreateAnimationSprite(L"Monster",2,2,D2D1::Point2F(180,350),251,133,0,2);
	pShark4->SetHotSpot(D2D1::Point2F(pShark4->GetWidth()/2,pShark4->GetHeight()/2));
	pShark4->SetScaleFactor(0.45f,0.45f);
	pShark4->Play();

	for(int i=0;i<2;i++)
	{
		pStone4[i] = pSpritesManager->CreateSprite(L"Material",D2D1::Point2F(0,0),160,150,150,40);
		pStone4[i]->SetHotSpot(D2D1::Point2F(pStone4[i]->GetWidth()/2,pStone4[i]->GetHeight()/2));
		pStone4[i]->SetScaleFactor(0.3f,0.3f);
	}
	pStone4[1]->SetScaleFactor(0.25f,0.25f);
	pStone4[0]->SetPos(D2D1::Point2F(100,360));
	pStone4[1]->SetPos(D2D1::Point2F(350,680));

	pCage[0] = pSpritesManager->CreateSprite(L"Material",D2D1::Point2F(150,255),130,145,320,400);
	pCage[1] = pSpritesManager->CreateSprite(L"Material",D2D1::Point2F(545,570),155,145,480,400);
	pCage[1]->SetScaleFactor(0.8,1.0);

	for(int i=0;i<4;i++)
	{
		pCageU[i]=pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(0,0),100,10);
		pCageD[i]=pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(0,0),100,10);
		pCageU[i]->SetVisible(false);
		pCageD[i]->SetVisible(false);
	}
	pCageU[0]->SetPos(D2D1::Point2F(160,285));
	pCageD[0]->SetPos(D2D1::Point2F(160,295));
	pCageU[1]->SetPos(D2D1::Point2F(165,375));
	pCageD[1]->SetPos(D2D1::Point2F(165,385));
	pCageU[2]->SetPos(D2D1::Point2F(560,605));
	pCageD[2]->SetPos(D2D1::Point2F(560,615));
	pCageU[3]->SetPos(D2D1::Point2F(560,705));
	pCageD[3]->SetPos(D2D1::Point2F(560,715));
	for(int i=0;i<3;i++)
	{
		pFloor4[i]=pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(0,0),50,10);
		pFloor4[i]->SetVisible(false);
	}
	pFloor4[0]->SetScaleFactor(3.1,1.0);
	pFloor4[0]->SetPos(D2D1::Point2F(0,385));
	pFloor4[1]->SetScaleFactor(2.0,1.0);
	pFloor4[1]->SetPos(D2D1::Point2F(690,375));
	pFloor4[2]->SetScaleFactor(3.0,1.0);
	pFloor4[2]->SetPos(D2D1::Point2F(890,310));

	for(int i=0;i<2;i++)
	{
		pLWall4[i]=pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(300,100),10,50);
		pLWall4[i]->SetVisible(false);
	}
	for(int i=0;i<2;i++)
	{
		pRWall4[i]=pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(300,100),10,50);
		pRWall4[i]->SetVisible(false);
	}
	pLWall4[0]->SetScaleFactor(1.0,8.0);
	pLWall4[0]->SetPos(D2D1::Point2F(700,385));
	pLWall4[1]->SetScaleFactor(1.0,8.0);
	pLWall4[1]->SetPos(D2D1::Point2F(890,310));
	pRWall4[0]->SetScaleFactor(1.0,8.0);
	pRWall4[0]->SetPos(D2D1::Point2F(145,390));
	pRWall4[1]->SetScaleFactor(1.0,8.0);
	pRWall4[1]->SetPos(D2D1::Point2F(780,385));

	//创建游戏文字提示精灵，可见性设置为不可见
	for(int i=0;i<4;i++)
	{
		pText4[i] = pSpritesManager->CreateSprite(L"Text",D2D1::Point2F(300,200),400,200,i*403,200);
		pText4[i]->SetVisible(false);
	}
	pCarText1 = pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(580,660),480,275,0,0);
	pCarText1->SetHotSpot(D2D1::Point2F(pCar->GetWidth()/2,pCar->GetHeight()/2));
	pCarText1->SetScaleFactor(0.2f,0.3f);
	pCarText1->SetVisible(false);

	pCarText2 = pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(720,320),480,275,0,0);
	pCarText2->SetHotSpot(D2D1::Point2F(pCar->GetWidth()/2,pCar->GetHeight()/2));
	pCarText2->SetScaleFactor(0.2f,0.3f);
	pCarText2->SetVisible(false);
	//GameSceme4

	//GameScene3
	//创建场景3背景
	pBg3=pSpritesManager->CreateSprite(L"GameScene3Bg",D2D1::Point2F(0,0));
	//创建场景3精灵
	pFloor3=pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(82,625),50,10);
	pFloor3->SetScaleFactor(3.3f,2.5f);
	pFloor3->SetVisible(false);
	pCorpse3 = pSpritesManager->CreateSprite(L"Material2",D2D1::Point2F(787,348),346,223,633,95);
	pCorpse3->SetHotSpot(D2D1::Point2F(pCorpse3->GetWidth()/2,pCorpse3->GetHeight()/2));
	pCorpse3->SetScaleFactor(0.3f,0.3f);
	pBook=pSpritesManager->CreateSprite(L"Material2",D2D1::Point2F(830,410),77,41,235,470);
	pBook->SetHotSpot(D2D1::Point2F(pBook->GetWidth()/2,pBook->GetHeight()/2));
	pBook->SetScaleFactor(0.5f,0.5f);
	pBackDoor2 = pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(960,510),20,265);
	pBackDoor2->SetVisible(false);
	pBackEnter2 = pSpritesManager->CreateAnimationSprite(L"EntranceBg2",2,2,D2D1::Point2F(900,510),115,120);	
	pBackEnter2->Play();
	pBackEnter2->SetScaleFactor(1.0f,2.0f);

	for(int i=0;i<2;i++)
	{
		pGetText3[i]=pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(300,100),50,10);
		pGetText3[i]->SetVisible(false);
	}
	pGetText3[0]->SetPos(D2D1::Point2F(720,300));
	pGetText3[0]->SetScaleFactor(0.2f,7.5f);
	pGetText3[1]->SetPos(D2D1::Point2F(84,593));
	pGetText3[1]->SetScaleFactor(3.5f,2.5f);
	for(int i=0;i<4;i++)
	{
		pText3[i] = pSpritesManager->CreateSprite(L"Text",D2D1::Point2F(300,200),400,200,i*403,600);
		pText3[i]->SetVisible(false);
	}

	//GameScene3

	//GameScene2
	//创建场景2背景
	pBg2=pSpritesManager->CreateSprite(L"GameScene2Bg",D2D1::Point2F(0,0));
	//创建场景2精灵
	pPlank = pSpritesManager->CreateSprite(L"Material",D2D1::Point2F(270,620),505,205,470,155);
	pPlank->SetHotSpot(D2D1::Point2F(pPlank->GetWidth()/2+70,pPlank->GetHeight()/2-20));
	pDoor2 = pSpritesManager->CreateSprite(L"Material",D2D1::Point2F(0,295),30,365,354,0);
	pRDoor2 = pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(0,490),20,265);
	pRDoor2->SetVisible(false);
	pEnter = pSpritesManager->CreateAnimationSprite(L"EntranceBg2",2,2,D2D1::Point2F(90,500),115,120);	
	pEnter->Play();
	pEnter->SetScaleFactor(-1.0f,3.0f);
	pBackDoor1 = pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(0,0),20,265);
	pBackDoor1->SetVisible(false);
	pBackEnter1 = pSpritesManager->CreateAnimationSprite(L"EntranceBg2",2,2,D2D1::Point2F(80,0),115,120);	
	pBackEnter1->Play();
	pBackEnter1->SetScaleFactor(-1.0f,2.0f);
	pBar   = pSpritesManager->CreateSprite(L"Material",D2D1::Point2F(739,207),153,81,507,28);
	pBox = pSpritesManager->CreateSprite(L"Material2",D2D1::Point2F(687,350),114,105,868,439);
	pBox->SetHotSpot(D2D1::Point2F(pBox->GetWidth()/2,pBox->GetHeight()/2));
	pBox->SetScaleFactor(0.9f,0.9f);
	pCorpse2 = pSpritesManager->CreateSprite(L"Material2",D2D1::Point2F(770,549),282,358,298,18);
	pCorpse2->SetHotSpot(D2D1::Point2F(pCorpse2->GetWidth()/2,pCorpse2->GetHeight()/2));
	pCorpse2->SetScaleFactor(0.3f,0.3f);
	pCrowbar = pSpritesManager->CreateSprite(L"Material2",D2D1::Point2F(730,585),248,113,432,506);
	pCrowbar->SetHotSpot(D2D1::Point2F(pCrowbar->GetWidth()/2,pCrowbar->GetHeight()/2));
	pCrowbar->SetScaleFactor(0.35f,0.8f);
	pCrowbar->SetRotationAngle(10.0f);
	pBoxText2 = pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(755,417),50,10,0,0);
	pBoxText2->SetHotSpot(D2D1::Point2F(pBox->GetWidth()/2,pBox->GetHeight()/2));
	pBoxText2->SetScaleFactor(2.3f,1.5f);
	pBoxText2->SetVisible(false);
	for(int i=0;i<3;i++)
	{
		pText2[i] = pSpritesManager->CreateSprite(L"Text",D2D1::Point2F(300,200),400,200,i*403,400);
		pText2[i]->SetVisible(false);
	}
	for(int i=0;i<7;i++)
	{
		pFloor2[i]=pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(300,100),50,10);
		pFloor2[i]->SetVisible(false);
	}
	for(int i=0;i<5;i++)
	{
		pDFloor2[i]=pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(300,100),50,10);
		pDFloor2[i]->SetVisible(false); 
	}

	pFloor2[0]->SetPos(D2D1::Point2F(577,233));
	pFloor2[0]->SetScaleFactor(3.3f,4.0f);
	pFloor2[1]->SetPos(D2D1::Point2F(861,234));
	pFloor2[1]->SetScaleFactor(3.3f,3.0f);
	pFloor2[2]->SetPos(D2D1::Point2F(489,379));
	pFloor2[2]->SetScaleFactor(10.0f,3.0f);
	pFloor2[3]->SetPos(D2D1::Point2F(149,615));
	pFloor2[3]->SetScaleFactor(2.0f,2.0f);
	pFloor2[4]->SetPos(D2D1::Point2F(741,245));
	pFloor2[4]->SetScaleFactor(2.5f,1.8f);
	pFloor2[5]->SetPos(D2D1::Point2F(806,231));
	pFloor2[5]->SetScaleFactor(2.5f,1.8f);
	pFloor2[6]->SetPos(D2D1::Point2F(320,570));
	pFloor2[6]->SetScaleFactor(2.5f,1.8f);
	pDFloor2[0]->SetPos(D2D1::Point2F(577,257));
	pDFloor2[0]->SetScaleFactor(3.3f,3.0f);
	pDFloor2[1]->SetPos(D2D1::Point2F(861,261));
	pDFloor2[1]->SetScaleFactor(3.3f,2.0f);
	pDFloor2[2]->SetPos(D2D1::Point2F(489,403));
	pDFloor2[2]->SetScaleFactor(10.0f,2.1f);
	pDFloor2[3]->SetPos(D2D1::Point2F(741,263));
	pDFloor2[3]->SetScaleFactor(1.3f,2.0f);
	pDFloor2[4]->SetPos(D2D1::Point2F(800,263));
	pDFloor2[4]->SetScaleFactor(1.3f,1.3f);
	//GameScene2

	//GameScene1
	//场景1参数
	xSharkSpeed=0.5;
	xOctopusSpeed=0.2;
	yOctopusSpeed=0.5;
	//创建场景1背景
	pBg1=pSpritesManager->CreateSprite(L"GameScene1Bg",D2D1::Point2F(0,0));
	//创建场景1精灵
	pStone = pSpritesManager->CreateSprite(L"Material",D2D1::Point2F(350,130),160,150,150,40);
	pStone->SetHotSpot(D2D1::Point2F(pStone->GetWidth()/2,pStone->GetHeight()/2));
	pStone->SetScaleFactor(0.4f,0.4f);
	pCorpse = pSpritesManager->CreateSprite(L"Material2",D2D1::Point2F(780,570),261,338,14,42);
	pCorpse->SetScaleFactor(0.3f,0.3f);
	pKey = pSpritesManager->CreateSprite(L"Material2",D2D1::Point2F(810,595),40,60,60,450);
	pKey->SetScaleFactor(0.5,0.5);
	pDoor = pSpritesManager->CreateSprite(L"Material",D2D1::Point2F(940,270),75,216);

	pTorpedo = pSpritesManager->CreateSprite(L"Material",D2D1::Point2F(360,235),250,120,30,380);
	pTorpedo->SetScaleFactor(0.3f,0.3f);

	//创建游戏文字提示精灵，可见性设置为不可见
	for(int i=0;i<4;i++)
	{
		pText[i] = pSpritesManager->CreateSprite(L"Text",D2D1::Point2F(300,200),400,200,i*403,0);
		pText[i]->SetVisible(false);
	}
	wcscpy(Text[0], TEXT("找到了二战时期美军的哑火鱼雷，看来如传言所说，阿波丸号确实是美军击沉的…"));
	wcscpy(Text[1], TEXT("用石头砸死了巨型水母，水母是大型鱼类的最爱！"));
	wcscpy(Text[2], TEXT("找到了一具尸体并从尸体上摸出了一把钥匙！"));
	wcscpy(Text[3], TEXT("找到了通往下一个房间的门，但似乎需要钥匙才能打开！"));
	wcscpy(Text[4], TEXT(" "));
	//创建场景1怪物精灵
	pShark = pSpritesManager->CreateAnimationSprite(L"Monster",2,2,D2D1::Point2F(810,640),251,133,0,2);
	pShark->SetHotSpot(D2D1::Point2F(pShark->GetWidth()/2,pShark->GetHeight()/2));
	pShark->SetScaleFactor(0.5f,0.5f);
	pShark->Play();

	pOctopus = pSpritesManager->CreateAnimationSprite(L"Monster",3,3,D2D1::Point2F(160,250),177,206,0,148);
	pOctopus->SetHotSpot(D2D1::Point2F(pOctopus->GetWidth()/2,pOctopus->GetHeight()/2));
	pOctopus->SetScaleFactor(0.4f,0.4f);
	pOctopus->Play();

	pBait = pSpritesManager->CreateSprite(L"Monster",D2D1::Point2F(170,330),177,206,360,150);
	pBait->SetHotSpot(D2D1::Point2F(pBait->GetWidth()/2,pBait->GetHeight()/2));
	pBait->SetScaleFactor(0.3,0.2);
	pBait->SetRotationAngle(-90);
	pBait->SetVisible(false);
	IsGetKey=false;

	for(int i=0;i<8;i++)
	{
		pFloor[i]=pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(300,100),50,10);
		pFloor[i]->SetVisible(false);
	}
	for(int i=0;i<3;i++)
	{
		pDFloor[i]=pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(300,100),50,10);
		pDFloor[i]->SetVisible(false);
	}
	pFloor[0]->SetScaleFactor(5.0,1.0f);
	pFloor[0]->SetPos(D2D1::Point2F(0,370));
	pFloor[1]->SetPos(D2D1::Point2F(250,470));
	pFloor[2]->SetPos(D2D1::Point2F(300,520));
	pFloor[3]->SetScaleFactor(0.3f,1.0f);
	pFloor[3]->SetPos(D2D1::Point2F(340,540));
	pFloor[4]->SetScaleFactor(15.0f,1.0f);
	pFloor[4]->SetPos(D2D1::Point2F(230,270));
	pDFloor[0]->SetScaleFactor(15.0f,1.0f);
	pDFloor[0]->SetPos(D2D1::Point2F(230,280));
	pFloor[5]->SetScaleFactor(7.0,2.0f);
	pFloor[5]->SetPos(D2D1::Point2F(640,455));
	pDFloor[1]->SetScaleFactor(7.0,2.0f);
	pDFloor[1]->SetPos(D2D1::Point2F(640,465));
	pFloor[6]->SetScaleFactor(5.8,2.0f);
	pFloor[6]->SetPos(D2D1::Point2F(240,150));
	pDFloor[2]->SetScaleFactor(5.8,2.0f);
	pDFloor[2]->SetPos(D2D1::Point2F(240,160));
	pFloor[7]->SetScaleFactor(13.0f,2.0f);
	pFloor[7]->SetPos(D2D1::Point2F(340,666));

	for(int i=0;i<3;i++)
	{
		pLWall[i]=pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(300,100),10,50);
		pLWall[i]->SetVisible(false);
	}
	for(int i=0;i<6;i++)
	{
		pRWall[i]=pSpritesManager->CreateSprite(L"Collide",D2D1::Point2F(300,100),10,50);
		pRWall[i]->SetVisible(false);
	}

	pLWall[0]->SetScaleFactor(2.0f,1.0f);
	pLWall[0]->SetPos(D2D1::Point2F(238,150));
	pRWall[0]->SetScaleFactor(2.0f,1.0f);
	pRWall[0]->SetPos(D2D1::Point2F(250,150));
	pLWall[1]->SetScaleFactor(1.0f,2.8f);
	pRWall[1]->SetScaleFactor(1.0f,2.8f);	
	pLWall[1]->SetPos(D2D1::Point2F(470,150));
	pRWall[1]->SetPos(D2D1::Point2F(480,150));
	pLWall[2]->SetScaleFactor(1.0f,4.0f);
	pLWall[2]->SetPos(D2D1::Point2F(970,480));
	pRWall[2]->SetScaleFactor(1.0f,2.0f);
	pRWall[2]->SetPos(D2D1::Point2F(250,370));
	pRWall[3]->SetPos(D2D1::Point2F(300,470));
	pRWall[4]->SetScaleFactor(1.0f,0.4f);
	pRWall[4]->SetPos(D2D1::Point2F(345,520));
	pRWall[5]->SetScaleFactor(1.0f,2.3f);
	pRWall[5]->SetPos(D2D1::Point2F(330,550));
	//GameScene1

	//创建入口场景
	pEntranceBg = pSpritesManager->CreateSprite(L"EntranceBg",D2D1::Point2F(0,0));
	pEntranceBg2 = pSpritesManager->CreateAnimationSprite(L"EntranceBg2",2,2,D2D1::Point2F(270,450),115,120);	
	pEntranceBg2->Play();

	//初始化游戏角色位置
	target.x = 100;
	target.y = 100;
	//创建游戏角色行走精灵，设置热点为精灵中心，可见性设置为不可见
	pHeroWalk = pSpritesManager->CreateAnimationSprite(TEXT("HeroWalker"),4,2,target,50,80,150,0);
	pHeroWalk->SetHotSpot(D2D1::Point2F(pHeroWalk->GetWidth()/2,pHeroWalk->GetHeight()/2));
	pHeroWalk->SetScaleFactor(0.9,0.9);
	pHeroWalk->Play();
	pHeroWalk->SetVisible(false);
	//创建游戏角色游泳精灵，设置热点为精灵中心
	pHeroSwim = pSpritesManager->CreateAnimationSprite(TEXT("HeroSwim"),4,2,target,100,60);
	pHeroSwim->SetHotSpot(D2D1::Point2F(pHeroSwim->GetWidth()/2,pHeroSwim->GetHeight()/2));
	pHeroSwim->SetScaleFactor(0.9,0.9);
	pHeroSwim->Play();
	//创建碰撞精灵，设置热点为精灵中心
	pCollideFloor = pSpritesManager->CreateSprite(L"Collide",target,10,60);
	pCollideFloor->SetHotSpot(D2D1::Point2F(pCollideFloor->GetWidth()/2,pCollideFloor->GetHeight()/2));
	pCollideFloor->SetVisible(false);
	pCollideWall = pSpritesManager->CreateSprite(L"Collide",target,60,10);
	pCollideWall->SetHotSpot(D2D1::Point2F(pCollideWall->GetWidth()/2,pCollideWall->GetHeight()/2));
	pCollideWall->SetVisible(false);
	pCollide = pSpritesManager->CreateSprite(L"Collide",target,20,20);
	pCollide->SetHotSpot(D2D1::Point2F(pCollide->GetWidth()/2,pCollide->GetHeight()/2));
	pCollide->SetVisible(false);

	//创建角色死亡按钮选项背景和按钮
	pOverBg = pSpritesManager->CreateSprite(L"OverBg",D2D1::Point2F(0,0));
	pOverBg->SetVisible(false);

	//创建暂停背景板
	pBtBg = pSpritesManager->CreateSprite(L"GameUI",D2D1::Point2F(260,170),490,400,310,250);
	pBtBg->SetVisible(false);
	//创建暂停UI
	CSprite *pSuspendUp = pSpritesManager->CreateSprite(L"GameUI",D2D1::Point2F(0,0),90,90,410,145);
	CSprite *pSuspendDown= pSpritesManager->CreateSprite(L"GameUI",D2D1::Point2F(0,0),90,90,410,145);
	pSuspendUp->SetScaleFactor(0.7f,0.7f);
	pSuspendDown->SetScaleFactor(0.8f,0.8f);
	pButtons[0] = new CSpriteButton(Suspend,D2D1::Point2F(left + 900,top + 10),pSuspendUp,pSuspendDown);
	//创建继续游戏UI
	CSprite *pContinueUp = pSpritesManager->CreateSprite(L"GameUI",D2D1::Point2F(0,0),160,78,27,530);
	CSprite *pContinueDown= pSpritesManager->CreateSprite(L"GameUI",D2D1::Point2F(0,0),160,78,27,530);
	pContinueDown->SetScaleFactor(1.05f,1.05f);
	pButtons[1] = new CSpriteButton(Continue,D2D1::Point2F(left + 420,top + 300),pContinueUp,pContinueDown);
	pButtons[1]->SetVisible(false);
	//创建游戏结束UI
	CSprite *pOverUp = pSpritesManager->CreateSprite(L"GameUI",D2D1::Point2F(0,0),170,75,18,420);
	CSprite *pOverDown = pSpritesManager->CreateSprite(L"GameUI",D2D1::Point2F(0,0),170,75,18,420);
	pOverDown->SetScaleFactor(1.05f,1.05f);
	pButtons[2] = new CSpriteButton(Over,D2D1::Point2F(left + 415,top + 440),pOverUp,pOverDown);
	pButtons[2]->SetVisible(false);
	//创建再来一局UI
	CSprite *pAgainUp = pSpritesManager->CreateSprite(L"GameUI",D2D1::Point2F(0,0),160,78,27,282);
	CSprite *pAgainDown = pSpritesManager->CreateSprite(L"GameUI",D2D1::Point2F(0,0),160,78,27,282);
	pAgainDown->SetScaleFactor(1.05f,1.05f);
	pButtons[3] = new CSpriteButton(Again,D2D1::Point2F(left + 420,top + 350),pAgainUp,pAgainDown);
	pButtons[3]->SetVisible(false);

	//创建游戏故事背景精灵，该精灵必须为最后一个创建
	pCartoonSprite[2] = pSpritesManager->CreateSprite(L"StoryBg3",D2D1::Point2F(0,0));
	pCartoonSprite[1] = pSpritesManager->CreateSprite(L"StoryBg2",D2D1::Point2F(0,0));
	pCartoonSprite[0] = pSpritesManager->CreateSprite(L"StoryBg1",D2D1::Point2F(0,0));

	gsState=Entrance;
	//gsState=GameScene1;
	//gsState=GameScene5;
	//gsState=GameScene2;
	//gsState=GameScene3;

	/*this->SetGSVisible(GameScene4,false);
	this->SetGSVisible(GameScene3,false);
	this->SetGSVisible(GameScene2,false);
	this->SetGSVisible(GameScene1,false);
	this->SetGSVisible(Entrance,false);*/
}

void CGameScene::CollideWith()
{
	switch(gsState)
	{
	case Entrance:
		if(pCollide->GetPos().x>340&&pCollide->GetPos().y>480&&pCollide->GetPos().x<360&&pCollide->GetPos().y<540)//游戏角色进入入口时，将入口场景设为不可见
		{
			this->SetGSVisible(Entrance,false);
			gsState=GameScene1;
			target.x=100;
			target.y=100;
		}
		break;
	case GameScene1:
		if(pOctopus->IsVisible()&&pCollide->CollideWith(*pOctopus))//碰到章鱼时角色死亡，游戏结束
		{
			pOverBg->SetVisible(true);
			pButtons[2]->SetVisible(true);
			pButtons[3]->SetVisible(true);
			gsState=GameOver;
		}
		if(pCollide->CollideWith(*pShark))//碰到鲨鱼时角色死亡，游戏结束
		{
			pOverBg->SetVisible(true);
			pButtons[2]->SetVisible(true);
			pButtons[3]->SetVisible(true);
			gsState=GameOver;
		}
		if(pTorpedo->IsVisible()&&pCollide->CollideWith(*pTorpedo))//得到鱼雷，给出对应提示
		{
			target.x-=5;
			target.y-=5;
			pTorpedo->SetVisible(false);
			pText[0]->SetVisible(true);
		}
		if(pBait->IsVisible()&&pCollide->CollideWith(*pBait))//捡起诱饵
		{
			pText[1]->SetVisible(true);
			pBait->SetVisible(false);
		}
		if(pCorpse->IsVisible()&&pCollide->CollideWith(*pCorpse))//摸索尸体，得到尸体上的钥匙
		{
			target.x-=5;
			target.y-=5;
			pText[2]->SetVisible(true);
			pKey->SetVisible(false);
			IsGetKey=true;
		}
		if(!IsGetKey&&pCollide->CollideWith(*pDoor))//没有钥匙，与门接触，无法打开门
		{
			target.x-=5;
			pText[3]->SetVisible(true);
		}
		this->Push(pCollide,pStone);
		if(pStone->GetPos().y<pFloor[0]->GetPos().y-20&&pStone->GetPos().x<pFloor[6]->GetPos().x-30)//石头在指定条件下落，砸死章鱼
		{
			pStone->GetPos().y++;
			pStone->SetPos(pStone->GetPos());
			if(pStone->CollideWith(*pOctopus))
			{
				pOctopus->SetVisible(false);
				pBait->SetVisible(true);
			}
		}
		if(pStone->GetPos().x>pFloor[0]->GetPos ().x+255&&pStone->GetPos().y>pFloor[6]->GetPos().y+30&&pStone->GetPos().y<pFloor[7]->GetPos().y+10)//石头下落
		{
			pStone->GetPos().y++;
			pStone->SetPos(pStone->GetPos());
		}
		if(IsGetKey&&pCollide->CollideWith(*pDoor))//有钥匙，与门接触，打开门进入下一关
		{
			this->SetGSVisible(GameScene1,false);
			this->SetGSVisible(GameScene2,true);
			gsState=GameScene2;
			target.x=100;
			target.y=100;
		}
		break;
	case GameScene2:
		if(pCrowbar->IsVisible()&&pCollide->CollideWith(*pCrowbar))
		{
			if(pCrowbar->GetPos().x>810&&pCrowbar->GetPos().x<830&&pCollide->CollideWith(*pCrowbar))
			{
				pCrowbar->SetVisible(false);
				pBar->SetPos(D2D1::Point2F(739,307));
				pFloor2[4]->SetPos(D2D1::Point2F(739,0));
				pFloor2[5]->SetPos(D2D1::Point2F(739,0));
				pDFloor2[3]->SetPos(D2D1::Point2F(739,0));
				pDFloor2[4]->SetPos(D2D1::Point2F(739,0));
			}
			else
			{
				pCrowbar->SetVisible(false);
				pText2[1]->SetVisible(true);
				IsGetCrowbar=true;
			}
		}
		if(pCollideWall->CollideWith(*pDoor2))
		{
			pText2[0]->SetVisible(true);
		}
		if(pCollideWall->CollideWith(*pBoxText2))
		{
			pText2[2]->SetVisible(true);
			pBoxText2->SetPos(D2D1::Point2F(755,0));
		}
		this->PushBox(pCollide,pBox);
		if(pBox->GetPos().y<this->rectClient.bottom-60&&pBox->GetPos().x<pFloor2[2]->GetPos().x-20)
		{
			pBox->GetPos().y++;
			pBox->SetPos(pBox->GetPos());
			if(pBox->CollideWith(*pFloor2[6]))
			{
				pFloor2[6]->SetPos(pBox->GetPos());
			}
		}
		static float Rotation;
		if(pBox->CollideWith(*pFloor2[6]))
		{
			if(pPlank->GetRotationAngle()<45)
			{
				Rotation = pPlank->GetRotationAngle();
				Rotation+=0.4;
				pPlank->SetRotationAngle(Rotation);
				pDoor2->GetPos().y-=1.5;
				pDoor2->SetPos(pDoor2->GetPos());
			}
		}
		if(pCollideWall->CollideWith(*pRDoor2))
		{
			this->SetGSVisible(GameScene2,false);
			this->SetGSVisible(GameScene3,true);
			gsState=GameScene3;
			target.x=700;
			target.y=550;
		}
		if(pCollideWall->CollideWith(*pBackDoor1))
		{
			this->SetGSVisible(GameScene2,false);
			this->SetGSVisible(GameScene1,true);
			gsState=GameScene1;
			target.x=822;
			target.y=401;
		}
		break;
	case GameScene3:
		if(pCollideWall->CollideWith(*pGetText3[0]))
		{
			pText3[0]->SetVisible(true);
			pGetText3[0]->SetPos(D2D1::Point2F(755,0));
		}
		if(pCollide->CollideWith(*pCorpse3))
		{
			target.x-=10;
			pText3[1]->SetVisible(true);
		}
		if(pCollide->CollideWith(*pBook))
		{
			target.x-=10;
			pText3[2]->SetVisible(true);
		}
		if(pCollideWall->CollideWith(*pGetText3[1]))
		{
			pText3[3]->SetVisible(true);
			pGetText3[1]->SetPos(D2D1::Point2F(755,0));
		}
		if(pCollideWall->CollideWith(*pFloor3))
		{
			this->SetGSVisible(GameScene3,false);
			this->SetGSVisible(GameScene4,true);
			gsState=GameScene4;
			target.x=100;
			target.y=100;
		}
		if(pCollideWall->CollideWith(*pBackDoor2))
		{
			this->SetGSVisible(GameScene3,false);
			this->SetGSVisible(GameScene2,true);
			gsState=GameScene2;
			target.x=133;
			target.y=505;
		}
		break;
	case GameScene4:
		if(pChain[0]->CollideWith(*pCollide))//与铁链接触，触发提示
		{
			target.y+=5;
			pText4[0]->SetVisible(true);
		}
		if(pDoor4->IsVisible()&&pDoor4->CollideWith(*pCollide))//与石头门接触，触发提示
		{
			target.x-=5;
			pText4[2]->SetVisible(true);
		}
		if(!pDoor4->IsVisible()&&pDoor4->CollideWith(*pCollide))//石头门消失，进入下一关
		{
			this->SetGSVisible(GameScene4,false);
			gsState=GameScene5;
			target.x=100;
			target.y=100;
		}
		if(pCarText1->CollideWith(*pCollide))//在笼子里与车接触，触发提示
		{
			pText4[1]->SetVisible(true);
			pCarText1->GetPos().y+=500;
			pCarText1->SetPos(pCarText1->GetPos());
		}
		if(pCarText2->CollideWith(*pCollide)&&pCar->CollideWith(*pCollide))//在平台上与车接触，触发提示
		{
			pText4[3]->SetVisible(true);
			pCarText2->GetPos().y-=700;
			pCarText2->SetPos(pCarText1->GetPos());
		}
		if(pCollide->CollideWith(*pShark4))//与鲨鱼接触，角色死亡，游戏结束
		{
			pOverBg->SetVisible(true);
			pButtons[2]->SetVisible(true);
			pButtons[3]->SetVisible(true);
			gsState=GameOver;
		}
		if(pTorpedo4->IsVisible()&&pTorpedo4->CollideWith(*pCar))//放置导弹，按回车确定发射
		{
			if(GetKeyState(VK_RETURN))
			{
				IsLaunch=true;
			}
		}
		if(IsLaunch)//发射导弹
		{
			pTorpedo4->GetPos().x++;
			pTorpedo4->GetPos().y-=0.5;
			pTorpedo4->SetPos(pTorpedo4->GetPos());
			if(pTorpedo4->CollideWith(*pDoor4))
			{
				if(pTorpedo4->GetPos().x>910)
				{
					pBoom->SetVisible(false);
				}
				else
				{
					pBoom->SetVisible(true);
				}				
				pDoor4->SetVisible(false);
				pTorpedo4->SetVisible(false);
			}
		}
		if(pCar->GetPos().y<rectClient.bottom-pCar->GetHeight()/6)//车下落
		{
			if(pCar->CollideWith(*pFloor4[1])&&pCar->GetPos().x>pFloor4[1]->GetPos().x)
			{break;}
			pCar->GetPos().y+=0.8;
			pCar->SetPos(D2D1::Point2F(pCar->GetPos().x,pCar->GetPos().y));
		}
		for(int i=0;i<2;i++)//石头下落
		{
			if(pStone4[i]->CollideWith(*pFloor4[0]))
			{break;}
			if(pStone4[i]->GetPos().y<rectClient.bottom-pStone4[i]->GetHeight()/6)
			{
				pStone4[i]->GetPos().y+=0.7;
				pStone4[i]->SetPos(D2D1::Point2F(pStone4[i]->GetPos().x,pStone4[i]->GetPos().y));
			}
		}
		if(pStone4[0]->CollideWith(*pCageU[1])&&pStone4[1]->CollideWith(*pCageU[1]))//两块石头一起带动笼子下落
		{
			for(int i=0;i<2;i++)
			{
				pCageU[i]->GetPos().y+=1.5;
				pCageD[i]->GetPos().y+=1.5;
				pCageU[i]->SetPos(D2D1::Point2F(pCageU[i]->GetPos().x,pCageU[i]->GetPos().y));
				pCageD[i]->SetPos(D2D1::Point2F(pCageU[i]->GetPos().x,pCageU[i]->GetPos().y));
			}
			pCage[0]->GetPos().y+=1.5;
			pCage[0]->SetPos(D2D1::Point2F(pCage[0]->GetPos().x,pCage[0]->GetPos().y));
			for(int i=2;i<4;i++)
			{
				pCageU[i]->GetPos().y-=1.5;
				pCageD[i]->GetPos().y-=1.5;
				pCageU[i]->SetPos(D2D1::Point2F(pCageU[i]->GetPos().x,pCageU[i]->GetPos().y));
				pCageD[i]->SetPos(D2D1::Point2F(pCageU[i]->GetPos().x,pCageU[i]->GetPos().y));
			}
			pCage[1]->GetPos().y-=1.5;
			pCage[1]->SetPos(D2D1::Point2F(pCage[1]->GetPos().x,pCage[1]->GetPos().y));
			if(pCageU[3]->CollideWith(*pCar))
			{
				pCar->GetPos().y-=1.5;
				pCar->SetPos(D2D1::Point2F(pCar->GetPos().x,pCar->GetPos().y));
			}			
		}
		else if(pStone4[0]->CollideWith(*pCageU[1])||pStone4[1]->CollideWith(*pCageU[1]))//两块石头反别带动笼子下落
		{
			for(int i=0;i<2;i++)
			{
				pCageU[i]->GetPos().y+=0.7;
				pCageD[i]->GetPos().y+=0.7;
				pCageU[i]->SetPos(D2D1::Point2F(pCageU[i]->GetPos().x,pCageU[i]->GetPos().y));
				pCageD[i]->SetPos(D2D1::Point2F(pCageU[i]->GetPos().x,pCageU[i]->GetPos().y));
			}
			pCage[0]->GetPos().y+=0.7;
			pCage[0]->SetPos(D2D1::Point2F(pCage[0]->GetPos().x,pCage[0]->GetPos().y));
			for(int i=2;i<4;i++)
			{
				pCageU[i]->GetPos().y-=0.7;
				pCageD[i]->GetPos().y-=0.7;
				pCageU[i]->SetPos(D2D1::Point2F(pCageU[i]->GetPos().x,pCageU[i]->GetPos().y));
				pCageD[i]->SetPos(D2D1::Point2F(pCageU[i]->GetPos().x,pCageU[i]->GetPos().y));
			}
			pCage[1]->GetPos().y-=0.7;
			pCage[1]->SetPos(D2D1::Point2F(pCage[1]->GetPos().x,pCage[1]->GetPos().y));
			if(pCageU[3]->CollideWith(*pCar))
			{
				pCar->GetPos().y-=0.7;
				pCar->SetPos(D2D1::Point2F(pCar->GetPos().x,pCar->GetPos().y));
			}			
		}
		if(pCar->CollideWith(*pCageU[3]))//车带动笼子下落
		{
			for(int i=2;i<4;i++)
			{
				pCageU[i]->GetPos().y+=0.8;
				pCageD[i]->GetPos().y+=0.8;
				pCageU[i]->SetPos(D2D1::Point2F(pCageU[i]->GetPos().x,pCageU[i]->GetPos().y));
				pCageD[i]->SetPos(D2D1::Point2F(pCageU[i]->GetPos().x,pCageU[i]->GetPos().y));
			}
			pCage[1]->GetPos().y+=0.8;
			pCage[1]->SetPos(D2D1::Point2F(pCage[1]->GetPos().x,pCage[1]->GetPos().y));
			for(int i=0;i<2;i++)
			{
				pCageU[i]->GetPos().y-=0.8;
				pCageD[i]->GetPos().y-=0.8;
				pCageU[i]->SetPos(D2D1::Point2F(pCageU[i]->GetPos().x,pCageU[i]->GetPos().y));
				pCageD[i]->SetPos(D2D1::Point2F(pCageU[i]->GetPos().x,pCageU[i]->GetPos().y));
			}
			pCage[0]->GetPos().y-=0.8;
			pCage[0]->SetPos(D2D1::Point2F(pCage[0]->GetPos().x,pCage[0]->GetPos().y));
			for(int i=0;i<2;i++)
			{
				if(pCageU[1]->CollideWith(*pStone4[i]))
				{
					pStone4[i]->GetPos().y-=0.8;
					pStone4[i]->SetPos(D2D1::Point2F(pStone4[i]->GetPos().x,pStone4[i]->GetPos().y));
				}
			}			
		}
		if(pCollideFloor->CollideWith(*pCageU[1]))//人带动左边笼子下落
		{
			for(int i=0;i<2;i++)
			{
				pCageU[i]->GetPos().y+=1;
				pCageD[i]->GetPos().y+=1;
				pCageU[i]->SetPos(D2D1::Point2F(pCageU[i]->GetPos().x,pCageU[i]->GetPos().y));
				pCageD[i]->SetPos(D2D1::Point2F(pCageU[i]->GetPos().x,pCageU[i]->GetPos().y));
			}
			pCage[0]->GetPos().y+=1;
			pCage[0]->SetPos(D2D1::Point2F(pCage[0]->GetPos().x,pCage[0]->GetPos().y));
			for(int i=2;i<4;i++)
			{
				pCageU[i]->GetPos().y-=1;
				pCageD[i]->GetPos().y-=1;
				pCageU[i]->SetPos(D2D1::Point2F(pCageU[i]->GetPos().x,pCageU[i]->GetPos().y));
				pCageD[i]->SetPos(D2D1::Point2F(pCageU[i]->GetPos().x,pCageU[i]->GetPos().y));
			}
			pCage[1]->GetPos().y-=1;
			pCage[1]->SetPos(D2D1::Point2F(pCage[1]->GetPos().x,pCage[1]->GetPos().y));
			if(pCageU[3]->CollideWith(*pCar))
			{
				pCar->GetPos().y-=1;
				pCar->SetPos(D2D1::Point2F(pCar->GetPos().x,pCar->GetPos().y));
			}			
		}
		if(pCollideFloor->CollideWith(*pCageU[3]))//人带动右边笼子下落
		{
			if(pCageD[3]->CollideWith(*pCar))
			{
				break;
			}
			for(int i=2;i<4;i++)
			{
				pCageU[i]->GetPos().y+=1;
				pCageD[i]->GetPos().y+=1;
				pCageU[i]->SetPos(D2D1::Point2F(pCageU[i]->GetPos().x,pCageU[i]->GetPos().y));
				pCageD[i]->SetPos(D2D1::Point2F(pCageU[i]->GetPos().x,pCageU[i]->GetPos().y));
			}
			pCage[1]->GetPos().y+=1;
			pCage[1]->SetPos(D2D1::Point2F(pCage[1]->GetPos().x,pCage[1]->GetPos().y));
			for(int i=0;i<2;i++)
			{
				pCageU[i]->GetPos().y-=1;
				pCageD[i]->GetPos().y-=1;
				pCageU[i]->SetPos(D2D1::Point2F(pCageU[i]->GetPos().x,pCageU[i]->GetPos().y));
				pCageD[i]->SetPos(D2D1::Point2F(pCageU[i]->GetPos().x,pCageU[i]->GetPos().y));
			}
			pCage[0]->GetPos().y-=1;
			pCage[0]->SetPos(D2D1::Point2F(pCage[0]->GetPos().x,pCage[0]->GetPos().y));
			for(int i=0;i<2;i++)
			{
				if(pCageU[1]->CollideWith(*pStone4[i]))
				{
					pStone4[i]->GetPos().y-=1;
					pStone4[i]->SetPos(D2D1::Point2F(pStone4[i]->GetPos().x,pStone4[i]->GetPos().y));
				}
			}			
		}
		for(int i=0;i<2;i++)//人推动石头
		{
			if(pCollide->CollideWith(*pStone4[i]))
			{
				if(pStone4[i]->CollideWith(*pRWall4[0])||pStone4[i]->CollideWith(*pLWall4[0]))
				{break;}
				this->Push(pCollide,pStone4[i]);
			}
		}
		if(pStone4[0]->CollideWith(*pStone4[1]))//石头推动石头
		{
			pStone4[1]->SetPos(D2D1::Point2F(pStone4[0]->GetPos().x+pStone4[0]->GetWidth()/2-30,pStone4[0]->GetPos().y));
		}
		if(pCollide->CollideWith(*pCar))
		{
			if(pCar->CollideWith(*pRWall4[0])||pCar->CollideWith(*pLWall4[0]))
			{break;}
			this->PushCar(pCollide,pCar);
		}
		for(int i=0;i<2;i++)//鲨鱼推动石头
		{
			if(pShark4->CollideWith(*pStone4[i]))
			{
				pStone4[i]->GetPos().x-=10;
				pStone4[i]->SetPos(D2D1::Point2F(pStone4[i]->GetPos().x,pStone4[i]->GetPos().y));
			}
		}
		if(pCollideWall->CollideWith(*pBackDoor3))
		{
			this->SetGSVisible(GameScene4,false);
			this->SetGSVisible(GameScene3,true);
			gsState=GameScene3;
			target.x=224;
			target.y=488;
		}
		break;
	case GameScene5:
		if(pFan[0]->IsPlaying()&&pCollide->GetPos().x>pFan[0]->GetPos().x+15&&pCollide->GetPos().x<pFan[0]->GetPos().x+95)//被风扇1吹起
		{
			if((pHeroSwim->GetPos().y-pHeroSwim->GetHeight()/2)<this->rectClient.top)
			{
				return;
			}
			target.y-=1.5;
		}
		if(pFan[1]->IsPlaying()&&pCollide->GetPos().x>pFan[1]->GetPos().x+15&&pCollide->GetPos().x<pFan[1]->GetPos().x+95)//被风扇2吹起
		{
			if((pHeroSwim->GetPos().y-pHeroSwim->GetHeight()/2)<this->rectClient.top)
			{
				return;
			}
			target.y-=1.5;
		}
		if(pCollide->CollideWith(*pWaterBox))//推防水箱子
		{
			this->PushWBox(pCollide,pWaterBox);
		}
		if(pWaterBox->GetPos().x<725)//吹动防水箱子向上移动
		{
			if(pWaterBox->GetPos().y<110)
			{
				pWaterBox->SetPos(D2D1::Point2F(pWaterBox->GetPos().x,pWaterBox->GetPos().y+25));
			}
			pWaterBox->GetPos().y--;
			pWaterBox->SetPos(pWaterBox->GetPos());
		}
		if(pWaterBox->GetPos().x>760&&pWaterBox->CollideWith(*pShell[0]))//防水箱子被蚌咬开
		{
			pShell[0]->SetVisible(false);
			pShell[1]->SetVisible(true);
			pWaterBox->GetPos().y-=500;
			pWaterBox->SetPos(pWaterBox->GetPos());
			pWaterBox->SetVisible(false);
		}
		if(!pWaterBox->IsVisible()&&pShell[1]->IsVisible())//蚌打开显示操作杆
		{
			if(pPole2->GetPos().y==170)
			{
				pPole2->SetVisible(true);
				pShell[1]->SetVisible(false);
				pShell[0]->SetVisible(true);
			}
			else if(pPole2->GetPos().y<170)
			{
				pPole2->GetPos().y++;
				pPole2->SetPos(pPole2->GetPos());
			}
		}
		if(pPole2->IsVisible()&&pCollide->CollideWith(*pPole2)&pCollide->CollideWith(*pShell[0]))//拿到操作杆
		{
			pPole2->GetPos().y-=400;
			pPole2->SetPos(pPole2->GetPos());
			pPole2->SetVisible(false);
			pText5[2]->SetVisible(true);
		}
		if(pCollide->GetPos().x<pPole1->GetPos().x&&pCollide->CollideWith(*pPole1))//开电门
		{
			pPole1->SetRotationAngle(30);
			OPDoor5=1;
		}
		else if(pCollide->GetPos().x>pPole1->GetPos().x&&pCollide->CollideWith(*pPole1))//关电门
		{
			pPole1->SetRotationAngle(-30);
			OPDoor5=0;
		}
		if(pElectric[4]->IsVisible()&&OPDoor5==1&&pDoor5->GetPos().y<410)//电门上升与下落
		{
			pDoor5->GetPos().y++;
			pDoor5->SetPos(pDoor5->GetPos());
		}
		else if(pElectric[4]->IsVisible()&&OPDoor5==0&&pDoor5->GetPos().y>300)
		{
			pDoor5->GetPos().y--;
			pDoor5->SetPos(pDoor5->GetPos());
		}
		if(pCollide->GetPos().x<pPole2->GetPos().x&&pCollide->CollideWith(*pPole2)&&pPole2->GetPos().x<300)//操控左边操作杆
		{
			pPole2->SetRotationAngle(-30);
			IsLFElectric=1;
		}
		if(pCollide->GetPos().x>pPole2->GetPos().x&&pCollide->CollideWith(*pPole2)&&pPole2->GetPos().x<300)
		{
			pPole2->SetRotationAngle(30);
			IsLFElectric=0;
		}
		if(IsLFElectric==0)//拨片连接电线
		{
			pPole2->SetRotationAngle(30);
			pFan[0]->Stop();
			pFan[1]->Stop();
			pFan[2]->Resume();
			pElectric[0]->SetVisible(false);
			pElectric[1]->SetVisible(true);
			pElectric[2]->SetVisible(false);
			pPlectrum[0]->SetVisible(false);
			pPlectrum[1]->SetVisible(true);
		}
		else if(IsLFElectric==1)
		{
			pPole2->SetRotationAngle(0);
			pFan[0]->Resume();
			pFan[1]->Resume();
			pFan[2]->Stop();
			pElectric[0]->SetVisible(true);
			pElectric[1]->SetVisible(false);
			pElectric[2]->SetVisible(true);
			pPlectrum[0]->SetVisible(true);
			pPlectrum[1]->SetVisible(false);
		}
		if(pFan[2]->IsPlaying())//把鱼和头盖骨像右吹
		{
			pFish[0]->GetPos().x+=0.5;
			pFish[0]->SetPos(pFish[0]->GetPos());
			pHead->GetPos().x+=0.5;
			pHead->SetPos(pHead->GetPos());
		}
		if(pFish[0]->GetPos().x>390&&pFish[0]->CollideWith(*pElectric[3]))//鱼的电接通电线
		{
			pElectric[3]->SetVisible(true);
			pElectric[4]->SetVisible(true);
			pFan[3]->Resume();
		}
		else if(pFish[0]->GetPos().x<390&&!pFish[0]->CollideWith(*pElectric[3]))
		{
			pElectric[3]->SetVisible(false);
			pElectric[4]->SetVisible(false);
			pFan[3]->Stop();
		}
		if(pFan[3]->IsPlaying())//把鱼和头盖骨往左吹
		{
			if(!pFish[0]->CollideWith(*pDoor5))
			{
				pFish[0]->GetPos().x-=0.5;
				pFish[0]->SetPos(pFish[0]->GetPos());
			}
			if(pHead->GetPos().x>140)
			{
				pHead->GetPos().x-=0.5;
				pHead->SetPos(pHead->GetPos());
			}
		}
		if(pFan[0]->IsPlaying()&&pHead->GetPos().x>pFan[0]->GetPos().x&&pHead->GetPos().x<pFan[0]->GetPos().x+90)//把头盖骨往上吹
		{
			if(pHead->GetPos().y>rectClient.top+20)
			{
				pHead->GetPos().y-=1;
				pHead->SetPos(pHead->GetPos());
			}	
		}
		if(pText5Chunk[0]->CollideWith(*pCollide))
		{
			pText5[1]->SetVisible(true);
			pText5Chunk[0]->GetPos().y+=1000;
			pText5Chunk[0]->SetPos(pText5Chunk[0]->GetPos());
		}
		if(pText5Chunk[1]->CollideWith(*pCollideFloor))
		{
			pText5[3]->SetVisible(true);
			pText5Chunk[1]->GetPos().y-=1000;
			pText5Chunk[1]->SetPos(pText5Chunk[1]->GetPos());
		}
		if(pHead->IsVisible()&&pHead->CollideWith(*pCollide))
		{
			pText5[4]->SetVisible(true);
			pHead->SetVisible(false);
		}
		if(!pHead->IsVisible()&&!pText5[4]->IsVisible())
		{
			this->SetGSVisible(GameScene5,false);
			target.x-=1000;
			gsState=GameScene6;
		}
		break;
	case GameScene6:
		if(!pBg5->IsVisible())
		{
			if(pBg6->GetPos().y>-700)
			{
				pBg6->GetPos().y--;
				pBg6->SetPos(pBg6->GetPos());
			}
		}
		break;
	case GameOver:
		break;
	}

}

void CGameScene::MoveLeft()
{
	boolHeroLF = 0;
	switch(gsState)
	{
	case GameScene1:
		for(int i=0;i<6;i++)
		{
			if(pCollideWall->CollideWith(*pRWall[i]))
			{
				return;
			}
		}
		break;
	case GameScene2:
		break;
	case GameScene4:
		for(int i=0;i<2;i++)
		{
			if(pCollideWall->CollideWith(*pRWall4[i]))
			{
				return;
			}
		}
		break;
		case GameScene5:
		for(int i=0;i<4;i++)
		{
			if(pCollideWall->CollideWith(*pRWall5[i]))
			{
				return;
			}
		}
		break;
	}

	if((pHeroSwim->GetPos().x-pHeroSwim->GetWidth()/2)<this->rectClient.left)
	{
		return;
	}
	pHeroSwim->SetScaleFactor(-0.9,0.9);
	pHeroWalk->SetScaleFactor(-0.9,0.9);
	pHeroSwim->SetRotationAngle(0.0f);
	target.x-=2;
	pHeroSwim->SetPos(target);
	pHeroWalk->SetPos(target);
	pCollideFloor->SetPos(target);
	pCollideWall->SetPos(target);
	pCollide->SetPos(target);
}

void CGameScene::MoveRight()
{
	boolHeroLF = 1;
	switch(gsState)
	{
	case GameScene1:
		for(int i=0;i<3;i++)
		{
			if(pCollideWall->CollideWith(*pLWall[i]))
			{
				return;
			}
		}
		break;
	case GameScene2:
		break;
	case GameScene4:
		for(int i=0;i<2;i++)
		{
			if(pCollideWall->CollideWith(*pLWall4[i]))
			{
				return;
			}
		}
		break;
		case GameScene5:
		for(int i=0;i<4;i++)
		{
			if(pCollideWall->CollideWith(*pLWall5[i]))
			{
				return;
			}
		}
		break;
	}

	if((pHeroSwim->GetPos().x+pHeroSwim->GetWidth()/2)>this->rectClient.right )
	{
		return;
	}
	pHeroSwim->SetScaleFactor(0.9,0.9);
	pHeroWalk->SetScaleFactor(0.9,0.9);
	target.x+=2;
	pHeroSwim->SetPos(target);
	pHeroWalk->SetPos(target);
	pCollideFloor->SetPos(target);
	pCollideWall->SetPos(target);
	pCollide->SetPos(target);
}

void CGameScene::MoveUp()
{
	switch(gsState)
	{
	case GameScene1:
		if(pCollideFloor->CollideWith(*pRWall[0]))
		{
			return;
		}
		for(int i=0;i<3;i++)
		{
			if(pCollideFloor->CollideWith(*pDFloor[i]))
			{
				return;
			}
		}
		break;
	case GameScene2:
		for(int i=0;i<5;i++)
		{
			if(pCollideFloor->CollideWith(*pDFloor2[i]))
			{
				return;
			}
		}
		break;
	case GameScene4:
		for(int i=0;i<4;i++)
		{
			if(pCollideFloor->CollideWith(*pCageD[i]))
			{
				return;
			}
		}
		break;
	case GameScene5:
		for(int i=0;i<2;i++)
		{
			if(pCollideFloor->CollideWith(*pDFloor5[i]))
			{
				return;
			}
		}

		break;
	}

	if((pHeroSwim->GetPos().y-pHeroSwim->GetHeight()/2)<this->rectClient.top)
	{
		return;
	}
	target.y-=3;
	pHeroSwim->SetRotationAngle(0.0f);
	pHeroSwim->SetPos(target);
	pHeroWalk->SetPos(target);
	pCollideFloor->SetPos(target);
	pCollideWall->SetPos(target);
	pCollide->SetPos(target);
}

void CGameScene::MoveDown()
{
	switch(gsState)
	{
	case GameScene1:
		for(int i=0;i<8;i++)
		{
			if(pCollideFloor->CollideWith(*pFloor[i]))
			{
				return;
			}
		}
		break;
	case GameScene2:
		for(int i=0;i<7;i++)
		{
			if(pCollideFloor->CollideWith(*pFloor2[i]))
			{
				return;
			}
		}
	case GameScene4:
		for(int i=0;i<3;i++)
		{
			if(pCollideFloor->CollideWith(*pFloor4[i]))
			{
				return;
			}
		}
		for(int i=0;i<4;i++)
		{
			if(pCollideFloor->CollideWith(*pCageU[i]))
			{
				return;
			}
		}
		break;
			case GameScene5:
		for(int i=0;i<5;i++)
		{
			if(pCollideFloor->CollideWith(*pFloor5[i]))
			{
				return;
			}
		}
		break;
	}

	if((pHeroSwim->GetPos().y+pHeroSwim->GetHeight()/2)>this->rectClient.bottom)
	{
		return;
	}
	target.y++;
	if(boolHeroLF==0)
	{
		pHeroSwim->SetRotationAngle(-45.0f);
	}
	if(boolHeroLF==1)
	{
		pHeroSwim->SetRotationAngle(45.0f);
	}
	pHeroSwim->SetPos(target);
	pHeroWalk->SetPos(target);
	pCollideFloor->SetPos(target);
	pCollideWall->SetPos(target);
	pCollide->SetPos(target);
}

void CGameScene::HeroDown()
{
	switch(gsState)
	{
	case GameScene1:
		for(int i=0;i<8;i++)
		{
			if(pCollideFloor->CollideWith(*pFloor[i]))
			{
				pHeroSwim->SetVisible(false);
				pHeroWalk->SetVisible(true);
				return;
			}
		}
		break;
	case GameScene2:
		for(int i=0;i<7;i++)
		{
			if(pCollideFloor->CollideWith(*pFloor2[i]))
			{
				pHeroSwim->SetVisible(false);
				pHeroWalk->SetVisible(true);
				return;
			}
		}
		break;
	case GameScene4:
		for(int i=0;i<3;i++)
		{
			if(pCollideFloor->CollideWith(*pFloor4[i]))
			{
				pHeroSwim->SetVisible(false);
				pHeroWalk->SetVisible(true);
				return;
			}
		}
		for(int i=0;i<4;i++)
		{
			if(pCollideFloor->CollideWith(*pCageU[i]))
			{
				pHeroSwim->SetVisible(false);
				pHeroWalk->SetVisible(true);
				return;
			}
		}
		break;
			case GameScene5:
		for(int i=0;i<5;i++)
		{
			if(pCollideFloor->CollideWith(*pFloor5[i]))
			{
				pHeroSwim->SetVisible(false);
				pHeroWalk->SetVisible(true);
				return;
			}
		}
		break;
	}

	if((pHeroSwim->GetPos().y+pHeroSwim->GetHeight()/2)>this->rectClient.bottom)
	{
		pHeroSwim->SetVisible(false);
		pHeroWalk->SetVisible(true);
		return;
	}
	else
	{
		pHeroSwim->SetVisible(true);
		pHeroWalk->SetVisible(false);
	}
	target.y+=1;
	pHeroSwim->SetPos(target);
	pHeroWalk->SetPos(target);
	pCollideFloor->SetPos(target);
	pCollideWall->SetPos(target);
	pCollide->SetPos(target);
}

bool CGameScene::IsTextVisible()
{
	bool bVal=false;
	for(int i=0;i<4;i++)
	{
		if(pText[i]->IsVisible())
		{
			whichText=i;
			bVal=true;
			break;
		}
		if(pText4[i]->IsVisible())
		{
			whichText=i;
			bVal=true;
			break;
		}
	}
	for(int i=0;i<3;i++)
	{
		if(pText2[i]->IsVisible())
		{
			whichText=i;
			bVal=true;
			break;
		}
	}
	for(int i=0;i<4;i++)
	{
		if(pText3[i]->IsVisible())
		{
			whichText=i;
			bVal=true;
			break;
		}
	}
	for(int i=0;i<5;i++)
	{
		if(pText5[i]->IsVisible())
		{
			whichText=i;
			bVal=true;
			break;
		}
	}
	return bVal;
}

void CGameScene::HideText()
{
	switch(gsState)
	{
	case GameScene1:
		pText[whichText]->SetVisible(false);
		break;
	case GameScene2:
		pText2[whichText]->SetVisible(false);
		break;
	case GameScene3:
		pText3[whichText]->SetVisible(false);
		break;
	case GameScene4:
		pText4[whichText]->SetVisible(false);
		break;
	case GameScene5:
		pText5[whichText]->SetVisible(false);
		break;
	}
}

bool CGameScene::IsCartoonVisible()
{
	bool bVal=false;
	for(int i=0;i<3;i++)
	{
		if(pCartoonSprite[i]->IsVisible())
		{
			whichCartoon=i;
			bVal=true;
			break;
		}
	}
	return bVal;
}

void CGameScene::HideCartoon()
{
	pCartoonSprite[whichCartoon]->SetVisible(false);
}

void CGameScene::SharkMove(CAnimationSprite *tMonster,int w)
{
	static int monsterX=tMonster->GetPos().x,monsterY=tMonster->GetPos().y;

	if(pBait->GetPos().y>pRWall[5]->GetPos().x&&pBait->IsVisible())
	{
		if(tMonster->GetScaleX()>0)
		{
			static float sx0=tMonster->GetScaleX();
			tMonster->SetScaleFactor(-sx0,tMonster->GetScaleY());
			xSharkSpeed*=-1;
		}
		if(tMonster->GetPos().x-40<pBait->GetPos().x)
		{
			return;
		}
		tMonster->SetPos(D2D1::Point2F(tMonster->GetPos().x+xSharkSpeed,tMonster->GetPos().y));
	}
	else
	{
		tMonster->SetPos(D2D1::Point2F(tMonster->GetPos().x+xSharkSpeed,tMonster->GetPos().y));
		if(tMonster->GetPos().x==monsterX+w)
		{
			static float sx1=tMonster->GetScaleX();
			tMonster->SetScaleFactor(-sx1,tMonster->GetScaleY());
		}
		if(tMonster->GetPos().x==monsterX)
		{
			static float sx2=tMonster->GetScaleX();
			tMonster->SetScaleFactor(-sx2,tMonster->GetScaleY());
		}
		if(tMonster->GetPos().x>monsterX+w||tMonster->GetPos().x<monsterX)
		{
			xSharkSpeed*=-1;
		}
	}

}

void CGameScene::Shark4Move(CAnimationSprite *tMonster,int w)
{
	static int monsterX=tMonster->GetPos().x,monsterY=tMonster->GetPos().y;

	if(pBait->GetPos().y>pRWall[5]->GetPos().x&&pBait->IsVisible())
	{
		if(tMonster->GetScaleX()>0)
		{
			static float sx0=tMonster->GetScaleX();
			tMonster->SetScaleFactor(-sx0,tMonster->GetScaleY());
			xShark4Speed*=-1;
		}
		if(tMonster->GetPos().x-40<pBait->GetPos().x)
		{
			return;
		}
		tMonster->SetPos(D2D1::Point2F(tMonster->GetPos().x+xShark4Speed,tMonster->GetPos().y));
	}
	else
	{
		tMonster->SetPos(D2D1::Point2F(tMonster->GetPos().x+xShark4Speed,tMonster->GetPos().y));
		if(tMonster->GetPos().x==monsterX+w)
		{
			static float sx1=tMonster->GetScaleX();
			tMonster->SetScaleFactor(-sx1,tMonster->GetScaleY());
		}
		if(tMonster->GetPos().x==monsterX)
		{
			static float sx2=tMonster->GetScaleX();
			tMonster->SetScaleFactor(-sx2,tMonster->GetScaleY());
		}
		if(tMonster->GetPos().x>monsterX+w||tMonster->GetPos().x<monsterX)
		{
			xShark4Speed*=-1;
		}
	}

}

void CGameScene::OctopusMove(CAnimationSprite *tMonster,int w,int h)
{
	static int monsterX=tMonster->GetPos().x,monsterY=tMonster->GetPos().y;
	tMonster->SetPos(D2D1::Point2F(tMonster->GetPos().x+xOctopusSpeed,tMonster->GetPos().y+yOctopusSpeed));
	if(tMonster->GetPos().x==monsterX+w)
	{
		static float sx1=tMonster->GetScaleX();
		tMonster->SetScaleFactor(-sx1,tMonster->GetScaleY());
	}
	if(tMonster->GetPos().x==monsterX)
	{
		static float sx2=tMonster->GetScaleX();
		tMonster->SetScaleFactor(-sx2,tMonster->GetScaleY());
	}
	if(tMonster->GetPos().x>monsterX+w||tMonster->GetPos().x<monsterX)
	{
		xOctopusSpeed*=-1;
	}
	if(tMonster->GetPos().y>monsterY+h||tMonster->GetPos().y<monsterY)
	{
		yOctopusSpeed*=-1;
	}
}

void CGameScene::ControlMonsterMove()
{
	this->SharkMove(pShark,60);
	this->OctopusMove(pOctopus,40,60);
	this->Shark4Move(pShark4,300);
}

void CGameScene::PutDown()
{
	switch(gsState)
	{
	case GameScene1:
		if(!pBait->IsVisible()/*&&pCollide->CollideWith(*pBait)*/)
		{
			pBait->SetPos(D2D1::Point2F(pCollide->GetPos().x+50,pCollide->GetPos().y+15));
			pBait->SetVisible(true);
		}
		break;
	case GameScene2:
		if(!pCrowbar->IsVisible())
		{	
			pCrowbar->SetPos(D2D1::Point2F(pCollide->GetPos().x-80,pCollide->GetPos().y));
			pCrowbar->SetRotationAngle(90.0f);
			pCrowbar->SetVisible(true);
		}
		break;
	case GameScene4:
		if(!pTorpedo4->IsVisible()&&pCollideFloor->CollideWith(*pFloor4[1]))
		{
			pTorpedo4->SetPos(D2D1::Point2F(pCollide->GetPos().x-10,pCollide->GetPos().y-30));
			pTorpedo4->SetVisible(true);
		}
		break;
	case GameScene5:
		if(!pPole2->IsVisible()&&pCollideFloor->CollideWith(*pFloor5[0]))
		{
			pPole2->SetVisible(true);
			pPole2->SetPos(D2D1::Point2F(70,175));
		}
		break;
	}

}

bool CGameScene::IsGetProp()
{
	if(!pOctopus->IsVisible()&&!pBait->IsVisible())
	{
		return true;
	}
	else
	{
		return false;
	}
	if(!pCrowbar->IsVisible())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CGameScene::Push(CSprite *pPush,CSprite *pBePush)
{
	if(pBePush->IsVisible()&&pPush->CollideWith(*pBePush))
	{
		if((pBePush->GetPos().x-pBePush->GetWidth()/2)<this->rectClient.left)
		{
			return;
		}
		if((pBePush->GetPos().x+pBePush->GetWidth()/2)>this->rectClient.right )
		{
			return;
		}
		if(boolHeroLF==1)
		{
			pBePush->SetPos(D2D1::Point2F(pPush->GetPos().x+pBePush->GetWidth()/3,pBePush->GetPos().y));
		}
		if(boolHeroLF==0)
		{
			pBePush->SetPos(D2D1::Point2F(pPush->GetPos().x-pBePush->GetWidth()/3,pBePush->GetPos().y));
		}
	}
}

void CGameScene::PushBox(CSprite *pPush,CSprite *pBePush)
{
	if(pBePush->IsVisible()&&pPush->CollideWith(*pBePush))
	{
		if((pBePush->GetPos().x-pBePush->GetWidth()/2)<this->rectClient.left)
		{
			return;
		}
		if((pBePush->GetPos().x+pBePush->GetWidth()/2)>this->rectClient.right )
		{
			return;
		}
		if(boolHeroLF==1)
		{
			pBePush->SetPos(D2D1::Point2F(pPush->GetPos().x+pBePush->GetWidth()/2+10,pBePush->GetPos().y));
		}
		if(boolHeroLF==0)
		{
			pBePush->SetPos(D2D1::Point2F(pPush->GetPos().x-pBePush->GetWidth()/2-10,pBePush->GetPos().y));
		}
	}
}

void CGameScene::PushCar(CSprite *pPush,CSprite *pBePush)
{
	if(pBePush->IsVisible()&&pPush->CollideWith(*pBePush))
	{
		if((pBePush->GetPos().x-pBePush->GetWidth()/2)<this->rectClient.left)
		{
			return;
		}
		if((pBePush->GetPos().x+pBePush->GetWidth()/2)>this->rectClient.right )
		{
			return;
		}
		if(boolHeroLF==1)
		{
			pBePush->SetPos(D2D1::Point2F(pPush->GetPos().x+80,pBePush->GetPos().y));
		}
		if(boolHeroLF==0)
		{
			pBePush->SetPos(D2D1::Point2F(pPush->GetPos().x-80,pBePush->GetPos().y));
		}
	}
}

void CGameScene::PushWBox(CSprite *pPush,CSprite *pBePush)
{
	if(pBePush->IsVisible()&&pPush->CollideWith(*pBePush))
	{
		if((pBePush->GetPos().x-pBePush->GetWidth()/2)<this->rectClient.left)
		{
			return;
		}
		if((pBePush->GetPos().x+pBePush->GetWidth()/2)>this->rectClient.right )
		{
			return;
		}
		if(boolHeroLF==1)
		{
			pBePush->SetPos(D2D1::Point2F(pPush->GetPos().x+15,pBePush->GetPos().y));
		}
		if(boolHeroLF==0)
		{
			pBePush->SetPos(D2D1::Point2F(pPush->GetPos().x-55,pBePush->GetPos().y));
		}
	}
}

void CGameScene::SetGSVisible(GSState State,bool bVal)
{
	switch(State)
	{
	case Entrance:
		pEntranceBg->SetVisible(bVal);
		pEntranceBg2->SetVisible(bVal);
		break;
	case GameScene1:
		pBg1->SetVisible(bVal);
		pShark->SetVisible(bVal);
		pOctopus->SetVisible(bVal);
		pStone->SetVisible(bVal);
		pCorpse->SetVisible(bVal);
		pDoor->SetVisible(bVal);
		pBait->SetVisible(bVal);
		pTorpedo->SetVisible(bVal);
		pKey->SetVisible(bVal);
		break;
	case GameScene2:
		pBg2->SetVisible(bVal);
		pBox->SetVisible(bVal);
		pDoor2->SetVisible(bVal);
		pPlank->SetVisible(bVal);
		pBar->SetVisible(bVal);
		pCrowbar->SetVisible(bVal);
		pCorpse2->SetVisible(bVal);
		pEnter->SetVisible(bVal);
		pBackEnter1->SetVisible(bVal);
		break;
	case GameScene3:
		pBg3->SetVisible(bVal);
		pCorpse3->SetVisible(bVal);
		pBook->SetVisible(bVal);
		pBackEnter2->SetVisible(bVal);
		break;
	case GameScene4:
		pBg4->SetVisible(bVal);
		for(int i=0;i<3;i++)
		{pChain[i]->SetVisible(bVal);}
		for(int i=0;i<2;i++)
		{pCage[i]->SetVisible(bVal);
		pStone4[i]->SetVisible(bVal);}
		pCar->SetVisible(bVal);
		pShark4->SetVisible(bVal);
		pDoor4->SetVisible(bVal);
		pBackEnter3->SetVisible(bVal);
		break;
	case GameScene5:
		pBg5->SetVisible(bVal);
		pDoor5->SetVisible(bVal);
		pPole1->SetVisible(bVal);
		pPole2->SetVisible(bVal);
		for(int i=0;i<5;i++)
		{pElectric[i]->SetVisible(bVal);}
		for(int i=0;i<2;i++)
		{
			pShell[i]->SetVisible(bVal);
			pFish[i]->SetVisible(bVal);
			pPlectrum[i]->SetVisible(bVal);
		}
		for(int i=0;i<4;i++)
		{
			pFan[i]->SetVisible(bVal);
		}
		//target.x-=1000;
		break;
	case GameScene6:
		pBg6->SetVisible(bVal);
		break;
	}
}

bool CGameScene::HandleMouseUp(WPARAM wParam,LPARAM lParam)
{
	bool bRet = false;
	for(int i=0;i<4;i++)
	{
		if (pButtons[i]->HandleMouseUp(wParam,lParam))
		{
			bRet = true;
			if (pButtons[i]->btnState == BtnUp)
			{
				buttonState=i;
				break;
			}
		}
	}
	return bRet;
}

bool CGameScene::HandleMouseDown(WPARAM wParam,LPARAM lParam)
{
	bool bRet = false;
	for(int i=0;i<4;i++)
	{
		if (pButtons[i]->HandleMouseDown(wParam,lParam))
		{
			bRet = true;
		}
	}
	return bRet;
}

int CGameScene::GetButtonState()
{
	return buttonState;
}

void CGameScene::setButtonVisible(bool bVal)
{
	pBtBg->SetVisible(bVal);
	pButtons[1]->SetVisible(bVal);
	pButtons[2]->SetVisible(bVal);
}

void CGameScene::setOverVisible(bool bVal)
{
	pOverBg->SetVisible(bVal);
	pButtons[1]->SetVisible(bVal);
	pButtons[2]->SetVisible(bVal);
	pButtons[3]->SetVisible(bVal);
}

WCHAR* CGameScene::ReturnText()
{
	WCHAR* tText = new WCHAR[50];
	/*switch(gsState)
	{
	case GameScene1:	
		wcscpy(tText, Text[whichText]);
		break;
	}*/
	wcscpy(tText, Text[whichText]);
	return tText;
}