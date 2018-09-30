#include "stdafx.h"
#include "OMonsterDragonRed.h"
#include "OPlayer1.h"

OMonsterDragonRed::OMonsterDragonRed()
{
}


OMonsterDragonRed::~OMonsterDragonRed()
{
}

HRESULT OMonsterDragonRed::Init(string key, int pos)
{
	MonsterBase::Init(key, pos);
	myMoveBeat = 2;
	subX = 40;
	subY = 70;
	damage = 3;
	m_hp = 6;
	m_currentHp = 6;
	m_state = D_IDLE;
	fireRight = true;

	fire0 = IMAGEMANAGER->FindImage("fire0");
	fire1 = IMAGEMANAGER->FindImage("fire1");

	return S_OK;
}

void OMonsterDragonRed::Release()
{
}

void OMonsterDragonRed::Update()
{
	Anim();

	JumpMove();

	if (isBeatTime)
	{
		myCurrentMoveBeat++;

		if (SearchTarget() && myCurrentMoveBeat != 0) 
		{
			//myMoveBeat = 1;
			//myCurrentMoveBeat = 2;
		}
		else if (myMoveBeat <= myCurrentMoveBeat)
		{
			switch (m_state)
			{
			case D_IDLE :
				AStarLoad();
				SearchTarget();
				reload = true;
				break;
			case D_PREFIRE :
				Fire();

				break;
			case D_FIRE :
				break;
			}
			//RendomLoad();
			//PatternLoad();
			myCurrentMoveBeat = 0;
		}


		isBeatTime = false;
	}

	EffectAnim();
}

void OMonsterDragonRed::Render()
{
	MonsterBase::Render();

	FireRender();

}

void OMonsterDragonRed::Anim()
{
	count++;

	if (count % 3 == 0)
	{
		fireFrameX++;

		if (fireFrameX == 7)
		{
			isFire = false;
			m_state = D_IDLE;
			myMoveBeat = 2;
			myCurrentMoveBeat = 0;
		}
	}
	
	if (m_state == D_IDLE)
	{
		if (isRight)
		{
			if (count % 20 == 0)
			{
				count = 0;
				m_frameX = m_frameX - 1;
				if (m_frameX < 12) m_frameX = 13;
			}
		}
		else
		{
			if (count % 20 == 0)
			{
				count = 0;
				m_frameX = (m_frameX + 1) % 2;
			}
		}
	}
	else if (m_state == D_PREFIRE)
	{
		if (isRight)
		{
			if (count % 5 == 0)
			{
				count = 0;
				m_frameX = m_frameX - 1;
				if (m_frameX < 9) m_frameX = 9;
			}
		}
		else
		{
			if (count % 5 == 0)
			{
				count = 0;
				m_frameX = m_frameX + 1;
				if (m_frameX > 4) m_frameX = 4;
			}
		}
	}
	else if (m_state == D_FIRE)
	{
		if (isRight)
		{
			if (count % 5 == 0)
			{
				count = 0;
				m_frameX = m_frameX - 1;
				if (m_frameX < 7) m_frameX = 7;
			}
		}
		else
		{
			if (count % 5 == 0)
			{
				count = 0;
				m_frameX = m_frameX + 1;
				if (m_frameX > 6) m_frameX = 6;
			}
		}
	}
}

void OMonsterDragonRed::JumpMove()
{
	if (!isHalfMove)
	{
		switch (m_move)
		{
		case M_LEFT:
			moveCount -= 4;
			x -= 4;
			if (moveCount)
			{
				if (moveCount > TILESIZE / 2)
					jump -= 6;
				else jump += 6;
			}
			if (moveCount == 0)
			{
				SOUNDMANAGER->Play("en_dragon_walk_01",OBJECTMANAGER->GetEffectVolum());
				m_move = M_NONE;
			}
			break;
		case M_RIGHT:
			moveCount -= 4;
			x += 4;
			if (moveCount)
			{
				if (moveCount > TILESIZE / 2)
					jump -= 6;
				else jump += 6;
			}
			if (moveCount == 0)
			{
				SOUNDMANAGER->Play("en_dragon_walk_01", OBJECTMANAGER->GetEffectVolum());
				m_move = M_NONE;
			}
			break;
		case M_UP:
			moveCount -= 4;
			y -= 4;
			if (moveCount)
			{
				if (moveCount > TILESIZE / 2)
					jump -= 6;
				else jump += 6;
			}
			if (moveCount == 0)
			{
				SOUNDMANAGER->Play("en_dragon_walk_01", OBJECTMANAGER->GetEffectVolum());
				m_move = M_NONE;
			}
			break;
		case M_DOWN:
			moveCount -= 4;
			y += 4;
			if (moveCount)
			{
				if (moveCount > TILESIZE / 2)
					jump -= 6;
				else jump += 6;
			}
			if (moveCount == 0)
			{
				SOUNDMANAGER->Play("en_dragon_walk_01", OBJECTMANAGER->GetEffectVolum());
				m_move = M_NONE;
			}
			break;
		}
	}
	else
	{
		switch (m_move)
		{
		case M_LEFT:
			moveCount -= 4;
			if (moveCount)
			{
			if (moveCount > TILESIZE / 2)
			{
				jump -= 6;
				x -= 4;
			}
			else
			{
				jump += 6;
				x += 4;
			}
			}
			if (moveCount == 0)
			{
				isHalfMove = false;
				m_move = M_NONE;
			}
			break;
		case M_RIGHT:
			moveCount -= 4;
			if (moveCount)
			{
				if (moveCount > TILESIZE / 2)
				{
					x += 4;
					jump -= 6;
				}
				else
				{
					x -= 4;
					jump += 6;
				}
			}
			if (moveCount == 0)
			{
				isHalfMove = false;
				m_move = M_NONE;
			}
			break;
		case M_UP:
			moveCount -= 4;
			if (moveCount)
			{
				if (moveCount > TILESIZE / 2)
				{
					y -= 4;
					jump -= 6;
				}
				else
				{
					y += 4;
					jump += 6;
				}
			}
			if (moveCount == 0)
			{
				isHalfMove = false;
				m_move = M_NONE;
			}
			break;
		case M_DOWN:
			moveCount -= 4;

			if (moveCount)
			{
				if (moveCount > TILESIZE / 2)
				{
					jump -= 6;
					y += 4;
				}
				else
				{
					jump += 6;
					y -= 4;
				}
			}
			if (moveCount == 0)
			{
				isHalfMove = false;
				m_move = M_NONE;
			}
			break;
		}

	}
}

bool OMonsterDragonRed::SearchTarget()
{
	if (m_state != D_IDLE || reload == false)
		return false;

	OPlayer1 * player = OBJECTMANAGER->GetPlayer();
	int playerPos = player->GetPos();

	if (playerPos / 50 == m_pos / 50)
	{

		if (playerPos < m_pos)
		{
			for (int i = 1; i < m_pos - playerPos; i++)
			{
				GameObject * obj = OBJECTMANAGER->GetIsThereObj(m_pos - i);
				if (obj != NULL)
				{
					if (obj->GetObjKind() == OBJ_WALL)
						return false;
				}
			}

			SOUNDMANAGER->Play("en_dragon_attack_prefire", OBJECTMANAGER->GetEffectVolum());
			m_state = D_PREFIRE;
			isRight = false;
			fireRight = false;
			myMoveBeat = 1;
			myCurrentMoveBeat = 0;
			return true;
		}
		else
		{
			for (int i = 1; i < playerPos - m_pos; i++)
			{
				GameObject * obj = OBJECTMANAGER->GetIsThereObj(m_pos + i);
				if (obj != NULL)
				{
					if (obj->GetObjKind() == OBJ_WALL)
						return false;
				}
			}

			SOUNDMANAGER->Play("en_dragon_attack_prefire", OBJECTMANAGER->GetEffectVolum());
			m_state = D_PREFIRE;
			isRight = true;
			fireRight = true;
			myCurrentMoveBeat = 0;
			myMoveBeat = 1;
			return true;
		}
	}
	return false;
}

void OMonsterDragonRed::Fire()
{
	reload = false;
	m_state = D_FIRE;
	isFire = true;
	SOUNDMANAGER->Play("en_dragon_attack_fire");
	fireFrameX = 0;
	for (int i = 0; i < 50; i++) fireWay[i] = 0;

	GameObject * obj;
	if (fireRight)
	{
		for (int i = 1; ;i++)
		{
			obj = OBJECTMANAGER->GetIsThereObj(m_pos + i);
			fireWay[i] = 52 * i;
			if (obj != NULL)
			{
				if (obj->GetObjKind() == OBJ_WALL)
				{
					fireWay[i] = 0;
					break;
				}
				else if (obj->GetObjKind() == OBJ_MONSTER || obj->GetObjKind() == OBJ_PLAYER)
				{
					obj->Defence(2);
				}
			}
		}
	}
	else
	{
		for (int i = 1; ; i++)
		{
			obj = OBJECTMANAGER->GetIsThereObj(m_pos - i);
			fireWay[i] = - (52 * i);

			if (obj != NULL)
			{
				if (obj->GetObjKind() == OBJ_WALL)
				{
					fireWay[i] = 0;
					break;
				}
				else if (obj->GetObjKind() == OBJ_MONSTER || obj->GetObjKind() == OBJ_PLAYER)
				{
					obj->Defence(2);
				}
			}
		}
	}
}

void OMonsterDragonRed::FireRender()
{
	if (isFire)
	{
		for (int i = 1; ; i++)
		{
			if (fireWay[i] == 0) break;
			
			if (i == 1)
			{
				if (fireRight)
					fire0->FrameRender(GetMemDC(),x + fireWay[i],y-20, fireFrameX,0);
				else
					fire0->FrameRender(GetMemDC(),x + fireWay[i], y-20, 13 - fireFrameX, 0);
			}
			else
			{
				fire1->FrameRender(GetMemDC(),x + fireWay[i], y-20, fireFrameX,0);
			}
		}
	}

}
