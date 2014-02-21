#include "stdafx.h"

// 类定义:角色精灵
bool Sprite::OutOfClient()
{
	return GetX()<0 || GetY()<0 || GetX()+w >= pGameWorld->Width-1 || GetY()+h >= pGameWorld->Height-1;
}

bool Sprite::OutOfSight()
{
	return x+w<0 || y+h<0 || x>=pGameWorld->Width || y>=pGameWorld->Height;
}

Sprite::Sprite(GameWorld *pgw, int x_value, int y_value)
{
	sx=0;
	sy=0;
	w=0;
	h=0;

	cx=0;
	cy=0;
	cw=0;
	ch=0;

	Life=1;
	Atackness=1;

	Used=true;

	dx=0;
	dy=0;

	x=x_value;
	y=y_value;

	pGameWorld=pgw;
}

void Sprite::AdjustPosition()
{
	x -= w / 2;
	if( x < 0 )
		x = 0;
	else if( x + w - 1 >= pGameWorld->Width )
		x = pGameWorld->Width - w;

	if( y < 0 )
		y = y - h;
	else
		y -= h / 2;
}

void Sprite::Update()
{
	if(Life>0)
	{
		x += dx * pGameWorld->GetKFPS();
		y += dy * pGameWorld->GetKFPS();
	}
	pGameWorld->DrawSprite(this);
}