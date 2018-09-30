#include "stdafx.h"
#include "OMonsterBatBlack.h"


OMonsterBatBlack::OMonsterBatBlack()
{
}


OMonsterBatBlack::~OMonsterBatBlack()
{
}

HRESULT OMonsterBatBlack::Init(string key, int pos)
{
	MonsterBase::Init(key, pos);

	myMoveBeat = 1;
	subX = 0;
	subY = 20;
	damage = 2;
	m_hp = 3;
	m_currentHp = 3;

	return S_OK;
}

void OMonsterBatBlack::Release()
{
}

void OMonsterBatBlack::Update()
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

void OMonsterBatBlack::Render()
{
	MonsterBase::Render();
}

void OMonsterBatBlack::Anim()
{
	count++;
	if (isRight)
	{
		if (count % 10 == 0)
		{
			count = 0;
			//m_frameX = 7 - (m_frameX + 1) % 4;
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
