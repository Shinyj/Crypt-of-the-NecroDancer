#include "stdafx.h"
#include "OItemArmorSpiked.h"


OItemArmorSpiked::OItemArmorSpiked()
{
}


OItemArmorSpiked::~OItemArmorSpiked()
{
}

HRESULT OItemArmorSpiked::Init(string key, int pos, ITEMKIND kind)
{
	ItemBase::Init(key,pos,kind);
	infoImage = IMAGEMANAGER->FindImage("hint_1defense");
	return S_OK;
}

void OItemArmorSpiked::Release()
{
}

void OItemArmorSpiked::Update()
{
	ItemBase::Update();
}

void OItemArmorSpiked::Render()
{
	ItemBase::Render();
	//this->ShowInfo();
}

void OItemArmorSpiked::ShowInfo()
{
	infoImage->Render(GetMemDC(),x + 26 - 40, y - 18 );
}
