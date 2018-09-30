#include "stdafx.h"
#include "ItemBase.h"

ItemBase::ItemBase()
{
}


ItemBase::~ItemBase()
{
}

HRESULT ItemBase::Init(string key, int pos, ITEMKIND kind)
{
	mainImage = IMAGEMANAGER->FindImage(key);

	m_imageKey = key;
	m_pos = pos;
	m_objKind = OBJ_ITEM;
	m_kind = kind;
	x = pos % TILEX * TILESIZE;
	y = pos / TILEY * TILESIZE - 20;
	count = 0;
	g = 4;
	jump = 0;
	isGoInven = false;
	isHereInven = false;

	m_frameX = 0;
	m_frameY = 0;
	light = false;
	isSight = false;
	return S_OK;
}

void ItemBase::Release()
{
}

void ItemBase::Update()
{
	this->Anim();
	this->goInven();
}

void ItemBase::Render()
{
	if (isSight)
	{
		if (!isHereInven)
		{
			if (isFirstSight)
			{
				//shadowImage->AlphaRender(GetMemDC(), x, y - 20, 50);

				//mainImage->FrameRender(GetMemDC(), x, y, m_frameX, m_frameY);

				if (isSight)
				{
					if (light)
					{
						mainImage->FrameRender(GetMemDC(), x, y - jump, m_frameX, 0);
					}
					else
					{
						mainImage->FrameRender(GetMemDC(), x, y - jump, m_frameX, 1);
					}
				}
				else
				{
					mainImage->FrameRender(GetMemDC(), x, y - jump, m_frameX, 1);
				}
			}
		}
			//mainImage->FrameRender(GetMemDC(), x, y - jump, m_frameX, m_frameY);
	}
	else if (isGoInven)
	{
		mainImage->FrameRender(GetMemDC(), x, y - jump, m_frameX, m_frameY);
	}


	//light = 0;
	//isSight = 0;

}

void ItemBase::GoInventory(int x, int y)
{
	isGoInven = true;
	goX = x;
	goY = y;
}

void ItemBase::Anim()
{
	if (!isHereInven)
	{
		count++;
		if (count % 40 == 0)
		{
			count = 0;
			jump += g;

			if (jump > 7 || jump < 0)
				g = (-1) * g;
		}
	}
}

void ItemBase::goInven()
{
	if (isGoInven)
	{
		this->x -= (this->x - goX) / 10.0f;
		this->y -= (this->y - goY) / 10.0f;

		if (x - goX < 5) x = goX;
		if (y - goY < 5) y = goY;

		if (x == goX && y == goY)
		{
			isGoInven = false;
			OBJECTMANAGER->SetTilePos(this, 2499);
			isHereInven = true;
			//OBJECTMANAGER->GetPlayer()
		}
	}
}
