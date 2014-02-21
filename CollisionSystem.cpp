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
	
	// �����л�
	pEnermy = pEnermySystem->GetFirstEnermy();
	while(pEnermy)
	{
		// ���л������ս������ײ
		CheckForCollision(pPlayer, pEnermy);

		// ���л�������ӵ�����ײ
		pBullet = pPlayerBulletSystem->GetFirstBullet();
		while(pBullet)
		{
			CheckForCollision(pEnermy, pBullet);
			pBullet = pPlayerBulletSystem->GetNextBullet();
		}

		pEnermy = pEnermySystem->GetNextEnermy();
	}

	// �������˵��ӵ�
	pBullet = pEnermyBulletSystem->GetFirstBullet();
	while(pBullet)
	{
		// ������������ӵ�����ײ
		CheckForCollision(pPlayer, pBullet);
		pBullet = pEnermyBulletSystem->GetNextBullet();
	}
}

// ��ײ��⣺�л�������ӵ�
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

// ��ײ��⣺�����з��ӵ�
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

// ��ײ��⣺�����л�
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