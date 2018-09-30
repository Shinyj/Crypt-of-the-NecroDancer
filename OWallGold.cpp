#include "stdafx.h"
#include "OWallGold.h"
#include "GameObject.h"


OWallGold::OWallGold()
{
}


OWallGold::~OWallGold()
{
}

HRESULT OWallGold::Init(string key, int pos, bool torch)
{
	WallBase::Init(key, pos, torch);
	Hard = 5;
	return S_OK;
}

void OWallGold::Release()
{
}

void OWallGold::Update()
{
	WallBase::Update();
}

void OWallGold::Render()
{
	WallBase::Render();
	//IMAGEMANAGER->FrameRender("wall_shop_stone",GetMemDC(),x,y, m_frameX, m_frameY);
	//mainImage->FrameRender(GetMemDC(), x, y, m_frameX, m_frameY);
}
