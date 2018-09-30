#include "stdafx.h"
#include "OItemArmorGi.h"


OItemArmorGi::OItemArmorGi()
{
}


OItemArmorGi::~OItemArmorGi()
{
}

HRESULT OItemArmorGi::Init(string key, int pos, ITEMKIND kind)
{
	ItemBase::Init(key,pos,kind);
	//infoImage = IMAGEMANAGER->FindImage("hint_1defense");
	return S_OK;
}

void OItemArmorGi::Release()
{
}

void OItemArmorGi::Update()
{
	ItemBase::Update();

}

void OItemArmorGi::Render()
{
	ItemBase::Render();
}

void OItemArmorGi::ShowInfo()
{
	
}
