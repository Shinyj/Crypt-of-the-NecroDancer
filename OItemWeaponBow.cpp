#include "stdafx.h"
#include "OItemWeaponBow.h"
#include "OPlayer1.h"

OItemWeaponBow::OItemWeaponBow()
{
}


OItemWeaponBow::~OItemWeaponBow()
{
}

HRESULT OItemWeaponBow::Init(string key, int pos, ITEMKIND kind)
{
	ItemBase::Init(key,pos,kind);
	infoImage = IMAGEMANAGER->FindImage("hint_rangedattack");

	effectU = IMAGEMANAGER->FindImage("swipe_arrow_U");
	effectD	= IMAGEMANAGER->FindImage("swipe_arrow_D");
	effectL	= IMAGEMANAGER->FindImage("swipe_arrow_L");
	effectR	= IMAGEMANAGER->FindImage("swipe_arrow_R");


	direction = 5;
	posX = -1;
	posY = 0;
	effectX = 0;
	effectY = 0;
	effectCount = 0;

	isEffectAnim = false;

	attribute = 1;

	range = 0;

	return S_OK;
}

void OItemWeaponBow::Release()
{
	ItemBase::Release();
}

void OItemWeaponBow::Update()
{
	ItemBase::Update();

	if (isEffectAnim)
		EffectAnim();
}

void OItemWeaponBow::Render()
{
	ItemBase::Render();

	if (isEffectAnim)
		EffectRender();
}

void OItemWeaponBow::ShowInfo()
{
	infoImage->Render(GetMemDC(), x + 26 - 46, y - 18 );
}

bool OItemWeaponBow::UseIt(int pos, int dir)
{
	GameObject * obj[3];
	//GameObject * player;
	posX = OBJECTMANAGER->GetPlayer()->GetX();
	posY = OBJECTMANAGER->GetPlayer()->GetY();
	posY -= 10;
	switch (dir)
	{
	case 8:
		obj[0] = OBJECTMANAGER->GetIsThereObj(pos);
		obj[1] = OBJECTMANAGER->GetIsThereObj(pos - 50);
		obj[2] = OBJECTMANAGER->GetIsThereObj(pos - 100);
		posY -= 52;
		break;
	case 2:
		obj[0] = OBJECTMANAGER->GetIsThereObj(pos);
		obj[1] = OBJECTMANAGER->GetIsThereObj(pos + 50);
		obj[2] = OBJECTMANAGER->GetIsThereObj(pos + 100);
		posY += 52;
		break;
	case 4:
		obj[0] = OBJECTMANAGER->GetIsThereObj(pos);
		obj[1] = OBJECTMANAGER->GetIsThereObj(pos - 1 );
		obj[2] = OBJECTMANAGER->GetIsThereObj(pos - 2 );
		posX -= 52;
		break;
	case 6:
		obj[0] = OBJECTMANAGER->GetIsThereObj(pos);
		obj[1] = OBJECTMANAGER->GetIsThereObj(pos + 1);
		obj[2] = OBJECTMANAGER->GetIsThereObj(pos + 2);
		posX += 52;
		break;
	}

	bool existObj = false;
	range = 0;
	for (int i = 0; i < 3; i++)
	{
		range++;
		if (obj[i] != NULL && obj[i]->GetObjKind() == OBJ_MONSTER)
		{
			direction = dir;
			effectX = 0;
			effectY = 0;
			//posX = obj[1]->GetX();
			//posY = obj[1]->GetY();

			obj[i]->Defence(attribute);
			isEffectAnim = true;
			existObj = true;
			break;
		}
	}

	return existObj;
}

void OItemWeaponBow::EffectAnim()
{
	effectCount++;

	if (effectCount % 1 == 0)
	{
		effectCount = 0;
		effectX++;
		effectY++;

		if (effectX == 6 || effectY == 6)
			isEffectAnim = false;
	}
}

void OItemWeaponBow::EffectRender()
{

	switch (direction)
	{
	case 8:
		for (int i = 0; i < range; i++)
		{
			effectU->FrameRender(GetMemDC(), posX + 10, posY - i * 52, 0, 6 - effectY -i);
		}
		break;
	case 2:
		for (int i = 0; i < range; i++)
		{
			effectD->FrameRender(GetMemDC(), posX + 10, posY + i * 52, 0, 6 - effectY-i);
		}
		break;
	case 4:
		for (int i = 0; i < range; i++)
		{
			effectL->FrameRender( GetMemDC(), posX - i * 52, posY, 6 - effectX -i , 0);
		}
		break;
	case 6:
		for (int i = 0; i < range; i++)
		{
			effectR->FrameRender(GetMemDC(), posX + i * 52, posY, effectX - i, 0);
		}
		break;
	}

}
