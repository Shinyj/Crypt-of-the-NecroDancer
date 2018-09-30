#include "stdafx.h"
#include "OItemWeaponBroad.h"
#include "OPlayer1.h"

OItemWeaponBroad::OItemWeaponBroad()
{
}


OItemWeaponBroad::~OItemWeaponBroad()
{
}

HRESULT OItemWeaponBroad::Init(string key, int pos, ITEMKIND kind)
{
	ItemBase::Init(key,pos,kind);
	infoImage = IMAGEMANAGER->FindImage("hint_wideattack");

	effectU = IMAGEMANAGER->FindImage("swipe_broadsword_U");
	effectD = IMAGEMANAGER->FindImage("swipe_broadsword_D");
	effectL = IMAGEMANAGER->FindImage("swipe_broadsword_L");
	effectR = IMAGEMANAGER->FindImage("swipe_broadsword_R");

	direction = 5;
	posX = -1; // ÀÌÆåÆ® Ãâ·Â ÁÂÇ¥
	posY = 0;
	effectX = 0;
	effectY = 0;

	effectCount = 0;

	isEffectAnim = false;
	attribute = 1;

	return S_OK;
}

void OItemWeaponBroad::Release()
{
	ItemBase::Release();
}

void OItemWeaponBroad::Update()
{
	ItemBase::Update();
	if (isEffectAnim)
		EffectAnim();
}

void OItemWeaponBroad::Render()
{
	ItemBase::Render();

	if (isEffectAnim)
		EffectRender();
}

void OItemWeaponBroad::ShowInfo()
{
	infoImage->Render(GetMemDC(), x + 26 - 36, y - 18);
}

bool OItemWeaponBroad::UseIt(int pos, int dir)
{
	GameObject * obj[3];
	//GameObject * player;
	posX = OBJECTMANAGER->GetPlayer()->GetX();
	posY = OBJECTMANAGER->GetPlayer()->GetY();

	switch (dir)
	{
	case 8 :
		obj[0] = OBJECTMANAGER->GetIsThereObj(pos-1);
		obj[1] = OBJECTMANAGER->GetIsThereObj(pos);
		obj[2] = OBJECTMANAGER->GetIsThereObj(pos+1);
		posX -= 52;
		posY -= 52;
		break;
	case 2 :
		obj[0] = OBJECTMANAGER->GetIsThereObj(pos-1);
		obj[1] = OBJECTMANAGER->GetIsThereObj(pos);
		obj[2] = OBJECTMANAGER->GetIsThereObj(pos+1);
		posX -= 52;
		posY += 52;
		break;
	case 4 :
		obj[0] = OBJECTMANAGER->GetIsThereObj(pos -50);
		obj[1] = OBJECTMANAGER->GetIsThereObj(pos);
		obj[2] = OBJECTMANAGER->GetIsThereObj(pos + 50);
		posX -= 52;
		posY -= 52;
		break;
	case 6 :
		obj[0] = OBJECTMANAGER->GetIsThereObj(pos - 50);
		obj[1] = OBJECTMANAGER->GetIsThereObj(pos );
		obj[2] = OBJECTMANAGER->GetIsThereObj(pos + 50);
		posX += 52;
		posY -= 52;
		break;
	}

	bool existObj = false;

	for (int i = 0; i < 3; i++)
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

void OItemWeaponBroad::EffectAnim()
{
	effectCount++;

	if (effectCount % 5 == 0)
	{
		effectCount = 0;
		effectX++;
		effectY++;

		if (effectX == 3 || effectY == 3)
			isEffectAnim = false;
	}
}

void OItemWeaponBroad::EffectRender()
{
	switch (direction)
	{
	case 8:
		effectU->FrameRender(GetMemDC(), posX, posY, 0, 2 - effectY);
		break;				
	case 2:					
		effectD->FrameRender(GetMemDC(), posX, posY, 0, effectY);
		break;				
	case 4:					
		effectL->FrameRender(GetMemDC(), posX, posY, 2 - effectX, 0);
		break;				
	case 6:					
		effectR->FrameRender(GetMemDC(), posX, posY, effectX, 0);
		break;
	}
}
