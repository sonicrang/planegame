#include "stdafx.h"
#include <iostream>
#include "mmsystem.h"
#include "resource.h"
#pragma comment(lib,"winmm.lib")


using namespace std;// ��������
const int GameWorld::Width=640;
const int GameWorld::Height=480;
const int GameWorld::MsPerFrame=20;
const double GameWorld::PI=3.1415926535897932;

// ���캯��
GameWorld::GameWorld(HWND hwnd)
	:GameWindow(hwnd)
{
    


	Time=GetTickCount();
       
	ZeroMemory(&FPS, sizeof(FPS));
	FPS.LastTime = Time;
	kFPS = 1.0;

	srand(time(0));
	BufKey=0;
	CurKey=0;
	Level = 1;

	pScreen				= new Display(this);
	pPlayer				= new Player(this, Width/2, Height/2);
	pPlayerBulletSystem		= new BulletSystem(this);
	pEnermyBulletSystem		= new BulletSystem(this);
	pEnermySystem		= new EnermySystem(this);
	pCollisionSystem	= new CollisionSystem(this);
	
	PlaySound(
    MAKEINTRESOURCE(IDR_WAVE1), 
    GetModuleHandle(NULL),  
    SND_ASYNC|SND_RESOURCE|SND_NODEFAULT|SND_LOOP);
}

// �͹�����
GameWorld::~GameWorld() 
{
	delete pScreen;
}

// ˢ����Ϸ
void GameWorld::Update()
{
	int t=GetTickCount();
	if( t-Time < MsPerFrame )
		return;
	Time=t;
	
	// �Ѷ�����
	if(pPlayer->Score >= Level*300)
	{
		pEnermySystem->AddDifficulty();
		Level++;
	}

	// �����Ļ
	pScreen->Clear();

	pCollisionSystem->Update();
	pEnermyBulletSystem->Update();
	pPlayerBulletSystem->Update();
	pEnermySystem->Update();
	pPlayer->Update();

	UpdateFPS();
	ShowInfomation();
	pScreen->DrawAllToScreen();
}

// ˢ��֡����
void GameWorld::UpdateFPS()
{
	FPS.FrameCount++;
	if( Time-FPS.LastTime >= 1000 )
	{
		FPS.FPS = FPS.FrameCount;
		FPS.FrameCount = 0;
		FPS.LastTime=Time;
		kFPS = (double)1000 / ( MsPerFrame * FPS.FPS );
	}
}
// ��ʾ��Ϣ
void GameWorld::ShowInfomation()
{
	HDC hdc = pScreen->GetOffscreenDC();
	ostringstream info;
    if (pPlayer->Life<=0) {
		MessageBox(NULL,TEXT("you lose!"),TEXT("��ʾ"),MB_OK); 
		cin.get();
		exit(0);
	}
	info << "֡����:" << FPS.FPS <<" (Max:50 " << "k=" << kFPS <<")";
	info << "    ����:" << pPlayer->Life <<"    ����:";
	switch( pPlayer->BulletType )
	{
	case 0:
		info << "������";
		break;
	case 1:
		info << "������";
		break;
	case 2:
		info << "ɢ��ǹ";
		break;
	}
	info << "    ɱ��:" << pPlayer->KillEnermy << "    ����:" << pPlayer->Score; 
	info << "    ����:" << Level;

	SetBkMode(hdc, TRANSPARENT );
	SetTextColor(hdc, RGB(100, 100, 100));
	TextOut(hdc, 7, 7, info.str().c_str(), info.str().length() );
	SetTextColor(hdc, RGB(0, 255, 255));
	TextOut(hdc, 5, 5, info.str().c_str(), info.str().length() );
	SetTextColor(hdc, RGB(0, 0, 0));
}
// �����ӵ�
void GameWorld::EnermyFire(Enermy *pEnermy)
{
	pEnermyBulletSystem->FireHappened(pEnermy->BulletType, pEnermy->GetX()+pEnermy->w/2, pEnermy->GetY()+pEnermy->h/2, pEnermy->dx, pEnermy->dy);	
}

void GameWorld::PlayerFire(Player *pPlayer)
{
	pPlayerBulletSystem->FireHappened(pPlayer->BulletType, pPlayer->GetX()+pPlayer->w/2, pPlayer->GetY()+pPlayer->h/2, pPlayer->dx, pPlayer->dy);	
}

// ����ɫ
void GameWorld::DrawSprite(Sprite *pSprite)
{
	pScreen->DrawToOffscreen(pSprite->GetX(), pSprite->GetY(), pSprite->w, pSprite->h, pSprite->sx, pSprite->sy, false);
}

// KeyDown
void GameWorld::KeyDown(WPARAM KeyCode)
{
	switch(KeyCode)
	{
	case VK_LEFT:
	case VK_RIGHT:
	case VK_UP:
	case VK_DOWN:
		if(KeyCode==CurKey || KeyCode==BufKey) return;		// �ظ��ļ�����Ϣ������
		if(BufKey && CurKey) return;	// ͬʱ��3����������Ƿ����룬����		
		BufKey=CurKey;
		CurKey=KeyCode;

		if( BufKey==VK_LEFT && CurKey==VK_UP || BufKey==VK_UP && CurKey==VK_LEFT )
			pPlayer->Action( Player::GO_LEFT_UP );
		else if( BufKey==VK_LEFT && CurKey==VK_DOWN || BufKey==VK_DOWN && CurKey==VK_LEFT )
			pPlayer->Action( Player::GO_LEFT_DOWN );
		else if( BufKey==VK_RIGHT && CurKey==VK_UP || BufKey==VK_UP && CurKey==VK_RIGHT )
			pPlayer->Action( Player::GO_RIGHT_UP );
		else if( BufKey==VK_RIGHT && CurKey==VK_DOWN || BufKey==VK_DOWN && CurKey==VK_RIGHT )
			pPlayer->Action( Player::GO_RIGHT_DOWN );
		else
			pPlayer->Action( (Player::ACTION) (Player::GO_LEFT + KeyCode - VK_LEFT) );

		break;
	case VK_SPACE:
		pPlayer->Action(Player::START_FIRING);
		break;
	case VK_TAB:
		pPlayer->Action(Player::CHANGE_WEAPON);
		break;
	}
}

// KeyUp
void GameWorld::KeyUp(WPARAM KeyCode)
{
	if(KeyCode==CurKey)
	{
		CurKey=0;
		if(BufKey)
		{
			CurKey=BufKey;
			BufKey=0;
			pPlayer->Action( ( Player::ACTION )( CurKey - VK_LEFT ) );
		}
		else
		{
			pPlayer->Action( Player::STOP_MOVING );
		}
	}
	else if(KeyCode==BufKey)
		BufKey=0;
	else if(KeyCode==VK_SPACE)
		pPlayer->Action(Player::STOP_FIRING);
}

// ���ý�ɫ
void GameWorld::ResetPlayer()
{
	delete pPlayer;
	pPlayer = new Player( this, Width / 2, Height / 2 );
	Level = 1;
	pEnermySystem->ResetDifficulty();
}