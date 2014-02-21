#include "stdafx.h"

Enermy::Enermy(GameWorld *pgw, int x_value, int y_value)
:FighterPlane(pgw, x_value, y_value)
{
	Used=true;
	dx=0;
	dy=0;
}

void Enermy::Update()
{
	FighterPlane::Update();
	if( OutOfSight() && y>=GameWorld::Height )
		Used=false;
}

void Enermy::Fire()
{
	if( pGameWorld->Time - LastFireTime < Bullet::GetFireInterval( BulletType ) )
		return;
	pGameWorld->EnermyFire(this);
	LastFireTime=pGameWorld->Time;
}

// Tom
Enermy_Tom::Enermy_Tom(GameWorld *pgw, int x_value, int y_value)
:Enermy(pgw, x_value, y_value)
{
	sx=0;
	sy=33;
	w=62;
	h=50;

	cx=16;
	cy=12;
	cw=31;
	ch=29;

	Life = 8;

	dy=2;
	Direction=DIR_FORWARD;
	BulletType=Bullet::ENERMY_BULLET_1;

	SetLastFireTime();
	AdjustPosition();
}

void Enermy_Tom::ChangeDirection()
{
	Direction = ( DIRECTION ) ( rand() % 3 );
}

void Enermy_Tom::Update()
{
	Enermy::Update();
	if(Life<=0) return;

	switch( Direction )
	{
	case DIR_LEFT:
		x--;
		if( x<0 )
		{
			x=0;
			Direction = DIR_FORWARD;
		}
		break;
	case DIR_RIGHT:
		x++;
		if( x + w > GameWorld::Width )
		{
			x = GameWorld::Width - w;
			Direction = DIR_FORWARD;
		}
		break;
	}

	if( rand() < 300 )
		ChangeDirection();
}
// Mimi
Enermy_Mimi::Enermy_Mimi(GameWorld *pgw, int x_value, int y_value)
:Enermy(pgw, x_value, y_value)
{
	sx=41;
	sy=0;
	w=33;
	h=28;

	cx=7;
	cy=4;
	cw=20;
	ch=21;

	Life = 2;

	dy=5;
	BulletType=Bullet::ENERMY_BULLET_2;

	SetLastFireTime();
	AdjustPosition();
}

// Jack
Enermy_Jack::Enermy_Jack(GameWorld *pgw, int x_value, int y_value)
:Enermy(pgw, x_value, y_value)
{
	sx=74;
	sy=0;
	w=43;
	h=42;

	cx=12;
	cy=5;
	cw=19;
	ch=25;

	Life = 5;

	dy=3;
	BulletType=Bullet::ENERMY_BULLET_3;

	SetLastFireTime();
	AdjustPosition();
}