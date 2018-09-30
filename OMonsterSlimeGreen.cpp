#include "stdafx.h"
#include "OMonsterSlimeGreen.h"


OMonsterSlimeGreen::OMonsterSlimeGreen()
{
}


OMonsterSlimeGreen::~OMonsterSlimeGreen()
{
}

HRESULT OMonsterSlimeGreen::Init(string key, int pos)
{
	MonsterBase::Init(key, pos);

	myMoveBeat = 2;
	subX = 0;
	subY = 20;
	damage = 100;
	m_hp = 3;
	m_currentHp = 3;

	return S_OK;
}

void OMonsterSlimeGreen::Release()
{
}

void OMonsterSlimeGreen::Update()
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
			//AStarLoad();
		}


		isBeatTime = false;
	}

	EffectAnim();
}

void OMonsterSlimeGreen::Render()
{
	MonsterBase::Render();
}

void OMonsterSlimeGreen::Anim()
{
	count++;
	if (isRight)
	{
		if (count % 10 == 0)
		{
			count = 0;
			m_frameX = m_frameX - 1;
			if (m_frameX < 5) m_frameX = 7;
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
