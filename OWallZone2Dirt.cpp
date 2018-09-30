#include "stdafx.h"
#include "OWallZone2Dirt.h"


OWallZone2Dirt::OWallZone2Dirt()
{
}


OWallZone2Dirt::~OWallZone2Dirt()
{
}

HRESULT OWallZone2Dirt::Init(string key, int pos, bool torch)
{
	WallBase::Init(key,pos, torch);
	Hard = 1;
	m_frameX = RND->GetInt(4);
	return S_OK;
}

void OWallZone2Dirt::Release()
{
}

void OWallZone2Dirt::Update()
{
	WallBase::Update();
}

void OWallZone2Dirt::Render()
{
	WallBase::Render();
}
