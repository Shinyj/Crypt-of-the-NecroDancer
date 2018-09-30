#include "stdafx.h"
#include "OItemTorch1.h"


OItemTorch1::OItemTorch1()
{
}


OItemTorch1::~OItemTorch1()
{
}

HRESULT OItemTorch1::Init(string key, int pos, ITEMKIND kind)
{
	ItemBase::Init(key, pos, kind);
	infoImage = IMAGEMANAGER->FindImage("hint_torch1");
	attribute = 1;
	
	return S_OK;
}

void OItemTorch1::Release()
{
	ItemBase::Release();
}

void OItemTorch1::Update()
{
	ItemBase::Update();
}

void OItemTorch1::Render()
{
	ItemBase::Render();
}

void OItemTorch1::ShowInfo()
{
	infoImage->Render(GetMemDC(), x + 26 - 31, y - 18);
}
