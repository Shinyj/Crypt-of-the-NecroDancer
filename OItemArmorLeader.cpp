#include "stdafx.h"
#include "OItemArmorLeader.h"

OItemArmorLeader::OItemArmorLeader()
{
}


OItemArmorLeader::~OItemArmorLeader()
{
}

HRESULT OItemArmorLeader::Init(string key, int pos, ITEMKIND kind)
{
	ItemBase::Init(key,pos,kind);
	infoImage = IMAGEMANAGER->FindImage("hint_0-5defense");
	return S_OK;
}

void OItemArmorLeader::Release()
{
	
}

void OItemArmorLeader::Update()
{
	ItemBase::Update();
	//ItemBase::Update();
}

void OItemArmorLeader::Render()
{
	ItemBase::Render();
	//ItemBase::Render();
	//this->ShowInfo();
}

void OItemArmorLeader::ShowInfo()
{
	infoImage->Render(GetMemDC(), (x + 26) - 47, y - 18);
}

