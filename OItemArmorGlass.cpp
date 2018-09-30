#include "stdafx.h"
#include "OItemArmorGlass.h"


OItemArmorGlass::OItemArmorGlass()
{
}


OItemArmorGlass::~OItemArmorGlass()
{
}

HRESULT OItemArmorGlass::Init(string key, int pos, ITEMKIND kind)
{
	ItemBase::Init(key, pos, kind);
	//infoImage = IMAGEMANAGER->FindImage("hint_0-5defense");
	return S_OK;
}

void OItemArmorGlass::Release()
{
}

void OItemArmorGlass::Update()
{
	ItemBase::Update();
}

void OItemArmorGlass::Render()
{
	ItemBase::Render();
}

void OItemArmorGlass::ShowInfo()
{
	//infoImage->Render(GetMemDC(), (x + 26) - 47, y - 18);
}
