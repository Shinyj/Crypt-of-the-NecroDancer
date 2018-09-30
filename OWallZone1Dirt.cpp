#include "stdafx.h"
#include "OWallZone1Dirt.h"


OWallZone1Dirt::OWallZone1Dirt()
{
}


OWallZone1Dirt::~OWallZone1Dirt()
{
}

HRESULT OWallZone1Dirt::Init(string key, int pos, bool isTorch)
{
	WallBase::Init(key, pos, isTorch);
	Hard = 1;
	m_frameX = RND->GetInt(8);
	return S_OK;
}

void OWallZone1Dirt::Release()
{
}

void OWallZone1Dirt::Update()
{
	WallBase::Update();
}

void OWallZone1Dirt::Render()
{
	WallBase::Render();
}
