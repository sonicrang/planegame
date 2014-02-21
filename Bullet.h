#ifndef BULLET_H
#define BULLET_H

// 定义子弹基类
class Bullet:public Sprite
{
protected:
	void SetMovement(double speed, int angle);
public:
	static enum BULLET_TYPE { PLAYER_BULLET_FIRE, PLAYER_BULLET_MISSILE, PLAYER_BULLET_ROUND_BULLET, ENERMY_BULLET_1, ENERMY_BULLET_2, ENERMY_BULLET_3, BULLET_COUNT };

	void Update();
	static int GetFireInterval(BULLET_TYPE BulletType);
	Bullet(GameWorld *pgw, int x_value, int y_value, double sprite_vx, double sprite_vy);
};

// Fire
class PlayerBullet_Fire:public Bullet
{
public:
	PlayerBullet_Fire(GameWorld *pgw, int x_value, int y_value, double sprite_vx, double sprite_vy);
};

// Missile
class PlayerBullet_Missile:public Bullet
{
	int Angle, dAngle;
	int x0, Range;
public:
	PlayerBullet_Missile(GameWorld *pgw, int x_value, int y_value, double sprite_vx, double sprite_vy, int angle);
	void Update();
};

// RoundBullet
class PlayerBullet_RoundBullet:public Bullet
{
public:
	PlayerBullet_RoundBullet(GameWorld *pgw, int x_value, int y_value, double sprite_vx, double sprite_vy, int angle);
};

// EnermyBullet1
class EnermyBullet1:public Bullet
{
public:
	EnermyBullet1(GameWorld *pgw, int x_value, int y_value, double sprite_vx, double sprite_vy, int angle);
};

// EnermyBullet2
class EnermyBullet2:public Bullet
{
public:
	EnermyBullet2(GameWorld *pgw, int x_value, int y_value, double sprite_vx, double sprite_vy, int angle);
};

// EnermyBullet3
class EnermyBullet3:public Bullet
{
public:
	EnermyBullet3(GameWorld *pgw, int x_value, int y_value, double sprite_vx, double sprite_vy, int angle);
};
#endif