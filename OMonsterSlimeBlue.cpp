#include "stdafx.h"
#include "OMonsterSlimeBlue.h"


OMonsterSlimeBlue::OMonsterSlimeBlue()
{
}


OMonsterSlimeBlue::~OMonsterSlimeBlue()
{
}

HRESULT OMonsterSlimeBlue::Init(string key, int pos)
{
	MonsterBase::Init(key,pos);

	myMoveBeat = 2;
	subX = 0;
	subY = 20;
	damage = 1;
	m_hp = 2;
	m_currentHp = 2;

	return S_OK;
}

void OMonsterSlimeBlue::Release()
{
}

void OMonsterSlimeBlue::Update()
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
			PatternLoad();
			//AStarLoad();
		}
		

		isBeatTime = false;
	}

		EffectAnim();
}

void OMonsterSlimeBlue::Render()
{
	MonsterBase::Render();
	//mainImage->FrameRender(GetMemDC(), x - subX, y - subY - jump, m_frameX, 0);
	////{
	////
	////if (isSight)
	////{
	////	if (light == 0)
	////		mainImage->FrameRender(GetMemDC(), x-subX, y-subY, m_frameX, 1);
	////	else
	////		mainImage->FrameRender(GetMemDC(), x - subX, y - subY, m_frameX, 0);
	////}
	////else
	////{
	////	if (isFirstSight)
	////	{
	////		mainImage->FrameRender(GetMemDC(), x- subX, y-subY, m_frameX, 1);
	////	}
	////}
	//// ¸Â¾ÑÀ» °æ¿ì hp ·»´õ
	//if (isShowHp && m_hp != m_currentHp)
	//{
	//	for (int i = m_currentHp; i < m_hp; i++)
	//	{
	//		//IMAGEMANAGER->Render("TEMP_heart_empty_small", GetMemDC(), (x + 26) - (m_hp / 2) * 24 + 24 * i - 7, y - 71);
	//		maxHpImage->Render(GetMemDC(), (x + 26) - (m_hp / 2) * 24 + 24 * i - 7, y - subY -  24);
	//	}
	//	for (int i = 0; i < m_currentHp; i++)
	//	{
	//		//IMAGEMANAGER->Render("TEMP_heart_small", GetMemDC(), (x + 26) - (m_hp / 2) * 24 + 24 * i - 7, y - 71);
	//		curHpImage->Render(GetMemDC(), (x + 26) - (m_hp / 2) * 24 + 24 * i - 7, y - subY - 24);
	//	}
	//}
	////light = 0;
	////isSight = 0;
	////
	//
	//EffectRender();

}

void OMonsterSlimeBlue::Anim()
{
	count++;
	if (isRight)
	{
		if (count % 5 == 0)
		{
			count = 0;
			m_frameX = m_frameX - 1;
			if (m_frameX < 8) m_frameX = 15;
		}
	}
	else
	{
		if (count % 5 == 0)
		{
			count = 0;
			m_frameX = (m_frameX + 1) % 8;
		}
	}
}
