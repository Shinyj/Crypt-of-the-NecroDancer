#include "stdafx.h"
#include "OItemWeaponRapier.h"
#include "OPlayer1.h"

OItemWeaponRapier::OItemWeaponRapier()
{
}


OItemWeaponRapier::~OItemWeaponRapier()
{
}

HRESULT OItemWeaponRapier::Init(string key, int pos, ITEMKIND kind)
{
	ItemBase::Init(key,pos,kind);
	infoImage = IMAGEMANAGER->FindImage("hint_lungefordoubledamage");

	effectU = IMAGEMANAGER->FindImage("swipe_rapier_U");
	effectD = IMAGEMANAGER->FindImage("swipe_rapier_D");
	effectL = IMAGEMANAGER->FindImage("swipe_rapier_L");
	effectR = IMAGEMANAGER->FindImage("swipe_rapier_R");

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

void OItemWeaponRapier::Release()
{
	ItemBase::Release();
}

void OItemWeaponRapier::Update()
{
	ItemBase::Update();

	if (isEffectAnim)
		EffectAnim();
}

void OItemWeaponRapier::Render()
{
	ItemBase::Render();

	if (isEffectAnim)
		EffectRender();
}

void OItemWeaponRapier::ShowInfo()
{
	infoImage->Render(GetMemDC(),x + 26 - 76,  y - 18);
}

bool OItemWeaponRapier::UseIt(int pos, int dir)
{
	GameObject * obj[2];
	OPlayer1 * player = OBJECTMANAGER->GetPlayer();
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

			isEffectAnim = true;
			existObj = true;

			if (i == 1)
			{
				obj[i]->Defence(attribute * 2);
				longRange = true;

				switch (dir)
				{
				case 8:
					OBJECTMANAGER->SetTilePos(player, player->GetPos() - 50);
					player->SetIsJump(UP);
					break;
				case 2:
					OBJECTMANAGER->SetTilePos(player, player->GetPos() + 50);
					player->SetIsJump(DOWN);
					break;
				case 4:
					OBJECTMANAGER->SetTilePos(player, player->GetPos() - 1);
					player->SetIsJump(LEFT);
					break;
				case 6:
					OBJECTMANAGER->SetTilePos(player, player->GetPos() + 1);
					player->SetIsJump(RIGHT);
					break;
				}

			}
			else
				obj[i]->Defence(attribute);

			break;
		}
	}

	return existObj;
}

void OItemWeaponRapier::EffectAnim()
{
	effectCount++;

	if (effectCount % 5 == 0)
	{
		effectCount = 0;
		effectX++;
		effectY++;

		if (longRange)
		{
			if (effectX == 4 || effectY == 4)
				isEffectAnim = false;
		}
		else
		{
			if (effectX == 3 || effectY == 3)
				isEffectAnim = false;
		}
	}
}

void OItemWeaponRapier::EffectRender()
{
	if (!longRange)
	{
		switch (direction)
		{
		case 8:
			subEffectU->FrameRender(GetMemDC(), posX, posY + 52, 0, 3 - effectY);
			break;
		case 2:
			subEffectD->FrameRender(GetMemDC(), posX, posY, 0, 3 - effectY);
			break;
		case 4:
			subEffectL->FrameRender(GetMemDC(), posX + 52, posY, 3 - effectX, 0);
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
			effectU->FrameRender(GetMemDC(), posX, posY, 0, 4 - effectY);
			break;
		case 2:
			effectD->FrameRender(GetMemDC(), posX, posY, 0, 4 - effectY);
			break;
		case 4:
			effectL->FrameRender(GetMemDC(), posX, posY, 4 - effectX, 0);
			break;
		case 6:
			effectR->FrameRender(GetMemDC(), posX, posY, effectX, 0);
			break;
		}
		
	}
}
