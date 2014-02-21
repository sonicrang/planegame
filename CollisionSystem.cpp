#include "stdafx.h"

CollisionSystem::CollisionSystem(GameWorld *pgw)
{
	pPlayer				= pgw->pPlayer;
	pEnermySystem		= pgw->pEnermySystem;
	pPlayerBulletSystem	= pgw->pPlayerBulletSystem;
	pEnermyBulletSystem	= pgw->pEnermyBulletSystem;
}


void CollisionSystem::Update()
{

	Enermy	*pEnermy;
	Bullet	*pBullet;
	
	// 遍历敌机
	pEnermy = pEnermySystem->GetFirstEnermy();
	while(pEnermy)
	{
		// 检查敌机与玩家战机的碰撞
		CheckForCollision(pPlayer, pEnermy);

		// 检查敌机与玩家子弹的碰撞
		pBullet = pPlayerBulletSystem->GetFirstBullet();
		while(pBullet)
		{
			CheckForCollision(pEnermy, pBullet);
			pBullet = pPlayerBulletSystem->GetNextBullet();
		}

		pEnermy = pEnermySystem->GetNextEnermy();
	}

	// 遍历敌人的子弹
	pBullet = pEnermyBulletSystem->GetFirstBullet();
	while(pBullet)
	{
		// 检查玩家与敌人子弹的碰撞
		CheckForCollision(pPlayer, pBullet);
		pBullet = pEnermyBulletSystem->GetNextBullet();
	}
}

// 碰撞检测：敌机与玩家子弹
void CollisionSystem::CheckForCollision(Enermy *pFighterPlane, Bullet *pBullet)
{
	if( pFighterPlane->Life <= 0 || pBullet->Life <= 0 ) return;
	if( pFighterPlane->GetX() + pFighterPlane->cx + pFighterPlane->cw > pBullet->GetX() + pBullet->cx &&
		pFighterPlane->GetY() + pFighterPlane->cy + pFighterPlane->ch > pBullet->GetY() + pBullet->ch &&
		pFighterPlane->GetX() + pFighterPlane->cx < pBullet->GetX() + pBullet->cx + pBullet->cw &&
		pFighterPlane->GetY() + pFighterPlane->cy < pBullet->GetY() + pBullet->cy + pBullet->ch )
	{
		pFighterPlane->Life -= pBullet->Atackness;
		pBullet->Life = 0;
		pPlayer->Score += pFighterPlane->Life;
		if(pFighterPlane->Life <= 0 )
			pPlayer->KillEnermy++;
	}
}

// 碰撞检测：玩家与敌方子弹
void CollisionSystem::CheckForCollision(Player *pFighterPlane, Bullet *pBullet)
{
	if( pFighterPlane->Life <= 0 || pBullet->Life <= 0 ) return;
	if( pFighterPlane->GetX() + pFighterPlane->cx + pFighterPlane->cw > pBullet->GetX() + pBullet->cx &&
		pFighterPlane->GetY() + pFighterPlane->cy + pFighterPlane->ch > pBullet->GetY() + pBullet->ch &&
		pFighterPlane->GetX() + pFighterPlane->cx < pBullet->GetX() + pBullet->cx + pBullet->cw &&
		pFighterPlane->GetY() + pFighterPlane->cy < pBullet->GetY() + pBullet->cy + pBullet->ch )
	{
		pFighterPlane->Life -= pBullet->Atackness;
		pBullet->Life = 0;
	}
}

// 碰撞检测：玩家与敌机
void CollisionSystem::CheckForCollision(Player *pPlayer, Enermy *pEnermy)
{
	if( pPlayer->Life <= 0 || pEnermy->Life <= 0 ) return;
	if( pPlayer->GetX() + pPlayer->cx + pPlayer->cw > pEnermy->GetX() + pEnermy->cx &&
		pPlayer->GetY() + pPlayer->cy + pPlayer->ch > pEnermy->GetY() + pEnermy->ch &&
		pPlayer->GetX() + pPlayer->cx < pEnermy->GetX() + pEnermy->cx + pEnermy->cw &&
		pPlayer->GetY() + pPlayer->cy < pEnermy->GetY() + pEnermy->cy + pEnermy->ch )
	{
		pPlayer->Life -= 5;
		pPlayer->KillEnermy++;
		pPlayer->Score += pEnermy->Life;
		pEnermy->Life = 0;
	}
}