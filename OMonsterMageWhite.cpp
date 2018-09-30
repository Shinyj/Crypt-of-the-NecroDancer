#include "stdafx.h"
#include "OMonsterMageWhite.h"
#include "OPlayer1.h"


OMonsterMageWhite::OMonsterMageWhite()
{
}


OMonsterMageWhite::~OMonsterMageWhite()
{
}

HRESULT OMonsterMageWhite::Init(string key, int pos)
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

void OMonsterMageWhite::Release()
{
}

void OMonsterMageWhite::Update()
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
			if (GrapMagic())
			{
				OBJECTMANAGER->FlashOn();
			}
			else
				AStarLoad();
		}


		isBeatTime = false;
	}

	EffectAnim();
}

void OMonsterMageWhite::Render()
{
	MonsterBase::Render();
}

void OMonsterMageWhite::Anim()
{
	count++;
	if (isRight)
	{
		if (myCurrentMoveBeat == 0)
		{
			if (count % 10 == 0)
			{
				count = 0;
				m_frameX -= 1;
				if (m_frameX < 9)
					m_frameX = 13;
			}

		}
		else if (myCurrentMoveBeat == 1)
		{
			if (count % 10 == 0)
			{
				count = 0;

				m_frameX -= 1;
				if (m_frameX < 7)
					m_frameX = 8;
			}
		}
	}
	else
	{
		if (myCurrentMoveBeat == 0)
		{
			if (count % 10 == 0)
			{
				count = 0;

				m_frameX = (m_frameX + 1) % 5;

			}
		}
		else if (myCurrentMoveBeat == 1)
		{
			if (count % 10 == 0)
			{
				count = 0;

				if (m_frameX != 5)
					m_frameX = 5;
				else
					m_frameX = 6;

			}
		}
	}
}

bool OMonsterMageWhite::GrapMagic()
{
	OPlayer1 * player = OBJECTMANAGER->GetPlayer();
	int playerPos = player->GetPos();

	if (playerPos == m_pos + 2)
	{
		if (OBJECTMANAGER->GetIsThereObj(m_pos + 1) == NULL)
		{
			SOUNDMANAGER->Play("wep_spell_wind",OBJECTMANAGER->GetEffectVolum());
			int x = player->GetX();
			int y = player->GetY();
			OBJECTMANAGER->SetTilePos(player, m_pos + 1);
			player->SetXY2(x - 52, y);
			return true;
		}
	}
	else if (playerPos == m_pos - 2)
	{
		if (OBJECTMANAGER->GetIsThereObj(m_pos - 1) == NULL)
		{
			SOUNDMANAGER->Play("wep_spell_wind", OBJECTMANAGER->GetEffectVolum());
			int x = player->GetX();
			int y = player->GetY();
			OBJECTMANAGER->SetTilePos(player, m_pos - 1);
			player->SetXY2(x + 52, y);
			//player->SetXY(POINT{ x + 52, y });
			return true;
		}
	}
	else if (playerPos == m_pos - 100)
	{
		if (OBJECTMANAGER->GetIsThereObj(m_pos - 50) == NULL)
		{
			SOUNDMANAGER->Play("wep_spell_wind", OBJECTMANAGER->GetEffectVolum());
			int x = player->GetX();
			int y = player->GetY();
			OBJECTMANAGER->SetTilePos(player, m_pos - 50);
			player->SetXY2(x, y + 52);
			return true;
		}
	}
	else if (playerPos == m_pos + 100)
	{
		if (OBJECTMANAGER->GetIsThereObj(m_pos + 50) == NULL)
		{
			SOUNDMANAGER->Play("wep_spell_wind", OBJECTMANAGER->GetEffectVolum());
			int x = player->GetX();
			int y = player->GetY();
			OBJECTMANAGER->SetTilePos(player, m_pos + 50);
			player->SetXY2(x, y - 52);
			return true;
		}
	}
	return false;
}
