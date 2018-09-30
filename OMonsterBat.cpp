#include "stdafx.h"
#include "OMonsterBat.h"


OMonsterBat::OMonsterBat()
{
}


OMonsterBat::~OMonsterBat()
{
}

HRESULT OMonsterBat::Init(string key, int pos)
{
	MonsterBase::Init(key, pos);
	myMoveBeat = 1;
	subX = 0;
	subY = 20;
	damage = 1;
	m_hp = 1;
	m_currentHp = 1;
	return S_OK;
}

void OMonsterBat::Release()
{
}

void OMonsterBat::Update()
{
	Anim();

	JumpMove();

	if (isBeatTime)
	{
		myCurrentMoveBeat++;
		if (myMoveBeat == myCurrentMoveBeat)
		{
			myCurrentMoveBeat = 0;
			//RendomLoad();
			//PatternLoad();
			AStarLoad();
		}


		isBeatTime = false;
	}

	EffectAnim();
}

void OMonsterBat::Render()
{
	MonsterBase::Render();
}

void OMonsterBat::Anim()
{
	count++;
	if (isRight)
	{
		if (count % 10 == 0)
		{
			count = 0;

			m_frameX = 7 - (m_frameX + 1) % 4;
		}
	}
	else
	{
		if (count % 10 == 0)
		{
			count = 0;

			m_frameX = (m_frameX + 1) % 4;

		}
	}
}