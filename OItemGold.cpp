#include "stdafx.h"
#include "OItemGold.h"


OItemGold::OItemGold()
{
}


OItemGold::~OItemGold()
{
}

HRESULT OItemGold::Init(string key, int pos, ITEMKIND kind)
{

	ItemBase::Init(key, pos, kind);

	attribute = RND->GetFromInto(2, 9) * (OBJECTMANAGER->GetFever() + 1);
	m_kind = ITEM_GOLD;


	x = OBJECTMANAGER->GetIsThereObj(pos)->GetX();
	y = OBJECTMANAGER->GetIsThereObj(pos)->GetY();

	if (attribute == 2)
		body = IMAGEMANAGER->FindImage("coin2");
	else if (attribute == 3)
		body = IMAGEMANAGER->FindImage("coin3");
	else if (attribute == 4)
		body = IMAGEMANAGER->FindImage("coin4");
	else if (attribute == 5)
		body = IMAGEMANAGER->FindImage("coin5");
	else if (attribute == 6)
		body = IMAGEMANAGER->FindImage("coin6");
	else if (attribute == 7)
		body = IMAGEMANAGER->FindImage("coin7");
	else if (attribute == 8)
		body = IMAGEMANAGER->FindImage("coin8");
	else if (attribute == 9)
		body = IMAGEMANAGER->FindImage("coin9");
	else if (attribute == 10)
		body = IMAGEMANAGER->FindImage("coin10");
	else if (attribute > 10)
		body = IMAGEMANAGER->FindImage("small");
	else if (attribute > 20)
		body = IMAGEMANAGER->FindImage("gold");
	else if (attribute > 30)
		body = IMAGEMANAGER->FindImage("hoard");

	return S_OK;
}

void OItemGold::Release()
{
	ItemBase::Release();
}

void OItemGold::Update()
{
	//ItemBase::Update();
}

void OItemGold::Render()
{
	//if(isSight)
		body->FrameRender(GetMemDC(),x,y,0,0);
	//else
		//body->FrameRender(GetMemDC(), x, y, 0, 1);

	//char str[20];
	//sprintf(str, "%d", m_pos);
	//TextOut(GetMemDC(), x, y, str, strlen(str));
}
