#include "stdafx.h"
#include "OWallBossWall.h"


OWallBossWall::OWallBossWall()
{
}


OWallBossWall::~OWallBossWall()
{
}

HRESULT OWallBossWall::Init(string key, int pos, bool torch)
{
	WallBase::Init(key, pos, torch);
	Hard = 5;
	m_frameX = RND->GetInt(5);
	return S_OK;
}

void OWallBossWall::Release()
{
}

void OWallBossWall::Update()
{
	WallBase::Update();
}

void OWallBossWall::Render()
{
	WallBase::Render();
}
