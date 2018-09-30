#include "stdafx.h"
#include "OItemWeaponSpear.h"
#include "OPlayer1.h"


OItemWeaponSpear::OItemWeaponSpear()
{
}


OItemWeaponSpear::~OItemWeaponSpear()
{
}

HRESULT OItemWeaponSpear::Init(string key, int pos, ITEMKIND kind)
{
	ItemBase::Init(key,pos,kind);
	infoImage = IMAGEMANAGER->FindImage("hint_longattackthrowable");

	effectU = IMAGEMANAGER->FindImage("swipe_rapier_U");
	effectD = IMAGEMANAGER->FindImage("swipe_rapier_D");
	effectL = IMAGEMANAGER->FindImage("swipe_rapier_L");
	effectR = IMAGEMANAGER->FindImage("swipe_rapier_R");

	direction = 5;
	posX = -1;
	posY = 0;
	effectX = 0;
	effectY = 0;
	effectCount = 0;

	isEffectAnim = false;

	attribute = 1;

	return S_OK;
}

void OItemWeaponSpear::Release()
{
	ItemBase::Release();
}

void OItemWeaponSpear::Update()
{
	ItemBase::Update();

	if (isEffectAnim)
		EffectAnim();
}

void OItemWeaponSpear::Render()
{
	ItemBase::Render();

	if (isEffectAnim)
		EffectRender();
}

void OItemWeaponSpear::ShowInfo()
{
	infoImage->Render(GetMemDC(), x + 26 - 82 , y - 18);
}

bool OItemWeaponSpear::UseIt(int pos, int dir)
{
	GameObject * obj[2];
	//GameObject * player;
	posX = OBJECTMANAGER->GetPlayer()->GetX();
	posY = OBJECTMANAGER->GetPlayer()->GetY();
	posY -= 10;
	switch (dir)
	{
	case 8:
		obj[0] = OBJECTMANAGER->GetIsThereObj(pos - 50);
		obj[1] = OBJECTMANAGER->GetIsThereObj(pos);
		posY -= 104;
		break;
	case 2:
		obj[0] = OBJECTMANAGER->GetIsThereObj(pos + 50);
		obj[1] = OBJECTMANAGER->GetIsThereObj(pos);
		posY += 52;
		break;
	case 4:
		obj[0] = OBJECTMANAGER->GetIsThereObj(pos - 1);
		obj[1] = OBJECTMANAGER->GetIsThereObj(pos);
		posX -= 104;
		break;
	case 6:
		obj[0] = OBJECTMANAGER->GetIsThereObj(pos + 1);
		obj[1] = OBJECTMANAGER->GetIsThereObj(pos);
		posX += 52;
		break;
	}

	bool existObj = false;

	for (int i = 0; i < 2; i++)
	{
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
		}
	}

	return existObj;
}

void OItemWeaponSpear::EffectAnim()
{
	effectCount++;

	if (effectCount % 5 == 0)
	{
		effectCount = 0;
		effectX++;
		effectY++;

		if (effectX == 6 || effectY == 6)
			isEffectAnim = false;
	}
}

void OItemWeaponSpear::EffectRender()
{
	switch (direction)
	{
	case 8:
		effectU->FrameRender(GetMemDC(), posX, posY, 0, 6 - effectY);
		break;
	case 2:
		effectD->FrameRender(GetMemDC(), posX, posY, 0, 6 - effectY);
		break;
	case 4:
		effectL->FrameRender(GetMemDC(), posX, posY, 6 - effectX, 0);
		break;
	case 6:
		effectR->FrameRender(GetMemDC(), posX, posY, effectX, 0);
		break;
	}
}
