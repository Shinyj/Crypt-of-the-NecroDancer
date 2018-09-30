#include "stdafx.h"
#include "OItemTorch2.h"


OItemTorch2::OItemTorch2()
{
}


OItemTorch2::~OItemTorch2()
{
}

HRESULT OItemTorch2::Init(string key, int pos, ITEMKIND kind)
{
	ItemBase::Init(key,pos,kind);
	infoImage = IMAGEMANAGER->FindImage("hint_torch2");
	attribute = 2;
	return S_OK;
}

void OItemTorch2::Release()
{
	ItemBase::Release();
}

void OItemTorch2::Update()
{
	ItemBase::Update();
}

void OItemTorch2::Render()
{
	ItemBase::Render();
}

void OItemTorch2::ShowInfo()
{
	infoImage->Render(GetMemDC(),x + 26 - 31 , y - 18 );
}
