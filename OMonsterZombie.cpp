#include "stdafx.h"
#include "OMonsterZombie.h"
#include "OItemGold.h"
#include "OPlayer1.h"
#include "OMonsterKingconga.h"
OMonsterZombie::OMonsterZombie()
{
}


OMonsterZombie::~OMonsterZombie()
{
}

HRESULT OMonsterZombie::Init(string key, int pos)
{
	MonsterBase::Init(key, pos);


	myMoveBeat = 2;
	subX = 0;
	subY = 20;
	damage = 1;
	m_hp = 1;
	m_currentHp = 1;
	isShowHp = true;

	m_state = Z_IDLE;
	
	nextPos = -1;
	
	nextZombie = NULL;
	beforeZombie = NULL;
	isJump = false;
	isZombieUpdate = false;
	return S_OK;
}

void OMonsterZombie::Release()
{
}

void OMonsterZombie::Update()
{

	GameObject * obj = OBJECTMANAGER->GetIsThereFloor(m_pos);
	obj->SetLight(true);
	obj->SetFirstSight();
	obj->SetIsSight(true);


	if (KEYMANAGER->IsOnceKeyDown('D'))
		this->Die();

	Anim();

	JumpMove();

	if (!isZombieUpdate)
	{
		if (beforeZombie == NULL)
		{
			m_state = Z_HEAD;
			if (nextZombie == NULL)
			{
				myMoveBeat = 1;
				myCurrentMoveBeat = 0;
				m_state = Z_ALONE;
			}
		}
		else
			nextPos = beforeZombie->GetPos();

		if (m_state == Z_HEAD || m_state == Z_ALONE)
		{
			if(isBeatTime)
				HeadUpdate();

		}
	}
	else 
	{
		

		if (isBeatTime)
		{
			myCurrentMoveBeat++;
			if (myMoveBeat <= myCurrentMoveBeat)
			{
				isJump = true;;
				myCurrentMoveBeat = 0;
				//RendomLoad();
				//PatternLoad();
				
				if (m_state == Z_HEAD || m_state == Z_ALONE)
				{
					AStarLoad();
					//HeadUpdate();
				}
				else
				{
					moveCount = TILESIZE;

					
					m_move = (DIRECTION) ( nextPos - m_pos);
					direction = m_move;
					GameObject * obj = OBJECTMANAGER->GetIsThereObj(m_pos + m_move);
					OBJECTKIND objKind;

					switch (direction)
					{
					case M_UP:
						break;
					case M_DOWN:
						break;
					case M_LEFT:
						isRight = false;
						break;
					case M_RIGHT:
						isRight = true;
						break;
					}

					if (obj != NULL)
					{
						objKind = obj->GetObjKind();

						if (objKind == OBJ_PLAYER)
							Attcked(m_move);
						else
						{
							isHalfMove = true;

						}
						//m_move = M_NONE;
						//moveCount = 0;
					}
					else
						OBJECTMANAGER->SetTilePos(this, m_pos + m_move);
				}
			}
			isBeatTime = false;
		}
	}

	EffectAnim();
}

void OMonsterZombie::Render()
{
	//MonsterBase::Render();
	//mainImage->FrameRender(GetMemDC(), x - subX, y - subY + jump, m_frameX, 0);
	//{
	//

	int dummyFrameX = m_frameX;

	switch (direction)
	{
	case M_UP :
		break;
	case M_DOWN:
		dummyFrameX += 16;
		break;
	case M_LEFT:
		dummyFrameX += 8;
		break;
	case M_RIGHT:
		dummyFrameX += 8;
		break;
	}

	switch (m_state)
	{
	case Z_IDLE:
		if (isRight)
			mainImage->FrameRender(GetMemDC(), x - subX, y - subY + jump, 71 - dummyFrameX, 1);
		else
			mainImage->FrameRender(GetMemDC(), x - subX, y - subY + jump, dummyFrameX, 0);
		break;
	case Z_HEAD:
		if (isRight)
			mainImage->FrameRender(GetMemDC(), x - subX, y - subY + jump, 71 - (dummyFrameX + 24), 1);
		else
			mainImage->FrameRender(GetMemDC(), x - subX, y - subY + jump, dummyFrameX + 24, 0);
		break;
	case Z_ALONE:
		if (isRight)
			mainImage->FrameRender(GetMemDC(), x - subX, y - subY + jump, 71 - (dummyFrameX + 48 ), 1);
		else
			mainImage->FrameRender(GetMemDC(), x - subX, y - subY + jump, dummyFrameX + 48, 0);
		break;
	}


	////                  여기 풀어
	//if (isSight)
	//{
	//	if (light == 0)
	//		mainImage->FrameRender(GetMemDC(), x-subX, y-subY, m_frameX, 1);
	//	else
	//		mainImage->FrameRender(GetMemDC(), x - subX, y - subY, m_frameX, 0);
	//}
	//else
	//{
	//	if (isFirstSight)
	//	{
	//		mainImage->FrameRender(GetMemDC(), x- subX, y-subY, m_frameX, 1);
	//	}
	//}
	////// 맞앗을 경우 hp 렌더


	if (isShowHp)
	{
		for (int i = m_currentHp; i < m_hp; i++)
		{
			//IMAGEMANAGER->Render("TEMP_heart_empty_small", GetMemDC(), (x + 26) - (m_hp / 2) * 24 + 24 * i - 7, y - 71);
			maxHpImage->Render(GetMemDC(), (x + 26) - (m_hp / 2) * 24 + 24 * i - 7, y - subY - 24);
		}
		for (int i = 0; i < m_currentHp; i++)
		{
			//IMAGEMANAGER->Render("TEMP_heart_small", GetMemDC(), (x + 26) - (m_hp / 2) * 24 + 24 * i - 7, y - 71);
			curHpImage->Render(GetMemDC(), (x + 26) - (m_hp / 2) * 24 + 24 * i - 7, y - subY - 24);
		}
	}
	//light = 0;
	//isSight = 0;
	// ////////////////////////////// 

	//char str[100];
	//sprintf(str, "%d", direction);
	//TextOut(GetMemDC(), x, y, str, strlen(str));

	EffectRender();
}

void OMonsterZombie::SetNextNULL()
{
	nextZombie = NULL;
}

void OMonsterZombie::SetBeforeNULL()
{
	beforeZombie = NULL;
}

void OMonsterZombie::SetNext(OMonsterZombie * obj)
{
	this->nextZombie = obj;
}

void OMonsterZombie::SetBefore(OMonsterZombie * obj)
{
	this->beforeZombie = obj;
}

void OMonsterZombie::Anim()
{
	count++;

	if (isJump)
	{
		if (count % 10 == 0)
		{
			count = 0;
			m_frameX = (m_frameX + 1);
			if (m_frameX > 5) m_frameX = 2;
		}
	}
	else
	{
		if (count % 10 == 0)
		{
			count = 0;
			if (m_frameX == 0) m_frameX = 1;
			else if (m_frameX == 1) m_frameX = 6;
			else if (m_frameX == 6) m_frameX = 7;
			else if (m_frameX == 7) m_frameX = 0;
		}
	}
}

void OMonsterZombie::Die()
{
	king->SetZombieDieCount();
	
	VoiceDie();
	OBJECTMANAGER->SetFever();

	if (nextZombie != NULL)
		nextZombie->SetBeforeNULL();
	if (beforeZombie != NULL)
		beforeZombie->SetNextNULL();
	

	OBJECTMANAGER->DeleteObj(this);
	
}

void OMonsterZombie::Defence(int damage)
{
	VoiceHit();
	isShowHp = true;

	m_currentHp -= damage;

	if (m_currentHp <= 0)
		this->Die();
}

void OMonsterZombie::ZomebieUpdate()
{
	isZombieUpdate = true;
	isBeatTime = true;
	//myCurrentMoveBeat = 2;
	Update();
	isZombieUpdate = false;
	isBeatTime = false;
	//myCurrentMoveBeat = 0;
}

void OMonsterZombie::HeadUpdate()
{
	OMonsterZombie * cur = this;
	//cur = cur->nextZombie;

	while (cur)
	{
		cur->ZomebieUpdate();
		cur = cur->nextZombie;
	}
}
