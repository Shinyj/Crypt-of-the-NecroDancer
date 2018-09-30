#include "stdafx.h"
#include "OFloorZone1.h"
#include "Image\Image.h"

OFloorZone1::OFloorZone1()
{
}


OFloorZone1::~OFloorZone1()
{
}

HRESULT OFloorZone1::Init(int pos)
{
	body = IMAGEMANAGER->FindImage("floor_zone1");
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
	light = 0;
	isFirstSight = false;
	isSight = false;
	alph = 0;
	return S_OK;
}

void OFloorZone1::Release()
{
	//SAFE_DELETE(body);
}

void OFloorZone1::Update()
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

void OFloorZone1::Render()
{
	//IMAGEMANAGER->FrameRender("floor_zone1",GetMemDC(),x,y,m_frameX, m_frameY);
	
	///body->FrameRender(GetMemDC(), x, y, m_frameX, m_frameY);

	//if (!isFirstSight)
	//{
	//
	//}
	//else if (isFirstSight)
	//{
	//	body->FrameRender(GetMemDC(), x, y, m_frameX, m_frameY,125);
	//	//darkImage->AlphaRender(GetMemDC(), x, y, 0, 0, 52, 52, 125);
	//}
	//if (light != 0)
	//{
	//	body->FrameRender(GetMemDC(),x,y,m_frameX, m_frameY, 255 * (light / 3.0f));
	//	//darkImage->AlphaRender(GetMemDC(), x, y, 0, 0, 52, 52,  255 - 255 *(light / 3.0f));
	//}
	
	//if (isSight)
	//{
	//	//body->FrameRender(GetMemDC(), x, y, m_frameX, m_frameY);
	//	
	//	if(light == 1)
	//		body->FrameRender(GetMemDC(), x, y, m_frameX, m_frameY,140);
	//		//darkImage->AlphaRender(GetMemDC(), x, y, 0, 0, 52, 52, 140);
	//	else if(light == 2)
	//		body->FrameRender(GetMemDC(), x, y, m_frameX, m_frameY,70);
	//		//darkImage->AlphaRender(GetMemDC(), x, y, 0, 0, 52, 52, 70);
	//	else if(light == 3)
	//		body->FrameRender(GetMemDC(), x, y, m_frameX, m_frameY,0);
	//		//darkImage->AlphaRender(GetMemDC(), x, y, 0, 0, 52, 52, 0);
	//}
	//else
	//{
	//	if (isFirstSight)
	//	{
	//		body->FrameRender(GetMemDC(), x, y, m_frameX, m_frameY,125);
	//		//darkImage->AlphaRender(GetMemDC(), x, y, 0, 0, 52, 52, 125);
	//	}
	//}
	
	//////////////////////////////////////// 여기 풀어
	if (m_frameX == 0)
	{

		if (isFirstSight)
		{
			if (isSight)
			{
				if (light)
					body->FrameRender(GetMemDC(), x, y, m_frameX, 1);
				else
					body->FrameRender(GetMemDC(), x, y, m_frameX, 1,150);
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
	//sprintf(str, "%d", isFirstSight);
	//TextOut(GetMemDC(), x, y, str, strlen(str));
	//sprintf(str, "%d", isSight);
	//TextOut(GetMemDC(), x + 20, y, str, strlen(str));
	//sprintf(str, "%d", light);
	//TextOut(GetMemDC(), x, y+20, str, strlen(str));
	/////////////////////////////////////////////////////////////////// 여기 풀어
	//light = false;
	//isSight = false;
}

void OFloorZone1::CheckPattern(int pos)
{
	//int n1, n2, n3, n4; // 격자로 깜박이기 위한 변수 ( 각 자리수를 더할거임)
	//int n5;

	//n1 = pos / 1000;
	//n2 = (pos - n1 * 1000) / 100;
	//n3 = (pos - n1 * 1000 - n2 * 100) / 10;
	//n4 = (pos - n1 * 1000 - n2 * 100 - n3 * 10) / 1;

	//n5 = n1 + n2 + n3 + n4;

	//myPattern = ((n5 % 2) == 0);

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

	return;
}

void OFloorZone1::Anim()
{
	/*count += TIMEMANAGER->GetElapsedTime();

	if (count > 2.00f)
	{
		count = 0.0f;
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
	}*/

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
