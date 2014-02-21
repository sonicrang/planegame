#include "stdafx.h"
#include <iostream>
#include "mmsystem.h"
#include "resource.h"
#pragma comment(lib,"winmm.lib")


using namespace std;// 常数定义
const int GameWorld::Width=640;
const int GameWorld::Height=480;
const int GameWorld::MsPerFrame=20;
const double GameWorld::PI=3.1415926535897932;

// 构造函数
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

// 释构函数
GameWorld::~GameWorld() 
{
	delete pScreen;
}

// 刷新游戏
void GameWorld::Update()
{
	int t=GetTickCount();
	if( t-Time < MsPerFrame )
		return;
	Time=t;
	
	// 难度升级
	if(pPlayer->Score >= Level*300)
	{
		pEnermySystem->AddDifficulty();
		Level++;
	}

	// 清空屏幕
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

// 刷新帧速率
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
// 显示信息
void GameWorld::ShowInfomation()
{
	HDC hdc = pScreen->GetOffscreenDC();
	ostringstream info;
    if (pPlayer->Life<=0) {
		MessageBox(NULL,TEXT("you lose!"),TEXT("提示"),MB_OK); 
		cin.get();
		exit(0);
	}
	info << "帧速率:" << FPS.FPS <<" (Max:50 " << "k=" << kFPS <<")";
	info << "    生命:" << pPlayer->Life <<"    武器:";
	switch( pPlayer->BulletType )
	{
	case 0:
		info << "机关炮";
		break;
	case 1:
		info << "导弹　";
		break;
	case 2:
		info << "散弹枪";
		break;
	}
	info << "    杀敌:" << pPlayer->KillEnermy << "    分数:" << pPlayer->Score; 
	info << "    级数:" << Level;

	SetBkMode(hdc, TRANSPARENT );
	SetTextColor(hdc, RGB(100, 100, 100));
	TextOut(hdc, 7, 7, info.str().c_str(), info.str().length() );
	SetTextColor(hdc, RGB(0, 255, 255));
	TextOut(hdc, 5, 5, info.str().c_str(), info.str().length() );
	SetTextColor(hdc, RGB(0, 0, 0));
}
// 发射子弹
void GameWorld::EnermyFire(Enermy *pEnermy)
{
	pEnermyBulletSystem->FireHappened(pEnermy->BulletType, pEnermy->GetX()+pEnermy->w/2, pEnermy->GetY()+pEnermy->h/2, pEnermy->dx, pEnermy->dy);	
}

void GameWorld::PlayerFire(Player *pPlayer)
{
	pPlayerBulletSystem->FireHappened(pPlayer->BulletType, pPlayer->GetX()+pPlayer->w/2, pPlayer->GetY()+pPlayer->h/2, pPlayer->dx, pPlayer->dy);	
}

// 画角色
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
		if(KeyCode==CurKey || KeyCode==BufKey) return;		// 重复的键盘消息，忽略
		if(BufKey && CurKey) return;	// 同时按3个方向键，非法输入，忽略		
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

// 重置角色
void GameWorld::ResetPlayer()
{
	delete pPlayer;
	pPlayer = new Player( this, Width / 2, Height / 2 );
	Level = 1;
	pEnermySystem->ResetDifficulty();
}