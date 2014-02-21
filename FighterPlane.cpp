#include "stdafx.h"

// 类定义:战斗机
FighterPlane::FighterPlane(GameWorld *pgw, int x_value, int y_value)
:Sprite(pgw, x_value, y_value)
{
	LastFireTime=0;
	ExplosionFrameCount = 8 * 4;
	ExplosionFrameIndex = -1;
}

void FighterPlane::Update()
{
	Sprite::Update();
	if(Firing)
		Fire();
	if(Life<=0)
	{
		if( ++ExplosionFrameIndex == 0 )
		{
			x += w/2-82;
			y += h/2-73;
			w = 180;
			h = 135;
			dx = 0;
			dy = 0;
			sx = 0;
			sy = 115;
			Firing = false;
		}
		else if(ExplosionFrameIndex == ExplosionFrameCount)
			Used = false;
		else
		{
			sx = 180 * ( ExplosionFrameIndex / 4 % 4 );
			sy = 115 + 135 * ( ExplosionFrameIndex / 4 / 4 );
		}
	}
}

void FighterPlane::StartFiring()
{
	Firing=true;
}

void FighterPlane::StopFiring()
{
	Firing=false;
}

void FighterPlane::SetLastFireTime()
{
	LastFireTime = pGameWorld->Time - rand() % Bullet::GetFireInterval( BulletType );
}
