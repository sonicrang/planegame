#ifndef BULLETSYSTEM_H
#define BULLETSYSTEM_H

using namespace std;

class BulletSystem
{
	list<Bullet*>	BulletList;
	list<Bullet*>::iterator		pCurElement;
	int BulletIndex, BulletCount;
	GameWorld		*pGameWorld;
public:
	BulletSystem(GameWorld *pgw);
	Bullet* GetFirstBullet();
	Bullet* GetNextBullet();
	~BulletSystem();
	void FireHappened(Bullet::BULLET_TYPE BulletType, int x, int y, double sprite_vx, double sprite_vy);
	void Update();
};

#endif