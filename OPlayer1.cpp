#include "stdafx.h"
#include "OPlayer1.h"
#include "Image\Image.h"
#include "OItemWeaponDagger.h"
#include "OItemShovelBasic.h"
OPlayer1::OPlayer1()
{
}


OPlayer1::~OPlayer1()
{
}

HRESULT OPlayer1::Init(int pos)
{
	strcpy(m_headImageKey, "player_head");
	strcpy(m_bodyImageKey, "player_body");

	headImage = IMAGEMANAGER->FindImage("player_head");
	bodyImage = IMAGEMANAGER->FindImage("player_body");

	heartImage = IMAGEMANAGER->FindImage("heart");
	heratLargeImage = IMAGEMANAGER->FindImage("heart_large");
	heartHalfImage = IMAGEMANAGER->FindImage("heart_half");
	heartHalfLageImage = IMAGEMANAGER->FindImage("heart_half_large");
	heartEmpty = IMAGEMANAGER->FindImage("heart_empty");

	euipWImage = IMAGEMANAGER->FindImage("slot_attack");
	euipAImage = IMAGEMANAGER->FindImage("slot_body");
	euipPImage = IMAGEMANAGER->FindImage("slot_item");
	euipSImage = IMAGEMANAGER->FindImage("slot_shovel");
	euipTImage = IMAGEMANAGER->FindImage("slot_torch");
	
	euipRImage = IMAGEMANAGER->FindImage("hud_slot_reload");
	euipGImage = IMAGEMANAGER->FindImage("weapon_gun");

	numberImage = IMAGEMANAGER->FindImage("TEMP_digits");
	XImage = IMAGEMANAGER->FindImage("X");

	coin = IMAGEMANAGER->FindImage("coin");
	diamond = IMAGEMANAGER->FindImage("diamond");

	shadowImage = IMAGEMANAGER->FindImage("shadow_small");

	//euipRImage
	m_frameX = 0; // x 프레임 인덱스
	m_frameY = 0; // y 프레임 인덱스
	m_headFrameX = 0;
	m_headFrameY = 0;
	m_maxX = IMAGEMANAGER->FindImage(m_headImageKey)->GetMaxFrameX();

	x = (pos % TILEX) * TILESIZE;
	y = (pos / TILEY) * TILESIZE;

	m_move = NONE;
	count = 0.0f;
	jump = 0;

	m_pos = pos;

	m_HP = 50;
	m_MaxHP = 50;

	defence = 0;
	curCoin = 0;

	isPlayerDie = false;
	
	isCheat = false;

	m_equipWeapon = nullptr;
	m_equipArmor = nullptr;
	m_posion = nullptr;
	m_shovel = nullptr;
	m_torch = nullptr;

	inven[0] = { 25, 5, "", nullptr };
	inven[1] = { 90, 5, "", nullptr };
	inven[2] = { 155, 5, "", nullptr };
	inven[3] = { 220, 5, "", nullptr };
	inven[4] = { 25, 85, "", nullptr };

	for(int i = 0 ; i < 5 ; i++)
		isUseInven[i] = false;

	isEarthquake = false;
	earthquakeCount = 0;

	sight = 2; // 처음의 밝기는 3 ( 3칸을 이동해야함
	isSight = true; // 플레이어니까 당연히 보여야함
	isFirstSight = true; // 이것도 당연하지

	GameObject obj;
	GameObject * pObj;
	OItemWeaponDagger  weapon;// = new OItemWeaponDagger;

	weapon.Init("weapon_dagger", 2001, ITEM_WEAPON);
	obj = weapon;
	pObj = OBJECTMANAGER->ObjPush(obj);
	//SetInven(obj);
	m_equipWeapon = pObj;
	
	m_equipWeapon->SetIsGoInven(false);
	OBJECTMANAGER->SetTilePos(m_equipWeapon, 2499);
	m_equipWeapon->SetIsHereInven(true);

	
	OItemShovelBasic  shovel;// = new OItemShovelBasic;
	shovel.Init("shovel_basic", 2000, ITEM_SHOVEL);
	obj = shovel;
	pObj = OBJECTMANAGER->ObjPush(obj);
	m_shovel = pObj;
	
	m_shovel->SetIsGoInven(false);
	OBJECTMANAGER->SetTilePos(m_shovel, 2498);
	m_shovel->SetIsHereInven(true);

	if (m_shovel != NULL)
	{
		isUseInven[0] = true;
		inven[0].uiKey = "slot_shovel";
		inven[0].obj = m_shovel;
	}
	if (m_equipWeapon != NULL)
	{
		for (int i = 0; i < 2; i++)
		{
			if (isUseInven[i] == false)
			{
				isUseInven[i] = true;
				inven[i].uiKey = "slot_attack";
				inven[i].obj = m_equipWeapon;
				break;
			}
		}
	}


	return S_OK;
}

void OPlayer1::Release()
{

	SAFE_DELETE(m_equipWeapon);
	SAFE_DELETE(m_equipArmor);
	SAFE_DELETE(m_posion);
	SAFE_DELETE(m_shovel);
	SAFE_DELETE(m_torch);
}

void OPlayer1::Update()
{
	if (KEYMANAGER->IsOnceKeyDown('C'))
	{
		isCheat = !isCheat;
	}

	if (KEYMANAGER->IsOnceKeyDown('H'))
		m_HP -= 5;
	else if (KEYMANAGER->IsOnceKeyDown('J'))
		m_HP += 5;
	PlayerMove();
	Anim();

	if (KEYMANAGER->IsOnceKeyDown('I'))
		this->Die();
	//LayCast();

	LayCast();
}

void OPlayer1::Render()
{
	if (!isPlayerDie)
	{
		shadowImage->AlphaRender(GetMemDC(), x, y - 20, 60);
		//IMAGEMANAGER->AlphaRender("shadow_large",GetMemDC(),x,y-20,100);
		//IMAGEMANAGER->AlphaRender("shadow_small", GetMemDC(), x, y - 39,80);
		if (isRight)
		{
			bodyImage->FrameRender(GetMemDC(), x, y - 18 + jump, m_frameX, m_frameY);
			headImage->FrameRender(GetMemDC(), x, y - 18 + jump, m_frameX, 0);
		}
		else
		{
			bodyImage->FrameRender(GetMemDC(), x, y - 18 + jump, m_frameX + 4, m_frameY);
			headImage->FrameRender(GetMemDC(), x, y - 18 + jump, m_frameX + 4, 0);
		}
		//IMAGEMANAGER->f(m_headImageKey, GetMemDC(), x, y - 18, m_frameX, m_frameY);

	}

		ShowItemInfo();

		//char str[100];
		//sprintf(str, "%d", m_pos);
		//TextOut(GetMemDC(), 500, 0, str, strlen(str));

		// 레이캐스트
		if (KEYMANAGER->IsStayKeyDown('V'))
		{

			int x = m_pos % 50; // 플레이어의 x 인덱스
			int y = m_pos / 50; // 플레이어의 y 인덱스

			float distance = 1.4f; // 레이의 가중치 // 삼각함수로 닿은 인덱스를 구한다.

			float layVal = light * 1.0f; // 레이가 뻗는 대로 줄어들 가중치 
			int lightPower = light;

			float r = 0.0f; // 쏠 레이의 각도
			float angle = (15.0f * 3.141592) / 180.0f; // 레이 각도의 증가량


			while (r < 2 * 3.141592)
			{

				HPEN pen, oldPen;



				if (layVal < 0.0f)
				{
					layVal = light * 1.0f;
					r += angle;
					x = m_pos % 50;
					y = m_pos / 50;
					lightPower = light;
				}
				int a = x; int b = y;
				x = x + ((int)distance * cos(r));
				y = y + ((int)distance * (-sin(r)));

				pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 255));
				oldPen = (HPEN)SelectObject(GetMemDC(), pen);
				LineMake(GetMemDC(), this->x + 26, this->y + 26, this->x + 26 + 400 * cos(r), this->y + 26 + 400 * (-sin(r)));

				SelectObject(GetMemDC(), oldPen);
				DeleteObject(pen);

				layVal -= 1.4f;
				lightPower--;
			}
		}
		//HPEN pen, oldPen;
		//pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 255));
		//oldPen = (HPEN)SelectObject(GetMemDC(), pen);
		//LineMake(GetMemDC(), this->x + 26, this->y + 26,
		//	this->x + 26 + layVal * cos(r) * TILESIZE, this->y + layVal * (-sin(r)));

		////tempX = x1 + layVal * cos(r);
		////tempY = y1 + layVal * (-sin(r));
		////
		//SelectObject(GetMemDC(), oldPen);
		//DeleteObject(pen);

		//LayCast();
}

void OPlayer1::PlayerMove()
{
	GameObject * targetTileObj;
	//targetTileObj->Init("", -1, OBJ_NONE);
	if (KEYMANAGER->IsStayKeyDown(VK_DOWN))
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT))
		{
			if (isBeatTime)
			{
				if (m_posion != NULL) {
					m_posion->UseIt(m_pos, 0);
					SOUNDMANAGER->Play("vo_p_heal",OBJECTMANAGER->GetEffectVolum() - 0.3);
				}
				isBeatTime = false;
			}
		}
	}

	if (m_move != NONE)
	{
		Moving(isJumpMoving);
	}
	else if (KEYMANAGER->IsOnceKeyDown(VK_LEFT))
	{
		isRight = false;
		if (isBeatTime)
		{
			targetTileObj = OBJECTMANAGER->GetIsThereObj(m_pos - 1);
			if (m_equipWeapon != NULL && m_equipWeapon->UseIt(m_pos - 1, 4)) 
			{ 
				SOUNDMANAGER->Play("vo_p_melee", OBJECTMANAGER->GetEffectVolum() - 0.3);
				isEarthquake = true; 
			}
			else if (targetTileObj == NULL || targetTileObj->GetObjKind() == OBJ_FLOOR || 
						targetTileObj->GetObjKind() == OBJ_ITEM)
			{
				putPos = m_pos;
				OBJECTMANAGER->SetTilePos(this, m_pos - 1);
				if (putObj != NULL)
				{
					PutItem(putObj);
					putObj = nullptr;
				}
				m_move = LEFT;
				moveCount = TILESIZE;
				jump = 0;
				//x -= TILESIZE;

				// 가려는 곳에 아이템이 있다면 줍고 떨구기
				if (targetTileObj != NULL && targetTileObj->GetObjKind() == OBJ_ITEM)
				{
					SetInven(targetTileObj);
					//targetTileObj->GoInventory(33, 23);
				}
			}
			else if (targetTileObj->GetObjKind() == OBJ_WALL)
			{

				if (targetTileObj->GetImageKey() == "wall_door_side")
				{
					SOUNDMANAGER->Play("obj_door_open");
					isEarthquake = true;
					OBJECTMANAGER->DeleteObj(targetTileObj);
				}
				else if (m_shovel != NULL)
					if (m_shovel->UseIt(m_pos - 1, 4))
					{
						isEarthquake = true;
						SOUNDMANAGER->Play("vo_p_dig", OBJECTMANAGER->GetEffectVolum() - 0.3);
					}
			}
		}
		isBeatTime = false;
	}
	else if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT))
	{
		isRight = true;
		if (isBeatTime)
		{

			targetTileObj = OBJECTMANAGER->GetIsThereObj(m_pos + 1);
			if (m_equipWeapon != NULL && m_equipWeapon->UseIt(m_pos + 1, 6)) 
			{ 
				isEarthquake = true;
				SOUNDMANAGER->Play("vo_p_melee", OBJECTMANAGER->GetEffectVolum() - 0.3);
			}
			else if (targetTileObj == NULL || targetTileObj->GetObjKind() == OBJ_FLOOR ||
				targetTileObj->GetObjKind() == OBJ_ITEM)
			{
				putPos = m_pos;
				OBJECTMANAGER->SetTilePos(this, m_pos + 1);
				if (putObj != NULL)
				{
					PutItem(putObj);
					putObj = nullptr;
				}
				m_move = RIGHT;
				moveCount = TILESIZE;
				jump = 0;
				//x += TILESIZE;
				if (targetTileObj != NULL && targetTileObj->GetObjKind() == OBJ_ITEM)
					SetInven(targetTileObj);
					//targetTileObj->GoInventory(33, 23);
			}
			else if (targetTileObj->GetObjKind() == OBJ_WALL)
			{
				if (targetTileObj->GetImageKey() == "wall_door_side")
				{
					SOUNDMANAGER->Play("obj_door_open");
					isEarthquake = true;
					OBJECTMANAGER->DeleteObj(targetTileObj);
				}
				else if (m_shovel != NULL)
					if (m_shovel->UseIt(m_pos + 1, 6))
					{
						isEarthquake = true;
						SOUNDMANAGER->Play("vo_p_dig", OBJECTMANAGER->GetEffectVolum() - 0.3);
					}
			}
		}

		isBeatTime = false;
	}
	else if (KEYMANAGER->IsOnceKeyDown(VK_UP))
	{
		if (isBeatTime)
		{
			targetTileObj = OBJECTMANAGER->GetIsThereObj(m_pos - 50);
			if (m_equipWeapon != NULL && m_equipWeapon->UseIt(m_pos - 50, 8)) { 
				isEarthquake = true; 
				SOUNDMANAGER->Play("vo_p_melee", OBJECTMANAGER->GetEffectVolum() - 0.3);
			}
			else if (targetTileObj == NULL || targetTileObj->GetObjKind() == OBJ_FLOOR ||
				targetTileObj->GetObjKind() == OBJ_ITEM)
			{
				putPos = m_pos;
				OBJECTMANAGER->SetTilePos(this, m_pos - 50);
				if (putObj != NULL)
				{
					PutItem(putObj);
					putObj = nullptr;
				}
				m_move = UP;
				moveCount = TILESIZE;
				jump = 1;
				//y -= TILESIZE ;
				if (targetTileObj != NULL && targetTileObj->GetObjKind() == OBJ_ITEM)
					SetInven(targetTileObj);
					//targetTileObj->GoInventory(33, 23);
			}
			else if (targetTileObj->GetObjKind() == OBJ_WALL)
			{
				if (targetTileObj->GetImageKey() == "wall_door_side")
				{
					SOUNDMANAGER->Play("obj_door_open");
					isEarthquake = true;
					OBJECTMANAGER->DeleteObj(targetTileObj);
				}
				else if (m_shovel != NULL)
					if (m_shovel->UseIt(m_pos - 50, 8))
					{
						isEarthquake = true;
						SOUNDMANAGER->Play("vo_p_dig", OBJECTMANAGER->GetEffectVolum() - 0.3);
					}
			}
		}

		isBeatTime = false;
	}
	else if (KEYMANAGER->IsOnceKeyDown(VK_DOWN))
	{
		if (isBeatTime)
		{
			targetTileObj = OBJECTMANAGER->GetIsThereObj(m_pos + 50);
			if (m_equipWeapon != NULL && m_equipWeapon->UseIt(m_pos + 50, 2)) 
			{ 
				isEarthquake = true; 
				SOUNDMANAGER->Play("vo_p_melee",OBJECTMANAGER->GetEffectVolum());
			}
			else if (targetTileObj == NULL || targetTileObj->GetObjKind() == OBJ_FLOOR ||
				targetTileObj->GetObjKind() == OBJ_ITEM)
			{
				putPos = m_pos;
				OBJECTMANAGER->SetTilePos(this, m_pos + 50);
				if (putObj != NULL)
				{
					PutItem(putObj);
					putObj = nullptr;
				}
				m_move = DOWN;
				moveCount = TILESIZE;
				jump = 0;
				//y += TILESIZE;
				if (targetTileObj != NULL && targetTileObj->GetObjKind() == OBJ_ITEM)
					SetInven(targetTileObj);
					//targetTileObj->GoInventory(33, 23);
			}
			else if (targetTileObj->GetObjKind() == OBJ_WALL)
			{
				if (targetTileObj->GetImageKey() == "wall_door_side")
				{
					SOUNDMANAGER->Play("obj_door_open");
					isEarthquake = true;
					OBJECTMANAGER->DeleteObj(targetTileObj);
				}
				else if (m_shovel != NULL)
					if (m_shovel->UseIt(m_pos + 50, 2))
					{
						SOUNDMANAGER->Play("vo_p_dig", OBJECTMANAGER->GetEffectVolum() - 0.3);
						isEarthquake = true;
					}
			}
		}
		isBeatTime = false;
	}
	else if (KEYMANAGER->IsOnceKeyDown(VK_SPACE))
	{
		if (isBeatTime)
		{
			if (m_equipWeapon->GetImageKey() == "weapon_gun", OBJECTMANAGER->GetEffectVolum() - 0.3)
			{
				m_equipWeapon->UseIt(-1, 5);
			}
			isBeatTime = false;
		}
	}
	//if (targetTileObj->GetObjKind() == OBJ_ITEM)
	//{
	//	targetTileObj->GoInventory(x,y);
	//}
	Earthquake();
}

void OPlayer1::Anim()
{
	// 요기는 프레임 타임에 맞춘 프레임 인덱스 조정
	/*count += TIMEMANAGER->GetElapsedTime();
	if (count > 1.00f)
	{
		count = 0.0f;
		m_frameX = (m_frameX + 1) % m_maxX;
	}*/


	count++;
	if (count % 10 == 0)
	{
		count = 0;
		m_frameX = (m_frameX + 1) % (m_maxX /2 );
		m_headFrameX = (m_frameX + 1) % (m_maxX / 2);
	}
}

void OPlayer1::Defence(int damage)
{
	if (isCheat)
	{
		isEarthquake = true;
	}
	else
	{
		int d = damage * 10 - defence;
		if (d < 0)
			d = 0;
		m_HP = m_HP - d;
		SOUNDMANAGER->Play("vo_p_hurt", OBJECTMANAGER->GetEffectVolum() - 0.3);
		OBJECTMANAGER->LostFever();
		
		if (m_equipArmor != NULL)
		{ 
			if (m_equipArmor->GetImageKey() == "armor_glass")
			{
				m_frameY = 0;
				SOUNDMANAGER->Play("sfx_glass_break");

				m_equipArmor = NULL;
				defence = 0;
				{
				inven[0] = { 25, 5 , "", nullptr };
				inven[1] = { 90, 5,"",nullptr };
				inven[2] = { 155, 5,"",nullptr };
				inven[3] = { 220, 5,"",nullptr };
				inven[4] = { 25, 85,"",nullptr };

				for (int i = 0; i < 5; i++)
					isUseInven[i] = false;

				if (m_shovel != NULL)
				{
					isUseInven[0] = true;
					inven[0].uiKey = "slot_shovel";
					inven[0].obj = m_shovel;
				}
				if (m_equipWeapon != NULL)
				{
					for (int i = 0; i < 2; i++)
					{
						if (isUseInven[i] == false)
						{
							isUseInven[i] = true;
							inven[i].uiKey = "slot_attack";
							inven[i].obj = m_equipWeapon;
							break;
						}
					}
				}
				if (m_equipArmor != NULL)
				{
					for (int i = 0; i < 3; i++)
					{
						if (isUseInven[i] == false)
						{
							isUseInven[i] = true;
							inven[i].uiKey = "slot_body";
							inven[i].obj = m_equipArmor;
							break;
						}
					}
				}
				if (m_torch != NULL)
				{
					for (int i = 0; i < 4; i++)
					{
						if (isUseInven[i] == false)
						{
							isUseInven[i] = true;
							inven[i].uiKey = "slot_torch";
							inven[i].obj = m_torch;
							break;
						}
					}
				}
				if (m_posion != NULL)
				{
					for (int i = 0; i < 5; i++)
					{
						if (isUseInven[i] == false)
						{
							isUseInven[i] = true;
							inven[i].uiKey = "slot_item";
							inven[i].obj = m_posion;
							break;
						}
					}
				}
			}
			}
		}

		isEarthquake = true;
		if (m_HP <= 0)
		{
			m_HP = 0;
			this->Die();
		}
	}
}

void OPlayer1::Die()
{
	isPlayerDie = true;
	SOUNDMANAGER->Play("vo_p_death", OBJECTMANAGER->GetEffectVolum() - 0.3);
	OBJECTMANAGER->SetPlayerDie();
	//OBJECTMANAGER->SetTilePos(this, 2480);
}

void OPlayer1::Moving(bool isJump)
{
	// 상하좌우 점핑 무빙
	
	if (isJump)
	{
		switch (m_move)
		{
		case LEFT:
			moveCount -= 4;
			x -= 4;
			if (moveCount)
			{
				if (moveCount > TILESIZE / 2)
					jump -= 6;
				else jump += 6;
			}
			if (moveCount == 0)
				m_move = NONE;
			break;
		case RIGHT:
			moveCount -= 4;
			x += 4;
			if (moveCount)
			{
				if (moveCount > TILESIZE / 2)
					jump -= 6;
				else jump += 6;
			}
			if (moveCount == 0)
				m_move = NONE;
			break;
		case UP:
			moveCount -= 4;
			y -= 4;
			if (moveCount)
			{
				if (moveCount > TILESIZE / 2)
					jump -= 6;
				else jump += 6;
			}
			if (moveCount == 0)
				m_move = NONE;
			break;
		case DOWN:
			moveCount -= 4;
			y += 4;
			if (moveCount)
			{
				if (moveCount > TILESIZE / 2)
					jump -= 6;
				else jump += 6;
			}
			if (moveCount == 0)
				m_move = NONE;
			break;
		}
		if (moveCount == 0) isJumpMoving = true;
	}
	else
	{
		switch (m_move)
		{
		case LEFT:
			moveCount -= 4;
			x -= 4;
			if (moveCount == 0)
				m_move = NONE;
			break;
		case RIGHT:
			moveCount -= 4;
			x += 4;
			if (moveCount == 0)
				m_move = NONE;
			break;
		case UP:
			moveCount -= 4;
			y -= 4;
			if (moveCount == 0)
				m_move = NONE;
			break;
		case DOWN:
			moveCount -= 4;
			y += 4;
			if (moveCount == 0)
				m_move = NONE;
			break;
		}
		if (moveCount == 0) isJumpMoving = true;
	}
}


void OPlayer1::RenderUI()
{

	int fullHeart = m_HP / 10;
	int halfHeart = m_HP % 10;
	int emptyHeart = fullHeart - m_MaxHP / 10;

	// HP 렌더 ( 쿵쾅하는 것, hp에 따른 ui 렌더 )
	for (int i = 0; i < m_MaxHP / 10; i++)
	{
		if (i < fullHeart)
		{
			if (i == hpBeate && hpBeatCount > 0 )
			{
				heratLargeImage->FrameRender(GetMemDC(), 562 + i * 53, 7, 0, 0);
				hpBeatCount--;
			}
			else
				heartImage->FrameRender(GetMemDC(), 565 + i * 53, 10, 0, 0);

		}
		else if (halfHeart)
		{
			if (i == hpBeate && hpBeatCount > 0)
			{
				heartHalfLageImage->FrameRender(GetMemDC(), 562 + i * 53, 7, 0, 0);
				hpBeatCount--;
			}
			else 
				heartHalfImage->FrameRender(GetMemDC(), 565 + i * 53, 10, 0, 0);

			halfHeart = 0;
		}
		else
			heartEmpty->FrameRender(GetMemDC(), 565 + i * 53, 10, 0, 0);
	
		//char str[20];
		//sprintf(str, "%d", i);
		//TextOut(GetMemDC(), 300, 20, str, strlen(str));
	}

	// 장비 렌더, 나중에 아이템 개발하게 되면 원본처럼 구현하기

	//IMAGEMANAGER->FrameRender("slot_shovel",GetMemDC(), 25, 5);
	//IMAGEMANAGER->FrameRender("slot_attack", GetMemDC(), 90, 5);
	//IMAGEMANAGER->FrameRender("slot_body", GetMemDC(), 155, 5);
	//IMAGEMANAGER->FrameRender("slot_torch", GetMemDC(), 220, 5);
	//IMAGEMANAGER->FrameRender("slot_item", GetMemDC(), 25, 85);


	for (int i = 0; i < 5; i++)
	{
		if (isUseInven[i] == true)
		{
			inven[i].obj->SetXY2(inven[i].pos.x + 8,inven[i].pos.y + 13);
			
			
			if (inven[i].obj->GetX() == inven[i].pos.x + 8)
			{
				if (inven[i].obj->GetImageKey() == "weapon_gun")
					euipGImage->FrameRender(GetMemDC(), inven[i].pos.x + 3, inven[i].pos.y - 10,
						inven[i].obj->GetFrameX(), inven[i].obj->GetFrameY());
				else
					IMAGEMANAGER->FrameRender(inven[i].obj->GetImageKey(),GetMemDC(), inven[i].pos.x + 8, inven[i].pos.y + 13,
						inven[i].obj->GetFrameX(), inven[i].obj->GetFrameY());

			}
			if (inven[i].obj->GetImageKey() == "weapon_gun")
			{
				if (inven[i].obj->GetFrameX() == 1)
					euipRImage->FrameRender(GetMemDC(), inven[i].pos.x, inven[i].pos.y);
				else
					euipWImage->FrameRender(GetMemDC(), inven[i].pos.x, inven[i].pos.y);
			} //inven[i].uiKey
			else
			{
				if (inven[i].uiKey == "slot_body")
					euipAImage->FrameRender(GetMemDC(), inven[i].pos.x, inven[i].pos.y);
				else if(inven[i].uiKey == "slot_attack")
					euipWImage->FrameRender(GetMemDC(), inven[i].pos.x, inven[i].pos.y);
				else if (inven[i].uiKey == "slot_item")
					euipPImage->FrameRender(GetMemDC(), inven[i].pos.x, inven[i].pos.y);
				else if (inven[i].uiKey == "slot_shovel")
					euipSImage->FrameRender(GetMemDC(), inven[i].pos.x, inven[i].pos.y);
				else if (inven[i].uiKey == "slot_torch")
					euipTImage->FrameRender(GetMemDC(), inven[i].pos.x, inven[i].pos.y);
			}
			//IMAGEMANAGER->FrameRender(inven[i].uiKey, GetMemDC(), inven[i].pos.x, inven[i].pos.y);
		

  /*euipWImage = IMAGEMANAGER->FindImage("slot_body");
	euipAImage = IMAGEMANAGER->FindImage("slot_attack");
	euipPImage = IMAGEMANAGER->FindImage("slot_item");
	euipSImage = IMAGEMANAGER->FindImage("slot_shovel");
	euipTImage = IMAGEMANAGER->FindImage("slot_torch");
	
	euipRImage = IMAGEMANAGER->FindImage("hud_slot_reload");
	euipGImage = IMAGEMANAGER->FindImage("weapon_gun");*/
		}
	}

	// 다이아몬드와 코인 렌더

	XImage->Render(GetMemDC(), 885, 35);
	XImage->Render(GetMemDC(), 885, 85);

	int num[4] = { 0,0,0,0 };
	num[0] = curCoin / 1000;
	num[1] = (curCoin  - num[0] * 1000) / 100;
	num[2] = (curCoin - num[0] * 1000 - num[1] * 100) / 10;
	num[3] = (curCoin - num[0] * 1000 - num[1] * 100 - num[2] * 10) / 1;
	bool b = false;
	for (int i = 0; i < 4; i++)
	{
		if (b || i == 3)
		{
			numberImage->FrameRender(GetMemDC(),890 + 8 * i , 30, num[i],0);
		}

		else if (b == false && num[i] != 0)
		{
			numberImage->FrameRender(GetMemDC(), 890 + 8 * i, 30, num[i], 0);
			b = true;
		}
	}
	num[0] = curDia / 1000;
	num[1] = (curDia - num[0] * 1000) / 100;
	num[2] = (curDia - num[0] * 1000 - num[1] * 100) / 10;
	num[3] = (curDia - num[0] * 1000 - num[1] * 100 - num[2] * 10) / 1;
	b = false;
	for (int i = 0; i < 4; i++)
	{
		if (b || i == 3)
		{
			numberImage->FrameRender(GetMemDC(), 890 + 8 * i, 80, num[i], 0);
		}

		else if (b == false && num[i] != 0)
		{
			numberImage->FrameRender(GetMemDC(), 890 + 8 * i, 80, num[i], 0);
			b = true;
		}
	}
	//numberImage->Render(GetMemDC(), 0, 0);
	coin->FrameRender(GetMemDC(),840,5,0,0);
	diamond->FrameRender(GetMemDC(),840,50,0,0);

}

void OPlayer1::hp_beat()
{
		
	if (isPlayerDie == false)
	{
		hpBeate++;
		hpBeatCount = 4;
		int i = m_HP / 10;
		bool j = ((m_HP % 10) != 0);

		hpBeate = hpBeate % (i + j);
	}

}

void OPlayer1::UpdateEquit()
{
	if (m_equipWeapon)
		m_equipWeapon->Update();
	if (m_equipArmor)
		m_equipArmor->Update();
	if (m_posion)
		m_posion->Update();
	if (m_shovel)
		m_shovel->Update();
	if (m_torch)
		m_torch->Update();
}

bool OPlayer1::GetIsMoving()
{
	if (m_move != NONE)
		return true;
	else return false;
}

// 인벤토리 세팅
void OPlayer1::SetInven(GameObject * obj)
{
	//OBJECTMANAGER->SetTilePos(obj,2499);

	if (obj->GetObjKind() != OBJ_NONE)
	{
		switch (obj->GetItemKind())
		{
		case ITEM_ARMOR:
			SOUNDMANAGER->Play("sfx_pickup_armor", OBJECTMANAGER->GetEffectVolum());
			putObj = m_equipArmor;
			m_equipArmor = obj;

			if (obj->GetImageKey() == "armor_leather")
			{
				m_frameY = 1;
				defence = 5;
			}
			else if (obj->GetImageKey() == "armor_chain")
			{
				defence = 10;
				m_frameY = 2;
			}
			else if (obj->GetImageKey() == "armor_gi")
				m_frameY = 5;
			else if (obj->GetImageKey() == "armor_glass")
			{
				defence = 40;
				m_frameY = 9;
			}

			break;
		case ITEM_WEAPON:
			SOUNDMANAGER->Play("sfx_pickup_weapon", OBJECTMANAGER->GetEffectVolum());
			putObj = m_equipWeapon;
			m_equipWeapon = obj;
			break;
		case ITEM_SHOVEL:
			SOUNDMANAGER->Play("sfx_pickup_gold_01", OBJECTMANAGER->GetEffectVolum());
			putObj = m_shovel;
			m_shovel = obj;
			break;
		case ITEM_TORCH:
			SOUNDMANAGER->Play("sfx_pickup_gold_01", OBJECTMANAGER->GetEffectVolum());
			putObj = m_torch;
			m_torch = obj;
			break;
		case ITEM_POSION:
			SOUNDMANAGER->Play("sfx_pickup_gold_01", OBJECTMANAGER->GetEffectVolum());
			putObj = m_posion;
			m_posion = obj;
			break;
		case ITEM_GOLD:
			SOUNDMANAGER->Play("sfx_pickup_gold_01", OBJECTMANAGER->GetEffectVolum());
			curCoin += obj->GetAttribute();
			OBJECTMANAGER->DeleteObj(obj);
			break;
		}
		/*if (putObj != NULL)
		PutItem(putObj);*/
	}
	//GameObject * putObj;
	

	inven[0] = { 25, 5 , "", nullptr };
	inven[1] = { 90, 5,"",nullptr };
	inven[2] = { 155, 5,"",nullptr };
	inven[3] = { 220, 5,"",nullptr };
	inven[4] = { 25, 85,"",nullptr };

	for (int i = 0; i < 5; i++)
		isUseInven[i] = false;

	if (m_shovel != NULL)
	{
		isUseInven[0] = true;
		inven[0].uiKey = "slot_shovel";
		inven[0].obj = m_shovel;

		if (m_shovel == obj)
		{
			//PutItem(putObj);
			obj->GoInventory(inven[0].pos.x + 8, inven[0].pos.y + 13);
		}
	}
	if (m_equipWeapon != NULL)
	{
		for (int i = 0; i < 2; i++)
		{
			if (isUseInven[i] == false)
			{
				isUseInven[i] = true;
				inven[i].uiKey = "slot_attack";
				inven[i].obj = m_equipWeapon;
				if (m_equipWeapon == obj)
				{
					//PutItem(putObj);
					obj->GoInventory(inven[i].pos.x + 8, inven[i].pos.y + 13);
				}
				break;
			}
		}
	}
	if (m_equipArmor != NULL)
	{	
		for (int i = 0; i < 3; i++)
		{
			if (isUseInven[i] == false)
			{
				isUseInven[i] = true;
				inven[i].uiKey = "slot_body";
				inven[i].obj = m_equipArmor;
				if (m_equipArmor == obj)
				{
					//PutItem(putObj);
					obj->GoInventory(inven[i].pos.x + 8, inven[i].pos.y + 13);
				}
				break;
			}
		}
	}
	if (m_torch != NULL)
	{
		for (int i = 0; i < 4; i++)
		{
			if (isUseInven[i] == false)
			{
				isUseInven[i] = true;
				inven[i].uiKey = "slot_torch";
				inven[i].obj = m_torch;
				if (m_torch == obj)
				{
					//PutItem(putObj);
					obj->GoInventory(inven[i].pos.x + 8, inven[i].pos.y + 13);
				}
				break;
			}
		}
	}
	if (m_posion != NULL)
	{
		for (int i = 0; i < 5; i++)
		{
			if (isUseInven[i] == false)
			{
				isUseInven[i] = true;
				inven[i].uiKey = "slot_item";
				inven[i].obj = m_posion;
				if (m_posion == obj)
				{
					//PutItem(putObj);
					obj->GoInventory(inven[i].pos.x + 8, inven[i].pos.y + 13);
				}
				break;
			}
		}
	}
}

// 아이템 떨구기
void OPlayer1::PutItem(GameObject * obj)
{
	//int a = m_pos % TILEX * TILESIZE;
	//int b = m_pos / TILEY * TILESIZE - 20;
	//obj->SetPos(m_pos);
	obj->SetXY2(x , y - 20);
	OBJECTMANAGER->SetTilePos(obj, putPos);
	obj->SetIsHereInven(false);
}

// 주변 아이템 정보 띄우기
void OPlayer1::ShowItemInfo()
{
	GameObject * obj;
	obj = OBJECTMANAGER->GetIsThereObj(m_pos+1);
	if (obj != NULL && obj->GetObjKind() == OBJ_ITEM)
		obj->ShowInfo();
	obj = OBJECTMANAGER->GetIsThereObj(m_pos - 1);
	if (obj != NULL && obj->GetObjKind() == OBJ_ITEM)
		obj->ShowInfo();
	obj = OBJECTMANAGER->GetIsThereObj(m_pos + 50);
	if (obj != NULL && obj->GetObjKind() == OBJ_ITEM)
		obj->ShowInfo();
	obj = OBJECTMANAGER->GetIsThereObj(m_pos - 50);
	if (obj != NULL && obj->GetObjKind() == OBJ_ITEM)
		obj->ShowInfo();
}

// 화면 흔들기
void OPlayer1::Earthquake()
{
	if (isEarthquake)
	{
		if (earthquakeCount == 16)
		{
			isEarthquake = false;
			earthquakeCount = 0;
		}
		else 
		{
			if (earthquakeCount  < 16)
			{
				if (earthquakeCount % 2 == 0)
				{
					beforX = RND->GetFromInto(7, 11);
					beforY = RND->GetFromInto(7, 11);

					if (RND->GetInt(2) == 0)
						beforX *= -1;
					if (RND->GetInt(2) == 0)
						beforY *= -1;

					x += beforX;
					y += beforY;
				}
				else
				{
					x -= beforX;
					y -= beforY;
				}
			
			}
		}
		earthquakeCount++;
	}
	else
		earthquakeCount = 0;
}

void OPlayer1::LayCast()
{
	OBJECTMANAGER->InitLight();

	
	// 1. 내 좌표를 기준으로 15도씩 마다 레이를 쏜다. 가중치는 자신의 밝기

	// 2. 레이에 닿은 오브젝트들의 밝기 값을 레이의 가중치 만큼 올린다.

	// 3. 레이는 벽에 닿거나 본인의 가중치가 다 소모 되면 종료한다.
		

	x1 = (float)(m_pos % 50); // 플레이어의 x 인덱스
	y1 = (float)(m_pos / 50); // 플레이어의 y 인덱스

	layVal = 0.0f;
	layMax = (float)sight - 0.25;
	
	float bright = 0.0f;
	int asd = 0;
	float sightMax = 6.0f;
	float curSight = 0.0f;
	if (m_torch != NULL)
	{
		layMax += (float)m_torch->GetAttribute();
		asd = m_torch->GetAttribute();
	}

	r = 0.0f; // 쏠 레이의 각도
	angle = (12.0f * 3.141592) / 180.0f; // 레이 각도의 증가량



	while (r < 2 * 3.141592)
	{
		if (KEYMANAGER->IsStayKeyDown('B'))
		{
			HPEN pen, oldPen;
			pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 255));
			oldPen = (HPEN)SelectObject(GetMemDC(), pen);
			LineMake(GetMemDC(), this->x + 26, this->y + 26,
				this->x + 26 + layVal * cos(r) * TILESIZE, this->y + 26 +  layVal * (-sin(r)) * TILESIZE);
			SelectObject(GetMemDC(), oldPen);
			DeleteObject(pen);

			//char str[25];
			//sprintf(str,"%.1f", r);
			//TextOut(GetMemDC(), x, y-20, str, strlen(str));
		}

		//tempX = x1 + layVal * cos(r);
		//tempY = y1 + layVal * (-sin(r));
		//
		if (layVal > layMax)
			bright = 0.0f;
		else
			bright = layVal;
			
		if (curSight > sightMax)
		{
			curSight = 0.0f;
			bright = 0.0f;
			layVal = 0.0f;
			r += angle;
		}
			//break;

		tempX = x1 + curSight * cos(r)    + 0.5;
		tempY = y1 + curSight * (-sin(r)) + 0.5;

		if (x1 < 0 || y1 < 0)
		{
			curSight = sightMax + 0.1f;
			continue;
		}

		int a = tempX - x1;
		if (a < 0) a *= -1;
		int b = tempY - y1;
		if (b < 0) b *= -1;
		int s;
		if (a > b) s = a; else s = b;
		s = a + b;
		GameObject * obj = OBJECTMANAGER->GetIsThereObj(tempX + tempY * 50);
		GameObject * floorObj = OBJECTMANAGER->GetIsThereFloor(tempX + tempY * 50);
		
		if (obj != NULL)
		{

			if (obj->GetIsSight() == false)
			{
				//obj->SetLight(3 - s);
				
				if (s <= 2 + asd)
				{
					obj->SetLight(true);
					obj->SetFirstSight();
				}

				obj->SetIsSight(true);

			}


			if (obj->GetObjKind() == OBJ_WALL)
			{
				if (obj->GetImageKey() == "wall_door_side")
				{
					if (floorObj->GetIsSight() == false)
					{
						//floorObj->SetLight(3 - s);
						if (s <= 2 + asd)
						{
							floorObj->SetLight(true);
							floorObj->SetFirstSight();
						}
						floorObj->SetIsSight(true);
					}
				}

				layVal = 0.0f;
				curSight = 0.0f;
				r += angle;
				continue;
			}
			
		}
		
		if (floorObj != NULL)
		{
			if (floorObj->GetIsSight() == false)
			{
				//floorObj->SetLight(3 - s);
				if (s <= 2 + asd)
				{
					floorObj->SetLight(true);
					floorObj->SetFirstSight();
				}
				floorObj->SetIsSight(true);
			}
		}

		layVal += 0.25;
		curSight += 0.25;
	}
}
