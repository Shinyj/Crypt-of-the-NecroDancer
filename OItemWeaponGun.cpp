#include "stdafx.h"
#include "OItemWeaponGun.h"
#include "OPlayer1.h"

OItemWeaponGun::OItemWeaponGun()
{
}


OItemWeaponGun::~OItemWeaponGun()
{
}

HRESULT OItemWeaponGun::Init(string key, int pos, ITEMKIND kind)
{
	ItemBase::Init(key,pos,kind);
	infoImage = IMAGEMANAGER->FindImage("hint_rangedattackneedsloadingpiercing");

	effectU = IMAGEMANAGER->FindImage("swipe_blunderbuss_U");
	effectD = IMAGEMANAGER->FindImage("swipe_blunderbuss_D");
	effectL = IMAGEMANAGER->FindImage("swipe_blunderbuss_L");
	effectR = IMAGEMANAGER->FindImage("swipe_blunderbuss_R");

	direction = 5;
	posX = -1;
	posY = 0;
	effectX = 0;
	effectY = 0;
	effectCount = 0;

	isEffectAnim = false;

	attribute = 1;
	isReload = true;

	back = 0; // ³Ë¹é °Å¸®
	return S_OK;
}

void OItemWeaponGun::Release()
{
	ItemBase::Release();
}

void OItemWeaponGun::Update()
{
	ItemBase::Update();

	if (isEffectAnim)
		EffectAnim();

	if (!isReload)
		m_frameX = 1;
	else
		m_frameX = 0;
}

void OItemWeaponGun::Render()
{
	//ItemBase::Render();

	if (!isHereInven)
		IMAGEMANAGER->FrameRender(m_imageKey, GetMemDC(), x, y - jump - 20, m_frameX, m_frameY);


	if (isEffectAnim)
		EffectRender();

}

void OItemWeaponGun::ShowInfo()
{
	infoImage->Render(GetMemDC() ,x + 26 - 120 ,y - 18);
	//else
	//	IMAGEMANAGER->Render("hint_rangedattackneedsloadingpiercing", GetMemDC(), x + 26 - 120, y - 18, 1,0);

}

bool OItemWeaponGun::UseIt(int pos, int dir)
{

	if (isReload && dir != 5)
	{
		GameObject * obj[9];
		OPlayer1 * player = OBJECTMANAGER->GetPlayer();
		posX = OBJECTMANAGER->GetPlayer()->GetX();
		posY = OBJECTMANAGER->GetPlayer()->GetY();
		posY -= 10;
		switch (dir)
		{
		case 8:
			obj[0] = OBJECTMANAGER->GetIsThereObj(pos);
			obj[1] = OBJECTMANAGER->GetIsThereObj(pos - 51);
			obj[2] = OBJECTMANAGER->GetIsThereObj(pos - 50);
			obj[3] = OBJECTMANAGER->GetIsThereObj(pos - 49);
			obj[4] = OBJECTMANAGER->GetIsThereObj(pos - 102);
			obj[5] = OBJECTMANAGER->GetIsThereObj(pos - 101);
			obj[6] = OBJECTMANAGER->GetIsThereObj(pos - 100);
			obj[7] = OBJECTMANAGER->GetIsThereObj(pos - 99);
			obj[8] = OBJECTMANAGER->GetIsThereObj(pos - 98);
			posY -= 208;
			posX -= 104;
			break;
		case 2:
			obj[0] = OBJECTMANAGER->GetIsThereObj(pos);
			obj[1] = OBJECTMANAGER->GetIsThereObj(pos + 49);
			obj[2] = OBJECTMANAGER->GetIsThereObj(pos + 50);
			obj[3] = OBJECTMANAGER->GetIsThereObj(pos + 51);
			obj[4] = OBJECTMANAGER->GetIsThereObj(pos + 98);
			obj[5] = OBJECTMANAGER->GetIsThereObj(pos + 99);
			obj[6] = OBJECTMANAGER->GetIsThereObj(pos + 100);
			obj[7] = OBJECTMANAGER->GetIsThereObj(pos + 101);
			obj[8] = OBJECTMANAGER->GetIsThereObj(pos + 102);
			posY += 52;
			posX -= 104;
			break;
		case 4:
			obj[0] = OBJECTMANAGER->GetIsThereObj(pos);
			obj[1] = OBJECTMANAGER->GetIsThereObj(pos - 51);
			obj[2] = OBJECTMANAGER->GetIsThereObj(pos - 1);
			obj[3] = OBJECTMANAGER->GetIsThereObj(pos + 49);
			obj[4] = OBJECTMANAGER->GetIsThereObj(pos - 102);
			obj[5] = OBJECTMANAGER->GetIsThereObj(pos - 51);
			obj[6] = OBJECTMANAGER->GetIsThereObj(pos - 1);
			obj[7] = OBJECTMANAGER->GetIsThereObj(pos + 49);
			obj[8] = OBJECTMANAGER->GetIsThereObj(pos + 99);
			posX -= 156;
			posY -= 104;
			break;
		case 6:
			obj[0] = OBJECTMANAGER->GetIsThereObj(pos);
			obj[1] = OBJECTMANAGER->GetIsThereObj(pos - 49);
			obj[2] = OBJECTMANAGER->GetIsThereObj(pos + 1);
			obj[3] = OBJECTMANAGER->GetIsThereObj(pos + 51);
			obj[4] = OBJECTMANAGER->GetIsThereObj(pos - 98);
			obj[5] = OBJECTMANAGER->GetIsThereObj(pos - 48);
			obj[6] = OBJECTMANAGER->GetIsThereObj(pos + 2);
			obj[7] = OBJECTMANAGER->GetIsThereObj(pos + 52);
			obj[8] = OBJECTMANAGER->GetIsThereObj(pos + 102);
			posX += 52;
			posY -= 104;
			break;
		}

		bool existObj = false;

		for (int i = 0; i < 9; i++)
		{
			if (obj[i] != NULL && obj[i]->GetObjKind() == OBJ_MONSTER)
			{
				existObj = true;
				obj[i]->Defence(attribute);
			}
		}
		if (existObj)
		{
			SOUNDMANAGER->Play("wep_fire",OBJECTMANAGER->GetEffectVolum());
			direction = dir;
			effectX = 0;
			effectY = 0;
			isEffectAnim = true;
			back = 0;
			GameObject * obj;
			switch (dir)
			{
			case 8:
				obj = OBJECTMANAGER->GetIsThereObj(player->GetPos() + 50);
				if (obj == NULL || obj->GetObjKind() == OBJ_ITEM)
				{
					OBJECTMANAGER->SetTilePos(player, player->GetPos() + 50);
					player->SetIsJump(DOWN);
				}
				break;
			case 2:
				obj = OBJECTMANAGER->GetIsThereObj(player->GetPos() - 50);
				if (obj == NULL || obj->GetObjKind() == OBJ_ITEM)
				{
					OBJECTMANAGER->SetTilePos(player, player->GetPos() - 50);
					player->SetIsJump(UP);
				}
				break;
			case 4:
				obj = OBJECTMANAGER->GetIsThereObj(player->GetPos() + 1);
				if (obj == NULL || obj->GetObjKind() == OBJ_ITEM)
				{
					OBJECTMANAGER->SetTilePos(player, player->GetPos() + 1);
					player->SetIsJump(RIGHT);
				}
				break;
			case 6:
				obj = OBJECTMANAGER->GetIsThereObj(player->GetPos() - 1);
				if (obj == NULL || obj->GetObjKind() == OBJ_ITEM)
				{
					OBJECTMANAGER->SetTilePos(player, player->GetPos() - 1);
					player->SetIsJump(LEFT);
				}
				break;
			}
			isReload = false;
		}

		return existObj;
	}
	else if (dir == 5)
	{
		isReload = true;
		SOUNDMANAGER->Play("wep_reload",OBJECTMANAGER->GetEffectVolum());
		return false;
	}
	else 
		return false;
	
}

void OItemWeaponGun::EffectAnim()
{
	effectCount++;
	//back += 4;
	if (effectCount % 6 == 0)
	{
		back += 4;
		//effectCount = 0;
		effectX++;
		effectY++;

		if (effectX == 8 || effectY == 8)
		{
			isEffectAnim = false;
			back = 0;
			effectCount = 0;
		}
	}

	if(effectCount < 20)
		back += 4;
}

void OItemWeaponGun::EffectRender()
{
	switch (direction)
	{
	case 8:
		effectU->FrameRender(GetMemDC(), posX + 10, posY + 20 - back, 0, 8 - effectY);
		break;
	case 2:
		effectD->FrameRender(GetMemDC(), posX + 25, posY + back, 0, effectY);
		break;
	case 4:
		effectL->FrameRender(GetMemDC(), posX - 20 - back, posY + 20, 8 - effectX, 0);
		break;
	case 6:
		effectR->FrameRender(GetMemDC(), posX + back, posY, effectX, 0);
		break;
	}
}
