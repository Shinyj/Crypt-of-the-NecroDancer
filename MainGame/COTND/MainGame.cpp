#include "stdafx.h"
#include "../../stdafx.h"
#include "../../GameNode.h"
#include "MainGame.h"
#include <fstream>

// 씬들
#include "../../LevelEdit.h"
#include "../../LobbyScene.h"
#include "../LodingScene/LoadingScene.h"
#include "../../Zone1_1.h"
#include "../../BossStatge.h"
#include "../../kingcongaIntro.h"
#include "../../IntroScene.h"
#include "../../TestScene.h"
MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

HRESULT MainGame::Init()
{
	GameNode::Init();
	m_loading = new LoadingScene;
	m_levelEdit = new LevelEdit;
	m_lobby = new LobbyScene;
	m_zone1_1 = new Zone1_1;
	m_bossStage = new BossStatge;
	m_bossIntro = new kingcongaIntro;
	m_testMap = new TestScene;
	//m_Intro = new IntroScene;
	//m_lobby->Init();
	m_loading->Init();
	//m_levelEdit->Init();


	SCENEMANAGER->AddScene("levelEdit", m_levelEdit);
	SCENEMANAGER->AddScene("lobby", m_lobby);
	SCENEMANAGER->AddScene("loading", m_loading);
	SCENEMANAGER->AddScene("zone1_1", m_zone1_1);
	SCENEMANAGER->AddScene("boss", m_bossStage);
	SCENEMANAGER->AddScene("bossIntro", m_bossIntro);
	SCENEMANAGER->AddScene("test", m_testMap);
	//SCENEMANAGER->AddScene("intro", m_Intro);

	SCENEMANAGER->ChangeScene("loading");


	return S_OK;
}
void MainGame::Release()
{
	GameNode::Release();

	SAFE_DELETE(m_loading);
	SAFE_DELETE(m_levelEdit);
	SAFE_DELETE(m_lobby);
	SAFE_DELETE(m_zone1_1);

	IMAGEMANAGER->Release();
	SCENEMANAGER->Release();

}
void MainGame::Update()
{
	GameNode::Update();
	
	SCENEMANAGER->Update();


}
void MainGame::Render()
{
	//흰색 빈 비트맵
	PatBlt(GetMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=============================================================
	
	SCENEMANAGER->Render();

	/////////////////////////////////////////

	// 편하게 마우스 포인터 좌표를 찍자

	//char str[256];

	//sprintf(str, "%d %d", ptMouse.x, ptMouse.y);
	//TextOut(GetMemDC(), 840, 140,str,strlen(str));
	//
	//TIMEMANAGER->Render(GetMemDC());

	//==============================================================
	//백버퍼의 내용을 HDC에 그린다 (지우지 말것!!)
	this->GetBackBuffer()->Render(GetHDC(), 0, 0);

}
