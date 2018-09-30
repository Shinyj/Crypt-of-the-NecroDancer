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


		//������ ���� ������ Ÿ���� Ŭ���ϸ� -1�� �����ؾ���
		if (cellX < 0)
		{
			cellX = (cellX - CELL_WIDTH) / CELL_WIDTH;
		}
		else
		{
			//�� ��ŭ ������ �ִ���(�������� ����)�� ��ġȭ
			cellX = cellX / (float)CELL_WIDTH;
		}

		//y�� - ������ ���� ���밪���� ���Ѵ�.
		int cellY = abs(ptMouse.y - INIT_Y) / CELL_HEIGHT;

		//�� ���������� -�ϼ� �ֱ� ������ - ��� -1�� �����ش�.
		cellY = (ptMouse.y < INIT_Y) ? cellY * -1 : cellY;

		//x �� y�� �������� ����� ������ �۾����� 
		int isoX = (int)cellX + (int)cellY;

		//y�� x �� - �� ������ Ŀ����.
		int isoY = (int)cellY - (int)cellX;

		//���� x��ǥ�� 0���� ũ�� �ִ�Ÿ�ϼ� ���� �۰�
		//Y��ǥ�� 0���� ũ�� �ִ� Ÿ�ϼ� ���� ������ �ϴ� �˻�
		if (isoX >= 0 && isoX < TILE_COUNT_X &&
			isoY >= 0 && isoY < TILE_COUNT_Y)
		{
			//1�и��̸� [x-1][y]
			//2�и��̸� [x][y-1]
			//3�и��̸� [x][y+1]
			//4�и��̸� [x + 1][y]

			//�ڳ� ����(��� �и鿡 ��������)
			int corner = GetCornerIndex(isoX, isoY);

			//���� 4�и��� ���� �Ǿ��µ� �װ� ������ �ȿ� �ִ��� Ȯ��
			if (IsIRhombus(corner, isoX, isoY))
			{
				//���� �� �ִٸ� ������ isoX, isoY�� �ǵ��ʿ� ����.
				//������ �ȿ� ������ ����ó���� �ʿ� ����.
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
			 

			//Ŭ���ϸ� ���󺯰�
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

//Ÿ�� 1���� �׷��ش�.
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
	//Ŭ���� ��ǥ���� ���ؼ� ��Ʈ�� left, top�� ���Ѵ�.
	int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
	int top = INIT_Y + (isoY * RADIUS_HEIGHT) + (isoX * RADIUS_HEIGHT);

	int right = left + CELL_WIDTH;
	int bottom = top + CELL_HEIGHT;

	//left - top : 1 , right - top  : 2, right - bottom :4 left - bottom :3

	//left ���� ���콺 ���� ���� => �̵���
	//�̵����� / ��ü���� -> 0.0 ~ 1.0 -> ������
	//�������� �̿� ��� �и� ��������� Ȯ��
	float dx = (ptMouse.x - left) / (float)CELL_WIDTH;
	float dy = (ptMouse.y - top) / (float)CELL_HEIGHT;

	//���� �Ѵ� 0.5���� ������ 1��и�
	if (dx < 0.5f && dy < 0.5f) return 1;
	//���� x�� 0.5���� ũ�� y�� 0.5���� ������ 2��и�
	if (dx >= 0.5f && dy < 0.5f) return 2;
	//���� x�� 0.5���� �۰� y�� 0.5���� ũ�� 3��и�
	if (dx < 0.5f && dy >= 0.5f) return 3;
	//���� �Ѵ� 0.5���� ũ�� 4��и�
	if (dx >= 0.5f && dy >= 0.5f) return 4;

	return 0;
}

bool IsoMatrix::IsIRhombus(int corner, int isoX, int isoY)
{
	// ������ �ȿ� ���� ����� �� �������� ������ ������ ���� ��� ���� ������ ���� ����


	// 1��и� �ȿ� ������ 
	if (corner == 1)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

		// ��Ʈ �ȿ��� ���콺�� �̵� ��
		// 0 ~ 1 ������ ������ ���
		float dx = (float)(ptMouse.x - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(ptMouse.y - top) / (CELL_HEIGHT / 2.0f);

		// 1�� ���� ������ top���� ���� ���̸� ��� �߱� ������
		// ���ҿ��������� ���� ���ϱ� ����
		if ((1.0f - dy) <= dx) return true;
		else return false;
	}
	// 2 ��и�
	else if (corner == 2)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		left += (CELL_WIDTH / 2.0f);
		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

		// ��Ʈ �ȿ��� ���콺�� �̵� ��
		// 0 ~ 1 ������ ������ ���
		float dx = (float)(ptMouse.x - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(ptMouse.y - top) / (CELL_HEIGHT / 2.0f);

		if (dy >= dx) return true;
		else return false;
	}
	// 3��и�
	else if (corner == 3)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

		top += (CELL_HEIGHT / 2.0f);

		// ��Ʈ �ȿ��� ���콺�� �̵� ��
		// 0 ~ 1 ������ ������ ���
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
		// ��Ʈ �ȿ��� ���콺�� �̵� ��
		// 0 ~ 1 ������ ������ ���
		float dx = (float)(ptMouse.x - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(ptMouse.y - top) / (CELL_HEIGHT / 2.0f);

		if ((1.0f - dy) >= dx) return true;
		else return false;
	}



	return false;
}
