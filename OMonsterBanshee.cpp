#include "stdafx.h"
#include "OMonsterBanshee.h"


OMonsterBanshee::OMonsterBanshee()
{
}


OMonsterBanshee::~OMonsterBanshee()
{
}

HRESULT OMonsterBanshee::Init(string key, int pos)
{

	MonsterBase::Init(key,pos);
	//m_imageKey = key;
	//m_pos = pos;
	

	myMoveBeat = 1;
	subX = 7;
	subY = 47;
	damage = 2;
	m_hp = 3;
	m_currentHp = 3;

	isPattern = false;

	return S_OK;
}

void OMonsterBanshee::Release()
{
}

void OMonsterBanshee::Update()
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

void OMonsterBanshee::Render()
{
	MonsterBase::Render();

	//if (isSight)
	//{
	//	if (light == 0)
	//		mainImage->FrameRender(GetMemDC(), x - 7, y - 47, m_frameX, 1);
	//	else
	//		mainImage->FrameRender(GetMemDC(), x - 7, y - 47, m_frameX, 0);
	//}
	//else
	//{
	//	if (isFirstSight)
	//	{
	//		mainImage->FrameRender(GetMemDC(), x - 7, y - 47, m_frameX, 1);
	//	}
	//}
	//
	//if (isShowHp && m_hp != m_currentHp)
	//{
	//	for (int i = m_currentHp; i < m_hp; i++)
	//	{
	//		maxHpImage->Render(GetMemDC(), (x + 26) - (m_hp / 2) * 24 + 24 * i - 7, y - 71);
	//	}
	//	for (int i = 0; i < m_currentHp; i++)
	//	{
	//		curHpImage->Render(GetMemDC(), (x + 26) - (m_hp / 2) * 24 + 24 * i - 7, y - 71);
	//	}
	//}
	//
	//light = 0;
	//isSight = 0;
}

void OMonsterBanshee::Defence(int num)
{

	if (isPattern == false)
	{
		isPattern = true;
		SOUNDMANAGER->SetBGMVolume(SOUNDMANAGER->GetBgmKey(),0.0f);
		//SOUNDMANAGER->resume(SOUNDMANAGER->GetBgmKey(), 0.0);
		SOUNDMANAGER->Play("en_banshee_loop",OBJECTMANAGER->GetBgmVolum());
	}
	MonsterBase::Defence(num);
}

void OMonsterBanshee::Anim()
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
