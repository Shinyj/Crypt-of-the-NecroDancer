#include "stdafx.h"
#include "../stdafx.h"
#include "../GameNode.h"
#include "../GameObject.h"
#include "../Image/Image.h"

#include "ObjectManager.h"
#include <algorithm>
#include "../OPlayer1.h"

#include "../OFloorZone1.h"
#include "../OFloorStairs.h"
#include "../OFloorBoss.h"

#include "../OWallDoor.h"
#include "../OWallGold.h"
#include "../OWallBossWall.h"
#include "../OWallEnd.h"
#include "../OWallZone1Dirt.h"
#include "../OWallZone1Stone.h"
#include "../OWallZone2Dirt.h"
#include "../OWallZone2Stone.h"
#include "../OWallBossWall.h"


#include "../OItemShovelBasic.h"
#include "../OItemArmorLeader.h"
#include "../OItemArmorGi.h"
#include "../OItemArmorGlass.h"
#include "../OItemArmorSpiked.h"
#include "../OItemPosionFood2.h"
#include "../OItemShovelTitanium.h"
#include "../OItemTorch1.h"
#include "../OItemTorch2.h"
#include "../OItemTorch3.h"
#include "../OItemWeaponBow.h"
#include "../OItemWeaponBroad.h"
#include "../OItemWeaponDagger.h"
#include "../OItemWeaponFlail.h"
#include "../OItemWeaponGun.h"
#include "../OItemWeaponLongSword.h"
#include "../OItemWeaponRapier.h"
#include "../OItemWeaponSpear.h"

// 몬스터
#include "../OMonsterBanshee.h"
#include "../OMonsterBanshee2.h"
#include "../OMonsterBat.h"
#include "../OMonsterBatBlack.h"
#include "../OMonsterBatGreen.h"
#include "../OMonsterBatMiniBoss.h"
#include "../OMonsterBatRed.h"
#include "../OMonsterDragonRed.h"
#include "../OMonsterMageBlack.h"
#include "../OMonsterMageWhite.h"
#include "../OMonsterMageYellow.h"
#include "../OMonsterMiniBossYellow.h"
#include "../OMonsterMinotaur.h"
#include "../OMonsterMinotaur2.h"
#include "../OMonsterShopKeeper.h"
#include "../OMonsterSkeleton.h"
#include "../OMonsterSkeletonBlack.h"
#include "../OMonsterSkeletonYellow.h"
#include "../OMonsterSlimeGreen.h"
#include "../OMonsterSlimeBlue.h"
#include "../OMonsterShopKeeper.h"
#include "../OMonsterZombie.h"
#include "../OMonsterKingconga.h"


ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

HRESULT ObjectManager::Init()
{
	heartImage = IMAGEMANAGER->FindImage("heart_beat");
	blueBarImage = IMAGEMANAGER->FindImage("beat_blue");
	greenBarImage = IMAGEMANAGER->FindImage("beat_green");
	redBarImage = IMAGEMANAGER->FindImage("beat_red");

	backgroundBlack = IMAGEMANAGER->FindImage("overlay_black");
	backgroundRed = IMAGEMANAGER->FindImage("overlay_red");
	backgroundWhite = IMAGEMANAGER->FindImage("overlay_white");
	backgroundGray = IMAGEMANAGER->FindImage("popup_back");

	coinMultiple = IMAGEMANAGER->FindImage("coinmultiplier");
	numberImage = IMAGEMANAGER->FindImage("TEMP_digits");

	titleImage   = IMAGEMANAGER->FindImage("runsummary");
	scoreImage	 = IMAGEMANAGER->FindImage("game_score");
	goLobbyImage = IMAGEMANAGER->FindImage("options_quickrestart");
	goLobbyImage_s = IMAGEMANAGER->FindImage("options_quickrestart_s");
	restartImage = IMAGEMANAGER->FindImage("options_quit_lobby");
	restartImage_s = IMAGEMANAGER->FindImage("options_quit_lobby_s");
	numberImageBig = IMAGEMANAGER->FindImage("TEMP_digits2");
	isFlash = 0;
	feverTime = 0;
	killCount = 0;
	isPlayerDie = false;
	selectNum = 0;
	return S_OK;
}

void ObjectManager::UpdateDeatUI()
{
	if (isPlayerDie)
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_DOWN))
		{
			selectOption[selectNum] = false;
			selectNum = (selectNum + 1) % 2;
			selectOption[selectNum] = true;
		}
		else if (KEYMANAGER->IsOnceKeyDown(VK_UP))
		{
			selectOption[selectNum] = false;
			selectNum = (selectNum - 1);
			if (selectNum < 0) selectNum = 1;
			selectOption[selectNum] = true;
		}
		else if (KEYMANAGER->IsOnceKeyDown(VK_RETURN))
		{
			switch (selectNum)
			{
			case 1 :
				isPlayerDie = false;
				SOUNDMANAGER->AllStop();
				SCENEMANAGER->ChangeScene("lobby");
				break;
			case 0:
				isPlayerDie = false;
				SOUNDMANAGER->AllStop();
				string bgm = SOUNDMANAGER->GetBgmKey();
				SCENEMANAGER->ChangeScene("lobby");
				SCENEMANAGER->ChangeScene(bgm);
				break;
			}
		}
	}
}

void ObjectManager::RenderDeathUI()
{


	if (isPlayerDie)
	{
		backgroundBlack->AlphaRender(GetMemDC(), 0, 0, 100);

			//titleImage =
			//scoreImage =
			//goLobbyImage =
			//goLobbyImage_s
			//restartImage =
			//restartImage_s

		titleImage->Render(GetMemDC(), WINSIZEX2 / 2 - titleImage->GetWidth() / 2,70);
		
		scoreImage->Render(GetMemDC(), 410, 170);


		if (selectNum == 0)
			goLobbyImage_s->Render(GetMemDC(), WINSIZEX2 / 2 - goLobbyImage_s->GetWidth() / 2, 310);
		else
			goLobbyImage->Render(GetMemDC(), WINSIZEX2 / 2 - goLobbyImage->GetWidth() / 2, 310);

		if (selectNum == 1)
			restartImage_s->Render(GetMemDC(), WINSIZEX2 / 2 - restartImage_s->GetWidth() / 2, 350);
		else
			restartImage->Render(GetMemDC(), WINSIZEX2 / 2 - restartImage->GetWidth() / 2, 350);
	
		int curCoin = player->GetGold();
		int num[4] = { 0,0,0,0 };
		num[0] = curCoin / 1000;
		num[1] = (curCoin - num[0] * 1000) / 100;
		num[2] = (curCoin - num[0] * 1000 - num[1] * 100) / 10;
		num[3] = (curCoin - num[0] * 1000 - num[1] * 100 - num[2] * 10) / 1;
		bool b = false;
		for (int i = 0; i < 4; i++)
		{
			if (b || i == 3)
			{
				numberImageBig->FrameRender(GetMemDC(), 500 + 16 * i, 165,num[i], 0);
			}

			else if (b == false && num[i] != 0)
			{
				numberImageBig->FrameRender(GetMemDC(), 500 + 16 * i, 165, num[i], 0);
				b = true;
			}
		}
	}
}

void ObjectManager::ObjClear()
{
	m_viObj = m_vObj.begin();

	//for (m_viObj; m_viObj != m_vObj.end(); ++m_viObj )
	//{
	//
	//	delete (*m_viObj);
	//	m_viObj = m_vObj.erase(m_viObj);
	//}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		objTile[i] = nullptr;
		FloorTile[i] = nullptr;
	}

	m_vObj.clear();
}

GameObject *  ObjectManager::ObjPush(GameObject obj)
{
	// 만들어진 오브젝트의 종류에 따라 다른 객체들을 만들어서
	// 벡터에다가 넣어야함 여기가 겁나 복잡해 질 듯
	GameObject * newObj;
	switch (obj.GetObjKind())
	{
	case OBJ_FLOOR:
		newObj = CreateFloor(obj);
		newObj->SetObjKind(OBJ_FLOOR);
		if (obj.GetImageKey() == "floor_stairs")
			objTile[newObj->GetPos()] = newObj;
		else
			FloorTile[obj.GetPos()] = newObj;
		break;
	case OBJ_WALL:
		newObj = CreateWall(obj);
		newObj->SetObjKind(OBJ_WALL);
		objTile[newObj->GetPos()] = newObj;
		break;
	case OBJ_ITEM:
		newObj = CreateItem(obj);
		newObj->SetObjKind(OBJ_ITEM);
		objTile[newObj->GetPos()] = newObj;
		break;
	case OBJ_MONSTER:
		newObj = CreateMonster(obj);
		newObj->SetObjKind(OBJ_MONSTER);
		objTile[newObj->GetPos()] = newObj;
		break;
	case OBJ_PLAYER:
		newObj = CreatePlayer(obj);
		newObj->SetObjKind(OBJ_PLAYER);
		objTile[newObj->GetPos()] = newObj;
		break;
	}

	m_vObj.push_back(newObj);

	return newObj;
}

void ObjectManager::ObjNormalUpdate()
{
}

void ObjectManager::ObjTurnUpdate()
{
}

void ObjectManager::SetCamera(POINT camera)
{
	m_viObj = m_vObj.begin();
	for (m_viObj; m_viObj != m_vObj.end(); m_viObj++)
		(*m_viObj)->SetXY(camera);
}

void ObjectManager::ObjSort()
{
	// 벡터를 정렬시켜서 z 오더를 해결 했다.
	// 오브젝트 벡터 안에 있는 오브젝트들을 모두 렌더
	sort(m_vObj.begin(), m_vObj.end(), less_than_key());

}

void ObjectManager::AllObjUpdate()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (FloorTile[i] != NULL)
			FloorTile[i]->Update();

		if (objTile[i] != NULL)
		{
			if (objTile[i]->GetObjKind() == OBJ_PLAYER)
				continue;
			else
				objTile[i]->Update();
			
			//if (objTile[i]->GetObjKind() == OBJ_FLOOR)
			//{
			//	// 중단점
			//	int num = 0;
			//}
		}

	}
	player->UpdateEquit();

}

void ObjectManager::DeleteObj(GameObject * obj)
{
	//POINT temp = { -1000,-1000 };
	//objTile[obj->GetPos()]->SetXY2(-1000,-1000);
	int temp = obj->GetPos();

	m_viObj = m_vObj.begin();

	for (m_viObj; m_viObj != m_vObj.end(); )
	{
		if ((*m_viObj)->GetObjKind() != obj->GetObjKind())
		{
			m_viObj++;
			continue;
		}
		if ((*m_viObj)->GetPos() == temp)
		{
			delete(*m_viObj);
			m_viObj = m_vObj.erase(m_viObj);
			break;
		}
		else
			m_viObj++;
	}
	objTile[temp] = nullptr;
}

void ObjectManager::SetBeat()
{
	m_vBeat = SOUNDMANAGER->GetVBeat();
	m_viBeat = SOUNDMANAGER->GetViBeat();

	m_viBeat = m_vBeat.begin();
	int index = 0;
	arr_start = index;
	for (m_viBeat; m_viBeat != m_vBeat.end(); m_viBeat++)
		//arr[index++] = (float)(*m_viBeat);
		arr[index++] = (((float)(*m_viBeat))/ 450.0) * 120;
	
	arr_end = index;
}

void ObjectManager::Release()
{
	SAFE_DELETE_ARRAY(*objTile);
	SAFE_DELETE(player);
}
static float lastTime = timeGetTime();
void ObjectManager::Update()
{
	if (KEYMANAGER->IsOnceKeyDown('R'))
	{
		SOUNDMANAGER->AllStop();
		SetBeat();
		SOUNDMANAGER->Play(SOUNDMANAGER->GetBgmKey(), bgmVolum);
	}

	// 가운데 심장 프레임 관리
	

	if (!KEYMANAGER->IsStayKeyDown('Z'))
	{
		//curTime = timeGetTime();
		//frameDelta = (curTime - lastTime) * 0.001f;

		//if(frameDelta >= 1.0f / 1000.0f)
		if (GetTickCount() - curTime >= 1000)
		{
			// 비트들 이동시키는 곳
			for (int i = arr_start; i < arr_end; i++)
			{
				arr[i] = arr[i] - bit;//  4.25f;//2.5;
			}

			lastTime = curTime;
		}



				// 플레이어의 비트타임 설정
				if (arr[arr_start] <= 40 && player->GetBeatTime() == false && !isGiveBeatTime)
				{
					player->SetBeatTime(true);
					isGiveBeatTime = true;
				}

				// 오브젝트들의 비트 타임 설정
				if (arr[arr_start] <= -12)
				{
					arr_start++;
					for (m_viObj = m_vObj.begin(); m_viObj != m_vObj.end(); m_viObj++)
					{
						if ((*m_viObj)->GetObjKind() == OBJ_PLAYER || (*m_viObj)->GetObjKind() == OBJ_WALL) continue;

						if (isPlayerDie == false)
						{

							(*m_viObj)->SetBeatTime(true);
						}
					}
					frameX_heart = 1;

					if (player->GetIsPlayerDie() == false)
						player->hp_beat();

					if (player->GetBeatTime())
						LostFever();

					player->SetBeatTime(false);

					isGiveBeatTime = false;
				}
				else if (frameX_heart == 1)
				{
					heart_count++;
					if (heart_count % 4 == 0)
					{
						heart_count = 0;
						frameX_heart = 0;
					}
				}
			
	}


	UpdateDeatUI();
}

void ObjectManager::Render()
{

	// 오브젝트들을 정렬시킨뒤 화면 안의 객체들만 렌더시킨다.
	ObjSort();
	RECT temp;
	RECT globalRC = { -100,-100,1000,600 };
	
	// 바닥 랜더
	m_viObj = m_vObj.begin();
	for (m_viObj; m_viObj != m_vObj.end(); m_viObj++)
	{
		POINT temp = { (*m_viObj)->GetX() ,(*m_viObj)->GetY() };
		if (PtInRect(&globalRC, temp))
		{
			if ((*m_viObj)->GetObjKind() == OBJ_FLOOR)
			{
				if(objTile[(*m_viObj)->GetPos()] == NULL)
					(*m_viObj)->Render();
				else if(objTile[(*m_viObj)->GetPos()]->GetImageKey() == "wall_door_front" ||
					objTile[(*m_viObj)->GetPos()]->GetImageKey() == "wall_door_side")
					(*m_viObj)->Render();
		        else if(objTile[(*m_viObj)->GetPos()]->GetObjKind() != OBJ_WALL)
					(*m_viObj)->Render();
	
				
			}
		}
	}

	//// 다른 오브젝트 랜더
	m_viObj = m_vObj.begin();
	for (m_viObj; m_viObj != m_vObj.end(); m_viObj++)
	{
		POINT temp = { (*m_viObj)->GetX() ,(*m_viObj)->GetY() };
		if (PtInRect(&globalRC, temp))
		{
			if ((*m_viObj)->GetObjKind() != OBJ_FLOOR)
			{
				(*m_viObj)->Render();

			}
		}
	}
	// 오브젝트 정렬, 카메라안쪽 렌더 end

	// 여기다가 비트에 맞는 바를 렌더 


	// 요기는 플래시 효과를 위한 자리
	Flash();

	// 인터페이스 ui 관련 내용

	for (int i = arr_start; i < arr_start + 5; i++)
	{

		blueBarImage->FrameRender(GetMemDC(), WINSIZEX2/2 + (arr[i]), 430, 0, 0);
		blueBarImage->FrameRender(GetMemDC(), WINSIZEX2/2 - (arr[i]), 430, 0, 0);
	}

	//IMAGEMANAGER->FrameRender("beat_blue", GetMemDC(), WINSIZEX2 / 2 - 40, 470, 0, 0);
	//IMAGEMANAGER->FrameRender("beat_blue", GetMemDC(), WINSIZEX2 / 2, 470, 0, 0);
	//IMAGEMANAGER->FrameRender("beat_blue", GetMemDC(), WINSIZEX2 / 2 + 40, 470, 0, 0);
	// 맵 중앙 심장 렌더

	heartImage->FrameRender(GetMemDC(), WINSIZEX2/2- 35, 400, frameX_heart,0);
	player->RenderUI();
	
	coinMultiple->Render(GetMemDC(), WINSIZEX2 /2-50,510);
	
	numberImage->FrameRender(GetMemDC(), WINSIZEX2 / 2 + 40, 510,1 + feverTime, 0);

	

	RenderDeathUI();


	if(KEYMANAGER->IsOnceKeyDown('W'))
	{
		bit += 0.05;
	}
	else if (KEYMANAGER->IsOnceKeyDown('S'))
	{
		bit -= 0.05;
	}

	//char str[20];
	//sprintf(str, "%f", bit);
	//TextOut(GetMemDC(), 0, 400, str, strlen(str));
}



void ObjectManager::SetFever()
{
	if (feverTime == 0)
	{
		feverTime++;
		SOUNDMANAGER->Play("sfx_chain_groove_ST",effectVolum/2);
	}


	killCount++;
	
	if (killCount % 5 == 0 && feverTime < 4)
	{
		feverTime++;
		SOUNDMANAGER->Play("sfx_chain_groove_ST", effectVolum / 2);
	}
}

void ObjectManager::LostFever()
{
	if (feverTime != 0)
	{
		SOUNDMANAGER->Play("sfx_chain_break_ST", effectVolum / 2);
		killCount = 0;
		feverTime = 0;
	}
}

void ObjectManager::InitLight()
{

	m_viObj2 = m_vObj.begin();
	for (m_viObj2; m_viObj2 != m_vObj.end(); m_viObj2++)
	{
		
		if ((*m_viObj2)->GetObjKind() != OBJ_PLAYER)
		{
			(*m_viObj2)->SetLight(false);
			(*m_viObj2)->SetIsSight(false);
			
		}
	}
}

void ObjectManager::InitSight()
{
	m_viObj2 = m_vObj.begin();
	for (m_viObj2; m_viObj2 != m_vObj.end(); m_viObj2++)
	{

		if ((*m_viObj2)->GetObjKind() != OBJ_PLAYER)
		{
			if ((*m_viObj2)->GetImageKey() == "wall_end") continue;
			(*m_viObj2)->SetFirstSight();

		}
	}
}

void ObjectManager::Flash()
{
	if (isFlash)
	{
		isFlash++;
		if (isFlash < 2)
			backgroundBlack->Render(GetMemDC());
		else if (isFlash < 4)
			backgroundRed->Render(GetMemDC());
		else if (isFlash < 6)
			backgroundWhite->Render(GetMemDC());
		else if (isFlash < 8)
			backgroundGray->Render(GetMemDC());
		else
			isFlash = 0;
	}
}

GameObject * ObjectManager::CreateFloor(GameObject obj)
{

	if (obj.GetImageKey() == "floor_zone1")
	{		
		OFloorZone1 * newObj = new OFloorZone1;
		newObj->Init(obj.GetPos());
		return newObj;
	}
	else if ( obj.GetImageKey() == "floor_stairs")
	{
		OFloorStairs * newObj = new OFloorStairs;
		newObj->Init(obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "floor_boss")
	{
		OFloorBoss * newObj = new OFloorBoss;
		newObj->Init(obj.GetPos());
		return newObj;
	}

	return nullptr;
}

GameObject * ObjectManager::CreateWall(GameObject obj)
{
	if (obj.GetImageKey() == "wall_shop_stone")
	{
		OWallGold * newObj = new OWallGold;
		newObj->Init(obj.GetImageKey(), obj.GetPos(),obj.GetIsTorch());
		return newObj;
	}
	else if (obj.GetImageKey() == "wall_door_front")
	{
		OWallDoor * newObj = new OWallDoor;
		newObj->Init(obj.GetPos(),false);
		return newObj;
	}
	else if (obj.GetImageKey() == "wall_door_side")
	{
		OWallDoor * newObj = new OWallDoor;
		newObj->Init(obj.GetPos(), true);
		return newObj;
	}
	else if (obj.GetImageKey() == "wall_end")
	{
		OWallEnd * newObj = new OWallEnd;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "wall_z1_drit")
	{
			OWallZone1Dirt * newObj = new OWallZone1Dirt;
		newObj->Init(obj.GetImageKey(), obj.GetPos(), obj.GetIsTorch());
		return newObj;
	}
	else if (obj.GetImageKey() == "wall_z1_stone")
	{
		OWallZone1Stone * newObj = new OWallZone1Stone;
		newObj->Init(obj.GetImageKey(), obj.GetPos(), obj.GetIsTorch());
		return newObj;
	}
	else if (obj.GetImageKey() == "wall_z2")
	{
		OWallZone2Dirt * newObj = new OWallZone2Dirt;
		newObj->Init(obj.GetImageKey(), obj.GetPos(), obj.GetIsTorch());
		return newObj;
	}
	else if (obj.GetImageKey() == "wall_z2_stone")
	{
		OWallZone2Stone * newObj = new OWallZone2Stone;
		newObj->Init(obj.GetImageKey(), obj.GetPos(), obj.GetIsTorch());
		return newObj;
	}
	else if (obj.GetImageKey() == "boss_wall")
	{
		OWallBossWall * newObj = new OWallBossWall;
		newObj->Init(obj.GetImageKey(), obj.GetPos(), obj.GetIsTorch());
		return newObj;
	}
}

GameObject * ObjectManager::CreateItem(GameObject obj)
{
	if (obj.GetImageKey() == "shovel_basic")
	{
		OItemShovelBasic * newObj = new OItemShovelBasic;
		newObj->Init(obj.GetImageKey(), obj.GetPos(), ITEM_SHOVEL);
		return newObj;
	}
	else if (obj.GetImageKey() == "armor_leather")
	{
		OItemArmorLeader * newObj = new OItemArmorLeader;
		newObj->Init(obj.GetImageKey(), obj.GetPos() , ITEM_ARMOR);
		return newObj;
	}
	else if (obj.GetImageKey() == "armor_chain")
	{
		OItemArmorSpiked * newObj = new OItemArmorSpiked;
		newObj->Init(obj.GetImageKey(), obj.GetPos(), ITEM_ARMOR);
		return newObj;
	}
	else if (obj.GetImageKey() == "armor_gi")
	{
		OItemArmorGi * newObj = new OItemArmorGi;
		newObj->Init(obj.GetImageKey(), obj.GetPos(), ITEM_ARMOR);
		return newObj;
	}
	else if (obj.GetImageKey() == "armor_glass")
	{
		OItemArmorGlass * newObj = new OItemArmorGlass;
		newObj->Init(obj.GetImageKey(), obj.GetPos(), ITEM_ARMOR);
		return newObj;
	}
	else if (obj.GetImageKey() == "food_2")
	{
		OItemPosionFood2 * newObj = new OItemPosionFood2;
		newObj->Init(obj.GetImageKey(), obj.GetPos(), ITEM_POSION);
		return newObj;
	}
	else if (obj.GetImageKey() == "shovel_titanium")
	{
		OItemShovelTitanium * newObj = new OItemShovelTitanium;
		newObj->Init(obj.GetImageKey(), obj.GetPos(), ITEM_SHOVEL);
		return newObj;
	}
	else if (obj.GetImageKey() == "torch_1")
	{
		OItemTorch1 * newObj = new OItemTorch1;
		newObj->Init(obj.GetImageKey(), obj.GetPos(), ITEM_TORCH);
		return newObj;
	}
	else if (obj.GetImageKey() == "torch_2")
	{
		OItemTorch2 * newObj = new OItemTorch2;
		newObj->Init(obj.GetImageKey(), obj.GetPos(), ITEM_TORCH);
		return newObj;
	}
	else if (obj.GetImageKey() == "torch_3")
	{
		OItemTorch3 * newObj = new OItemTorch3;
		newObj->Init(obj.GetImageKey(), obj.GetPos(), ITEM_TORCH);
		return newObj;
	}
	else if (obj.GetImageKey() == "weapon_bow")
	{
		OItemWeaponBow * newObj = new OItemWeaponBow;
		newObj->Init(obj.GetImageKey(), obj.GetPos(), ITEM_WEAPON);
		return newObj;
	}
	else if (obj.GetImageKey() == "weapon_broad")
	{
		OItemWeaponBroad * newObj = new OItemWeaponBroad;
		newObj->Init(obj.GetImageKey(), obj.GetPos(), ITEM_WEAPON);
		return newObj;
	}
	else if (obj.GetImageKey() == "weapon_dagger")
	{
		OItemWeaponDagger * newObj = new OItemWeaponDagger;
		newObj->Init(obj.GetImageKey(), obj.GetPos(), ITEM_WEAPON);
		return newObj;
	}
	else if (obj.GetImageKey() == "weapon_flail")
	{
		OItemWeaponFlail * newObj = new OItemWeaponFlail;
		newObj->Init(obj.GetImageKey(), obj.GetPos(), ITEM_WEAPON);
		return newObj;
	}
	else if (obj.GetImageKey() == "weapon_gun")
	{
		OItemWeaponGun * newObj = new OItemWeaponGun;
		newObj->Init(obj.GetImageKey(), obj.GetPos(), ITEM_WEAPON);
		return newObj;
	}
	else if (obj.GetImageKey() == "weapon_long")
	{
		OItemWeaponLongSword * newObj = new OItemWeaponLongSword;
		newObj->Init(obj.GetImageKey(), obj.GetPos(), ITEM_WEAPON);
		return newObj;
	}
	else if (obj.GetImageKey() == "weapon_rapier")
	{
		OItemWeaponRapier * newObj = new OItemWeaponRapier;
		newObj->Init(obj.GetImageKey(), obj.GetPos(), ITEM_WEAPON);
		return newObj;
	}
	else if (obj.GetImageKey() == "weapon_spear")
	{
		OItemWeaponSpear * newObj = new OItemWeaponSpear;
		newObj->Init(obj.GetImageKey(), obj.GetPos(), ITEM_WEAPON);
		return newObj;
	}
	
}

GameObject * ObjectManager::CreateMonster(GameObject obj)
{
	if (obj.GetImageKey() == "banshee")
	{
		OMonsterBanshee * newObj = new OMonsterBanshee;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "banshee2")
	{
		OMonsterBanshee2 * newObj = new OMonsterBanshee2;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "bat")
	{
		OMonsterBat * newObj = new OMonsterBat;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "bat_black")
	{
		OMonsterBatBlack * newObj = new OMonsterBatBlack;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "bat_green")
	{
		OMonsterBatGreen * newObj = new OMonsterBatGreen;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "bat_miniboss")
	{
		OMonsterBatMiniBoss * newObj = new OMonsterBatMiniBoss;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "bat_red")
	{
		OMonsterBatRed * newObj = new OMonsterBatRed;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "dragon_red")
	{
		OMonsterDragonRed * newObj = new OMonsterDragonRed;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "mage_black")
	{
		OMonsterMageBlack * newObj = new OMonsterMageBlack;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "mage_white")
	{
		OMonsterMageWhite * newObj = new OMonsterMageWhite;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "mage_yellow")
	{
		OMonsterMageYellow * newObj = new OMonsterMageYellow;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "miniboss_yellow")
	{
		OMonsterMiniBossYellow * newObj = new OMonsterMiniBossYellow;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "minotaur")
	{
		OMonsterMinotaur * newObj = new OMonsterMinotaur;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "minotaur2")
	{
		OMonsterMinotaur2 * newObj = new OMonsterMinotaur2;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "shopkeeper")
	{
		OMonsterShopKeeper * newObj = new OMonsterShopKeeper;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "skeleton")
	{
		OMonsterSkeleton * newObj = new OMonsterSkeleton;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "skeleton_black")
	{
		OMonsterSkeletonBlack * newObj = new OMonsterSkeletonBlack;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "skeleton_yellow")
	{
		OMonsterSkeletonYellow * newObj = new OMonsterSkeletonYellow;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "slime_green")
	{
		OMonsterSlimeGreen * newObj = new OMonsterSlimeGreen;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "slime_blue")
	{
		OMonsterSlimeBlue * newObj = new OMonsterSlimeBlue;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "shopkeeper")
	{
		OMonsterShopKeeper * newObj = new OMonsterShopKeeper;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "king_conga")
	{
		OMonsterKingconga * newObj = new OMonsterKingconga;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
	else if (obj.GetImageKey() == "zombie_snake")
	{
		OMonsterZombie * newObj = new OMonsterZombie;
		newObj->Init(obj.GetImageKey(), obj.GetPos());
		return newObj;
	}
}

GameObject * ObjectManager::CreatePlayer(GameObject obj)
{
	OPlayer1 * newObj = new OPlayer1;

	newObj->Init(obj.GetPos());
	player = newObj;
	return newObj;
}
