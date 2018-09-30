#include "stdafx.h"
#include "OItemShovelTitanium.h"
#include "OPlayer1.h"

OItemShovelTitanium::OItemShovelTitanium()
{
}


OItemShovelTitanium::~OItemShovelTitanium()
{
}

HRESULT OItemShovelTitanium::Init(string key, int pos, ITEMKIND kind)
{
	ItemBase::Init(key,pos,kind);
	infoImage = IMAGEMANAGER->FindImage("hint_2dig");
	Hard = 2;
	isEffectAnim = false;
	return S_OK;
}

void OItemShovelTitanium::Release()
{
	ItemBase::Release();
}

void OItemShovelTitanium::Update()
{
	ItemBase::Update();

	EffectAnim();
}

void OItemShovelTitanium::Render()
{
	ItemBase::Render();

	EffectRender();
}

void OItemShovelTitanium::ShowInfo()
{
	infoImage->Render(GetMemDC(), x + 26 - 42, y - 18 );
}

bool OItemShovelTitanium::UseIt(int pos, int dir)
{
	GameObject * obj = OBJECTMANAGER->GetIsThereObj(pos);
	OPlayer1 * player = OBJECTMANAGER->GetPlayer();

	posX = OBJECTMANAGER->GetPlayer()->GetX();
	posY = OBJECTMANAGER->GetPlayer()->GetY();

	switch (dir)
	{
	case 8:
		posY -= 52;
		break;
	case 2:
		posY += 52;
		break;
	case 4:
		posX -= 52;
		break;
	case 6:
		posX += 52;
		break;
	}
	effectCount = 0;
	isEffectAnim = true;

	if (obj != NULL)
	{
		if (obj->GetObjKind() == OBJ_WALL)
		{
			if (obj->CanCrush(Hard))
			{
				OBJECTMANAGER->DeleteObj(obj);
				return true;
			}
		}
	}

}

void OItemShovelTitanium::EffectAnim()
{
	if (isEffectAnim)
	{
		effectCount++;

		if (effectCount == 20)
			isEffectAnim = false;
	}
}

void OItemShovelTitanium::EffectRender()
{
	if (isEffectAnim)
		mainImage->FrameRender(GetMemDC(), posX, posY - 20);
}
