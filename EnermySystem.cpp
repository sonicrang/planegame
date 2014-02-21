#include "stdafx.h"

// 构造函数
EnermySystem::EnermySystem(GameWorld *pgw)
{
	pGameWorld=pgw;
	ResetDifficulty();
}

// 释构函数
EnermySystem::~EnermySystem()
{
	list<Enermy*>::iterator p, pend;;
	p=EnermyList.begin();
	pend=EnermyList.end();
	while(p!=pend)
	{
		delete *p;
		p++;
	}
} 

// 返回第一个敌机对象
Enermy* EnermySystem::GetFirstEnermy()
{
	EnermyIndex=-1;
	EnermyCount=EnermyList.size();
	if(EnermyCount==0)
		return NULL;

	pCurElement=EnermyList.end();
	return GetNextEnermy();
}

// 返回下一个敌机对象
Enermy* EnermySystem::GetNextEnermy()
{
	EnermyIndex++;
	pCurElement++;
	while( ( EnermyIndex < EnermyCount ) && ( *pCurElement )->Used==false )
	{
		delete *pCurElement;
		EnermyCount--;
		pCurElement=EnermyList.erase(pCurElement);
	}

	if(pCurElement==EnermyList.end())
		return NULL;
	else
		return *pCurElement;
}

// 创建新敌机
void EnermySystem::CreateEnermy(int x, int y)
{
	int i, n;
	Enermy::ENERMY_TYPE EnermyType = ( Enermy::ENERMY_TYPE ) ( rand() % Enermy::ENERMY_TYPE_COUNT );
	Enermy		*pEnermy;
	switch( EnermyType )
	{
	case Enermy::ENERMY_TOM:
		pEnermy = new Enermy_Tom( pGameWorld, x, y );
		EnermyList.push_back(pEnermy);
		break;
	case Enermy::ENERMY_MIMI:
		pEnermy = new Enermy_Mimi( pGameWorld, x, y );
		EnermyList.push_back(pEnermy);
		break;
	case Enermy::ENERMY_JACK:
		if( rand() % 3 > 0 ) break;
		n = rand() % 4 + 1;
		switch( rand() % 4 )
		{
		case 0:
			if( x + n * 50 > GameWorld::Width )
				x = GameWorld::Width - n * 50;
			for(i=0; i<n; i++)
			{
				pEnermy = new Enermy_Jack( pGameWorld, x + i * 50, y - i * 50 );
				EnermyList.push_back(pEnermy);
			}
			break;
		case 1:
			if( x < n * 50 )
				x = n * 50;
			for(i=0; i<n; i++)
			{
				pEnermy = new Enermy_Jack( pGameWorld, x - i * 50, y - i * 50 );
				EnermyList.push_back(pEnermy);
			}
			break;
		case 2:
			for(i=0; i<n; i++)
			{
				pEnermy = new Enermy_Jack( pGameWorld, x, y - i * 70 );
				EnermyList.push_back(pEnermy);
			}
			break;
		case 3:
			if( x + n * 50 > GameWorld::Width )
				x = GameWorld::Width - n * 50;
			for(i=0; i<n; i++)
			{
				pEnermy = new Enermy_Jack( pGameWorld, x + i * 70, y );
				EnermyList.push_back(pEnermy);
			}
		}
	}
}

void EnermySystem::Update()
{
	// 新增敌机
	if( rand() < Difficulty )
		CreateEnermy( rand()% pGameWorld->Width, -1 );

	// 刷新敌机
	Enermy *pEnermy=GetFirstEnermy();
	while(pEnermy)
	{
		pEnermy->Update();
		pEnermy=GetNextEnermy();
	}
}

// 增加难度
void EnermySystem::AddDifficulty()
{
	Difficulty = (int)(Difficulty * 1.2 );
}

// 重设难度
void EnermySystem::ResetDifficulty()
{
	Difficulty = 500;
}