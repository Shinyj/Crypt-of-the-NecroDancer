#include "stdafx.h"
#include "LevelEdit.h"
#include "GameObject.h"

LevelEdit::LevelEdit()
{
}


LevelEdit::~LevelEdit()
{
}

HRESULT LevelEdit::Init()
{
	SOUNDMANAGER->AllStop();
	isSave = false;
	m_vObj.clear();
	RECT rcClient = { 0,0,1600,900 };

	AdjustWindowRect(
		&rcClient,
		WINSTYLE,
		FALSE);

	SetWindowPos(

		hWnd, NULL,
		0, 0,
		(rcClient.right - rcClient.left),
		(rcClient.bottom - rcClient.top),
		SWP_NOZORDER | SWP_NOMOVE);



	//MoveWindow(hWnd,100,50,1600,900,TRUE);

	//curPlayerPos = 0;

	SOUNDMANAGER->AddSound("lobby", "sound/lobby.ogg", true, true);
	//SOUNDMANAGER->Play("lobby", 0.5);

	selectObj.Init("", 0, OBJ_NONE);
	SetInterface();

	MapToolSetUp();

	HANDLE file;
	DWORD read;
	
	file = CreateFile(_T("test"),
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	
	
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);
	CloseHandle(file);
	
	//for (int i = 0; i < TILEY; i++)
	//{
	//	for (int j = 0; j < TILEX; j++)
	//	{
	//
	//		//_tiles[i * TILEY + j].objKey.resize(sizeof(tagTile));
	//		_tiles[i * TILEY + j].SetObj();
	//		//_tiles[i * TILEY + j].objKey = "null";
	//		//_tiles[i * TILEY + j].floorKey = "null";
	//
	//		if (_tiles[i * TILEY + j].player != NULL)
	//		{
	//			_tiles[i * TILEY + j].player = _tiles[curPlayerPos].player;
	//			_tiles[i * TILEY + j].objObj = OBJ_PLAYER;
	//			_tiles[i * TILEY + j].objPos = i * TILEY + j;
	//			_tiles[curPlayerPos].player = nullptr;
	//			strcpy(_tiles[curPlayerPos].objKey, "");
	//			_tiles[curPlayerPos].objObj = OBJ_NONE;
	//			_tiles[curPlayerPos].objPos = -1;
	//			
	//			curPlayerPos = i * TILEY + j;
	//		}
	//		/*if (_tiles[i * TILEY + j].player.GetObjKind() == OBJ_PLAYER)
	//		_tiles[curPlayerPos].player.Init("",-1,OBJ_NONE);
	//		curPlayerPos = i * TILEY + j;*/
	//	}
	//}

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{

			//_tiles[i * TILEY + j].objKey.resize(sizeof(tagTile));
			_tiles[i * TILEY + j].SetObj();
			//_tiles[i * TILEY + j].objKey = "null";
			//_tiles[i * TILEY + j].floorKey = "null";

			if (_tiles[i * TILEY + j].player != NULL)
			{
				GameObject * player = new GameObject;
				player->Init("", i * TILEY + j, OBJ_PLAYER);
				_tiles[curPlayerPos].player = nullptr;
				curPlayerPos = i * TILEY + j;
				_tiles[curPlayerPos].player = player;
			}
			/*if (_tiles[i * TILEY + j].player.GetObjKind() == OBJ_PLAYER)
			_tiles[curPlayerPos].player.Init("",-1,OBJ_NONE);
			curPlayerPos = i * TILEY + j;*/
		}
	}

	SOUNDMANAGER->Play("boss_2",OBJECTMANAGER->GetBgmVolum());

	return S_OK;
}

void LevelEdit::Release()
{

}

void LevelEdit::Update()
{

	if (isSave == false)
	{
		// 배경 맵 툴 카메라 이동
		MoveCamera();
		// 메뉴얼 관련 update
		MoveMenual();

		// select
		SelectTile();
		// 고른거 넣어주기
		SetMap();


		//for (int i = 0; i < TILEX * TILEY; i++)
		//{
		//	if(_tiles[i].floor != NULL)
		//	_tiles[i].floor->Update();
		//}

		if (KEYMANAGER->IsOnceKeyDown(VK_BACK))
		{
			for (int i = 0; i < TILEY; i++)
			{
				for (int j = 0; j < TILEX; j++)
				{
					int index = i * TILEY + j;
					_tiles[index].rc = RectMake(50 + j * TILESIZE, 50 + i * TILESIZE, TILESIZE, TILESIZE);
					_tiles[index].floor = nullptr;
					_tiles[index].item = nullptr;
					_tiles[index].monster = nullptr;
					_tiles[index].wall = nullptr;
					_tiles[index].player = nullptr;
					strcpy(_tiles[index].floorKey, "");
					//_tiles[index].floorKey = "";
					_tiles[index].floorPos = index;
					_tiles[index].floorObj = OBJ_NONE;
					strcpy(_tiles[index].objKey, "");
					//_tiles[index].floorKey = "";
					_tiles[index].objPos = index;
					_tiles[index].objObj = OBJ_NONE;
					_tiles[index].isTorch = false;
				}
			}

			curPlayerPos = 0;

			GameObject * player = new GameObject;

			player->Init("", 0, OBJ_PLAYER);
			_tiles[0].player = player;
			_tiles[0].objObj = OBJ_PLAYER;
			_tiles[0].objPos = 0;
			SaveTest();
			SOUNDMANAGER->Stop("lobby");

			RECT rcClient = { 0,0,960,540 };

			AdjustWindowRect(
				&rcClient,
				WINSTYLE,
				FALSE);

			SetWindowPos(

				hWnd, NULL,
				0, 0,
				(rcClient.right - rcClient.left),
				(rcClient.bottom - rcClient.top),
				SWP_NOZORDER | SWP_NOMOVE);

			m_vObj.clear();

			SCENEMANAGER->ChangeScene("lobby");
		}
	}
}

void LevelEdit::Render()
{
	// 맵을 보여라
	ShowMap();
	// 메뉴얼을 보여라
	ShowMenual();


	//Rectangle(GetMemDC(), m_startRC.left, m_startRC.top, m_endRC.right, m_endRC.bottom);

	char str[100];
	sprintf(str, "%d", curPlayerPos);
	TextOut(GetMemDC(), 500, 0, str, strlen(str));
}

void LevelEdit::MapToolSetUp()
{

	// 맵 툴 셋팅
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			int index = i * TILEY + j;
			_tiles[index].rc = RectMake(50 + j * TILESIZE, 50 + i * TILESIZE, TILESIZE, TILESIZE);
			_tiles[index].floor = nullptr;
			_tiles[index].item = nullptr;
			_tiles[index].monster = nullptr;
			_tiles[index].wall = nullptr;
			_tiles[index].player = nullptr;
			strcpy(_tiles[index].floorKey,"");
			//_tiles[index].floorKey = "";
			_tiles[index].floorPos = index;
			_tiles[index].floorObj = OBJ_NONE;
			strcpy(_tiles[index].objKey, "");
			//_tiles[index].floorKey = "";
			_tiles[index].objPos = index;
			_tiles[index].objObj = OBJ_NONE;
			_tiles[index].isTorch = false;
		}
	}

	curPlayerPos = 0;

	GameObject * player = new GameObject;

	player->Init("", 0, OBJ_PLAYER);
	_tiles[curPlayerPos].player = player;
	_tiles[curPlayerPos].objObj = OBJ_PLAYER;
	_tiles[curPlayerPos].objPos = curPlayerPos;
	// 인터페이스에 들어갈 요소들 벡터에 세팅

	// 바닥과 벽, 흙벽 , 돌벽, 깨진 벽, 계단, 잠긴 계단, 상점 발판과 벽, 까지
	// 아마 여기 있는 것은 로딩 씬 구현되면 글루 옮겨질듯
	{
		GameObject obj;

		//IMAGEMANAGER->AddFrameImage("floor_boss", "images/level/floor_boss.bmp", TILESIZE * 3, TILESIZE * 2, 3, 2, true, RGB(255, 0, 255));

		// 바닥 타일 오브젝트 생성
		obj.Init("floor_boss", 0, OBJ_FLOOR);
		m_vObj.push_back(obj);
		obj.Init("floor_npc", 0, OBJ_FLOOR);
		m_vObj.push_back(obj);
		obj.Init("floor_shop", 0, OBJ_FLOOR);
		m_vObj.push_back(obj);
		obj.Init("floor_shop_next", 0, OBJ_FLOOR);
		m_vObj.push_back(obj);
		obj.Init("floor_shop_reset", 0, OBJ_FLOOR);
		m_vObj.push_back(obj);
		obj.Init("floor_stairs", 0, OBJ_FLOOR);
		m_vObj.push_back(obj);
		obj.Init("floor_stairs_locked", 0, OBJ_FLOOR);
		m_vObj.push_back(obj);
		obj.Init("floor_zone1", 0, OBJ_FLOOR);
		m_vObj.push_back(obj);
		obj.Init("floor_zone2", 0, OBJ_FLOOR);
		m_vObj.push_back(obj);
		obj.Init("floor_zone3_cold", 0, OBJ_FLOOR);
		m_vObj.push_back(obj);
		obj.Init("floor_zone3_hot", 0, OBJ_FLOOR);
		m_vObj.push_back(obj);
		obj.Init("floor_zone4", 0, OBJ_FLOOR);
		m_vObj.push_back(obj);
		obj.Init("wall_door_front", 0, OBJ_WALL);
		m_vObj.push_back(obj);
		obj.Init("wall_door_side", 0, OBJ_WALL);
		m_vObj.push_back(obj);
		obj.Init("wall_end", 0, OBJ_WALL);
		m_vObj.push_back(obj);
		obj.Init("wall_shop_stone", 0, OBJ_WALL);
		m_vObj.push_back(obj);
		obj.Init("wall_shop_stone_cracked", 0, OBJ_WALL);
		m_vObj.push_back(obj);
		obj.Init("wall_z1_drit", 0, OBJ_WALL);
		m_vObj.push_back(obj);
		obj.Init("wall_z1_stone", 0, OBJ_WALL);
		m_vObj.push_back(obj);
		obj.Init("wall_zone1_stone_cracked", 0, OBJ_WALL);
		m_vObj.push_back(obj);
		obj.Init("wall_z2", 0, OBJ_WALL);
		m_vObj.push_back(obj);
		obj.Init("wall_z2_stone", 0, OBJ_WALL);
		m_vObj.push_back(obj);
		obj.Init("wall_zone2_stone_cracked", 0, OBJ_WALL);
		m_vObj.push_back(obj);
		obj.Init("wall_zone3_dirt_cold", 0, OBJ_WALL);
		m_vObj.push_back(obj);
		obj.Init("wall_zone3_dirt_hot", 0, OBJ_WALL);
		m_vObj.push_back(obj);
		obj.Init("wall_zone3_stone_cold", 0, OBJ_WALL);
		m_vObj.push_back(obj);
		obj.Init("wall_zone3_stone_cold_cracked", 0, OBJ_WALL);
		m_vObj.push_back(obj);
		obj.Init("wall_zone3_stone_hot", 0, OBJ_WALL);
		m_vObj.push_back(obj);
		obj.Init("wall_zone3_stone_hot_cracked", 0, OBJ_WALL);
		m_vObj.push_back(obj);
		obj.Init("wall_zone4_dirt", 0, OBJ_WALL);
		m_vObj.push_back(obj);
		obj.Init("wall_zone4_stone", 0, OBJ_WALL);
		m_vObj.push_back(obj);
		//obj.Init("wall_zone4_stone_cracked", 0, OBJ_WALL);
		//m_vObj.push_back(obj);
		obj.Init("boss_wall", -1, OBJ_WALL);
		m_vObj.push_back(obj);
		///////////////////////// 몬스터 이미지

		obj.Init("banshee", -1, OBJ_MONSTER);
		m_vObj.push_back(obj);
		obj.Init("banshee2", -1, OBJ_MONSTER);
		m_vObj.push_back(obj);
		obj.Init("bat_black", -1, OBJ_MONSTER);
		m_vObj.push_back(obj);
		obj.Init("bat_green", -1, OBJ_MONSTER);
		m_vObj.push_back(obj);
		obj.Init("bat_miniboss", -1, OBJ_MONSTER);
		m_vObj.push_back(obj);
		obj.Init("miniboss_yellow", -1, OBJ_MONSTER);
		m_vObj.push_back(obj);
		obj.Init("bat_red", -1, OBJ_MONSTER);
		m_vObj.push_back(obj);
		obj.Init("dragon_red", -1, OBJ_MONSTER);
		m_vObj.push_back(obj);
		obj.Init("minotaur", -1, OBJ_MONSTER);
		m_vObj.push_back(obj);
		obj.Init("minotaur2", -1, OBJ_MONSTER);
		m_vObj.push_back(obj);
		obj.Init("skeleton", -1, OBJ_MONSTER);
		m_vObj.push_back(obj);
		obj.Init("skeleton_black", -1, OBJ_MONSTER);
		m_vObj.push_back(obj);
		obj.Init("mage_black", -1, OBJ_MONSTER);
		m_vObj.push_back(obj);
		obj.Init("mage_white", -1, OBJ_MONSTER);
		m_vObj.push_back(obj);
		obj.Init("mage_yellow", -1, OBJ_MONSTER);
		m_vObj.push_back(obj);
		obj.Init("skeleton_yellow", -1, OBJ_MONSTER);
		m_vObj.push_back(obj);
		obj.Init("slime_blue", -1, OBJ_MONSTER);
		m_vObj.push_back(obj);
		obj.Init("slime_green", -1, OBJ_MONSTER);
		m_vObj.push_back(obj);
		obj.Init("zombie_snake", -1, OBJ_MONSTER);
		m_vObj.push_back(obj);

		////////////////////// 아이템 이미지

		//IMAGEMANAGER->AddFrameImage("armor_gi", "images/item/armor_gi.bmp", 48, 96, 1, 2, true, RGB(255,0,255));
		obj.Init("armor_gi", -1, OBJ_ITEM);
		m_vObj.push_back(obj);
		obj.Init("armor_glass", -1, OBJ_ITEM);
		m_vObj.push_back(obj);
		obj.Init("armor_chain", -1, OBJ_ITEM);
		m_vObj.push_back(obj);
		obj.Init("armor_leather", -1, OBJ_ITEM);
		m_vObj.push_back(obj);
		obj.Init("food_2", -1, OBJ_ITEM);
		m_vObj.push_back(obj);
		obj.Init("shovel_basic", -1, OBJ_ITEM);
		m_vObj.push_back(obj);
		obj.Init("shovel_titanium", -1, OBJ_ITEM);
		m_vObj.push_back(obj);
		obj.Init("torch_1", -1, OBJ_ITEM);
		m_vObj.push_back(obj);
		obj.Init("torch_2", -1, OBJ_ITEM);
		m_vObj.push_back(obj);
		obj.Init("torch_3", -1, OBJ_ITEM);
		m_vObj.push_back(obj);
		obj.Init("weapon_gun", -1, OBJ_ITEM);
		m_vObj.push_back(obj);
		obj.Init("weapon_bow", -1, OBJ_ITEM);
		m_vObj.push_back(obj);
		obj.Init("weapon_broad", -1, OBJ_ITEM);
		m_vObj.push_back(obj);
		obj.Init("weapon_dagger", -1, OBJ_ITEM);
		m_vObj.push_back(obj);
		obj.Init("weapon_flail", -1, OBJ_ITEM);
		m_vObj.push_back(obj);
		obj.Init("weapon_long", -1, OBJ_ITEM);
		m_vObj.push_back(obj);
		obj.Init("weapon_rapier", -1, OBJ_ITEM);
		m_vObj.push_back(obj);
		obj.Init("weapon_spear", -1, OBJ_ITEM);
		m_vObj.push_back(obj);
		

		// 기타 이미지
		obj.Init("shopkeeper",-1,OBJ_ETC);
		m_vObj.push_back(obj);
		obj.Init("wall_torch", -1, OBJ_ETC);
		m_vObj.push_back(obj);
		obj.Init("king_conga", -1, OBJ_ETC);
		m_vObj.push_back(obj);
	}
	
}

// 고른 게임 오브젝트로 칠하잫
void LevelEdit::SetMap()
{
	GameObject temp;

	temp.Init("", -1, OBJ_NONE);

	if (!(PtInRect(&m_MenualRC, ptMouse) && m_isShowMenual))
		//if (selectObj.GetObjKind() != OBJ_NONE)
		//{	
		if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
		{

			for (int i = 0; i < TILEY; i++)
			{
				for (int j = 0; j < TILEX; j++)
				{
					if (KEYMANAGER->IsStayKeyDown(VK_LSHIFT))
					{
						int index = i * TILEY + j;
						if (PtInRect(&_tiles[index].rc, ptMouse))
						{
							if (m_startRC.left == -1)
								m_startRC = _tiles[index].rc;

							m_endRC = _tiles[index].rc;
						}
					}
					else if (PtInRect(&_tiles[i * TILEY + j].rc, ptMouse))
					{


						GameObject * temp = new GameObject;
						temp->Init("", -1, OBJ_NONE);
						// 그냥 꾹 눌러서 그릴 때
						int index = i * TILEY + j;
						if (!isErase)
						{
							GameObject * obj = new GameObject;
							GameObject * player;
							switch (selectObj.GetObjKind())
							{
							case OBJ_PLAYER:
								player = _tiles[curPlayerPos].player;
								_tiles[curPlayerPos].player = nullptr;
								strcpy(_tiles[curPlayerPos].objKey, "");
								_tiles[curPlayerPos].objObj = OBJ_NONE;
								_tiles[curPlayerPos].objPos = -1;
								curPlayerPos = index;
								_tiles[index].player = player;
								_tiles[index].item = nullptr;
								_tiles[index].wall = nullptr;
								_tiles[index].monster = nullptr;
								strcpy(_tiles[index].objKey, selectObj.GetImageKey().c_str());
								//_tiles[index].objKey = selectObj.GetImageKey();

								_tiles[index].objObj = selectObj.GetObjKind();
								_tiles[index].objPos = index;
								break;
							case OBJ_FLOOR:
								/*_tiles[i * TILEY + j].floor.Init(selectObj.GetImageKey(), i * TILEY + j, OBJ_FLOOR);
								_tiles[i * TILEY + j].floor.SetRC(_tiles[i * TILEY + j].rc);*/
								obj = new GameObject;
								obj->Init(selectObj.GetImageKey(), index, selectObj.GetObjKind());
								_tiles[index].floor = obj;
								strcpy(_tiles[index].floorKey, selectObj.GetImageKey().c_str());
								//_tiles[index].floorKey = selectObj.GetImageKey();
								_tiles[index].floorObj = selectObj.GetObjKind();
								_tiles[index].floorPos = index;
								break;
							case OBJ_WALL:
								obj = new GameObject;
								obj->Init(selectObj.GetImageKey(), index, selectObj.GetObjKind());
								_tiles[index].wall = obj;
								_tiles[index].item = nullptr;
								_tiles[index].monster = nullptr;
								strcpy(_tiles[index].objKey, selectObj.GetImageKey().c_str());
								//_tiles[index].objKey = selectObj.GetImageKey();
								_tiles[index].objObj = selectObj.GetObjKind();
								_tiles[index].objPos = index;
								break;
							case OBJ_ITEM:
								obj = new GameObject;
								obj->Init(selectObj.GetImageKey(), index, selectObj.GetObjKind());
								_tiles[index].wall = nullptr;
								_tiles[index].monster = nullptr;
								_tiles[index].item = obj;
								strcpy(_tiles[index].objKey, selectObj.GetImageKey().c_str());
								_tiles[index].objObj = selectObj.GetObjKind();
								_tiles[index].objPos = index;
								//_tiles[index].objKey.resize((string)selectObj.GetImageKey(), sizeof(selectObj.GetImageKey()));
								//_tiles[index].objKey.resize(sizeof(selectObj.GetImageKey()) + 1, selectObj.GetImageKey());
								//_tiles[index].objKey.resize(sizeof(selectObj.GetImageKey()));
								//_tiles[index].objKey.resize(24);
								//_tiles[index].objKey = (string)selectObj.GetImageKey();
						
								break;
							case OBJ_MONSTER:
								obj = new GameObject;
								obj->Init(selectObj.GetImageKey(), selectObj.GetPos(), selectObj.GetObjKind());
								_tiles[index].item = nullptr;
								_tiles[index].wall = nullptr;
								_tiles[index].monster = obj;
								strcpy(_tiles[index].objKey, selectObj.GetImageKey().c_str());
								//_tiles[index].objKey = selectObj.GetImageKey();
								_tiles[index].objObj = selectObj.GetObjKind();
								_tiles[index].objPos = index;
								break;
							case OBJ_ETC:
								obj = new GameObject;
								obj->Init(selectObj.GetImageKey(), selectObj.GetPos(), selectObj.GetObjKind());
								
								if (obj->GetImageKey() == "wall_torch")
								{
									if (_tiles[index].objObj == OBJ_WALL)
									{
										_tiles[index].isTorch = true;
									}
								}
								else
								{
									_tiles[index].monster = obj;
									_tiles[index].item = nullptr;
									_tiles[index].wall = nullptr;
									strcpy(_tiles[index].objKey, selectObj.GetImageKey().c_str());
									//_tiles[index].objKey = selectObj.GetImageKey();
									_tiles[index].objObj = OBJ_MONSTER;
									_tiles[index].objPos = index;
									break;
								}

								/*case OBJ_PLAYER :
								_pos[0] = _tiles[index].rc.left;
								_pos[1] = _tiles[index].rc.top;
								_tiles[index].monster = temp;
								_tiles[index].item = temp;
								_tiles[index].wall = temp;
								strcpy(_tiles[index].objKey, temp.GetImageKey());
								_tiles[index].objObj = temp.GetObjKind();
								_tiles[index].objPos = temp.GetPos();
								break;*/
							}
							break;
						}
						else
						{
							switch (selectObj.GetObjKind())
							{
							case OBJ_FLOOR:
								_tiles[index].floor = nullptr;
								strcpy(_tiles[index].floorKey, "");
								//_tiles[index].floorKey = "";
								_tiles[index].floorObj = OBJ_NONE;
								_tiles[index].floorPos = -1;
								break;
							case OBJ_PLAYER:
								_tiles[index].player = nullptr;
								strcpy(_tiles[index].objKey, "");
								//_tiles[index].objKey = "";
								_tiles[index].objObj = OBJ_NONE;
								_tiles[index].objPos = -1;
								break;
							default:
								_tiles[index].wall = nullptr;
								_tiles[index].item = nullptr;
								_tiles[index].monster = nullptr;
								strcpy(_tiles[index].objKey,"");
								//_tiles[index].objKey = "";
								_tiles[index].objObj = OBJ_NONE;
								_tiles[index].objPos = -1;
								break;
							}
						}

					}
				}
			}
		}
	RECT rc;
	RECT tempRC = { m_startRC.left,m_startRC.top,m_endRC.right,m_endRC.bottom };
	int index;
	// 영역을 만들어서 그릴 경우
	if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
	{

		for (int i = 0; i < TILEY; i++)
		{
			for (int j = 0; j < TILEX; j++)
			{
				index = i * TILEY + j;
				if (IntersectRect(&rc, &_tiles[index].rc, &tempRC))
				{
					if (!isErase)
					{
						GameObject * obj = new GameObject;
						switch (selectObj.GetObjKind())
						{
						case OBJ_FLOOR:
							obj = new GameObject;
							obj->Init(selectObj.GetImageKey(), i * TILEY + j, selectObj.GetObjKind());
							_tiles[index].floor = obj;
							_tiles[index].floor->SetRC(_tiles[i * TILEY + j].rc);
							strcpy(_tiles[index].floorKey, selectObj.GetImageKey().c_str());
							//_tiles[index].floorKey = selectObj.GetImageKey();
							_tiles[index].floorObj = selectObj.GetObjKind();
							_tiles[index].floorPos = index;
							break;
						case OBJ_WALL:
							obj = new GameObject;
							obj->Init(selectObj.GetImageKey(), i * TILEY + j, selectObj.GetObjKind());
							_tiles[index].wall = obj;
							_tiles[index].item = nullptr;
							_tiles[index].monster = nullptr;
							//_tiles[index].floor->SetRC(_tiles[i * TILEY + j].rc);
							strcpy(_tiles[index].objKey, selectObj.GetImageKey().c_str());
							//_tiles[index].objKey = selectObj.GetImageKey();
							_tiles[index].objObj = selectObj.GetObjKind();
							_tiles[index].objPos = index;
							break;
						case OBJ_ITEM:
							obj = new GameObject;
							obj->Init(selectObj.GetImageKey(), i * TILEY + j, selectObj.GetObjKind());
							_tiles[index].item = obj;
							_tiles[index].wall = nullptr;
							_tiles[index].monster = nullptr;
							strcpy(_tiles[index].objKey, selectObj.GetImageKey().c_str());
							//_tiles[index].objKey = selectObj.GetImageKey();
							_tiles[index].objObj = selectObj.GetObjKind();
							_tiles[index].objPos = index;
							break;
						case OBJ_MONSTER:
							obj = new GameObject;
							obj->Init(selectObj.GetImageKey(), i * TILEY + j, selectObj.GetObjKind());
							_tiles[index].monster = obj;
							_tiles[index].item = nullptr;
							_tiles[index].wall = nullptr;
							strcpy(_tiles[index].objKey, selectObj.GetImageKey().c_str());
							//_tiles[index].objKey = selectObj.GetImageKey();
							_tiles[index].objObj = selectObj.GetObjKind();
							_tiles[index].objPos = index;
							break;
						case OBJ_ETC:
							obj = new GameObject;
							obj->Init(selectObj.GetImageKey(), selectObj.GetPos(), selectObj.GetObjKind());

							if (obj->GetImageKey() == "wall_torch")
							{
								if (_tiles[index].objObj == OBJ_WALL)
								{
									_tiles[index].isTorch = true;
								}
							}
							else
							{
								_tiles[index].monster = obj;
								_tiles[index].item = nullptr;
								_tiles[index].wall = nullptr;
								strcpy(_tiles[index].objKey, selectObj.GetImageKey().c_str());
								//_tiles[index].objKey = selectObj.GetImageKey();
								_tiles[index].objObj = OBJ_MONSTER;
								_tiles[index].objPos = index;
								break;
							}
							break;
						}
					}
					else
					{
						switch (selectObj.GetObjKind())
						{
						case OBJ_FLOOR:
							_tiles[index].floor = nullptr;
							strcpy(_tiles[index].floorKey, temp.GetImageKey().c_str());
							//_tiles[index].floorKey = temp.GetImageKey();
							_tiles[index].floorObj = temp.GetObjKind();
							_tiles[index].floorPos = temp.GetPos();
							break;
						case OBJ_PLAYER:
							_tiles[index].player = nullptr;
							strcpy(_tiles[index].objKey, "");
							//_tiles[index].objKey = "";
							_tiles[index].objObj = OBJ_NONE;
							_tiles[index].objPos = -1;
							break;
						default:
							_tiles[index].wall = nullptr;
							_tiles[index].item = nullptr;
							_tiles[index].monster = nullptr;
							strcpy(_tiles[index].objKey, temp.GetImageKey().c_str());
							//_tiles[index].objKey = temp.GetImageKey();
							_tiles[index].objObj = temp.GetObjKind();
							_tiles[index].objPos = temp.GetPos();
							break;
						}

					}
				}
			}
			m_startRC = { -1,-1,-1,-1 };
			m_endRC = { -1,-1,-1,-1 };
		}

	}

}

void LevelEdit::Save()
{
	GameObject * obj = new GameObject;
	obj->Init("wall_end", 0, OBJ_WALL);
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			int index = i * TILEY + j;
			if (_tiles[index].floor != NULL)
			{
				if (_tiles[index - 1].floorObj == OBJ_NONE)
				{
					if (_tiles[index - 1].objObj == OBJ_NONE)
					{
						_tiles[index - 1].wall = obj;
						_tiles[index - 1].item = nullptr;
						_tiles[index - 1].monster = nullptr;
						strcpy(_tiles[index - 1].objKey, "wall_end");
						//_tiles[index].objKey = selectObj.GetImageKey();
						_tiles[index - 1].objObj = OBJ_WALL;
						_tiles[index - 1].objPos = index - 1;
					}
				}
			}
			if (_tiles[index].floor != NULL)
			{
				if (_tiles[index + 1].floorObj == OBJ_NONE)
				{
					if (_tiles[index + 1].objObj == OBJ_NONE)
					{
						_tiles[index + 1].wall = obj;
						_tiles[index + 1].item = nullptr;
						_tiles[index + 1].monster = nullptr;
						strcpy(_tiles[index + 1].objKey, "wall_end");
						//_tiles[index].objKey = selectObj.GetImageKey();
						_tiles[index + 1].objObj = OBJ_WALL;
						_tiles[index + 1].objPos = index + 1;
					}
				}
			}
			if (_tiles[index].floor != NULL)
			{
				if (_tiles[index - 50].floorObj == OBJ_NONE)
				{
					if (_tiles[index - 50].objObj == OBJ_NONE)
					{
						_tiles[index - 50].wall = obj;
						_tiles[index - 50].item = nullptr;
						_tiles[index - 50].monster = nullptr;
						strcpy(_tiles[index - 50].objKey, "wall_end");
						//_tiles[index].objKey = selectObj.GetImageKey();
						_tiles[index - 50].objObj = OBJ_WALL;
						_tiles[index - 50].objPos = index - 50;
					}
				}
			}
			if (_tiles[index].floor != NULL)
			{
				if (_tiles[index + 50].floorObj == OBJ_NONE)
				{
					if (_tiles[index + 50].objObj == OBJ_NONE)
					{
						_tiles[index + 50].wall = obj;
						_tiles[index + 50].item = nullptr;
						_tiles[index + 50].monster = nullptr;
						strcpy(_tiles[index + 50].objKey, "wall_end");
						//_tiles[index].objKey = selectObj.GetImageKey();
						_tiles[index + 50].objObj = OBJ_WALL;
						_tiles[index + 50].objPos = index + 50;
					}
				}
			}
		}
	}


	isSave = true;
	HANDLE file;
	DWORD write;

	HWND hEditFIleToBEOpened;
	OPENFILENAME OFN;
	const UINT nFileNameMaxLen = 512;
	LPSTR szFileName[nFileNameMaxLen];
	ptMouse.x = -1;

	char str[300];
	char lpstrFile[MAX_PATH] = "";

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = hWnd;
	OFN.lpstrFilter = "All File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 256;
	OFN.lpstrInitialDir = _T(".\\map\\");
	
	
	if (GetSaveFileName(&OFN) != 0)
	{
		file = CreateFile(OFN.lpstrFile,
			GENERIC_WRITE | GENERIC_READ,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
	}

	if (!strcmp(OFN.lpstrFile, ""))
	{
		isSave = false;
		return;
	}

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
	WriteFile(file, _pos, sizeof(int) * 2, &write, NULL);
	CloseHandle(file);
	isSave = false;
}

void LevelEdit::Load()
{

	HWND hEditFIleToBEOpened;
	OPENFILENAME OFN;
	const UINT nFileNameMaxLen = 512;
	LPSTR szFileName[nFileNameMaxLen];
	ptMouse.x = -1;


	char str[300];
	char lpstrFile[MAX_PATH] = "";

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = hWnd;
	OFN.lpstrFilter = "All File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 256;
	OFN.lpstrInitialDir = "c:\\User\ShinC\Documents\Visual Studio 2017\Projects\API_Main\test\map\"";

	HANDLE file;
	DWORD read;
	GetOpenFileName(&OFN);
	file = CreateFile(OFN.lpstrFile,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);
	CloseHandle(file);

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{

			//_tiles[i * TILEY + j].objKey.resize(sizeof(tagTile));
			_tiles[i * TILEY + j].SetObj();
			//_tiles[i * TILEY + j].objKey = "null";
			//_tiles[i * TILEY + j].floorKey = "null";

			if (_tiles[i * TILEY + j].player != NULL)
			{
				GameObject * player = new GameObject;
				player->Init("", i * TILEY + j, OBJ_PLAYER);
				_tiles[curPlayerPos].player = nullptr;
				curPlayerPos = i * TILEY + j;
				_tiles[curPlayerPos].player = player;
			}
			/*if (_tiles[i * TILEY + j].player.GetObjKind() == OBJ_PLAYER)
			_tiles[curPlayerPos].player.Init("",-1,OBJ_NONE);
			curPlayerPos = i * TILEY + j;*/
		}
	}

}

void LevelEdit::SaveTest()
{
	GameObject * obj = new GameObject;
	obj->Init("wall_end", 0, OBJ_WALL);
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			int index = i * TILEY + j;
			if (_tiles[index].floor != NULL)
			{
				if (_tiles[index - 1].floorObj == OBJ_NONE)
				{
					if (_tiles[index - 1].objObj == OBJ_NONE)
					{
						_tiles[index - 1].wall = obj;
						_tiles[index - 1].item = nullptr;
						_tiles[index - 1].monster = nullptr;
						strcpy(_tiles[index - 1].objKey, "wall_end");
						//_tiles[index].objKey = selectObj.GetImageKey();
						_tiles[index - 1].objObj = OBJ_WALL;
						_tiles[index - 1].objPos = index - 1;
					}
				}
			}
			if (_tiles[index].floor != NULL)
			{
				if (_tiles[index + 1].floorObj == OBJ_NONE)
				{
					if (_tiles[index + 1].objObj == OBJ_NONE)
					{
						_tiles[index + 1].wall = obj;
						_tiles[index + 1].item = nullptr;
						_tiles[index + 1].monster = nullptr;
						strcpy(_tiles[index + 1].objKey, "wall_end");
						//_tiles[index].objKey = selectObj.GetImageKey();
						_tiles[index + 1].objObj = OBJ_WALL;
						_tiles[index + 1].objPos = index + 1;
					}
				}
			}
			if (_tiles[index].floor != NULL)
			{
				if (_tiles[index - 50].floorObj == OBJ_NONE)
				{
					if (_tiles[index - 50].objObj == OBJ_NONE)
					{
						_tiles[index - 50].wall = obj;
						_tiles[index - 50].item = nullptr;
						_tiles[index - 50].monster = nullptr;
						strcpy(_tiles[index - 50].objKey, "wall_end");
						//_tiles[index].objKey = selectObj.GetImageKey();
						_tiles[index - 50].objObj = OBJ_WALL;
						_tiles[index - 50].objPos = index - 50;
					}
				}
			}
			if (_tiles[index].floor != NULL)
			{
				if (_tiles[index + 50].floorObj == OBJ_NONE)
				{
					if (_tiles[index + 50].objObj == OBJ_NONE)
					{
						_tiles[index + 50].wall = obj;
						_tiles[index + 50].item = nullptr;
						_tiles[index + 50].monster = nullptr;
						strcpy(_tiles[index + 50].objKey, "wall_end");
						//_tiles[index].objKey = selectObj.GetImageKey();
						_tiles[index + 50].objObj = OBJ_WALL;
						_tiles[index + 50].objPos = index + 50;
					}
				}
			}
		}
	}

	isSave = true;
	HANDLE file;
	DWORD write;

	
	file = CreateFile("test",
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		0,
		NULL);
	
	if (file == INVALID_HANDLE_VALUE)
	{
		//SOUNDMANAGER->Play("boss_1");
	}

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
	WriteFile(file, _pos, sizeof(int) * 2, &write, NULL);
	CloseHandle(file);
	isSave = false;
}

void LevelEdit::SetInterface()
{
	// 인터 페이스 관련 초기와
	m_camera = { 0,0 };
	m_backGround = { 0,0,WINSIZEX,WINSIZEY };
	m_MenualRC = RectMake(1030, 30, 610, 840);
	m_isShowMenual = false;
	m_startRC = { -1,-1,-1,-1 };
	m_endRC = { -1,-1,-1,-1 };
	for (int i = 0; i < 5; i++)
	{
		m_interfaceRC[i] = RectMake(
			m_MenualRC.left + 90 * i,
			m_MenualRC.top,
			90, 40);
	}
	m_interfaceRC[5] = RectMake(m_MenualRC.left + 90 * 0,
		m_MenualRC.top + 670, 90, 40);
	m_interfaceRC[6] = RectMake(m_MenualRC.left + 90 * 1,
		m_MenualRC.top + 670, 90, 40);
	m_interfaceRC[7] = RectMake(m_MenualRC.left + 90 * 2,
		m_MenualRC.top + 670, 90, 40);
	m_interfaceRC[8] = RectMake(m_MenualRC.left + 90 * 3,
		m_MenualRC.top + 670, 90, 40);
	m_interfaceRC[9] = RectMake(m_MenualRC.left + 90 * 4,
		m_MenualRC.top + 670, 90, 40);
	IMAGEMANAGER->AddImage("black2", "images/black.bmp", 540, 710);
}

void LevelEdit::MoveCamera()
{
	// 키보드 입력에 따른 카메라 이동
	if (KEYMANAGER->IsStayKeyDown('W')) m_camera.y += 10;
	if (KEYMANAGER->IsStayKeyDown('S')) m_camera.y -= 10;
	if (KEYMANAGER->IsStayKeyDown('A')) m_camera.x += 10;
	if (KEYMANAGER->IsStayKeyDown('D')) m_camera.x -= 10;

	// 마우스 이동에 따른 카메라 이동

	if (!(PtInRect(&m_MenualRC, ptMouse) && m_isShowMenual))
	{
		if (KEYMANAGER->IsStayKeyDown(VK_RBUTTON))
		{
			//curMounse = ptMouse;
			m_camera.x = m_camera.x + ptMouse.x - curMounse.x;
			m_camera.y = m_camera.y + ptMouse.y - curMounse.y;
		}
		curMounse.x = ptMouse.x;
		curMounse.y = ptMouse.y;
	}

	// 이동된 카메라를 모든 렉트에 적용
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			RECT rc = RectMake(
				50 + j * TILESIZE + m_camera.x,
				50 + i * TILESIZE + m_camera.y,
				TILESIZE, TILESIZE);
			int index = i * TILEY + j;
			_tiles[index].rc = rc;
			if (_tiles[index].floor != NULL)
				_tiles[index].floor->SetRC(rc);
			if (_tiles[index].item != NULL)
				_tiles[index].item->SetRC(rc);
			if (_tiles[index].monster != NULL)
				_tiles[index].monster->SetRC(rc);
			if (_tiles[index].wall != NULL)
				_tiles[index].wall->SetRC(rc);
		}
	}

}

void LevelEdit::MoveMenual()
{
	if (KEYMANAGER->IsOnceKeyDown(VK_TAB)) m_isShowMenual = !m_isShowMenual;

	if (m_isShowMenual)
	{
		// 마우스 포인터로 메뉴얼 옮기기
		if (PtInRect(&m_MenualRC, ptMouse))
		{
			if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
			{
				m_MenualRC.left = m_MenualRC.left + ptMouse.x - curMounse.x;
				m_MenualRC.top = m_MenualRC.top + ptMouse.y - curMounse.y;
				m_MenualRC.right = m_MenualRC.left + 540;
				m_MenualRC.bottom = m_MenualRC.top + 710;

			}
		}
		curMounse.x = ptMouse.x;
		curMounse.y = ptMouse.y;

		// 변경된 좌표를 선택지 렉트에 반영
		for (int i = 0; i < 5; i++)
		{
			m_interfaceRC[i] = RectMake(
				m_MenualRC.left + 90 * i,
				m_MenualRC.top,
				90, 40);
		}

		m_interfaceRC[5] = RectMake(m_MenualRC.left + 90 * 0,
			m_MenualRC.top + 670, 90, 40);
		m_interfaceRC[6] = RectMake(m_MenualRC.left + 90 * 1,
			m_MenualRC.top + 670, 90, 40);
		m_interfaceRC[7] = RectMake(m_MenualRC.left + 90 * 2,
			m_MenualRC.top + 670, 90, 40);
		m_interfaceRC[8] = RectMake(m_MenualRC.left + 90 * 3,
			m_MenualRC.top + 670, 90, 40);
		m_interfaceRC[9] = RectMake(m_MenualRC.left + 90 * 4,
			m_MenualRC.top + 670, 90, 40);

		// 선택지 렉트들 중 선택 됐을 때 변수 수정
		for (int i = 0; i < 10; i++)
		{
			if (PtInRect(&m_interfaceRC[i], ptMouse))
			{

				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					RECT rcClient;
					if (i < 5)
						selectNum = i;
					else
					{
						switch (i)
						{
						case 5:
							this->Save(); break;
						case 6:	this->Load(); 	break;
						case 7:
							isErase = !isErase;
							break;
						case 8: // Play 구현할 부분

							rcClient = { 0,0,960,540 };

							AdjustWindowRect(
								&rcClient,
								WINSTYLE,
								FALSE);

							SetWindowPos(

								hWnd, NULL,
								0, 0,
								(rcClient.right - rcClient.left),
								(rcClient.bottom - rcClient.top),
								SWP_NOZORDER | SWP_NOMOVE);
							SaveTest();

							SCENEMANAGER->ChangeScene("test");
							break;
						case 9: selectNum = 9;
							break;
						}
					}

				}
			}
		}

	}
}

void LevelEdit::SelectTile()
{
	int itemCount = 0;
	m_viObj = m_vObj.begin();
	int count = 0;
	RECT rc;
	int width, height;

	if (selectNum == 9) {
		selectObj.Init("", -1, OBJ_PLAYER); return;
	}

	for (m_viObj; m_viObj != m_vObj.end(); ++m_viObj)
	{


		// 내가 선택한 아이템 종류만 나와라
		if (m_viObj->GetObjKind() != selectNum) continue;

		if (PtInRect(&m_viObj->GetRC(), ptMouse))
		{
			if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
			{
				//selectObj.Init(m_viObj->GetImageKey(), -1,m_viObj->GetObjKind());
				selectObj = *m_viObj;
			}
		}

		count++;

		itemCount++;
	}
}

void LevelEdit::ShowMap()
{
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	FillRect(GetMemDC(), &m_backGround, brush);
	//DeleteObject(brush);


	int inMouse = -1;

	// 바둑판 맵 출력하면서 마우스 포인터 위치를 초록색으로 하는 부분
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			if (i * TILEY > 0 ||
				i * TILEY < WINSIZEY ||
				j * TILEX > 0 ||
				j * TILEX < WINSIZEX)
			{
				HPEN pen, oldPen;
				pen = CreatePen(PS_SOLID, 2, RGB(254, 254, 254));
				oldPen = (HPEN)SelectObject(GetMemDC(), pen);

				Rectangle(GetMemDC(), _tiles[i * TILEY + j].rc.left,
					_tiles[i * TILEY + j].rc.top,
					_tiles[i * TILEY + j].rc.right,
					_tiles[i * TILEY + j].rc.bottom);

				SelectObject(GetMemDC(), oldPen);
				DeleteObject(pen);

				HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
				FillRect(GetMemDC(), &_tiles[i * TILEY + j].rc, brush);
				DeleteObject(brush);

				if (PtInRect(&_tiles[i * TILEY + j].rc, ptMouse)) inMouse = i * TILEY + j;

			}
		}
	}


	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			if (_tiles[i * TILEY + j].floor != NULL)
				if (_tiles[i * TILEY + j].floor->GetObjKind() != OBJ_NONE)
					_tiles[i*TILEY + j].floor->Render();
			//IMAGEMANAGER->FrameRender(_tiles[i * TILEY + j].floor.GetImageKey(),GetMemDC(), _tiles[i * TILEY + j].rc.left, _tiles[i * TILEY + j].rc.top);
		}
	}
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			if (_tiles[i * TILEY + j].item != NULL)
				if (_tiles[i * TILEY + j].item->GetObjKind() != OBJ_NONE)
					IMAGEMANAGER->FrameRender(_tiles[i * TILEY + j].item->GetImageKey(), GetMemDC(), _tiles[i * TILEY + j].rc.left, _tiles[i * TILEY + j].rc.top);
		}


		for (int j = 0; j < TILEX; j++)
		{
			if (_tiles[i * TILEY + j].monster != NULL)
				if (_tiles[i * TILEY + j].monster->GetObjKind() != OBJ_NONE)
				{
					int subX = 0;
					int subY = 0;
					string m_imageKey = _tiles[i * TILEY + j].objKey;
					if (m_imageKey == "banshee" || m_imageKey == "banshee2")
					{
						subX = 7;
						subY = 47;
					}
					else if (m_imageKey == "bat" ||
						m_imageKey == "bat_black" ||
						m_imageKey == "bat_green" ||
						m_imageKey == "bat_red")
					{
						subX = 0;
						subY = 20;
					}
					else if (m_imageKey == "bat_miniboss" || m_imageKey == "miniboss_yellow")
					{
						subX = 12;
						subY = 20;
					}
					else if (m_imageKey == "dragon_red")
					{
						subX = 40;
						subY = 70;
					}
					else if (m_imageKey == "mage_black" ||
						m_imageKey == "mage_white" ||
						m_imageKey == "mage_yellow" ||
						m_imageKey == "skeleton_black" ||
						m_imageKey == "skeleton_yellow" ||
						m_imageKey == "skeleton")
					{
						subX = 0;
						subY = 20;
					}

					else if (m_imageKey == "minotaur" || m_imageKey == "minotaur2")
					{
						subX = 22;
						subY = 67;
					}
					else if (m_imageKey == "shopkeeper")
					{
						subX = 20;
						subY = 45;
					}
					else if (m_imageKey == "slime_green" || m_imageKey == "slime_blue")
					{
						subX = 0;
						subY = 20;
					}
					else if (m_imageKey == "king_conga")
					{
						subX = 35;
						subY = 79;
					}
					else if (m_imageKey == "zombie_snake")
					{
						subX = 0;
						subY = 20;
					}
					IMAGEMANAGER->FrameRender(_tiles[i * TILEY + j].monster->GetImageKey(), GetMemDC(), _tiles[i * TILEY + j].rc.left - subX, _tiles[i * TILEY + j].rc.top - subY);
				}
		}



		for (int j = 0; j < TILEX; j++)
		{
			if (_tiles[i * TILEY + j].wall != NULL)
			{
				if (_tiles[i * TILEY + j].wall->GetObjKind() != OBJ_NONE)
					IMAGEMANAGER->FrameRender(_tiles[i * TILEY + j].wall->GetImageKey(), GetMemDC(), _tiles[i * TILEY + j].rc.left, _tiles[i * TILEY + j].rc.top - 26);

				if (_tiles[i * TILEY + j].isTorch)
					IMAGEMANAGER->FrameRender("wall_torch", GetMemDC(), _tiles[i * TILEY + j].rc.left + 13, _tiles[i * TILEY + j].rc.top - 44);
			}
			
			if (_tiles[i * TILEY + j].player != NULL)
			{
				//if (_tiles[i * TILEY + j].player->GetObjKind() != OBJ_NONE)
				//{
					IMAGEMANAGER->FrameRender("player_body", GetMemDC(), _tiles[i * TILEY + j].rc.left, _tiles[i * TILEY + j].rc.top);
					IMAGEMANAGER->FrameRender("player_head", GetMemDC(), _tiles[i * TILEY + j].rc.left, _tiles[i * TILEY + j].rc.top);
				//}
			}


		}

		//

	}

	
	
	//for (int i = 0; i < TILEY; i++)
	//{
	//	for (int j = 0; j < TILEX; j++)
	//	{
	//		if (_tiles[i * TILEY + j].item != NULL)
	//			if (_tiles[i * TILEY + j].item->GetObjKind() != OBJ_NONE)
	//				IMAGEMANAGER->FrameRender(_tiles[i * TILEY + j].item->GetImageKey(), GetMemDC(), _tiles[i * TILEY + j].rc.left, _tiles[i * TILEY + j].rc.top);
	//	}
	//}
	//for (int i = 0; i < TILEY; i++)
	//{
	//	for (int j = 0; j < TILEX; j++)
	//	{
	//		if (_tiles[i * TILEY + j].monster != NULL)
	//			if (_tiles[i * TILEY + j].monster->GetObjKind() != OBJ_NONE)
	//			{
	//				int subX = 0;
	//				int subY = 0;
	//				string m_imageKey = _tiles[i * TILEY + j].objKey;
	//				if (m_imageKey == "banshee" || m_imageKey == "banshee2")
	//				{
	//					subX = 7;
	//					subY = 47;
	//				}
	//				else if (m_imageKey == "bat" ||
	//					m_imageKey == "bat_black" ||
	//					m_imageKey == "bat_green" ||
	//					m_imageKey == "bat_red")
	//				{
	//					subX = 0;
	//					subY = 20;
	//				}
	//				else if (m_imageKey == "bat_miniboss" || m_imageKey == "miniboss_yellow")
	//				{
	//					subX = 12;
	//					subY = 20;
	//				}
	//				else if (m_imageKey == "dragon_red")
	//				{
	//					subX = 40;
	//					subY = 70;
	//				}
	//				else if (m_imageKey == "mage_black" ||
	//					m_imageKey == "mage_white" ||
	//					m_imageKey == "mage_yellow" ||
	//					m_imageKey == "skeleton_black" ||
	//					m_imageKey == "skeleton_yellow" ||
	//					m_imageKey == "skeleton")
	//				{
	//					subX = 0;
	//					subY = 20;
	//				}
	//
	//				else if (m_imageKey == "minotaur" || m_imageKey == "minotaur2")
	//				{
	//					subX = 22;
	//					subY = 67;
	//				}
	//				else if (m_imageKey == "shopkeeper")
	//				{
	//					subX = 20;
	//					subY = 45;
	//				}
	//				else if (m_imageKey == "slime_green" || m_imageKey == "slime_blue")
	//				{
	//					subX = 0;
	//					subY = 20;
	//				}
	//				else if (m_imageKey == "king_conga")
	//				{
	//					subX = 35;
	//					subY = 79;
	//				}
	//				else if (m_imageKey == "zombie_snake")
	//				{
	//					subX = 0;
	//					subY = 20;
	//				}
	//				IMAGEMANAGER->FrameRender(_tiles[i * TILEY + j].monster->GetImageKey(), GetMemDC(), _tiles[i * TILEY + j].rc.left - subX, _tiles[i * TILEY + j].rc.top - subY);
	//			}
	//	}
	//}
	//for (int i = 0; i < TILEY; i++)
	//{
	//	for (int j = 0; j < TILEX; j++)
	//	{
	//		if (_tiles[i * TILEY + j].wall != NULL)
	//		{
	//			if (_tiles[i * TILEY + j].wall->GetObjKind() != OBJ_NONE)
	//				IMAGEMANAGER->FrameRender(_tiles[i * TILEY + j].wall->GetImageKey(), GetMemDC(), _tiles[i * TILEY + j].rc.left, _tiles[i * TILEY + j].rc.top - 26);
	//		
	//			if (_tiles[i * TILEY + j].isTorch)
	//				IMAGEMANAGER->FrameRender("wall_torch", GetMemDC(), _tiles[i * TILEY + j].rc.left + 13, _tiles[i * TILEY + j].rc.top - 44);
	//		}
	//		else if (_tiles[i * TILEY + j].player != NULL)
	//		{
	//			if (_tiles[i * TILEY + j].player->GetObjKind() != OBJ_NONE)
	//			{
	//				IMAGEMANAGER->FrameRender("player_body", GetMemDC(), _tiles[i * TILEY + j].rc.left, _tiles[i * TILEY + j].rc.top);
	//				IMAGEMANAGER->FrameRender("player_head", GetMemDC(), _tiles[i * TILEY + j].rc.left, _tiles[i * TILEY + j].rc.top);
	//			}
	//		}
	//
	//
	//	}
	//}

	// 요기가 마우스 포인터를 녹색으로
	if (!(PtInRect(&m_MenualRC, ptMouse) && m_isShowMenual))
	{
		HPEN pen, oldPen;
		pen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		oldPen = (HPEN)SelectObject(GetMemDC(), pen);
		HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(GetMemDC(), myBrush);
		if (m_startRC.left != -1)
		{
			Rectangle(GetMemDC(), m_startRC.left,
				m_startRC.top,
				m_endRC.right,
				m_endRC.bottom);
		}
		else if (inMouse != -1)
			Rectangle(GetMemDC(), _tiles[inMouse].rc.left,
				_tiles[inMouse].rc.top,
				_tiles[inMouse].rc.right,
				_tiles[inMouse].rc.bottom);

		SelectObject(GetMemDC(), oldBrush);
		DeleteObject(myBrush);
		DeleteObject(brush);
		SelectObject(GetMemDC(), oldPen);
		DeleteObject(pen);
	}


	/*IMAGEMANAGER->FrameRender("player_body", GetMemDC(), _pos[0] + m_camera.x,_pos[1] + m_camera.y);
	IMAGEMANAGER->FrameRender("player_head",GetMemDC(), _pos[0] + m_camera.x,_pos[1] + m_camera.y);
	*/
	//IMAGEMANAGER->FrameRender("player_body", GetMemDC(), 200,100);
	//IMAGEMANAGER->FrameRender("player_head",GetMemDC(), 200,100);

}

void LevelEdit::ShowMenual()
{


	if (m_isShowMenual)
	{
		IMAGEMANAGER->AlphaRender("black2", GetMemDC(), m_MenualRC.left, m_MenualRC.top, 126);
		//IMAGEMANAGER->Render("black", GetMemDC(), m_MenualRC.left, m_MenualRC.top);
		HPEN pen, oldPen;
		SetTextColor(GetMemDC(), RGB(255, 255, 255));
		SetBkMode(GetMemDC(), TRANSPARENT);
		pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		oldPen = (HPEN)SelectObject(GetMemDC(), pen);
		HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(GetMemDC(), myBrush);
		Rectangle(GetMemDC(), m_interfaceRC[selectNum].left, m_interfaceRC[selectNum].top, m_interfaceRC[selectNum].right, m_interfaceRC[selectNum].bottom);

		if (isErase)
			Rectangle(GetMemDC(), m_interfaceRC[7].left, m_interfaceRC[7].top, m_interfaceRC[7].right, m_interfaceRC[7].bottom);



		SelectObject(GetMemDC(), oldBrush);
		DeleteObject(myBrush);
		DeleteObject(brush);
		SelectObject(GetMemDC(), oldPen);
		DeleteObject(pen);

		DrawText(GetMemDC(), "FLOOR", -1, &m_interfaceRC[0], DT_CENTER | DT_WORDBREAK | DT_VCENTER | DT_SINGLELINE);
		DrawText(GetMemDC(), "WALL", -1, &m_interfaceRC[1], DT_CENTER | DT_WORDBREAK | DT_VCENTER | DT_SINGLELINE);
		DrawText(GetMemDC(), "ITEM", -1, &m_interfaceRC[2], DT_CENTER | DT_WORDBREAK | DT_VCENTER | DT_SINGLELINE);
		DrawText(GetMemDC(), "MONSTER", -1, &m_interfaceRC[3], DT_CENTER | DT_WORDBREAK | DT_VCENTER | DT_SINGLELINE);
		DrawText(GetMemDC(), "ETC", -1, &m_interfaceRC[4], DT_CENTER | DT_WORDBREAK | DT_VCENTER | DT_SINGLELINE);

		DrawText(GetMemDC(), "SAVE", -1, &m_interfaceRC[5], DT_CENTER | DT_WORDBREAK | DT_VCENTER | DT_SINGLELINE);
		DrawText(GetMemDC(), "LOAD", -1, &m_interfaceRC[6], DT_CENTER | DT_WORDBREAK | DT_VCENTER | DT_SINGLELINE);
		DrawText(GetMemDC(), "ERASE", -1, &m_interfaceRC[7], DT_CENTER | DT_WORDBREAK | DT_VCENTER | DT_SINGLELINE);
		DrawText(GetMemDC(), "PLAY", -1, &m_interfaceRC[8], DT_CENTER | DT_WORDBREAK | DT_VCENTER | DT_SINGLELINE);
		DrawText(GetMemDC(), "PLAYER", -1, &m_interfaceRC[9], DT_CENTER | DT_WORDBREAK | DT_VCENTER | DT_SINGLELINE);


		ShowObject(selectNum);
	}



}

void LevelEdit::ShowObject(int selectNum)
{

	int itemCount = 0;
	m_viObj = m_vObj.begin();
	int count = 0;
	RECT rc;
	int width, height;
	for (m_viObj; m_viObj != m_vObj.end(); ++m_viObj)
	{


		// 내가 선택한 아이템 종류만 나와라
		if (m_viObj->GetObjKind() != selectNum) continue;

		int i = count % 4;
		int j = count / 4;
		string key = m_viObj->GetImageKey();
		//IMAGEMANAGER->Render(key, GetMemDC(), x + 30 + i * 112, y + 160 + j * 38);
		width = IMAGEMANAGER->GetFrameWidth(key);
		height = IMAGEMANAGER->GetFrameHeight(key);
		rc = RectMake(m_MenualRC.left + 130 * i + 40, m_MenualRC.top + 120 * j + 80, width, height);

		m_viObj->SetRC(rc);
		count++;
		IMAGEMANAGER->FrameRender(key, GetMemDC(), rc.left, rc.top, 0, 0);

		// 
		if (m_viObj->GetImageKey() == selectObj.GetImageKey())
		{
			HPEN pen, oldPen;
			SetTextColor(GetMemDC(), RGB(255, 255, 255));
			SetBkMode(GetMemDC(), TRANSPARENT);
			pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(GetMemDC(), pen);
			HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
			HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
			HBRUSH oldBrush = (HBRUSH)SelectObject(GetMemDC(), myBrush);
			Rectangle(GetMemDC(), m_viObj->GetRC().left, m_viObj->GetRC().top, m_viObj->GetRC().right, m_viObj->GetRC().bottom);
			SelectObject(GetMemDC(), oldBrush);
			DeleteObject(myBrush);
			DeleteObject(brush);
			SelectObject(GetMemDC(), oldPen);
			DeleteObject(pen);
		}



		itemCount++;
	}

}

FLOOR LevelEdit::TerrainSelect(int frameX, int frameY)
{
	return FLOOR();
}

OBJECT LevelEdit::ObjSelect(int frameX, int frameY)
{
	return OBJECT();
}
