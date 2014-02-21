#include "stdafx.h"

// ���캯��
EnermySystem::EnermySystem(GameWorld *pgw)
{
	pGameWorld=pgw;
	ResetDifficulty();
}

// �͹�����
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

// ���ص�һ���л�����
Enermy* EnermySystem::GetFirstEnermy()
{
	EnermyIndex=-1;
	EnermyCount=EnermyList.size();
	if(EnermyCount==0)
		return NULL;

	pCurElement=EnermyList.end();
	return GetNextEnermy();
}

// ������һ���л�����
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

// �����µл�
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
	// �����л�
	if( rand() < Difficulty )
		CreateEnermy( rand()% pGameWorld->Width, -1 );

	// ˢ�µл�
	Enermy *pEnermy=GetFirstEnermy();
	while(pEnermy)
	{
		pEnermy->Update();
		pEnermy=GetNextEnermy();
	}
}

// �����Ѷ�
void EnermySystem::AddDifficulty()
{
	Difficulty = (int)(Difficulty * 1.2 );
}

// �����Ѷ�
void EnermySystem::ResetDifficulty()
{
	Difficulty = 500;
}