#include "stdafx.h"
#include "OMonsterMinotaur2.h"
#include "OMonsterMinotaur.h"
#include "OPlayer1.h"

OMonsterMinotaur2::OMonsterMinotaur2()
{
}


OMonsterMinotaur2::~OMonsterMinotaur2()
{
}

HRESULT OMonsterMinotaur2::Init(string key, int pos)
{
	MonsterBase::Init(key, pos);

	myMoveBeat = 1;
	subX = 22;
	subY = 67;
	damage = 2;
	m_hp = 3;
	m_currentHp = 3;

	m_state = MINO_IDLE;

	return S_OK;
}

void OMonsterMinotaur2::Release()
{
}

void OMonsterMinotaur2::Update()
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
			switch (m_state)
			{
			case MINO_IDLE:
				if (AStarLoad())
					SearchTarget();
				else
					Charged();
				break;
			case MINO_CHARGE:
				Charged();
				break;
			case MINO_STURN:
				Sturn();
				break;

			}
		}
		isBeatTime = false;
	}

	EffectAnim();
}

void OMonsterMinotaur2::Render()
{
	MonsterBase::Render();
}

void OMonsterMinotaur2::Anim()
{
	count++;

	switch (m_state)
	{
	case MINO_IDLE:
		if (isRight)
		{
			if (count % 10 == 0)
			{
				count = 0;
				m_frameX = m_frameX - 1;
				if (m_frameX < 14) m_frameX = 17;
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
		break;
	case MINO_CHARGE:
		if (isRight)
			m_frameX = 13;
		else
			m_frameX = 4;
		break;
	case MINO_STURN:
		if (isRight)
		{
			if (count % 10 == 0)
			{
				count = 0;
				m_frameX = m_frameX - 1;
				if (m_frameX < 9) m_frameX = 12;
			}
		}
		else
		{
			if (count % 10 == 0)
			{
				count = 0;
				m_frameX = m_frameX + 1;
				if (m_frameX > 8) m_frameX = 5;
			}
		}
		break;
	}
}

bool OMonsterMinotaur2::SearchTarget()
{
	OPlayer1 * player = OBJECTMANAGER->GetPlayer();
	int playerPos = player->GetPos();

	if (playerPos / 50 == m_pos / 50)
	{
		SOUNDMANAGER->Play("en_minotaur_charge", OBJECTMANAGER->GetEffectVolum());

		m_state = MINO_CHARGE;
		if (playerPos < m_pos)
		{
			direction = M_LEFT;
			isRight = false;
		}
		else
		{
			direction = M_RIGHT;
			isRight = true;
		}
		return true;
	}
	else if (playerPos % 10 == m_pos % 10)
	{
		SOUNDMANAGER->Play("en_minotaur_charge", OBJECTMANAGER->GetEffectVolum());

		m_state = MINO_CHARGE;
		if (playerPos < m_pos)
			direction = M_UP;
		else
			direction = M_DOWN;

		return true;
	}
	return false;
}

void OMonsterMinotaur2::Charged()
{
	GameObject * obj;

	obj = OBJECTMANAGER->GetIsThereObj(m_pos + direction);

	if (obj == NULL)
	{
		moveCount = TILESIZE;
		m_move = direction;
		OBJECTMANAGER->SetTilePos(this, m_pos + m_move);
	}
	else
	{
		if (obj->GetObjKind() == OBJ_WALL)
		{
			if (obj->CanCrush(2))
			{
				SOUNDMANAGER->Play("en_minotaur_wallimpact", OBJECTMANAGER->GetEffectVolum());
				OBJECTMANAGER->DeleteObj(obj);
			}

			OBJECTMANAGER->GetPlayer()->SetEarthquake();
		}
		else if (obj->GetObjKind() == OBJ_PLAYER)
		{
			SOUNDMANAGER->Play("en_minotaur_attack", OBJECTMANAGER->GetEffectVolum());
			obj->Defence(damage);
		}

		m_state = MINO_STURN;
		myMoveBeat = 2;
		myCurrentMoveBeat = 0;
	}
}

void OMonsterMinotaur2::Sturn()
{
	m_state = MINO_IDLE;
	myMoveBeat = 1;
	myCurrentMoveBeat = 0;
}
