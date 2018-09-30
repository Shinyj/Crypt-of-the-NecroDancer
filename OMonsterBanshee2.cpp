#include "stdafx.h"
#include "OMonsterBanshee2.h"


OMonsterBanshee2::OMonsterBanshee2()
{
}


OMonsterBanshee2::~OMonsterBanshee2()
{
}

HRESULT OMonsterBanshee2::Init(string key, int pos)
{
	MonsterBase::Init(key, pos);

	myMoveBeat = 1;
	subX = 7;
	subY = 47;
	damage = 3;
	m_hp = 5;
	m_currentHp = 5;

	isPattern = false;
	return S_OK;
}

void OMonsterBanshee2::Release()
{
}

void OMonsterBanshee2::Update()
{
	Anim();

	Move();

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

void OMonsterBanshee2::Render()
{
	MonsterBase::Render();
}

void OMonsterBanshee2::Defence(int num)
{
	if (isPattern == false)
	{
		isPattern = true;
		SOUNDMANAGER->SetBGMVolume(SOUNDMANAGER->GetBgmKey(), 0.0f);
		//SOUNDMANAGER->resume(SOUNDMANAGER->GetBgmKey(), 0.0);
		SOUNDMANAGER->Play("en_banshee_loop", OBJECTMANAGER->GetBgmVolum());
	}
	MonsterBase::Defence(num);
}

void OMonsterBanshee2::Anim()
{
	count++;
	if (!isPattern)
	{
		if (isRight)
		{
			if (count % 10 == 0)
			{
				count = 0;
				m_frameX = m_frameX - 1;
				if (m_frameX < 12) m_frameX = 15;
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
	else
	{
		if (isRight)
		{
			if (count % 10 == 0)
			{
				count = 0;
				m_frameX = m_frameX - 1;
				if (m_frameX < 8) m_frameX = 11;
			}
		}
		else
		{
			if (count % 10 == 0)
			{
				count = 0;
				m_frameX = m_frameX + 1;
				if (m_frameX > 7) m_frameX = 4;
			}
		}
	}
}
