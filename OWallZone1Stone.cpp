#include "stdafx.h"
#include "OWallZone1Stone.h"


OWallZone1Stone::OWallZone1Stone()
{
}


OWallZone1Stone::~OWallZone1Stone()
{
}

HRESULT OWallZone1Stone::Init(string key, int pos, bool torch)
{
	WallBase::Init(key,pos, torch);
	Hard = 2;
	return S_OK;
}

void OWallZone1Stone::Release()
{
}

void OWallZone1Stone::Update()
{
	WallBase::Update();
}

void OWallZone1Stone::Render()
{
	WallBase::Render();
}