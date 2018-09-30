#include "stdafx.h"
#include "OMonsterSkeletonYellow.h"
#include "OPlayer1.h"

OMonsterSkeletonYellow::OMonsterSkeletonYellow()
{
}


OMonsterSkeletonYellow::~OMonsterSkeletonYellow()
{
}

HRESULT OMonsterSkeletonYellow::Init(string key, int pos)
{
	MonsterBase::Init(key, pos);

	myMoveBeat = 2;
	subX = 0;
	subY = 20;
	damage = 1;
	m_hp = 2;
	m_currentHp = 2;
	isPattern = false;
	return S_OK;
}

void OMonsterSkeletonYellow::Release()
{
}

void OMonsterSkeletonYellow::Update()
{
	Anim();

	JumpMove();

	if (isBeatTime)
	{
		myCurrentMoveBeat++;
		if (myMoveBeat <= myCurrentMoveBeat)
		{
			myCurrentMoveBeat = 0;
			//RendomLoad();
			//PatternLoad();
			
			if (!isPattern)
				AStarLoad();
			else
				PatternMove();
		}


		isBeatTime = false;
	}

	EffectAnim();
}

void OMonsterSkeletonYellow::Render()
{
	MonsterBase::Render();
	//mainImage->FrameRender(GetMemDC(), x - subX, y - subY - jump, m_frameX, 0);
	//{
	//	//
	//	//if (isSight)
	//	//{
	//	//	if (light == 0)
	//	//		mainImage->FrameRender(GetMemDC(), x-subX, y-subY, m_frameX, 1);
	//	//	else
	//	//		mainImage->FrameRender(GetMemDC(), x - subX, y - subY, m_frameX, 0);
	//	//}
	//	//else
	//	//{
	//	//	if (isFirstSight)
	//	//	{
	//	//		mainImage->FrameRender(GetMemDC(), x- subX, y-subY, m_frameX, 1);
	//	//	}
	//	//}
	//	//// ¸Â¾ÑÀ» °æ¿ì hp ·»´õ
	//	//if (isShowHp && m_hp != m_currentHp)
	//	//{
	//	//	for (int i = m_currentHp; i < m_hp; i++)
	//	//	{
	//	//		//IMAGEMANAGER->Render("TEMP_heart_empty_small", GetMemDC(), (x + 26) - (m_hp / 2) * 24 + 24 * i - 7, y - 71);
	//	//		maxHpImage->Render(GetMemDC(), (x + 26) - (m_hp / 2) * 24 + 24 * i - 7, y - subY -  24);
	//	//	}
	//	//	for (int i = 0; i < m_currentHp; i++)
	//	//	{
	//	//		//IMAGEMANAGER->Render("TEMP_heart_small", GetMemDC(), (x + 26) - (m_hp / 2) * 24 + 24 * i - 7, y - 71);
	//	//		curHpImage->Render(GetMemDC(), (x + 26) - (m_hp / 2) * 24 + 24 * i - 7, y - subY - 24);
	//	//	}
	//}
	////light = 0;
	////isSight = 0;
	////
	//
	//EffectRender();
}

void OMonsterSkeletonYellow::Anim()
{
	count++;
	
	if (!isPattern)
	{
		if (isRight)
		{
			if (count % 5 == 0)
			{
				count = 0;
				if (myCurrentMoveBeat == 0)
				{
					m_frameX = m_frameX - 1;
					if (m_frameX < 14) m_frameX = 17;
				}
				else 
				{
					m_frameX = m_frameX - 1;
					if (m_frameX < 10) m_frameX = 13;
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
					m_frameX = (m_frameX + 1) % 4 +4;

			}
		}
	}
	else
	{
		if (isRight)
			m_frameX = 9;
		else
			m_frameX = 8;
	}
}


void OMonsterSkeletonYellow::Defence(int damage)
{
	isShowHp = true;

	m_currentHp -= damage;

	if (m_currentHp <= 0)
		this->Die();
	else if (m_currentHp == 1)
	{
		isPattern = true;
		OPlayer1 * player = OBJECTMANAGER->GetPlayer();

		int px = x - player->GetX();
		int py = y - player->GetY();
		int absX = (px > 0) ? px : -px;
		int absY = (py > 0) ? py : -py;

		if (absX > absY)
		{
			if (px > 0)
				patternDIr = M_RIGHT;
			else
				patternDIr = M_LEFT;
		}
		else
		{
			if (py > 0)
				patternDIr = M_UP;
			else
				patternDIr = M_DOWN;
		}

		myMoveBeat = 1;
		myCurrentMoveBeat = 1;
	}
}

void OMonsterSkeletonYellow::PatternMove()
{
	moveCount = TILESIZE;

	m_move = patternDIr;

	if (patternDIr == M_LEFT)
		isRight = false;
	else
		isRight = true;


	GameObject * obj = OBJECTMANAGER->GetIsThereObj(m_pos + m_move);
	OBJECTKIND objKind;

	if (obj != NULL)
	{
		objKind = obj->GetObjKind();

		if (objKind == OBJ_PLAYER)
			Attcked(m_move);

		m_move = patternDIr;
		isHalfMove = true;
		moveCount = TILESIZE;
		return;
	}

	OBJECTMANAGER->SetTilePos(this, m_pos + m_move);
}
