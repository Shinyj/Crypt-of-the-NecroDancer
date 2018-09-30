#include "stdafx.h"
#include "../stdafx.h"
#include "AStar.h"
#include "../GameNode.h"

AStar::AStar()
{
}


AStar::~AStar()
{
}


HRESULT AStar::Init()
{
	_aStarState = ASTAR_STATE_END;

	_selectedType = TILE_TYPE_EMPTY;
	_selectedTypeColor = RGB(255, 255, 255);

	_startPointSet = false;
	_endPointSet = false;

	for (int i = 0; i < TILE_X; i++)
	{
		for (int j = 0; j < TILE_Y; j++)
		{
			_tile[i][j].type = TILE_TYPE_EMPTY;
			_tile[i][j].color = RGB(255, 255, 255);
			_tile[i][j].parent = NULL;		//�θ� Ÿ�� = NULL;
			_tile[i][j].F = BIGNUM;
			_tile[i][j].H = 0;
			_tile[i][j].i = i;
			_tile[i][j].j = j;
			_tile[i][j].rc = RectMake(WINSIZEX - (TILE_X + 1) * WIDTH + WIDTH *j,
				WINSIZEY / 2 - (TILE_Y / 2) * HEIGHT + HEIGHT * i, WIDTH, HEIGHT);
		}
	}
	return S_OK;
}
void AStar::Release()
{
}
void AStar::Update()
{
	if (_aStarState == ASTAR_STATE_END)
	{
		TileComposition(); // Ÿ�� ��ġ
	}

	//����,���� ������ ��ġ �Ǿ��� �����̽� �ٸ� ������ ����
	if (KEYMANAGER->IsOnceKeyDown(VK_SPACE)
		&& _startPointSet && _endPointSet
		&& _aStarState == ASTAR_STATE_END)
	{
		TileInitializing();
	}
	//��ġ ��, �߰� �ߴ�, ���� ���ٸ� ���� x
	if (_aStarState == ASTAR_STATE_END ||
		_aStarState == ASTAR_STATE_FOUND ||
		_aStarState == ASTAR_STATE_NOWAY) return;

	AddOpenList(); // ���� ����Ʈ�� �߰�
	CalculateH(); // ���� ����Ʈ �� H �� ���
	CalculateF(); // F ���� ���
	AddCloseList(); // Ŭ���� ����Ʈ�� �߰�
	CheckArrive(); // ������ �ߴ°�
}
void AStar::Render()
{
	PatBlt(GetMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	TextOut(GetMemDC(), 15, 15, "1 : EMPTY", strlen("1 : EMPTY"));
	TextOut(GetMemDC(), 15, 35, "2 : START", strlen("2 : START"));
	TextOut(GetMemDC(), 15, 55, "3 : END", strlen("3 : END"));
	TextOut(GetMemDC(), 15, 75, "4 : WALL", strlen("4 : WALL"));

	char str[128];
	if (_aStarState == ASTAR_STATE_END)
		sprintf_s(str, "press Space to Start");
	else if (_aStarState == ASTAR_STATE_FOUND)
		sprintf_s(str, "Way found!!");
	else if (_aStarState == ASTAR_STATE_NOWAY)
		sprintf_s(str, "No Way!!!!");
	else if (_aStarState == ASTAR_STATE_SEARCHING)
		sprintf_s(str, "Now Searching.....");
	TextOut(GetMemDC(), 15, 150, str, strlen(str));

	HBRUSH newBrush, oldBrush;
	HFONT newFont, oldFont;

	newFont = CreateFont(9, 0, 0, 0, FW_NORMAL, false, false, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, "����");
	oldFont = (HFONT)SelectObject(GetMemDC(), newFont);

	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			newBrush = CreateSolidBrush(_tile[i][j].color);
			oldBrush = (HBRUSH)SelectObject(GetMemDC(), newBrush);
			Rectangle(GetMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
				_tile[i][j].rc.right, _tile[i][j].rc.bottom);
			SelectObject(GetMemDC(), oldBrush);
			DeleteObject(newBrush);

			//F�� BIGNUM���� ���� ��(F/G/H)�� ȭ�鿡 ǥ��
			if (_tile[i][j].F < BIGNUM)
			{
				SetBkColor(GetMemDC(), TRANSPARENT);

				sprintf_s(_tile[i][j].str, "%d", _tile[i][j].F);
				TextOut(GetMemDC(),
					_tile[i][j].rc.left + 2, _tile[i][j].rc.top + 2,
					_tile[i][j].str, strlen(_tile[i][j].str));

				sprintf_s(_tile[i][j].str, "%d", _tile[i][j].G);
				TextOut(GetMemDC(),
					_tile[i][j].rc.left + 2, _tile[i][j].rc.top + 22,
					_tile[i][j].str, strlen(_tile[i][j].str));

				sprintf_s(_tile[i][j].str, "%d", _tile[i][j].H);
				TextOut(GetMemDC(),
					_tile[i][j].rc.left + 22, _tile[i][j].rc.top + 22,
					_tile[i][j].str, strlen(_tile[i][j].str));
			}

			if (_tile[i][j].parent == NULL) continue;

			int length = 15;

			MoveToEx(GetMemDC(), (_tile[i][j].rc.left + _tile[i][j].rc.right) / 2,
				(_tile[i][j].rc.top + _tile[i][j].rc.bottom) / 2, NULL);
			LineTo(GetMemDC(),
				(_tile[i][j].parent->j - _tile[i][j].j) * length
				+ (_tile[i][j].rc.left + _tile[i][j].rc.right) / 2,
				(_tile[i][j].parent->i - _tile[i][j].i) * length
				+ (_tile[i][j].rc.top + _tile[i][j].rc.bottom) / 2
			);
		}
	}
	SelectObject(GetMemDC(), oldFont);
	DeleteObject(newFont);
}

//Initialize -> Init
void AStar::TileComposition() //Ÿ�� ��ġ							  
{
	//���������
	if (KEYMANAGER->IsOnceKeyDown('1'))
	{
		_selectedType = TILE_TYPE_EMPTY;
		_selectedTypeColor = RGB(255, 255, 255);
	}
	//��ŸƮ�϶�
	else if (KEYMANAGER->IsOnceKeyDown('2'))
	{
		_selectedType = TILE_TYPE_START;
		_selectedTypeColor = RGB(100, 255, 100);
	}
	//����
	else if (KEYMANAGER->IsOnceKeyDown('3'))
	{
		_selectedType = TILE_TYPE_END;
		_selectedTypeColor = RGB(255, 100, 100);
	}
	//���� ��
	else if (KEYMANAGER->IsOnceKeyDown('4'))
	{
		_selectedType = TILE_TYPE_WALL;
		_selectedTypeColor = RGB(100, 100, 255);
	}

	if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < TILE_Y; i++)
		{
			for (int j = 0; j < TILE_X; j++)
			{
				if (PtInRect(&_tile[i][j].rc, ptMouse))
				{
					//�������� �� ������ ����
					if (_tile[i][j].type == TILE_TYPE_START)
						_startPointSet = false;
					if (_tile[i][j].type == TILE_TYPE_END)
						_endPointSet = false;

					_tile[i][j].type = _selectedType;
					_tile[i][j].color = _selectedTypeColor;

					if (_selectedType == TILE_TYPE_START)
					{
						if (_startPointSet)
						{
							_tile[_startY][_startX].color = RGB(255, 255, 255);
							_tile[_startY][_startX].type = TILE_TYPE_EMPTY;
						}
						_startPointSet = true;
						_startX = j;
						_startY = i;
					}
					if (_selectedType == TILE_TYPE_END)
					{
						if (_endPointSet)
						{
							_tile[_endY][_endX].color = RGB(255, 255, 255);
							_tile[_endY][_endX].type = TILE_TYPE_EMPTY;
						}
						_endPointSet = true;
						_endX = j;
						_endY = i;
					}
				}
			}
		}
	}
}
void AStar::TileInitializing() //Ÿ�� ��ġ�� �Ӽ��� �°� Ÿ�� �ʱ�ȭ  
{
	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			if (_tile[i][j].type == TILE_TYPE_EMPTY)
			{
				_tile[i][j].walkable = true;
				_tile[i][j].listOn = false;
			}
			else if (_tile[i][j].type == TILE_TYPE_WALL)
			{
				_tile[i][j].walkable = false;
				_tile[i][j].listOn = false;
			}
			else if (_tile[i][j].type == TILE_TYPE_START)
			{
				_tile[i][j].walkable = true;
				_tile[i][j].listOn = true;
				_closeList.push_back(&_tile[i][j]);
			}
			else if (_tile[i][j].type == TILE_TYPE_END)
			{
				_tile[i][j].walkable = true;
				_tile[i][j].listOn = false;
				_endX = j;
				_endY = i;
			}
		}
	}
	_aStarState = ASTAR_STATE_SEARCHING;
	_lastIndex = 0;
}
void AStar::AddOpenList() //���¸���Ʈ�� �߰�						  
{

	Ci = _closeList[_lastIndex]->i;
	Cj = _closeList[_lastIndex]->j;
	Cg = _closeList[_lastIndex]->G;

	if (Ci != 0) //0��° �� �ƴ϶�� ��� ���� ���
	{
		if (_tile[Ci - 1][Cj].walkable) //��� ���
		{
			//���� ����Ʈ�� �߰��� �Ǿ����� �ʴ�.
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
				//���� G�� ���� ���� ����� G���� �۴ٸ�
				if (Cg + 10 < _tile[Ci - 1][Cj].G)
				{
					_tile[Ci - 1][Cj].G = Cg + 10;
					_tile[Ci - 1][Cj].parent = _closeList[_lastIndex];
				}
			}
		}//end of if(_tile[Ci-1][Cj],walkable
		if (Cj != 0) //�»���� �ƴϸ�
		{
			if (_tile[Ci - 1][Cj - 1].walkable &&
				_tile[Ci - 1][Cj].walkable &&
				_tile[Ci][Cj - 1].walkable)
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

			}//end of if(_tile[Ci - 1][Cj - 1].walkable &&_tile[Ci - 1][Cj].walkable &&_tile[Ci][Cj - 1].walkable
		}//end of if(Cj != 0)
		if (Cj != TILE_X - 1)
		{
			if (_tile[Ci - 1][Cj + 1].walkable &&
				_tile[Ci - 1][Cj].walkable &&
				_tile[Ci][Cj + 1].walkable)
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
					} // end of if (Cg + 14 < _tile[Ci - 1][Cj + 1].G)
				} //end of else 
			} //end of if (_tile[Ci - 1][Cj + 1].walkable &&_tile[Ci - 1][Cj].walkable &&_tile[Ci][Cj + 1].walkable
		}//end of if (Cj != TILE_X - 1)
	}//end of if(Ci !=0)

	if (Ci != TILE_Y - 1) //0��° �� �ƴ϶�� ��� ���� ���
	{
		if (_tile[Ci + 1][Cj].walkable) //��� ���
		{
			//���� ����Ʈ�� �߰��� �Ǿ����� �ʴ�.
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
				//���� G�� ���� ���� ����� G���� �۴ٸ�
				if (Cg + 10 < _tile[Ci + 1][Cj].G)
				{
					_tile[Ci + 1][Cj].G = Cg + 10;
					_tile[Ci + 1][Cj].parent = _closeList[_lastIndex];
				}
			}
		}//end of if(_tile[Ci-1][Cj],walkable
		if (Cj != 0) //�»���� �ƴϸ�
		{
			if (_tile[Ci + 1][Cj - 1].walkable &&
				_tile[Ci + 1][Cj].walkable &&
				_tile[Ci][Cj - 1].walkable)
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

			}//end of if(_tile[Ci - 1][Cj - 1].walkable &&_tile[Ci - 1][Cj].walkable &&_tile[Ci][Cj - 1].walkable
		}//end of if(Cj != 0)
		if (Cj != TILE_X - 1)
		{
			if (_tile[Ci + 1][Cj + 1].walkable &&
				_tile[Ci + 1][Cj].walkable &&
				_tile[Ci][Cj + 1].walkable)
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
					} // end of if (Cg + 14 < _tile[Ci - 1][Cj + 1].G)
				} //end of else 
			} //end of if (_tile[Ci - 1][Cj + 1].walkable &&_tile[Ci - 1][Cj].walkable &&_tile[Ci][Cj + 1].walkable
		}//end of if (Cj != TILE_X - 1)
	}//end of if(Ci != TILE_Y -1)

	if (Cj != 0)
	{
		if (_tile[Ci][Cj - 1].walkable)
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
	}
	if (Cj != TILE_Y - 1)
	{
		if (_tile[Ci][Cj+1].walkable)
		{
			if (!_tile[Ci][Cj+1].listOn)
			{
				_tile[Ci][Cj + 1].listOn = true;
				_tile[Ci][Cj + 1].color = RGB(220, 255, 220);
				_tile[Ci][Cj + 1].G = Cg + 10;
				_tile[Ci][Cj + 1].parent = _closeList[_lastIndex];
				_openList.push_back(&_tile[Ci][Cj+1]);
			}
			else
			{
				if (Cg + 10 < _tile[Ci][Cj+1].G)
				{
					_tile[Ci][Cj+1].G = Cg + 10;
					_tile[Ci][Cj+1].parent = _closeList[_lastIndex];
				}
			}
		}
	}

}
void AStar::CalculateH() //���¸���Ʈ �� H�� ���					 
{
	for (int i = 0; i < _openList.size(); i++)
	{
		int vertical = (_endX - _openList[i]->j) * 10; // ���� H��
		int horizontal = (_endY - _openList[i]->i) * 10; // ���� H��

		if (vertical < 0)vertical *= -1;
		if (horizontal < 0) horizontal *= -1;

		_openList[i]->H = vertical + horizontal; // �� H ��
	}
}
void AStar::CalculateF()
{
	for (int i = 0; i < _openList.size(); i++)
	{
		_openList[i]->F = _openList[i]->G + _openList[i]->H;
	}
}
void AStar::AddCloseList()
{
	if (_openList.size() == 0)
	{
		_aStarState = ASTAR_STATE_NOWAY;
		return; // �ִ� ��ΰ� ����
	}

	int index = 0; // ���� ����Ʈ �� ���� F���� ���� Ÿ���� �ε���
	int lowest = BIGNUM; // ���� ����Ʈ �� ���� ���� F��
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

	_lastIndex++; // ���� �������� �߰��� Ŭ������ �ε���
}

void AStar::CheckArrive()
{
	if (_closeList[_lastIndex]->i == _endY &&
		_closeList[_lastIndex]->j == _endX)
	{
		_aStarState = ASTAR_STATE_FOUND;
		_closeList[_lastIndex]->color = RGB(255, 100, 100);
		ShowWay(_closeList[_lastIndex]);
	}
}

void AStar::ShowWay(aStarTile* tile)
{
	if (!(tile->i == _endY && tile->j == _endY))
	{
		tile->color = RGB(255, 180, 180);
	}
	tile = tile->parent;

	if (tile->parent == NULL)
		return;
	else
		ShowWay(tile); // ��� �Լ� ( ������ ȣ���ϴ� �Լ� )
}