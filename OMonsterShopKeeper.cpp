#include "stdafx.h"
#include "OMonsterShopKeeper.h"
#include "OPlayer1.h"

OMonsterShopKeeper::OMonsterShopKeeper()
{
}


OMonsterShopKeeper::~OMonsterShopKeeper()
{
}

HRESULT OMonsterShopKeeper::Init(string key, int pos)
{
	MonsterBase::Init(key, pos);

	myMoveBeat = 1;
	subX = 20;
	subY = 45;

	damage = 10;
	m_hp = 9;
	m_currentHp = 9;

	isRight = true;
	isAnim = false;
	return S_OK;
}

void OMonsterShopKeeper::Release()
{
}

void OMonsterShopKeeper::Update()
{
	Anim();

	if (isBeatTime)
	{
		myCurrentMoveBeat++;
		if (myMoveBeat <= myCurrentMoveBeat)
		{
			myCurrentMoveBeat = 0;

			// 여기다가 플레이어와의 위치관계를 연산하면 될듯?

			isAnim = true;


			AStarLoad();

			m_frameX = 0;

		}
		isBeatTime = false;
	}

}

void OMonsterShopKeeper::Render()
{
	MonsterBase::Render();
}

void OMonsterShopKeeper::Anim()
{
	count++;

	if (isAnim)
	{
		if (isRight)
		{
			if (count % 10 == 0)
			{
				count = 0;
				m_frameX = m_frameX + 1;
		
				if (m_frameX > 2)
					isAnim = false;
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
}

void OMonsterShopKeeper::AStarLoad()
{
	OPlayer1 * player = OBJECTMANAGER->GetPlayer();

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
			// 여기다가는 길의 사이즈만큼 성량 측정

			float size = (float)_closeList.size();

			if (size < 13)
			{
				string song = SOUNDMANAGER->GetBgmKey() + "_shopkeeper";

				float volume = OBJECTMANAGER->GetBgmVolum();

				volume = OBJECTMANAGER->GetBgmVolum() * ( (13.0f - volume) / 12.0f);

				SOUNDMANAGER->SetVolume(song, volume);

			}
			else
			{
				string song = SOUNDMANAGER->GetBgmKey() + "_shopkeeper";
				SOUNDMANAGER->SetVolume(song, 0);
			}

			return;
		}
		else if (_aStarState == ASTAR_STATE_NOWAY)
		{
			
			// 여기다가는 무식하게 플레이어와의 위치를 구해서 성량 측정
			string song = SOUNDMANAGER->GetBgmKey() + "_shopkeeper";
			int pos = player->GetPos();

			int x = pos % 50;
			int y = pos / 50;

			int x2 = m_pos % 50;
			int y2 = m_pos / 50;

			if (x2 - 12 < x && x2 + 12 > x)
			{
				if (y2 - 12 < y && y2 + 12 > y)
				{
					string song = SOUNDMANAGER->GetBgmKey() + "_shopkeeper";

					float volume = OBJECTMANAGER->GetBgmVolum();

					volume = OBJECTMANAGER->GetBgmVolum() * ((13.0f - volume) / 12.0f);

					SOUNDMANAGER->SetVolume(song, volume / 2.0f);

					//SOUNDMANAGER->SetVolume(song, OBJECTMANAGER->GetBgmVolum()/2);
				}
				else
					SOUNDMANAGER->SetVolume(song, 0);
			}
			else
			{
				SOUNDMANAGER->SetVolume(song, 0);
			}

			return;
		}

		AddOpenList(); // 오픈 리스트에 추가
		CalculateH(); // 오픈 리스트 내 H 값 계산
		CalculateF(); // F 값을 계산
		AddCloseList(); // 클로즈 리스트에 추가
		CheckArrive(); // 도착을 했는가
	}
}

void OMonsterShopKeeper::TileInitializing()
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

void OMonsterShopKeeper::AddOpenList()
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

void OMonsterShopKeeper::CalculateH()
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

void OMonsterShopKeeper::CalculateF()
{
	for (int i = 0; i < _openList.size(); i++)
	{
		_openList[i]->F = _openList[i]->G + _openList[i]->H;
	}
}

void OMonsterShopKeeper::AddCloseList()
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

void OMonsterShopKeeper::CheckArrive()
{
	if (_closeList[_lastIndex]->i == _endY &&
		_closeList[_lastIndex]->j == _endX)
	{
		_aStarState = ASTAR_STATE_FOUND;
	}
}
