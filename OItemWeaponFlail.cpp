#include "stdafx.h"
#include "OItemWeaponFlail.h"
#include "OPlayer1.h"

OItemWeaponFlail::OItemWeaponFlail()
{
}


OItemWeaponFlail::~OItemWeaponFlail()
{
}

HRESULT OItemWeaponFlail::Init(string key, int pos, ITEMKIND kind)
{
	ItemBase::Init(key,pos,kind);
	infoImage = IMAGEMANAGER->FindImage("hint_knockbackattack");

	effectU = IMAGEMANAGER->FindImage("swipe_flail_U");
	effectD = IMAGEMANAGER->FindImage("swipe_flail_D");
	effectL = IMAGEMANAGER->FindImage("swipe_flail_L");
	effectR = IMAGEMANAGER->FindImage("swipe_flail_R");

	direction = 5;
	posX = -1;
	posY = 0;
	effectX = 0;
	effectY = 0;

	isEffectAnim = false;

	attribute = 1;
	
	return S_OK;
}

void OItemWeaponFlail::Release()
{
	ItemBase::Release();
}

void OItemWeaponFlail::Update()
{
	ItemBase::Update();

	if (isEffectAnim)
		EffectAnim();
}

void OItemWeaponFlail::Render()
{
	ItemBase::Render();

	if (isEffectAnim)
		EffectRender();
}

void OItemWeaponFlail::ShowInfo()
{
	infoImage->Render(GetMemDC() ,x + 26 - 36 ,y - 18 );
}

bool OItemWeaponFlail::UseIt(int pos, int dir)
{
	GameObject * obj[3];
	GameObject * temp;
	//GameObject * player;
	posX = OBJECTMANAGER->GetPlayer()->GetX();
	posY = OBJECTMANAGER->GetPlayer()->GetY();

	switch (dir)
	{
	case 8:
		obj[0] = OBJECTMANAGER->GetIsThereObj(pos - 1);
		obj[1] = OBJECTMANAGER->GetIsThereObj(pos);
		obj[2] = OBJECTMANAGER->GetIsThereObj(pos + 1);
		posX -= 52;
		posY -= 52;
		break;
	case 2:
		obj[0] = OBJECTMANAGER->GetIsThereObj(pos - 1);
		obj[1] = OBJECTMANAGER->GetIsThereObj(pos);
		obj[2] = OBJECTMANAGER->GetIsThereObj(pos + 1);
		posX -= 52;
		posY += 52;
		break;
	case 4:
		obj[0] = OBJECTMANAGER->GetIsThereObj(pos - 50);
		obj[1] = OBJECTMANAGER->GetIsThereObj(pos);
		obj[2] = OBJECTMANAGER->GetIsThereObj(pos + 50);
		posX -= 52;
		posY -= 52;
		break;
	case 6:
		obj[0] = OBJECTMANAGER->GetIsThereObj(pos - 50);
		obj[1] = OBJECTMANAGER->GetIsThereObj(pos);
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

			switch (dir)
			{
			case 8 :
				temp = OBJECTMANAGER->GetIsThereObj(obj[i]->GetPos() - 50);
				if (temp == NULL)
				{
					OBJECTMANAGER->SetTilePos(obj[i], obj[i]->GetPos() - 50);
					obj[i]->SetXY2(obj[i]->GetX(), obj[i]->GetY() - 52);
				}
				break;
			case 2 :
				temp = OBJECTMANAGER->GetIsThereObj(obj[i]->GetPos() + 50);
				if (temp == NULL)
				{ 
					OBJECTMANAGER->SetTilePos(obj[i], obj[i]->GetPos() + 50);
					obj[i]->SetXY2(obj[i]->GetX(), obj[i]->GetY() + 52);
				}
				break;
			case 4 :
				temp = OBJECTMANAGER->GetIsThereObj(obj[i]->GetPos() - 1);
				if (temp == NULL)
				{
					OBJECTMANAGER->SetTilePos(obj[i], obj[i]->GetPos() - 1);
					obj[i]->SetXY2(obj[i]->GetX() - 52, obj[i]->GetY());
				}
				break;
			case 6 :
				temp = OBJECTMANAGER->GetIsThereObj(obj[i]->GetPos() + 1);
				if (temp == NULL)
				{
					OBJECTMANAGER->SetTilePos(obj[i], obj[i]->GetPos() + 1);
					obj[i]->SetXY2(obj[i]->GetX() + 52, obj[i]->GetY());
				}
				break;
			}
			obj[i]->Defence(attribute);
			isEffectAnim = true;
			existObj = true;
		}
	}

	return existObj;
}

void OItemWeaponFlail::EffectAnim()
{
	effectCount++;

	if (effectCount % 5 == 0)
	{
		effectCount = 0;
		effectX++;
		effectY++;

		if (effectX == 5 || effectY == 5)
			isEffectAnim = false;
	}
}

void OItemWeaponFlail::EffectRender()
{
	switch (direction)
	{
	case 8:
		effectU->FrameRender(GetMemDC(), posX, posY - 30, 0, 5 - effectY);
		break;
	case 2:
		effectD->FrameRender(GetMemDC(), posX, posY - 52, 0, effectY);
		break;
	case 4:
		effectL->FrameRender(GetMemDC(), posX-20, posY-20, 5 - effectX, 0);
		break;
	case 6:
		effectR->FrameRender(GetMemDC(), posX - 52, posY - 20, effectX, 0);
		break;
	}
}
