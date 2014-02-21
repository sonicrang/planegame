#ifndef PLAYER_H
#define PLAYER_H

#include "Sprite.h"

// 定义玩家战机
class Player:public FighterPlane
{
	double speed;
	void Fire();
public:
	int KillEnermy, Score;
	enum ACTION { GO_LEFT, GO_UP, GO_RIGHT, GO_DOWN, GO_LEFT_UP, GO_LEFT_DOWN, GO_RIGHT_UP, GO_RIGHT_DOWN, STOP_MOVING, START_FIRING, STOP_FIRING, CHANGE_WEAPON};

	Player(GameWorld *pgw, int x_value, int y_value);
	void Update();
	void ChangeWeapon();
	void Action(ACTION NewAction);
};

#endif