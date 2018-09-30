#include "stdafx.h"
#include "OItemWeaponLongSword.h"
#include "OPlayer1.h"

OItemWeaponLongSword::OItemWeaponLongSword()
{
}


OItemWeaponLongSword::~OItemWeaponLongSword()
{
}

HRESULT OItemWeaponLongSword::Init(string key, int pos, ITEMKIND kind)
{
	ItemBase::Init(key,pos,kind);
	infoImage = IMAGEMANAGER->FindImage("hint_longattack");

	effectU = IMAGEMANAGER->FindImage("swipe_longsword_U");
	effectD = IMAGEMANAGER->FindImage("swipe_longsword_D");
	effectL = IMAGEMANAGER->FindImage("swipe_longsword_L");
	effectR = IMAGEMANAGER->FindImage("swipe_longsword_R");

	subEffectU = IMAGEMANAGER->FindImage("swipe_dagger_U");
	subEffectD = IMAGEMANAGER->FindImage("swipe_dagger_D");
	subEffectL = IMAGEMANAGER->FindImage("swipe_dagger_L");
	subEffectR = IMAGEMANAGER->FindImage("swipe_dagger_R");

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

void OItemWeaponLongSword::Release()
{
	ItemBase::Release();
}

void OItemWeaponLongSword::Update()
{
	ItemBase::Update();

	if (isEffectAnim)
		EffectAnim();
}

void OItemWeaponLongSword::Render()
{
	ItemBase::Render();

	if (isEffectAnim)
		EffectRender();
}

void OItemWeaponLongSword::ShowInfo()
{
	infoImage->Render(GetMemDC(), x + 26 - 28 , y - 18 );
}

bool OItemWeaponLongSword::UseIt(int pos, int dir)
{
	GameObject * obj[2];
	//GameObject * player;
	posX = OBJECTMANAGER->GetPlayer()->GetX();
	posY = OBJECTMANAGER->GetPlayer()->GetY();
	posY -= 10;
	switch (dir)
	{
	case 8:
		obj[1] = OBJECTMANAGER->GetIsThereObj(pos - 50);
		obj[0] = OBJECTMANAGER->GetIsThereObj(pos);
		posY -= 104;
		break;
	case 2:
		obj[1] = OBJECTMANAGER->GetIsThereObj(pos + 50);
		obj[0] = OBJECTMANAGER->GetIsThereObj(pos);
		posY += 52;
		break;
	case 4:
		obj[1] = OBJECTMANAGER->GetIsThereObj(pos - 1);
		obj[0] = OBJECTMANAGER->GetIsThereObj(pos);
		posX -= 104;
		break;
	case 6:
		obj[1] = OBJECTMANAGER->GetIsThereObj(pos + 1);
		obj[0] = OBJECTMANAGER->GetIsThereObj(pos);
		posX += 52;
		break;
	}

	longRange = false;

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

			if (i == 1)
				longRange = true;

			break;
		}
	}

	return existObj;
}

void OItemWeaponLongSword::EffectAnim()
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

void OItemWeaponLongSword::EffectRender()
{
	if (!longRange)
	{
		switch (direction)
		{
		case 8:
			subEffectU->FrameRender(GetMemDC(), posX, posY + 52, 0, 6 - effectY);
			break;
		case 2:
			subEffectD->FrameRender(GetMemDC(), posX, posY, 0, 6 - effectY);
			break;
		case 4:
			subEffectL->FrameRender(GetMemDC(), posX + 52, posY, 6 - effectX, 0);
			break;
		case 6:
			subEffectR->FrameRender(GetMemDC(), posX, posY, effectX, 0);
			break;
		}
	}
	else
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
}
