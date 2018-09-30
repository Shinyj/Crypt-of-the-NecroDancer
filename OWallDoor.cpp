#include "stdafx.h"
#include "OWallDoor.h"
#include "GameObject.h"

OWallDoor::OWallDoor()
{
}


OWallDoor::~OWallDoor()
{
}

HRESULT OWallDoor::Init(int pos, bool isVertical)
{
	
	WallBase::Init("", pos, false);
	Hard = 0;
	m_imageKey = "wall_door_side";
	mainImage = IMAGEMANAGER->FindImage("wall_door_side");
	mainImage2 = IMAGEMANAGER->FindImage("wall_door_front");
	m_pos = pos;
	darkImage = IMAGEMANAGER->FindImage("black");

	x = pos % TILEX * TILESIZE;
	y = pos / TILEY * TILESIZE - 35;

	this->isVertical = isVertical;

	return S_OK;
}

void OWallDoor::Release()
{
}

void OWallDoor::Update()
{
	WallBase::Update();
}

void OWallDoor::Render()
{
	
	if (isFirstSight)
	{
		if (isVertical)
			mainImage->FrameRender(GetMemDC(), x, y, 0, 0); //v
		else
			mainImage2->FrameRender(GetMemDC(), x, y, 0, 0);

		if (isSight)
		{
			if (light)
			{

			}
			else
			{
				darkImage->AlphaRender(GetMemDC(), x, y, 0, 0, 52, 52, 105);

			}
		}
		else
		{
			darkImage->AlphaRender(GetMemDC(), x, y, 0, 0, 52, 52, 105);

		}
	}

	//light = false;
	//isSight = false;
}
