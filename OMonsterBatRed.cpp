#include "stdafx.h"
#include "OMonsterBatRed.h"


OMonsterBatRed::OMonsterBatRed()
{
}


OMonsterBatRed::~OMonsterBatRed()
{
}

HRESULT OMonsterBatRed::Init(string key, int pos)
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

void OMonsterBatRed::Release()
{
}

void OMonsterBatRed::Update()
{
	Anim();

	Move();

	if (isBeatTime)
	{
		myCurrentMoveBeat++;
		if (myMoveBeat == myCurrentMoveBeat)
		{
			myCurrentMoveBeat = 0;
			RendomLoad();
			//PatternLoad();
			//AStarLoad();
		}


		isBeatTime = false;
	}

	EffectAnim();
}

void OMonsterBatRed::Render()
{
	MonsterBase::Render();
}

void OMonsterBatRed::Anim()
{
	count++;
	if (isRight)
	{
		if (count % 10 == 0)
		{
			count = 0;

			m_frameX = (m_frameX + 1) % 4;
		}
	}
	else
	{
		if (count % 10 == 0)
		{
			count = 0;

			m_frameX = m_frameX - 1;
			if (m_frameX < 4) m_frameX = 7;

		}
	}
}
