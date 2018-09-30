#include "stdafx.h"
#include "OMonsterSkeleton.h"


OMonsterSkeleton::OMonsterSkeleton()
{
}


OMonsterSkeleton::~OMonsterSkeleton()
{
}

HRESULT OMonsterSkeleton::Init(string key, int pos)
{
	MonsterBase::Init(key, pos);

	myMoveBeat = 2;
	subX = 0;
	subY = 20;
	damage = 1;
	m_hp = 1;
	m_currentHp = 1;

	return S_OK;
}

void OMonsterSkeleton::Release()
{
}

void OMonsterSkeleton::Update()
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

void OMonsterSkeleton::Render()
{
	MonsterBase::Render();
}

void OMonsterSkeleton::Anim()
{
	count++;
	if (isRight)
	{
		if (count % 5 == 0)
		{
			count = 0;
			if (myCurrentMoveBeat == 0)
			{
				m_frameX = m_frameX - 1;
				if (m_frameX < 12) m_frameX = 15;
			}
			else
			{
				m_frameX = m_frameX - 1;
				if (m_frameX < 8) m_frameX = 11;
			}
		}
	}
	else
	{
		if (count % 5 == 0)
		{
			count = 0;
			if (myCurrentMoveBeat == 0)
				m_frameX = (m_frameX + 1) % 4;
			else
				m_frameX = (m_frameX + 1) % 4 + 4;

		}
	}
}
