#ifndef ENERMY_H
#define ENERMY_H

class Enermy:public FighterPlane
{
protected:
	friend class EnermySystem;
	void Fire();
public:
	Enermy(GameWorld *pgw, int x_value, int y_value);
	static enum ENERMY_TYPE { ENERMY_TOM, ENERMY_MIMI, ENERMY_JACK, ENERMY_TYPE_COUNT };
	void Update();
};

class Enermy_Tom:public Enermy
{
	enum DIRECTION { DIR_LEFT, DIR_RIGHT, DIR_FORWARD } Direction;
	void ChangeDirection();
	void Update();
public:
	Enermy_Tom(GameWorld *pgw, int x_value, int y_value);
};

class Enermy_Mimi:public Enermy
{
public:
	Enermy_Mimi(GameWorld *pgw, int x_value, int y_value);
};

class Enermy_Jack:public Enermy
{
public:
	Enermy_Jack(GameWorld *pgw, int x_value, int y_value);
};

#endif