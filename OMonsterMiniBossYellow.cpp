#include "stdafx.h"
#include "OMonsterMiniBossYellow.h"


OMonsterMiniBossYellow::OMonsterMiniBossYellow()
{
}


OMonsterMiniBossYellow::~OMonsterMiniBossYellow()
{
}

HRESULT OMonsterMiniBossYellow::Init(string key, int pos)
{
	MonsterBase::Init(key, pos);

	myMoveBeat = 2;
	subX = 12;
	subY = 20;
	damage = 1;
	m_hp = 2;
	m_currentHp = 2;

	return S_OK;
}

void OMonsterMiniBossYellow::Release()
{

}

void OMonsterMiniBossYellow::Update()
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

void OMonsterMiniBossYellow::Render()
{
	MonsterBase::Render();
}

void OMonsterMiniBossYellow::Anim()
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
