#ifndef FIGHTER_PLANE
#define FIGHTER_PLANE

class FighterPlane:public Sprite
{
protected:
	bool Firing;
	int LastFireTime;
	void SetLastFireTime();
	virtual void Fire()=0;
public:
	Bullet::BULLET_TYPE		BulletType;
	FighterPlane::FighterPlane(GameWorld *pgw, int x_value, int y_value);
	void Update();
	void StartFiring();
	void StopFiring();
};

#endif