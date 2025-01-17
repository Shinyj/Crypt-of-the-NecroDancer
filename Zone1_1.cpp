#include "stdafx.h"
#include "Zone1_1.h"
#include "OPlayer1.h"

Zone1_1::Zone1_1()
{
}


Zone1_1::~Zone1_1()
{
}

HRESULT Zone1_1::Init()
{
	SOUNDMANAGER->Stop("lobby");
	// 변수 초기화
	isOpenOption = false;
	isOpenAudio = false;

	SOUNDMANAGER->AddSound("zone1_2", "sound/zone1_2.ogg", true, true);
	SOUNDMANAGER->SetBgm("zone1_2");
	SOUNDMANAGER->SetBit("zone1_2");
	//OBJECTMANAGER->ObjClear();

	OBJECTMANAGER->SetBeat();

	Load();
	

	m_vObj = OBJECTMANAGER->GetVObj();
	m_viObj = OBJECTMANAGER->GetViObj();

	bgmVolum = OBJECTMANAGER->GetBgmVolum();
	effectVolum = OBJECTMANAGER->GetEffectVolum();


	SOUNDMANAGER->PlayZoneBGM("zone1_2", OBJECTMANAGER->GetBgmVolum());
	//SOUNDMANAGER->Play("zone1_1_shopkeeper", OBJECTMANAGER->GetBgmVolum());
	return S_OK;
}

void Zone1_1::Release()
{
}

void Zone1_1::Update()
{
	if (!isOpenOption)
	{
		//  로비 업테이트
		OpenOption();
		OBJECTMANAGER->Update();
		SetCamera();
		OBJECTMANAGER->SetCamera(m_camera);
	}
	else
	{
		//옵션 업데이트
		OptionUpdate();
	}

	TIMEMANAGER->Render(GetMemDC());
}

void Zone1_1::Render()
{

	if (!isOpenOption)
		OBJECTMANAGER->Render();
	else
		OptionRedner();
}

void Zone1_1::OptionUpdate()
{
	if (!isOpenAudio)
	{
		// 그냥 옵션 부분 업데이트
		if (KEYMANAGER->IsOnceKeyDown(VK_DOWN))
		{
			SOUNDMANAGER->Play("sfx_ui_select_down");
			selectOption[selectNum] = false;
			selectNum = (selectNum + 1) % 5;
			selectOption[selectNum] = true;
		}
		else if (KEYMANAGER->IsOnceKeyDown(VK_UP))
		{
			SOUNDMANAGER->Play("sfx_ui_select_up");
			selectOption[selectNum] = false;
			selectNum = (selectNum - 1);
			if (selectNum < 0) selectNum = 4;
			selectOption[selectNum] = true;
		}
		else if (KEYMANAGER->IsOnceKeyDown(VK_RETURN))
		{
			switch (selectNum)
			{
			case 0:
				isOpenOption = false;
				SOUNDMANAGER->ResumeZoneBGM("zone1_2", OBJECTMANAGER->GetBgmVolum());
				break;
			case 1 :
				SOUNDMANAGER->Play("sfx_ui_start");
				isOpenAudio = true;
				selectNum = 0;
				selectOption[0] = true;
				selectOption[1] = true;
				selectOption[2] = true;
				break;
			case 2 :
				SCENEMANAGER->ChangeScene("lobby");
				SCENEMANAGER->ChangeScene("zone1_1");
				break;
			case 3 :
				SCENEMANAGER->ChangeScene("lobby");
				break;
			case 4 :

				PostQuitMessage(0);
				break;
			}
		}
		else if (KEYMANAGER->IsOnceKeyDown(VK_ESCAPE))
		{
			isOpenOption = false;
			SOUNDMANAGER->ResumeZoneBGM("zone1_2", OBJECTMANAGER->GetBgmVolum());
		}
	}
	else
	{
		// 오디오 옵션 업데이트
		if (KEYMANAGER->IsOnceKeyDown(VK_DOWN))
		{
			SOUNDMANAGER->Play("sfx_ui_select_down");
			selectOption[selectNum] = false;
			selectNum = (selectNum + 1) % 3;
			selectOption[selectNum] = true;
		}
		else if (KEYMANAGER->IsOnceKeyDown(VK_UP))
		{
			SOUNDMANAGER->Play("sfx_ui_select_up");
			selectOption[selectNum] = false;
			selectNum = (selectNum - 1);
			if (selectNum < 0) selectNum = 2;
			selectOption[selectNum] = true;
		}
		else if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT))
		{
			SOUNDMANAGER->Play("sfx_ui_toggle");
			if (selectNum == 0 && bgmVolum < 1.0f)
			{
				bgmVolum += 0.1;
				OBJECTMANAGER->SetBgmVolum(bgmVolum);
			}
			else if (selectNum == 1 && effectVolum < 1.0f)
			{
				effectVolum += 0.1;
				OBJECTMANAGER->SetEffectVolum(effectVolum);
			}
		}
		else if (KEYMANAGER->IsOnceKeyDown(VK_LEFT))
		{
			SOUNDMANAGER->Play("sfx_ui_toggle");
			if (selectNum == 0 && bgmVolum > 0.05f)
			{
				bgmVolum -= 0.1;
				OBJECTMANAGER->SetBgmVolum(bgmVolum);
			}
			else if (selectNum == 1 && effectVolum > 0.05f)
			{
				effectVolum -= 0.1;
				OBJECTMANAGER->SetEffectVolum(effectVolum);
			}
		}
		else if (KEYMANAGER->IsOnceKeyDown(VK_RETURN))
		{
			if (selectNum == 2)
			{
				SOUNDMANAGER->Play("sfx_ui_back");
				isOpenAudio = false;
				selectNum = 0;
				selectOption[0] = true;
				selectOption[1] = false;
				selectOption[2] = false;
			}
		}
		else if (KEYMANAGER->IsOnceKeyDown(VK_ESCAPE))
		{
			SOUNDMANAGER->Play("sfx_ui_back");
			isOpenAudio = false;
			selectNum = 0;
			selectOption[0] = true;
			selectOption[1] = false;
			selectOption[2] = false;
		}
	}

}

void Zone1_1::OptionRedner()
{
	if (!isOpenAudio)
	{
		// 그냥 옵션 렌더
		IMAGEMANAGER->Render("border_horizontal", GetMemDC(), 231, 85, 0, 0, 509, 24);
		IMAGEMANAGER->Render("black", GetMemDC(), 290, 75, 0, 0, 395, 100);
		IMAGEMANAGER->Render("border_horizontal", GetMemDC(), 231, 436, 0, 0, 509, 24);
		IMAGEMANAGER->Render("border_vertical", GetMemDC(), 185, 85, 0, 0, 24, 340);
		IMAGEMANAGER->Render("border_vertical", GetMemDC(), 776, 85, 0, 0, 24, 340);

		IMAGEMANAGER->Render("border_corner1", GetMemDC(), 185, 85);
		IMAGEMANAGER->Render("border_corner2", GetMemDC(), 740, 85);
		IMAGEMANAGER->Render("border_corner3", GetMemDC(), 740, 400);
		IMAGEMANAGER->Render("border_corner4", GetMemDC(), 185, 400);

		IMAGEMANAGER->Render("options_pause", GetMemDC(), 365, 65);

		if (selectNum == 0)
			IMAGEMANAGER->Render("options_continue_s", GetMemDC(), WINSIZEX2 / 2 - (IMAGEMANAGER->FindImage("options_continue_s")->GetWidth() / 2), 140);
		else
			IMAGEMANAGER->Render("options_continue", GetMemDC(), WINSIZEX2 / 2 - (IMAGEMANAGER->FindImage("options_continue")->GetWidth() / 2), 140);

		if (selectNum == 1)
			IMAGEMANAGER->Render("options_audiooptions_2", GetMemDC(), WINSIZEX2 / 2 - (IMAGEMANAGER->FindImage("options_audiooptions_2")->GetWidth() / 2), 185);
		else
			IMAGEMANAGER->Render("options_audiooptions", GetMemDC(), WINSIZEX2 / 2 - (IMAGEMANAGER->FindImage("options_audiooptions")->GetWidth() / 2), 185);

		if (selectNum == 2)
			IMAGEMANAGER->Render("options_quickrestart_s", GetMemDC(), WINSIZEX2 / 2 - (IMAGEMANAGER->FindImage("options_quickrestart_s")->GetWidth() / 2), 230);
		else
			IMAGEMANAGER->Render("options_quickrestart", GetMemDC(), WINSIZEX2 / 2 - (IMAGEMANAGER->FindImage("options_quickrestart")->GetWidth() / 2), 230);

		if (selectNum == 3)
			IMAGEMANAGER->Render("options_quit_lobby_s", GetMemDC(), WINSIZEX2 / 2 - (IMAGEMANAGER->FindImage("options_quit_lobby_s")->GetWidth() / 2), 275);
		else
			IMAGEMANAGER->Render("options_quit_lobby", GetMemDC(), WINSIZEX2 / 2 - (IMAGEMANAGER->FindImage("options_quit_lobby")->GetWidth() / 2), 275);

		if (selectNum == 4)
			IMAGEMANAGER->Render("options_exitgame_s", GetMemDC(), WINSIZEX2 / 2 - (IMAGEMANAGER->FindImage("options_exitgame_s")->GetWidth() / 2), 385);
		else
			IMAGEMANAGER->Render("options_exitgame", GetMemDC(), WINSIZEX2 / 2 - (IMAGEMANAGER->FindImage("options_exitgame")->GetWidth() / 2), 385);
	
		
	
	}
	else
	{
		// 오디오 옵션 렌더

		IMAGEMANAGER->Render("border_horizontal", GetMemDC(), 231, 85, 0, 0, 509, 24);
		IMAGEMANAGER->Render("black", GetMemDC(), 290, 75, 0, 0, 395, 100);
		IMAGEMANAGER->Render("border_horizontal", GetMemDC(), 231, 316, 0, 0, 509, 24);
		IMAGEMANAGER->Render("border_vertical", GetMemDC(), 185, 85, 0, 0, 24, 220);
		IMAGEMANAGER->Render("border_vertical", GetMemDC(), 776, 85, 0, 0, 24, 220);

		IMAGEMANAGER->Render("border_corner1", GetMemDC(), 185, 85);
		IMAGEMANAGER->Render("border_corner2", GetMemDC(), 740, 85);
		IMAGEMANAGER->Render("border_corner3", GetMemDC(), 740, 280);
		IMAGEMANAGER->Render("border_corner4", GetMemDC(), 185, 280);

		IMAGEMANAGER->Render("options_audiooptionstitle", GetMemDC(), 365, 65);

		if (selectNum == 0)
			IMAGEMANAGER->Render("options_musicvolume_s", GetMemDC(), 360 - IMAGEMANAGER->FindImage("options_musicvolume_s")->GetWidth() / 2, 140);
		else
			IMAGEMANAGER->Render("options_musicvolume", GetMemDC(), 360 - IMAGEMANAGER->FindImage("options_musicvolume")->GetWidth() / 2, 140);

		if (selectNum == 1)
			IMAGEMANAGER->Render("options_soundvolume_s", GetMemDC(), 360 - IMAGEMANAGER->FindImage("options_soundvolume_s")->GetWidth() / 2, 185);
		else
			IMAGEMANAGER->Render("options_soundvolume", GetMemDC(), 360 - IMAGEMANAGER->FindImage("options_soundvolume")->GetWidth() / 2, 185);

		if (selectNum == 2)
			IMAGEMANAGER->Render("options_done_s", GetMemDC(), WINSIZEX2 / 2 - IMAGEMANAGER->FindImage("options_done_s")->GetWidth() / 2, 270);
		else
			IMAGEMANAGER->Render("options_done", GetMemDC(), WINSIZEX2 / 2 - IMAGEMANAGER->FindImage("options_done")->GetWidth() / 2, 270);

		IMAGEMANAGER->Render("white", GetMemDC(), 450, 150);
		IMAGEMANAGER->Render("white", GetMemDC(), 450, 190);

		IMAGEMANAGER->Render("coin", GetMemDC(), 430 + bgmVolum * 200, 130);
		IMAGEMANAGER->Render("coin", GetMemDC(), 430 + effectVolum * 200, 170);
	}
}

void Zone1_1::Load()
{

	OBJECTMANAGER->ObjClear();

	HANDLE file;
	DWORD read;
	//GetOpenFileName(&OFN);

	file = CreateFile(_T(".\\map\\testMap"),
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	//ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);
	CloseHandle(file);

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			int index = i * TILEY + j;
			
			_tiles[index].SetObj();

			if (_tiles[index].floorObj == OBJ_FLOOR)
				OBJECTMANAGER->ObjPush(*_tiles[index].floor);
		}
	}

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			int index = i * TILEY + j;

			if (_tiles[index].objObj == OBJ_PLAYER)
			{
				OBJECTMANAGER->ObjPush(*_tiles[index].player);
				m_player.x = ((_tiles[index].player->GetPos() % TILEX) * TILESIZE);
				m_player.y = ((_tiles[index].player->GetPos() / TILEY) * TILESIZE);

				m_camera.x = (WINSIZEX2/2) - m_player.x - 24;//+ 86;
				m_camera.y = (WINSIZEY2/2) - m_player.y - 24;//+ 165;
			}
			else if(_tiles[index].objObj == OBJ_WALL)
				OBJECTMANAGER->ObjPush(*_tiles[index].wall);
			else if(_tiles[index].objObj == OBJ_ITEM)
				OBJECTMANAGER->ObjPush(*_tiles[index].item);
			else if(_tiles[index].objObj == OBJ_MONSTER)
				OBJECTMANAGER->ObjPush(*_tiles[index].monster);
		}
	}

	OBJECTMANAGER->SetCamera(m_camera);
	m_curPlayer.x = m_player.x ;//- m_camera.x;
	m_curPlayer.y = m_player.y ;//- m_camera.y;
}

void Zone1_1::OpenOption()
{
	if (KEYMANAGER->IsOnceKeyDown(VK_ESCAPE))
	{

		SOUNDMANAGER->Play("sfx_ui_start");
		SOUNDMANAGER->PauseZoneBGM("zone1_2");
		isOpenOption = true;
		selectNum = 0;
		selectOption[0] = true;
		selectOption[1] = false;
		selectOption[2] = false;
	}
}

void Zone1_1::SetCamera()
{
	m_vObj = OBJECTMANAGER->GetVObj();
	m_viObj = OBJECTMANAGER->GetViObj();

	OPlayer1 * player = OBJECTMANAGER->GetPlayer();

	m_player.x = player->GetX();
	m_player.y = player->GetY();

	player->Update();
	//m_viObj = m_vObj.begin();
	//for (m_viObj; m_viObj != m_vObj.end(); m_viObj++)
	//{
	//	//if ((*m_viObj) == NULL) continue;
	//	if ((*m_viObj)->GetObjKind() == OBJ_PLAYER)
	//	{
	//		m_player.x = (*m_viObj)->GetX();
	//		m_player.y = (*m_viObj)->GetY();
	//		(*m_viObj)->Update();
	//		m_curPlayer.x = (*m_viObj)->GetX();
	//		m_curPlayer.y = (*m_viObj)->GetY();
	//		m_camera.x = m_player.x - m_curPlayer.x;// + 86;
	//		m_camera.y = m_player.y - m_curPlayer.y;// + 165;
	//
	//		break;
	//	}
	//	//else
	//	//	(*m_viObj)->Update();
	//}

	//m_vObj = OBJECTMANAGER->GetVObj();
	//m_viObj = OBJECTMANAGER->GetViObj();
	//m_viObj = m_vObj.begin();
	//for (m_viObj; m_viObj != m_vObj.end(); m_viObj++)
	//{
	//	if ((*m_viObj)->GetObjKind() == OBJ_PLAYER)
	//	{
	//		continue;
	//	}
	//	else
	//		(*m_viObj)->Update();
	//}

	OBJECTMANAGER->AllObjUpdate();

	m_curPlayer.x = player->GetX();
	m_curPlayer.y = player->GetY();
	m_camera.x = m_player.x - m_curPlayer.x;// + 86;
	m_camera.y = m_player.y - m_curPlayer.y;// + 165;
	
}
