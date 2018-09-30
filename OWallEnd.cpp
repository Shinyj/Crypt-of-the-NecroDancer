#include "stdafx.h"
#include "OWallEnd.h"


OWallEnd::OWallEnd()
{
}


OWallEnd::~OWallEnd()
{
}

HRESULT OWallEnd::Init(string key, int pos)
{
	WallBase::Init(key, pos, false);
	Hard = 5;
	light = false;
	isSight = false;
	return S_OK;
}

void OWallEnd::Release()
{
}

void OWallEnd::Update()
{
}

void OWallEnd::Render()
{
	WallBase::Render();
}
