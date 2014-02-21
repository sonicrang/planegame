#include "stdafx.h"

// Bullet

Bullet::Bullet(GameWorld *pgw, int x_value, int y_value, double sprite_vx, double sprite_vy)
:Sprite(pgw, x_value, y_value)
{
	dx=sprite_vx;
	dy=sprite_vy;
	ExplosionFrameCount = 32;
	ExplosionFrameIndex = -1;
};

int Bullet::GetFireInterval(BULLET_TYPE BulletType)
{
	switch(BulletType)
	{
	case PLAYER_BULLET_FIRE:
		return 150;
	case PLAYER_BULLET_MISSILE:
		return 300;
	case PLAYER_BULLET_ROUND_BULLET:
		return 200;
	case ENERMY_BULLET_1:
		return 2000;
	case ENERMY_BULLET_2:
		return 700;
	case ENERMY_BULLET_3:
		return 1000;
	}
	return 0;
}

void Bullet::SetMovement(double speed, int angle)
{
	double a = GameWorld::PI * angle / 180;
	dx += speed * cos( a );
	dy += - speed * sin( a );
}

void Bullet::Update()
{
	if(OutOfSight())
		Used=false;	
	else if(Life<=0)
	{
		if(++ExplosionFrameIndex==0)
		{
			sx = 0;
			sy = 83;
			w = 32;
			h = 32;
			dx = 0;
			dy = 0;
		}
		else if(ExplosionFrameIndex>=ExplosionFrameCount)
			Used = false;
		else
		{
			sx = 32 * ( ExplosionFrameIndex / 4 );
		}
	}
	Sprite::Update();
}
// Fire
PlayerBullet_Fire::PlayerBullet_Fire(GameWorld *pgw, int x_value, int y_value, double sprite_vx, double sprite_vy)
:Bullet(pgw, x_value, y_value, sprite_vx, sprite_vy)
{
	Bullet::dx=0;
	Bullet::dy=-15;

	Sprite::sx=29;
	Sprite::sy=0;
	Sprite::w=3;
	Sprite::h=13;

	cx=0;
	cy=0;
	cw=3;
	ch=9;

	AdjustPosition();
};

// Missile
PlayerBullet_Missile::PlayerBullet_Missile(GameWorld *pgw, int x_value, int y_value, double sprite_vx, double sprite_vy, int angle)
:Bullet(pgw, x_value, y_value, sprite_vx, sprite_vy)
{
	Angle=angle;

	dAngle=3;

	Sprite::sx=32;
	Sprite::sy=0;
	Sprite::w=4;
	Sprite::h=8;

	cx=1;
	cy=0;
	cw=2;
	ch=6;

	x0=x_value;
	Range=5;

	AdjustPosition();
};

void PlayerBullet_Missile::Update()
{
	if(Life>0)
	{
		x=x0;
		dx=Range*cos(Angle*GameWorld::PI/180);
		dy=-10;
		Angle+=dAngle;
		Range+=2;
	}
	Bullet::Update();
}


// RoundBullet
PlayerBullet_RoundBullet::PlayerBullet_RoundBullet(GameWorld *pgw, int x_value, int y_value, double sprite_vx, double sprite_vy, int angle)
:Bullet(pgw, x_value, y_value, 0, 0)
{
	Sprite::sx=36;
	Sprite::sy=0;
	Sprite::w=5;
	Sprite::h=5;

	cx=1;
	cy=1;
	cw=3;
	ch=3;

	Atackness = 1;

	AdjustPosition();
	SetMovement(15, angle);
};

// EnermyBullet1
EnermyBullet1::EnermyBullet1(GameWorld *pgw, int x_value, int y_value, double sprite_vx, double sprite_vy, int angle)
:Bullet(pgw, x_value, y_value, sprite_vx, sprite_vy)
{
	Sprite::sx=30;
	Sprite::sy=25;
	Sprite::w=8;
	Sprite::h=8;

	cx=2;
	cy=2;
	cw=4;
	ch=4;

	AdjustPosition();
	SetMovement(2, angle);
};

// EnermyBullet2
EnermyBullet2::EnermyBullet2(GameWorld *pgw, int x_value, int y_value, double sprite_vx, double sprite_vy, int angle)
:Bullet(pgw, x_value, y_value, sprite_vx, sprite_vy)
{
	Sprite::sx=29;
	Sprite::sy=13;
	Sprite::w=7;
	Sprite::h=7;

	cx=1;
	cy=1;
	cw=5;
	ch=5;

	AdjustPosition();
	SetMovement(6, angle);
};

// EnermyBullet3
EnermyBullet3::EnermyBullet3(GameWorld *pgw, int x_value, int y_value, double sprite_vx, double sprite_vy, int angle)
:Bullet(pgw, x_value, y_value, sprite_vx, sprite_vy)
{
	Sprite::sx=29;
	Sprite::sy=20;
	Sprite::w=5;
	Sprite::h=5;

	cx=1;
	cy=1;
	cw=3;
	ch=3;

	AdjustPosition();
	SetMovement(4, angle);
};