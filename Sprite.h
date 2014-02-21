#ifndef SPRITE_H
#define SPRITE_H

class Sprite
{
protected:
	GameWorld *pGameWorld;
	int		ExplosionFrameCount, ExplosionFrameIndex;
	double x, y;
	void AdjustPosition();
public:
	int sx, sy, w, h;			// 在素材位图中的位置
	int cx, cy, cw, ch;			// 碰撞检测用矩形
	int Life, Atackness;
	double dx, dy;
	bool Used;

	bool OutOfClient();
	bool OutOfSight();
	int GetX(){ return (int)x; }
	int GetY(){ return (int)y; }
	void SetX(int x_value){ x=x_value; }
	void SetY(int y_value){ y=y_value; }
	Sprite(GameWorld *pgw, int x_value, int y_value);
	virtual void Update();
};


#endif