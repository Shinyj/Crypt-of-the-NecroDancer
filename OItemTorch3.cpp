#include "stdafx.h"
#include "OItemTorch3.h"


OItemTorch3::OItemTorch3()
{
}


OItemTorch3::~OItemTorch3()
{
}

HRESULT OItemTorch3::Init(string key, int pos, ITEMKIND kind)
{
	ItemBase::Init(key,pos,kind);
	infoImage = IMAGEMANAGER->FindImage("hint_torch3");
	attribute = 3;
	return S_OK;
}

void OItemTorch3::Release()
{
	ItemBase::Release();
}

void OItemTorch3::Update()
{
	ItemBase::Update();
}

void OItemTorch3::Render()
{
	ItemBase::Render();
}

void OItemTorch3::ShowInfo()
{
	infoImage->Render(GetMemDC(),x + 26 - 31 , y - 18 );
}
