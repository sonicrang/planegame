#ifndef ENERMY_SYSTEM_H
#define ENERMY_SYSTEM_H

using namespace std;

class EnermySystem
{
	list<Enermy*>	EnermyList;
	list<Enermy*>::iterator		pCurElement;
	int EnermyIndex, EnermyCount;

	int Difficulty;
	GameWorld		*pGameWorld;
public:
	void AddDifficulty();
	EnermySystem(GameWorld *pgw);
	~EnermySystem();
	Enermy* GetFirstEnermy();
	Enermy* GetNextEnermy();
	void CreateEnermy(int x, int y);
	void Update();
	void ResetDifficulty();
};

#endif