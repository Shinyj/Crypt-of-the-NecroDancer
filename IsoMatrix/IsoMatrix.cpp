#include "stdafx.h"
#include "../stdafx.h"
#include "IsoMatrix.h"
#include "../GameNode.h"

IsoMatrix::IsoMatrix()
{
}


IsoMatrix::~IsoMatrix()
{
}

HRESULT IsoMatrix::Init()
{
	_tileMap[TILE_COUNT_X][TILE_COUNT_Y] = 0;
	_isoX = 0;
	_isoY = 0;
	_corner = 0;
	memset(_tileMap, 0, sizeof(_tileMap));

	return S_OK;
}

void IsoMatrix::Release()
{
}

void IsoMatrix::Update()
{
	if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
	{
		float cellX = (float)(ptMouse.x - INIT_X);


		//기준점 보다 왼쪽인 타일을 클릭하면 -1을 적용해야함
		if (cellX < 0)
		{
			cellX = (cellX - CELL_WIDTH) / CELL_WIDTH;
		}
		else
		{
			//얼마 만큼 떨어져 있는지(가로지름 기준)를 수치화
			cellX = cellX / (float)CELL_WIDTH;
		}

		//y는 - 개념이 없다 절대값으로 구한다.
		int cellY = abs(ptMouse.y - INIT_Y) / CELL_HEIGHT;

		//단 시작점부터 -일수 있기 때문에 - 라면 -1을 곱해준다.
		cellY = (ptMouse.y < INIT_Y) ? cellY * -1 : cellY;

		//x 는 y가 기준점에 가까워 질수록 작어진다 
		int isoX = (int)cellX + (int)cellY;

		//y는 x 가 - 로 갈수록 커진다.
		int isoY = (int)cellY - (int)cellX;

		//만약 x좌표가 0보다 크고 최대타일수 보다 작고
		//Y좌표도 0보다 크고 최대 타일수 보다 작으면 일단 검사
		if (isoX >= 0 && isoX < TILE_COUNT_X &&
			isoY >= 0 && isoY < TILE_COUNT_Y)
		{
			//1분면이면 [x-1][y]
			//2분면이면 [x][y-1]
			//3분면이면 [x][y+1]
			//4분면이면 [x + 1][y]

			//코너 검출(어느 분면에 찍혔는지)
			int corner = GetCornerIndex(isoX, isoY);

			//만약 4분면이 검출 되었는데 그게 마름모 안에 있는지 확인
			if (IsIRhombus(corner, isoX, isoY))
			{
				//만약 들어가 있다면 지금의 isoX, isoY는 건들필요 없다.
				//마름모 안에 있으면 예외처리가 필요 없다.
				corner = 0;
			}

			_corner = corner;
			_isoX = isoX;
			_isoY = isoY;

			switch (corner)
			{
			case 1:
				isoX = isoX - 1;
				break;
			case 2:
				isoY = isoY - 1;
				break;
			case 3:
				isoY = isoY + 1;
				break;
			case 4:
				isoX = isoX + 1;
				break;
			}
			_tileMap[isoX][isoY] = 1;
		}

	}
}

void IsoMatrix::Render()
{
	DrawTileMap();
}

void IsoMatrix::DrawTileMap()
{
	for (int i = 0; i < TILE_COUNT_X; i++)
	{
		for (int j = 0; j < TILE_COUNT_Y; j++)
		{
			int left = INIT_X + (i * RADIUS_WIDTH) - (j * RADIUS_WIDTH);
			int top = INIT_Y + (i * RADIUS_HEIGHT) + (j *RADIUS_HEIGHT);

			int centerX = left + RADIUS_WIDTH;
			int centerY = top + RADIUS_HEIGHT;
			 

			//클릭하면 색상변경
			if (_tileMap[i][j] == 1)
			{
				HPEN myPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
				HPEN old = (HPEN)SelectObject(GetMemDC(), myPen);
				DrawRhombus(left, top);
				DeleteObject(SelectObject(GetMemDC(), old));

			}
			else
			{

				DrawRhombus(left, top);
			}

			SetTextColor(GetMemDC(), RGB(0, 0, 0));
			sprintf(str, "(%d, %d)", i, j);
			TextOut(GetMemDC(), centerX - 10, centerY - 5, str, strlen(str));

		}
	}
}

//타일 1개를 그려준다.
void IsoMatrix::DrawRhombus(int left, int top)
{
	int centerX = left + RADIUS_WIDTH;
	int centerY = top + RADIUS_HEIGHT;

	POINT p[5];

	p[0].x = centerX;
	p[0].y = centerY - RADIUS_HEIGHT;

	p[1].x = centerX - RADIUS_WIDTH;
	p[1].y = centerY;

	p[2].x = centerX;
	p[2].y = centerY + RADIUS_HEIGHT;

	p[3].x = centerX + RADIUS_WIDTH;
	p[3].y = centerY;

	p[4].x = centerX;
	p[4].y = centerY - RADIUS_HEIGHT;

	MoveToEx(GetMemDC(), p[0].x, p[0].y, NULL);
	for (int i = 0; i < 5; i++)
	{
		LineTo(GetMemDC(), p[i].x, p[i].y);
	}
}

int IsoMatrix::GetCornerIndex(int isoX, int isoY)
{
	//클릭한 좌표점을 통해서 렉트의 left, top을 구한다.
	int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
	int top = INIT_Y + (isoY * RADIUS_HEIGHT) + (isoX * RADIUS_HEIGHT);

	int right = left + CELL_WIDTH;
	int bottom = top + CELL_HEIGHT;

	//left - top : 1 , right - top  : 2, right - bottom :4 left - bottom :3

	//left 에서 마우스 값을 빼면 => 이동값
	//이동값을 / 전체길이 -> 0.0 ~ 1.0 -> 비율값
	//비율값을 이용 어느 분면 찍었는지를 확인
	float dx = (ptMouse.x - left) / (float)CELL_WIDTH;
	float dy = (ptMouse.y - top) / (float)CELL_HEIGHT;

	//만약 둘다 0.5보다 작으면 1사분면
	if (dx < 0.5f && dy < 0.5f) return 1;
	//만약 x가 0.5보다 크고 y는 0.5보다 작으면 2사분면
	if (dx >= 0.5f && dy < 0.5f) return 2;
	//만약 x가 0.5보다 작고 y는 0.5보다 크면 3사분면
	if (dx < 0.5f && dy >= 0.5f) return 3;
	//만약 둘다 0.5보다 크면 4사분면
	if (dx >= 0.5f && dy >= 0.5f) return 4;

	return 0;
}

bool IsoMatrix::IsIRhombus(int corner, int isoX, int isoY)
{
	// 마름모 안에 점을 찍엇을 때 마름모의 안인지 밖인지 가로 대비 세로 비율을 통해 구함


	// 1사분면 안에 있으면 
	if (corner == 1)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

		// 렉트 안에서 마우스의 이동 값
		// 0 ~ 1 사이의 비율값 계산
		float dx = (float)(ptMouse.x - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(ptMouse.y - top) / (CELL_HEIGHT / 2.0f);

		// 1을 빼준 이유는 top에서 부터 파이를 계산 했기 떄문에
		// 바텀에서부터의 값을 구하기 위함
		if ((1.0f - dy) <= dx) return true;
		else return false;
	}
	// 2 사분면
	else if (corner == 2)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		left += (CELL_WIDTH / 2.0f);
		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

		// 렉트 안에서 마우스의 이동 값
		// 0 ~ 1 사이의 비율값 계산
		float dx = (float)(ptMouse.x - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(ptMouse.y - top) / (CELL_HEIGHT / 2.0f);

		if (dy >= dx) return true;
		else return false;
	}
	// 3사분면
	else if (corner == 3)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

		top += (CELL_HEIGHT / 2.0f);

		// 렉트 안에서 마우스의 이동 값
		// 0 ~ 1 사이의 비율값 계산
		float dx = (float)(ptMouse.x - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(ptMouse.y - top) / (CELL_HEIGHT / 2.0f);
	
		if (dy <= dx) return true;
		else return false;
	}
	else if (corner == 4)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);
		
		left += (CELL_HEIGHT / 2.0f);
		top += (CELL_HEIGHT / 2.0f);
		// 렉트 안에서 마우스의 이동 값
		// 0 ~ 1 사이의 비율값 계산
		float dx = (float)(ptMouse.x - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(ptMouse.y - top) / (CELL_HEIGHT / 2.0f);

		if ((1.0f - dy) >= dx) return true;
		else return false;
	}



	return false;
}
