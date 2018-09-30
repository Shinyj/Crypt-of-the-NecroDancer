#include "stdafx.h"
#include "OMonsterBatMiniBoss.h"


OMonsterBatMiniBoss::OMonsterBatMiniBoss()
{
}


OMonsterBatMiniBoss::~OMonsterBatMiniBoss()
{
}

HRESULT OMonsterBatMiniBoss::Init(string key, int pos)
{
	MonsterBase::Init(key, pos);

	myMoveBeat = 2;
	subX = 12;
	subY = 20;
	damage = 2;
	m_hp = 3;
	m_currentHp = 3;

	return S_OK;
}

void OMonsterBatMiniBoss::Release()
{
}

void OMonsterBatMiniBoss::Update()
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

void OMonsterBatMiniBoss::Render()
{
	MonsterBase::Render();
}

void OMonsterBatMiniBoss::Anim()
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
