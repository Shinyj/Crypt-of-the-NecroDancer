#include "stdafx.h"
#include "OWallZone2Stone.h"


OWallZone2Stone::OWallZone2Stone()
{
}


OWallZone2Stone::~OWallZone2Stone()
{
}

HRESULT OWallZone2Stone::Init(string key, int pos, bool torch)
{
	WallBase::Init(key, pos, torch);
	Hard = 2;

	return S_OK;
}

void OWallZone2Stone::Release()
{
}

void OWallZone2Stone::Update()
{
	WallBase::Update();
}

void OWallZone2Stone::Render()
{
	WallBase::Render();
}
