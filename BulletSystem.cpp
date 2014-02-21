#include "stdafx.h"

// 构造函数
BulletSystem::BulletSystem(GameWorld *pgw)
{
	pGameWorld=pgw;
}

// 释构函数
BulletSystem::~BulletSystem()
{
	list<Bullet*>::iterator p, pend;;
	p=BulletList.begin();
	pend=BulletList.end();
	while(p!=pend)
	{
		delete *p;
		p++;
	}
}

// 新增子弹
void BulletSystem::FireHappened(Bullet::BULLET_TYPE BulletType, int x, int y, double sprite_vx, double sprite_vy)
{
	int i;
	Bullet *pNewBullet;

	switch(BulletType)
	{
	case Bullet::PLAYER_BULLET_FIRE:
		for(i=0; i<4; i++)
		{
			pNewBullet=new PlayerBullet_Fire(pGameWorld, x-12+8*i, y, sprite_vx, sprite_vy);
			BulletList.push_back(pNewBullet);
		}
		break;
	case Bullet::PLAYER_BULLET_MISSILE:
		for(i=0; i<6; i++)
		{
			pNewBullet=new PlayerBullet_Missile(pGameWorld, x-10+rand()%21, y-10+rand()%21, sprite_vx, sprite_vy, rand()%181);
			BulletList.push_back(pNewBullet);
		}
		break;
	case Bullet::PLAYER_BULLET_ROUND_BULLET:
		pNewBullet=new PlayerBullet_RoundBullet(pGameWorld, x, y, sprite_vx, sprite_vy, 20);
		BulletList.push_back(pNewBullet);
		pNewBullet=new PlayerBullet_RoundBullet(pGameWorld, x, y, sprite_vx, sprite_vy, 50);
		BulletList.push_back(pNewBullet);
		pNewBullet=new PlayerBullet_RoundBullet(pGameWorld, x, y, sprite_vx, sprite_vy, 70);
		BulletList.push_back(pNewBullet);
		pNewBullet=new PlayerBullet_RoundBullet(pGameWorld, x, y, sprite_vx, sprite_vy, 80);
		BulletList.push_back(pNewBullet);
		pNewBullet=new PlayerBullet_RoundBullet(pGameWorld, x, y, sprite_vx, sprite_vy, 90);
		BulletList.push_back(pNewBullet);
		pNewBullet=new PlayerBullet_RoundBullet(pGameWorld, x, y, sprite_vx, sprite_vy, 100);
		BulletList.push_back(pNewBullet);
		pNewBullet=new PlayerBullet_RoundBullet(pGameWorld, x, y, sprite_vx, sprite_vy, 110);
		BulletList.push_back(pNewBullet);
		pNewBullet=new PlayerBullet_RoundBullet(pGameWorld, x, y, sprite_vx, sprite_vy, 130);
		BulletList.push_back(pNewBullet);
		pNewBullet=new PlayerBullet_RoundBullet(pGameWorld, x, y, sprite_vx, sprite_vy, 160);
		BulletList.push_back(pNewBullet);
		break;
	case Bullet::ENERMY_BULLET_1:
		for(i=0; i<5; i++)
		{
			pNewBullet=new EnermyBullet1(pGameWorld, x+8*(i-2), y, sprite_vx, sprite_vy, 270+20*(i-2));
			BulletList.push_back(pNewBullet);
		}
		break;
	case Bullet::ENERMY_BULLET_2:
		pNewBullet=new EnermyBullet2(pGameWorld, x-10, y, sprite_vx, sprite_vy, 0);
		BulletList.push_back(pNewBullet);
		pNewBullet=new EnermyBullet2(pGameWorld, x+10, y, sprite_vx, sprite_vy, 180);
		BulletList.push_back(pNewBullet);
		break;
	case Bullet::ENERMY_BULLET_3:
		pNewBullet=new EnermyBullet3(pGameWorld, x-5, y, sprite_vx, sprite_vy, 225);
		BulletList.push_back(pNewBullet);
		pNewBullet=new EnermyBullet3(pGameWorld, x+5, y, sprite_vx, sprite_vy, 315);
		BulletList.push_back(pNewBullet);
		break;

	}

}

// 返回第一个子弹对象
Bullet* BulletSystem::GetFirstBullet()
{
	BulletIndex=-1;
	BulletCount=BulletList.size();
	if(BulletCount==0)
		return NULL;

	pCurElement=BulletList.end();
	return GetNextBullet();
}

// 返回下一个子弹对象
Bullet* BulletSystem::GetNextBullet()
{
	BulletIndex++;
	pCurElement++;
	while( ( BulletIndex < BulletCount ) && ( ( *pCurElement )->Used == false ) )
	{
		delete *pCurElement;
		BulletCount--;
		pCurElement=BulletList.erase(pCurElement);
	}

	if(pCurElement==BulletList.end())
		return NULL;
	else
		return *pCurElement;
}

void BulletSystem::Update()
{
	Bullet *pBullet=GetFirstBullet();
	while(pBullet)
	{
		pBullet->Update();
		pBullet=GetNextBullet();
	}
}
