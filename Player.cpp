#include "stdafx.h"

// 构造函数
Player::Player(GameWorld *pgw, int x_value, int y_value)
:FighterPlane(pgw, x_value, y_value)
{
	sx=0;
	sy=0;
	w=29;
	h=33;

	cx=6;
	cy=11;
	cw=17;
	ch=19;

	Life = 20;

	speed=3;
	KillEnermy = 0;
	Score = 0;

	dx=0;
	dy=0;
	Firing=false;
	FighterPlane::BulletType=Bullet::PLAYER_BULLET_FIRE;

	AdjustPosition();
}

// 刷新Player的状态
void Player::Update()
{
	if(!Used)
	{
		pGameWorld->ResetPlayer();
		return;
	}
	if(Life>0)
	{
		if(x+dx<0)
		{
			x=0;
			dx=0;
		}
		else if(y+dy<0)
		{
			y=0;
			dy=0;
		}
		else if(x+w+dx>GameWorld::Width-1)
		{
			x=GameWorld::Width-w-1;
			dx=0;
		}
		else if(y+h+dy>GameWorld::Height-1)
		{
			y=GameWorld::Height-h-1;
			dy=0;
		}
	}
	FighterPlane::Update();
}

void Player::ChangeWeapon()
{
	BulletType=(Bullet::BULLET_TYPE)((BulletType+1)%3);
}

void Player::Action(ACTION NewAction)
{
	if(Life<=0) return;
	switch(NewAction)
	{
	case GO_LEFT:
		dx=-speed;
		dy=0;
		break;
	case GO_RIGHT:
		dx=speed;
		dy=0;
		break;
	case GO_UP:
		dx=0;
		dy=-speed;
		break;
	case GO_DOWN:
		dx=0;
		dy=speed;
		break;
	case GO_LEFT_UP:
		dx=-0.7*speed;
		dy=-0.7*speed;
		break;
	case GO_LEFT_DOWN:
		dx=-0.7*speed;
		dy=0.7*speed;
		break;
	case GO_RIGHT_UP:
		dx=0.7*speed;
		dy=-0.7*speed;
		break;
	case GO_RIGHT_DOWN:
		dx=0.7*speed;
		dy=0.7*speed;
		break;
	case STOP_MOVING:
		dx=0;
		dy=0;
		break;
	case START_FIRING:
		StartFiring();
		break;
	case STOP_FIRING:
		StopFiring();
		break;
	case CHANGE_WEAPON:
		ChangeWeapon();
		break;
	}
}

void Player::Fire()
{
	if( pGameWorld->Time - LastFireTime < Bullet::GetFireInterval( BulletType ) )
		return;
	pGameWorld->PlayerFire(this);
	LastFireTime=pGameWorld->Time;
}
