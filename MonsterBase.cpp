#include "stdafx.h"
#include "MonsterBase.h"
#include "OPlayer1.h"
#include "OItemGold.h"

MonsterBase::MonsterBase()
{
}


MonsterBase::~MonsterBase()
{
}

HRESULT MonsterBase::Init(string key, int pos)
{
	m_imageKey = key;
	isHalfMove = false;
	mainImage = IMAGEMANAGER->FindImage(key);
	maxHpImage = IMAGEMANAGER->FindImage("TEMP_heart_empty_small");
	curHpImage = IMAGEMANAGER->FindImage("TEMP_heart_small");
	darkImage = IMAGEMANAGER->FindImage("black");

	effectU = IMAGEMANAGER->FindImage("swipe_enemy_U");
	effectR = IMAGEMANAGER->FindImage("swipe_enemy_R");
	effectD = IMAGEMANAGER->FindImage("swipe_enemy_D");
	effectL = IMAGEMANAGER->FindImage("swipe_enemy_L");

	maxHpImage = IMAGEMANAGER->FindImage("TEMP_heart_empty_small");
	curHpImage = IMAGEMANAGER->FindImage("TEMP_heart_small");

	shadowImage = IMAGEMANAGER->FindImage("shadow_large");


	myMoveBeat = 1;
	myCurrentMoveBeat = 0;

	m_pos = pos;
	
	m_maxFrameX = mainImage->GetMaxFrameX();
	m_maxFrameY = mainImage->GetMaxFrameY();

	x = m_pos % TILEX * TILESIZE;
	y = m_pos / TILEY * TILESIZE;

	m_objKind = OBJ_MONSTER;
	m_hp = 5;
	m_currentHp = 5;
	myCurrentMoveBeat = 0;
	damage = 1;
	count = 0;
	isRight = false;

	m_frameY = 0;
	m_frameX = 0;

	isBeatTime = false;

	g = 0;
	jump = 0;

	isShowHp = true;
	subX = 0;
	subY = 0;
	m_move = M_NONE;
	isFirstSight = false;
	isEffectAnim = false;
	direction = M_NONE;
	effectCount = 0;

	return S_OK;
}

void MonsterBase::Release()
{
}

void MonsterBase::Update()
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
	//if (KEYMANAGER->IsOnceKeyDown('N'))
	//	Defence(1);
}

void MonsterBase::Render()
{
	//mainImage->FrameRender(GetMemDC(), x - subX, y - subY + jump, m_frameX, 0);
	//{
	//
	
	////                  여기 풀어
	//if (isSight)
	//{
	//	shadowImage->AlphaRender(GetMemDC(), x, y - 20, 50);
	//	
	//	if (light == 0)
	//		mainImage->FrameRender(GetMemDC(), x-subX, y-subY + jump, m_frameX, 1);
	//	else
	//		mainImage->FrameRender(GetMemDC(), x - subX, y - subY + jump, m_frameX, 0);
	//}
	//else
	//{
	//	if (isFirstSight)
	//	{
	//		mainImage->FrameRender(GetMemDC(), x- subX, y-subY + jump, m_frameX, 1);
	//	}
	//}

	if (isFirstSight)
	{
		shadowImage->AlphaRender(GetMemDC(), x, y - 20, 50);

		//mainImage->FrameRender(GetMemDC(), x, y, m_frameX, m_frameY);

		if (isSight)
		{
			if (light)
			{
				mainImage->FrameRender(GetMemDC(), x - subX, y - subY + jump, m_frameX, 0);
			}
			else
			{
				mainImage->FrameRender(GetMemDC(), x - subX, y - subY + jump, m_frameX, 1);
			}
		}
		else
		{
			mainImage->FrameRender(GetMemDC(), x - subX, y - subY + jump, m_frameX, 1);

		}
	}

	////// 맞앗을 경우 hp 렌더
	if (isShowHp && m_hp != m_currentHp)
	{
		for (int i = m_currentHp; i < m_hp; i++)
		{
			//IMAGEMANAGER->Render("TEMP_heart_empty_small", GetMemDC(), (x + 26) - (m_hp / 2) * 24 + 24 * i - 7, y - 71);
			maxHpImage->Render(GetMemDC(), (x + 26) - (m_hp / 2) * 24 + 24 * i - 7, y - subY -  24);
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
	
	EffectRender();

}

void MonsterBase::Anim()
{
	count++;
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

void MonsterBase::Move()
{
		switch (m_move)
		{
		case M_LEFT:
			moveCount -= 4;
			x -= 4;
			
			if (moveCount == 0)
				m_move = M_NONE;
			break;
		case M_RIGHT:
			moveCount -= 4;
			x += 4;
			
			if (moveCount == 0)
				m_move = M_NONE;
			break;
		case M_UP:
			moveCount -= 4;
			y -= 4;
			
			if (moveCount == 0)
				m_move = M_NONE;
			break;
		case M_DOWN:
			moveCount -= 4;
			y += 4;
			
			if (moveCount == 0)
				m_move = M_NONE;
			break;
		}
}

void MonsterBase::JumpMove()
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

void MonsterBase::RendomLoad()
{
	moveCount = TILESIZE;
	if (RND->GetInt(2) == 0)
	{
		if (RND->GetInt(2) == 0)
		{
			isRight = false;
			m_frameX = 0;
			m_move = M_LEFT;
			isRight = false;
		}
		else
		{
			isRight = true;
			m_frameX = 15;
			m_move = M_RIGHT;
			isRight = true;
		}
	}
	else
	{
		if (RND->GetInt(2) == 0)
			m_move = M_UP;
		else
			m_move = M_DOWN;
	}

	GameObject * obj = OBJECTMANAGER->GetIsThereObj(m_pos + m_move);
	OBJECTKIND objKind;

	if (obj != NULL)
	{
		objKind = obj->GetObjKind();

		if (objKind == OBJ_PLAYER)
			Attcked(m_move);
		
		m_move = M_NONE;
		moveCount = 0;
	}

	OBJECTMANAGER->SetTilePos(this, m_pos+m_move);

}

void MonsterBase::PatternLoad()
{
	moveCount = TILESIZE;
	
	if ((m_pos / 10) % 2 == 0)
		m_move = M_UP;
	else
		m_move = M_DOWN;
	
	GameObject * obj = OBJECTMANAGER->GetIsThereObj(m_pos + m_move);
	OBJECTKIND objKind;

	if (obj != NULL)
	{
		objKind = obj->GetObjKind();

		if (objKind == OBJ_PLAYER)
			Attcked(m_move);

		m_move = M_NONE;
		moveCount = 0;
	}

	OBJECTMANAGER->SetTilePos(this, m_pos + m_move);
}

bool MonsterBase::AStarLoad()
{
	OPlayer1 * player = OBJECTMANAGER->GetPlayer();

	int dirction = player->GetPos() - m_pos;

	if (dirction == -1 || dirction == 1 || dirction == -50 || dirction == 50)
	{
		this->direction = (DIRECTION)dirction;
		Attcked(direction);
		return true;
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
				}
				moveCount = TILESIZE;
				OBJECTMANAGER->SetTilePos(this, m_pos + m_move);
			}
			else if (obj->GetObjKind() == OBJ_MONSTER)
			{
				if(obj->GetImageKey() != "banshee" || obj->GetImageKey() != "banshee2")
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
				}
				moveCount = TILESIZE;
				isHalfMove = true;
			}
			return true;
		}
		else if (_aStarState == ASTAR_STATE_NOWAY)
		{
			//PatternLoad();
			return false;
		}

		AddOpenList(); // 오픈 리스트에 추가
		CalculateH(); // 오픈 리스트 내 H 값 계산
		CalculateF(); // F 값을 계산
		AddCloseList(); // 클로즈 리스트에 추가
		CheckArrive(); // 도착을 했는가
	}
}

// AStar에 관련된 함수들

void MonsterBase::TileComposition()
{
}

void MonsterBase::TileInitializing()
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

void MonsterBase::AddOpenList() // 오픈 리스트에 추가
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
}

void MonsterBase::CalculateH() // 오픈 리스트 내 H 값 계산
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

void MonsterBase::CalculateF()
{
	for (int i = 0; i < _openList.size(); i++)
	{
		_openList[i]->F = _openList[i]->G + _openList[i]->H;
	}
}

void MonsterBase::AddCloseList()
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

void MonsterBase::CheckArrive()
{
	if (_closeList[_lastIndex]->i == _endY &&
		_closeList[_lastIndex]->j == _endX)
	{
		_aStarState = ASTAR_STATE_FOUND;
	}
}

void MonsterBase::EffectAnim()
{
	if (isEffectAnim)
	{
		effectCount++;

		if (effectCount % 5 == 0)
		{
			effectCount = 0;
			effectX++;
			effectY++;

			if (effectX == 5 || effectY == 5)
				isEffectAnim = false;
		}
	}
}

void MonsterBase::EffectRender()
{
	if (isEffectAnim)
	{
		switch (direction)
		{
		case M_UP:
			effectU->FrameRender(GetMemDC(), posX, posY, 0, 5 - effectY);
			break;
		case M_DOWN:
			effectD->FrameRender(GetMemDC(), posX, posY, 0, effectY);
			break;
		case M_LEFT:
			effectL->FrameRender(GetMemDC(), posX, posY, 5 - effectX, 0);
			break;
		case M_RIGHT:
			effectR->FrameRender(GetMemDC(), posX, posY, effectX, 0);
			break;
		}
	}
}

void MonsterBase::VoiceAtt()
{

	if (m_imageKey == "banshee" || m_imageKey == "banshee2")
	{
		SOUNDMANAGER->Play("en_banshee_attack",OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "bat" ||
		m_imageKey == "bat_black" ||
		m_imageKey == "bat_green" ||
		m_imageKey == "bat_red")
	{
		SOUNDMANAGER->Play("en_bat_attack", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "bat_miniboss" || m_imageKey == "miniboss_yellow")
	{
		SOUNDMANAGER->Play("en_bat_miniboss_attack", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "dragon_red")
	{
		SOUNDMANAGER->Play("en_dragon_attack_melee", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "mage_black" ||
		m_imageKey == "mage_white" ||
		m_imageKey == "mage_yellow" ||
		m_imageKey == "skeleton_black" ||
		m_imageKey == "skeleton_yellow"||
		m_imageKey == "skeleton"	)
	{
		SOUNDMANAGER->Play("en_skel_attack_melee", OBJECTMANAGER->GetEffectVolum());
	}

	else if (m_imageKey == "minotaur" || m_imageKey == "minotaur2")
	{
		SOUNDMANAGER->Play("en_minotaur_attack", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "shopkeeper")
	{
		SOUNDMANAGER->Play("en_minotaur_attack", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "slime_green"|| m_imageKey == "slime_blue")
	{
		SOUNDMANAGER->Play("en_slime_attack", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "king_conga")
	{
		SOUNDMANAGER->Play("en_kingconga_attack_01", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "zombie_snake")
	{
		SOUNDMANAGER->Play("en_zombie_attack", OBJECTMANAGER->GetEffectVolum());
	}
	
}

void MonsterBase::VoiceHit()
{
	if (m_imageKey == "banshee" || m_imageKey == "banshee2")
	{
		SOUNDMANAGER->Play("en_banshee_hit_01", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "bat" ||
		m_imageKey == "bat_black" ||
		m_imageKey == "bat_green" ||
		m_imageKey == "bat_red")
	{
		SOUNDMANAGER->Play("en_bat_hit", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "bat_miniboss" || m_imageKey == "miniboss_yellow")
	{
		SOUNDMANAGER->Play("en_bat_miniboss_hit", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "dragon_red")
	{
		SOUNDMANAGER->Play("en_dragon_hit", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "mage_black" ||
		m_imageKey == "mage_white" ||
		m_imageKey == "mage_yellow" ||
		m_imageKey == "skeleton_black" ||
		m_imageKey == "skeleton_yellow" ||
		m_imageKey == "skeleton")
	{
		SOUNDMANAGER->Play("en_skel_hit", OBJECTMANAGER->GetEffectVolum());
	}

	else if (m_imageKey == "minotaur" || m_imageKey == "minotaur2")
	{
		SOUNDMANAGER->Play("en_minotaur_hit", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "shopkeeper")
	{
		SOUNDMANAGER->Play("en_shopkeep_norm_hit_01", OBJECTMANAGER->GetEffectVolum());
		string bgm;
		bgm = SOUNDMANAGER->GetBgmKey();
		bgm = bgm + "_shopkeeper";
		SOUNDMANAGER->Stop(bgm);
	}
	else if (m_imageKey == "slime_green" || m_imageKey == "slime_blue")
	{
		SOUNDMANAGER->Play("en_slime_hit", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "king_conga")
	{
		SOUNDMANAGER->Play("en_kingconga_hit_01", OBJECTMANAGER->GetEffectVolum());
	}
	
}

void MonsterBase::VoiceDie()
{
	if (m_imageKey == "banshee" || m_imageKey == "banshee2")
	{
		SOUNDMANAGER->Play("en_banshee_death", OBJECTMANAGER->GetEffectVolum());
		SOUNDMANAGER->Stop("en_banshee_loop");
		//SOUNDMANAGER->resume(SOUNDMANAGER->GetBgmKey(), OBJECTMANAGER->GetBgmVolum());
		//SOUNDMANAGER->SetBGMVolume(SOUNDMANAGER->GetBgmKey(), OBJECTMANAGER->GetBgmVolum());
		//SOUNDMANAGER->ResumeZoneBGM(SOUNDMANAGER->GetBgmKey(), OBJECTMANAGER->GetBgmVolum());
		SOUNDMANAGER->SetBGMVolume(SOUNDMANAGER->GetBgmKey(),OBJECTMANAGER->GetBgmVolum());

	}
	else if (m_imageKey == "bat" ||
		m_imageKey == "bat_black" ||
		m_imageKey == "bat_green" ||
		m_imageKey == "bat_red")
	{
		SOUNDMANAGER->Play("en_bat_death", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "bat_miniboss" || m_imageKey == "miniboss_yellow")
	{
		SOUNDMANAGER->Play("en_bat_miniboss_death", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "dragon_red")
	{
		SOUNDMANAGER->Play("en_dragon_death", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "mage_black" ||
		m_imageKey == "mage_white" ||
		m_imageKey == "mage_yellow" ||
		m_imageKey == "skeleton_black" ||
		m_imageKey == "skeleton_yellow" ||
		m_imageKey == "skeleton")
	{
		SOUNDMANAGER->Play("en_skel_death", OBJECTMANAGER->GetEffectVolum());
	}

	else if (m_imageKey == "minotaur" || m_imageKey == "minotaur2")
	{
		SOUNDMANAGER->Play("en_minotaur_death", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "shopkeeper")
	{
		SOUNDMANAGER->Play("en_shopkeep_norm_death_01", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "slime_green" || m_imageKey == "slime_blue")
	{
		SOUNDMANAGER->Play("en_slime_death", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "king_conga")
	{
		SOUNDMANAGER->Play("en_kingconga_death", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "zombie_snake")
	{
		SOUNDMANAGER->Play("en_zombie_death", OBJECTMANAGER->GetEffectVolum());
	}
}

void MonsterBase::VoiceCry()
{
	if (m_imageKey == "banshee" || m_imageKey == "banshee2")
	{
		SOUNDMANAGER->Play("en_banshee_cry", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "bat_miniboss" || m_imageKey == "miniboss_yellow")
	{
		SOUNDMANAGER->Play("en_bat_miniboss_cry", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "dragon_red")
	{
		SOUNDMANAGER->Play("en_dragon_cry", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "minotaur" || m_imageKey == "minotaur2")
	{
		SOUNDMANAGER->Play("en_minotaur_cry", OBJECTMANAGER->GetEffectVolum());
	}
	else if (m_imageKey == "king_conga")
	{
		SOUNDMANAGER->Play("en_kingconga_cry", OBJECTMANAGER->GetEffectVolum());
	}
}

void MonsterBase::Attcked(DIRECTION dir)
{
	VoiceAtt();
	direction = dir;
	OPlayer1 * player = OBJECTMANAGER->GetPlayer();
	isEffectAnim = true;
	//isEffectAnim = true;
	effectCount = 0;
	posX = player->GetX();
	posY = player->GetY();
	effectX = 0;
	effectY = 0;
	player->Defence(damage);
	//player->SetEarthquake();
}

void MonsterBase::Defence(int damage)
{
	VoiceHit();
	isShowHp = true;

	m_currentHp -= damage;
	
	if(m_currentHp <= 0)
		this->Die();
	
}

void MonsterBase::Die()
{
	VoiceDie();
	OBJECTMANAGER->SetFever();
	
	OItemGold * obj = new OItemGold;
	obj->Init("", m_pos, ITEM_GOLD);

	OBJECTMANAGER->DeleteObj(this);
	OBJECTMANAGER->PushObject(obj);
}

