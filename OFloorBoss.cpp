#include "stdafx.h"
#include "OFloorBoss.h"


OFloorBoss::OFloorBoss()
{
}


OFloorBoss::~OFloorBoss()
{
}

HRESULT OFloorBoss::Init(int pos)
{
	body = IMAGEMANAGER->FindImage("floor_boss");
	//Image * img = IMAGEMANAGER->FindImage("floor_zone1");

	//body->Init("images/level/floor_zone1.bmp", TILESIZE * 3, TILESIZE * 2, 3, 2, true, RGB(255, 0, 255));

	darkImage = IMAGEMANAGER->FindImage("black");
	count = 0.0f;
	CheckPattern(pos);
	m_pos = pos;
	if (myPattern)
	{
		m_frameX = 0;
		m_frameY = 0;
	}
	else
	{
		m_frameX = 2;
		m_frameY = 0;
	}

	x = (pos % TILEX) * TILESIZE;
	y = (pos / TILEY) * TILESIZE;
	light = false;
	isFirstSight = false;
	isSight = false;
	alph = 0;
	return S_OK;
}

void OFloorBoss::Release()
{
}

void OFloorBoss::Update()
{
	//Anim();
	if (isBeatTime)
	{
		if (myPattern)
		{
			if (m_frameX == 0) m_frameX = 1;
			else m_frameX = 0;
		}
		else
		{
			if (m_frameX == 0) m_frameX = 2;
			else m_frameX = 0;
		}
		isBeatTime = false;
	}

	if (OBJECTMANAGER->GetFever() != 0)
		m_frameY = 1;
	else
		m_frameY = 0;
}

void OFloorBoss::Render()
{
	if (m_frameX == 0)
	{

		if (isFirstSight)
		{
			if (isSight)
			{
				if (light)
					body->FrameRender(GetMemDC(), x, y, m_frameX, 1);
				else
					body->FrameRender(GetMemDC(), x, y, m_frameX, 1, 150);
			}
			else
			{
				body->FrameRender(GetMemDC(), x, y, m_frameX, 1, 150);
			}
		}

	}
	else
	{

		if (isFirstSight)
		{
			if (isSight)
			{
				if (light)
					body->FrameRender(GetMemDC(), x, y, m_frameX, m_frameY);
				else
					body->FrameRender(GetMemDC(), x, y, m_frameX, m_frameY, 150);
			}
			else
			{
				body->FrameRender(GetMemDC(), x, y, m_frameX, m_frameY, 150);
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////

	//body->AlphaRender(GetMemDC(), 0, 0, alph);

	//if (KEYMANAGER->IsStayKeyDown(VK_UP) && alph < 240)
	//	alph += 10;
	//else if (KEYMANAGER->IsStayKeyDown(VK_DOWN) && alph > 10)
	//	alph -= 10;
	//
	//char str[10];
	//sprintf(str, "%d", light);
	//TextOut(GetMemDC(), x, y, str, strlen(str));

	/////////////////////////////////////////////////////////////////// 여기 풀어
	//light = false;
	//isSight = false;
}

void OFloorBoss::CheckPattern(int pos)
{
	int n1;
	n1 = (pos / 50) % 2;

	if (n1 == 0)
	{
		if ((pos % 10) % 2 == 0) myPattern = true;
		else myPattern = false;
	}
	else
	{
		if ((pos % 10) % 2 == 0) myPattern = false;
		else myPattern = true;
	}
}

void OFloorBoss::Anim()
{
	count++;
	if (count % 40 == 0)
	{
		count = 0;
		if (myPattern)
		{
			if (m_frameX == 0) m_frameX = 1;
			else m_frameX = 0;
		}
		else
		{
			if (m_frameX == 0) m_frameX = 2;
			else m_frameX = 0;
		}
	}
}
