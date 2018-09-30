#include "stdafx.h"
#include "OItemWeaponDagger.h"

class OPlayer1;

OItemWeaponDagger::OItemWeaponDagger()
{
}


OItemWeaponDagger::~OItemWeaponDagger()
{
}

HRESULT OItemWeaponDagger::Init(string key, int pos, ITEMKIND kind)
{
	ItemBase::Init(key,pos,kind);
	infoImage = IMAGEMANAGER->FindImage("hint_daggerthrowable");

	effectU = IMAGEMANAGER->FindImage("swipe_dagger_U");
	effectD = IMAGEMANAGER->FindImage("swipe_dagger_D");
	effectL = IMAGEMANAGER->FindImage("swipe_dagger_L");
	effectR = IMAGEMANAGER->FindImage("swipe_dagger_R");

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

void OItemWeaponDagger::Release()
{
	ItemBase::Release();
}

void OItemWeaponDagger::Update()
{
	ItemBase::Update();

	if (isEffectAnim)
		EffectAnim();
}

void OItemWeaponDagger::Render()
{
	ItemBase::Render();

	if (isEffectAnim)
		EffectRender();
}

void OItemWeaponDagger::ShowInfo()
{
	infoImage->Render(GetMemDC(), x + 26 - 70 , y - 18 );
}

void OItemWeaponDagger::EffectAnim()
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

void OItemWeaponDagger::EffectRender()
{
	switch (direction)
	{
	case 8 :
		effectU->FrameRender(GetMemDC(),posX,posY,0, 2 - effectY);
		break;
	case 2 :
		effectD->FrameRender(GetMemDC(), posX, posY, 0, effectY);
		break;
	case 4 :
		effectL->FrameRender(GetMemDC(), posX, posY, 2 - effectX, 0);
		break;
	case 6 :
		effectR->FrameRender(GetMemDC(), posX, posY, effectX, 0);
		break;
	}
}

bool OItemWeaponDagger::UseIt(int pos, int dir)
{
	GameObject * obj = OBJECTMANAGER->GetIsThereObj(pos);

	if (obj == NULL)
		return false;
	else if (obj->GetObjKind() == OBJ_MONSTER)
	{
		direction = dir;
		effectX = 0;
		effectY = 0;
		posX = obj->GetX();
		posY = obj->GetY();

		obj->Defence(attribute);

		isEffectAnim = true;
		return true;
	}
	return false;
}
