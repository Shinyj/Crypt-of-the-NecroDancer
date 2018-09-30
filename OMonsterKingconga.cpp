#include "stdafx.h"
#include "OMonsterKingconga.h"
#include "OPlayer1.h"

OMonsterKingconga::OMonsterKingconga()
{
}


OMonsterKingconga::~OMonsterKingconga()
{
}

HRESULT OMonsterKingconga::Init(string key, int pos)
{
	MonsterBase::Init(key, pos);

	myMoveBeat = 1;

	subX = 35; 
	subY = 79;
	damage = 2;
	m_hp = 6;
	m_currentHp = 6;
	isDrumming = true;
	drummingCount = 0;
	zombieDieCount = 0;

	chairImage = IMAGEMANAGER->FindImage("king_conga_throne");

	return S_OK;
}

void OMonsterKingconga::Release()
{
}

void OMonsterKingconga::Update()
{
	//MonsterBase::Update();
	Anim();
	
	JumpMove();
	
	GameObject * obj = OBJECTMANAGER->GetIsThereFloor(m_pos);
	obj->SetLight(true);
	obj->SetFirstSight();
	obj->SetIsSight(true);


	if (zombieDieCount >= 16 && isDrumming)
	{
		isDrumming = false;
		SOUNDMANAGER->Play("en_kingconga_cry_01",OBJECTMANAGER->GetEffectVolum());
	}
	
	
	if (isBeatTime)
	{
		drummingCount++;
		myCurrentMoveBeat++;
		if ( myMoveBeat <= myCurrentMoveBeat)
		{
			myCurrentMoveBeat = 0;
	
			if (isDrumming)
			{
	
			}
			else
				AStarLoad();
		}
		isBeatTime = false;
	}
	EffectAnim();
}

void OMonsterKingconga::Render()
{
	//chairImage->Render(GetMemDC(), chairX - 18, chairY - subY);
	
	light = true;
	isSight = true;

	if (isSight)
	{
		shadowImage->AlphaRender(GetMemDC(), x, y - 20, 50);

		if (light == 0)
			mainImage->FrameRender(GetMemDC(), x - subX, y - subY - jump, m_frameX, 1);
		else
			mainImage->FrameRender(GetMemDC(), x - subX, y - subY - -jump, m_frameX, 0);
	}
	else
	{
		if (isFirstSight)
		{
			mainImage->FrameRender(GetMemDC(), x - subX, y - subY, m_frameX, 1);
		}
	}
	////// 맞앗을 경우 hp 렌더
	if (isShowHp && m_hp != m_currentHp)
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
	isSight = 0;
	// ////////////////////////////// 

	EffectRender();
}

void OMonsterKingconga::Anim()
{
	count++;

	chairX = OBJECTMANAGER->GetIsThereFloor(458)->GetX();
	chairY = OBJECTMANAGER->GetIsThereFloor(458)->GetY();

	if(isDrumming)
	{
		if (drummingCount > 6)
		{
			m_frameX = 4;
		}
		else
		{

			if (m_frameX == 0 || m_frameX == 2)
			{
				if (count % 10 == 0)
				{
					count = 0;
					m_frameX = m_frameX + 1;
			
				}
			}
			else
			{
				if (isBeatTime)
					m_frameX++;
			}

			if (m_frameX > 3) m_frameX = 0;
		}

		if (isBeatTime)
			if (drummingCount > 6)
			{
				drummingCount = 0;
			}
	}
	else
	{
		if (isBeatTime)
		{
			if (isRight)
			{
				if (m_frameX != 7)
					m_frameX = 7;
				else
					m_frameX = 8;
			}
			else
			{
				if (m_frameX != 6)
					m_frameX = 6;
				else
					m_frameX = 5;
			}
		}
	}

}


void OMonsterKingconga::Die()
{
	VoiceDie();
	OBJECTMANAGER->SetFever();

	OBJECTMANAGER->DeleteObj(this);
	
	for (int i = 406; i < 411; i++)
		OBJECTMANAGER->DeleteObj(OBJECTMANAGER->GetIsThereObj(i));

}

void OMonsterKingconga::AStarLoad()
{

	OPlayer1 * player = OBJECTMANAGER->GetPlayer();

	int dirction = player->GetPos() - m_pos;

	if (dirction == -1 || dirction == 1 || dirction == -50 || dirction == 50
		|| dirction == 51 || dirction == 49 || dirction == -49 || dirction == -51)
	{
		this->direction = (DIRECTION)dirction;
		Attcked(direction);
		return;
	}

	_startPointSet = false;
	_endPointSet = false;

	for (int i = 0; i < TILEX; i++)
	{
		for (int j = 0; j < TILEY; j++)
		{
			_tile[i][j].type = TILE_TYPE_EMPTY;
			_tile[i][j].parent = NULL;		//부모 타일 = NULL;
			_tile[i][j].F = 5000;
			_tile[i][j].H = 0;
			_tile[i][j].i = i;
			_tile[i][j].j = j;
		}
	}
	_closeList.clear();
	_openList.clear();
	TileInitializing();
	while (1)
	{

		if (_aStarState == ASTAR_STATE_FOUND)
		{
			int i, j;
			aStarTile * tile = _closeList[_lastIndex];
			while (1)
			{
				tile = tile->parent;
				if (tile->parent == NULL || tile->parent->parent == NULL)
					break;
			}
			GameObject * obj;
			int nextPos = tile->i * 50 + tile->j;
			obj = OBJECTMANAGER->GetIsThereObj(nextPos);

			if (obj == NULL)
			{
				direction = (DIRECTION)(nextPos - m_pos);
				m_move = direction;

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
				case M_RD :
					isRight = true;
					break;
				case M_RU:
					isRight = true;
					break;
				case M_LD:
					isRight = false;
					break;
				case M_LU:
					isRight = false;
					break;
				}
				moveCount = TILESIZE;
				OBJECTMANAGER->SetTilePos(this, m_pos + m_move);
			}
			else if (obj->GetObjKind() == OBJ_MONSTER)
			{
				if (obj->GetImageKey() != "banshee" || obj->GetImageKey() != "banshee2")
					direction = (DIRECTION)(nextPos - m_pos);
				m_move = direction;

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
				case M_RD:
					isRight = true;
					break;
				case M_RU:
					isRight = true;
					break;
				case M_LD:
					isRight = false;
					break;
				case M_LU:
					isRight = false;
					break;
				}
				moveCount = TILESIZE;
				isHalfMove = true;
			}
			return;
		}
		else if (_aStarState == ASTAR_STATE_NOWAY)
		{
			//PatternLoad();
			return;
		}

		AddOpenList(); // 오픈 리스트에 추가
		CalculateH(); // 오픈 리스트 내 H 값 계산
		CalculateF(); // F 값을 계산
		AddCloseList(); // 클로즈 리스트에 추가
		CheckArrive(); // 도착을 했는가
	}
}

void OMonsterKingconga::TileComposition()
{

}

void OMonsterKingconga::TileInitializing()
{
	GameObject * obj;
	//objTile = OBJECTMANAGER->GetTileArr();

	for (int i = 0; i < TILEX; i++)
	{
		for (int j = 0; j < TILEY; j++)
		{
			obj = OBJECTMANAGER->GetIsThereObj(i * 50 + j);

			if (obj == NULL)
			{
				_tile[i][j].walkable = true;
				_tile[i][j].listOn = false;
			}
			else
			{
				OBJECTKIND kind = obj->GetObjKind();
				if (kind == OBJ_WALL)
				{
					_tile[i][j].walkable = false;
					_tile[i][j].listOn = false;
				}
				else if (kind == OBJ_ITEM)
				{
					_tile[i][j].walkable = false;
					_tile[i][j].listOn = false;
				}
				else if (kind == OBJ_MONSTER)
				{
					if (obj->GetPos() == m_pos)
					{
						_tile[i][j].walkable = true;
						_tile[i][j].listOn = true;
						_closeList.push_back(&_tile[i][j]);
						_startPointSet = true;
						_startX = j;
						_startY = i;
					}
					else
					{
						_tile[i][j].walkable = false;
						_tile[i][j].listOn = false;
					}
				}
				else if (kind == OBJ_PLAYER)
				{
					_tile[i][j].walkable = true;
					_tile[i][j].listOn = false;
					_endX = j;
					_endY = i;
				}
			}
		}
	}
	_aStarState = ASTAR_STATE_SEARCHING;
	_lastIndex = 0;
}

void OMonsterKingconga::AddOpenList()
{
	Ci = _closeList[_lastIndex]->i;
	Cj = _closeList[_lastIndex]->j;
	Cg = _closeList[_lastIndex]->G;


	if (_tile[Ci - 1][Cj].walkable) //상단 
	{
		//오픈 리스트에 추가가 되어있지 않다.
		if (!_tile[Ci - 1][Cj].listOn)
		{
			_tile[Ci - 1][Cj].listOn = true;
			_tile[Ci - 1][Cj].color = RGB(220, 255, 220);
			_tile[Ci - 1][Cj].G = Cg + 10;
			_tile[Ci - 1][Cj].parent = _closeList[_lastIndex];
			_openList.push_back(&_tile[Ci - 1][Cj]);
		}
		else
		{
			//기존 G값 보다 새로 계산한 G값이 작다면
			if (Cg + 10 < _tile[Ci - 1][Cj].G)
			{
				_tile[Ci - 1][Cj].G = Cg + 10;
				_tile[Ci - 1][Cj].parent = _closeList[_lastIndex];
			}
		}
	}
	// 좌상
	if (_tile[Ci - 1][Cj - 1].walkable)
	{
		if (!_tile[Ci - 1][Cj - 1].listOn)
		{
			_tile[Ci - 1][Cj - 1].listOn = true;
			_tile[Ci - 1][Cj - 1].color = RGB(220, 255, 220);
			_tile[Ci - 1][Cj - 1].G = Cg + 14;
			_tile[Ci - 1][Cj - 1].parent = _closeList[_lastIndex];
			_openList.push_back(&_tile[Ci - 1][Cj - 1]);
		}
		else
		{
			if (Cg + 14 < _tile[Ci - 1][Cj - 1].G)
			{
				_tile[Ci - 1][Cj - 1].G = Cg + 14;
				_tile[Ci - 1][Cj - 1].parent = _closeList[_lastIndex];
			}
		}
	}
	// 우상
	if (_tile[Ci - 1][Cj + 1].walkable) // 우
	{
		if (!_tile[Ci - 1][Cj + 1].listOn)
		{
			_tile[Ci - 1][Cj + 1].listOn = true;
			_tile[Ci - 1][Cj + 1].color = RGB(220, 255, 220);
			_tile[Ci - 1][Cj + 1].G = Cg + 14;
			_tile[Ci - 1][Cj + 1].parent = _closeList[_lastIndex];
			_openList.push_back(&_tile[Ci - 1][Cj + 1]);
		}
		else
		{
			if (Cg + 14 < _tile[Ci - 1][Cj + 1].G)
			{
				_tile[Ci - 1][Cj + 1].G = Cg + 14;
				_tile[Ci - 1][Cj + 1].parent = _closeList[_lastIndex];
			}
		}
	}
	if (_tile[Ci + 1][Cj].walkable) // 하단
	{
		//오픈 리스트에 추가가 되어있지 않다.
		if (!_tile[Ci + 1][Cj].listOn)
		{
			_tile[Ci + 1][Cj].listOn = true;
			_tile[Ci + 1][Cj].color = RGB(220, 255, 220);
			_tile[Ci + 1][Cj].G = Cg + 10;
			_tile[Ci + 1][Cj].parent = _closeList[_lastIndex];
			_openList.push_back(&_tile[Ci + 1][Cj]);
		}
		else
		{
			//기존 G값 보다 새로 계산한 G값이 작다면
			if (Cg + 10 < _tile[Ci + 1][Cj].G)
			{
				_tile[Ci + 1][Cj].G = Cg + 10;
				_tile[Ci + 1][Cj].parent = _closeList[_lastIndex];
			}
		}
	}
	// 좌하
	if (_tile[Ci + 1][Cj - 1].walkable)
	{
		if (!_tile[Ci + 1][Cj - 1].listOn)
		{
			_tile[Ci + 1][Cj - 1].listOn = true;
			_tile[Ci + 1][Cj - 1].color = RGB(220, 255, 220);
			_tile[Ci + 1][Cj - 1].G = Cg + 14;
			_tile[Ci + 1][Cj - 1].parent = _closeList[_lastIndex];
			_openList.push_back(&_tile[Ci + 1][Cj - 1]);
		}
		else
		{
			if (Cg + 14 < _tile[Ci + 1][Cj - 1].G)
			{
				_tile[Ci + 1][Cj - 1].G = Cg + 14;
				_tile[Ci + 1][Cj - 1].parent = _closeList[_lastIndex];
			}
		}
	}
	// 우하
	if (_tile[Ci + 1][Cj + 1].walkable) // 우
	{
		if (!_tile[Ci + 1][Cj + 1].listOn)
		{
			_tile[Ci + 1][Cj + 1].listOn = true;
			_tile[Ci + 1][Cj + 1].color = RGB(220, 255, 220);
			_tile[Ci + 1][Cj + 1].G = Cg + 14;
			_tile[Ci + 1][Cj + 1].parent = _closeList[_lastIndex];
			_openList.push_back(&_tile[Ci + 1][Cj + 1]);
		}
		else
		{
			if (Cg + 14 < _tile[Ci + 1][Cj + 1].G)
			{
				_tile[Ci + 1][Cj + 1].G = Cg + 14;
				_tile[Ci + 1][Cj + 1].parent = _closeList[_lastIndex];
			}
		}
	}
	if (_tile[Ci][Cj - 1].walkable) // 좌
	{
		if (!_tile[Ci][Cj - 1].listOn)
		{
			_tile[Ci][Cj - 1].listOn = true;
			_tile[Ci][Cj - 1].color = RGB(220, 255, 220);
			_tile[Ci][Cj - 1].G = Cg + 10;
			_tile[Ci][Cj - 1].parent = _closeList[_lastIndex];
			_openList.push_back(&_tile[Ci][Cj - 1]);
		}
		else
		{
			if (Cg + 10 < _tile[Ci][Cj - 1].G)
			{
				_tile[Ci][Cj - 1].G = Cg + 10;
				_tile[Ci][Cj - 1].parent = _closeList[_lastIndex];
			}
		}
	}

	if (_tile[Ci][Cj + 1].walkable) // 우
	{
		if (!_tile[Ci][Cj + 1].listOn)
		{
			_tile[Ci][Cj + 1].listOn = true;
			_tile[Ci][Cj + 1].color = RGB(220, 255, 220);
			_tile[Ci][Cj + 1].G = Cg + 10;
			_tile[Ci][Cj + 1].parent = _closeList[_lastIndex];
			_openList.push_back(&_tile[Ci][Cj + 1]);
		}
		else
		{
			if (Cg + 10 < _tile[Ci][Cj + 1].G)
			{
				_tile[Ci][Cj + 1].G = Cg + 10;
				_tile[Ci][Cj + 1].parent = _closeList[_lastIndex];
			}
		}
	}
	/////////////////////////////////
}

void OMonsterKingconga::CalculateH()
{
	for (int i = 0; i < _openList.size(); i++)
	{
		int vertical = (_endX - _openList[i]->j) * 10; // 가로 H값
		int horizontal = (_endY - _openList[i]->i) * 10; // 세로 H값

		if (vertical < 0)vertical *= -1;
		if (horizontal < 0) horizontal *= -1;

		_openList[i]->H = vertical + horizontal; // 총 H 값
	}
}

void OMonsterKingconga::CalculateF()
{
	for (int i = 0; i < _openList.size(); i++)
	{
		_openList[i]->F = _openList[i]->G + _openList[i]->H;
	}
}

void OMonsterKingconga::AddCloseList()
{
	if (_openList.size() == 0)
	{
		_aStarState = ASTAR_STATE_NOWAY;
		return; // 최단 경로가 없당
	}

	int index = 0; // 오픈 리스트 중 가장 F값이 작은 타일의 인덱스
	int lowest = 5000; // 오픈 리스트 중 가장 작은 F값
	for (int i = 0; i < _openList.size(); i++)
	{
		if (_openList[i]->F < lowest)
		{
			lowest = _openList[i]->F;
			index = i;
		}
	}
	_openList[index]->color = RGB(180, 180, 255);
	_closeList.push_back(_openList[index]);
	_openList.erase(_openList.begin() + index);

	_lastIndex++; // 가장 마지막에 추가된 클로즈의 인덱스
}

void OMonsterKingconga::CheckArrive()
{
	if (_closeList[_lastIndex]->i == _endY &&
		_closeList[_lastIndex]->j == _endX)
	{
		_aStarState = ASTAR_STATE_FOUND;
	}
}

void OMonsterKingconga::JumpMove()
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
			m_move = M_NONE;
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
			m_move = M_NONE;
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
			m_move = M_NONE;
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
			m_move = M_NONE;
		break;

	case M_LU :
		moveCount -= 4;
		x -= 4;
		y -= 4;
		if (moveCount)
		{
			if (moveCount > TILESIZE / 2)
				jump -= 6;
			else jump += 6;
		}
		if (moveCount == 0)
			m_move = M_NONE;
		break;
	case M_LD:
		moveCount -= 4;
		x -= 4;
		y += 4;
		if (moveCount)
		{
			if (moveCount > TILESIZE / 2)
				jump -= 6;
			else jump += 6;
		}
		if (moveCount == 0)
			m_move = M_NONE;
		break;
	case M_RU:
		moveCount -= 4;
		x += 4;
		y -= 4;
		if (moveCount)
		{
			if (moveCount > TILESIZE / 2)
				jump -= 6;
			else jump += 6;
		}
		if (moveCount == 0)
			m_move = M_NONE;
		break;
	case M_RD:
		moveCount -= 4;
		x += 4;
		y += 4;
		if (moveCount)
		{
			if (moveCount > TILESIZE / 2)
				jump -= 6;
			else jump += 6;
		}
		if (moveCount == 0)
			m_move = M_NONE;
		break;
	}
}

void OMonsterKingconga::Defence(int damage)
{
	VoiceHit();
	isShowHp = true;

	m_currentHp -= damage;

	int num = RND->GetInt(4);

	if (num == 0)
		num = 502;
	else if (num == 1)
		num = 514;
	else if (num == 2)
		num = 902;
	else
		num = 914;

	GameObject * obj = OBJECTMANAGER->GetIsThereFloor(num);
	OBJECTMANAGER->SetTilePos(this, num);
	x = obj->GetX();
	y = obj->GetY();

	if (m_currentHp <= 0)
		this->Die();
}
