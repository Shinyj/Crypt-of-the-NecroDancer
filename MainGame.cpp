#include "stdafx.h"
#include "MainGame.h"
#include "TestScene_01.h"
#include "TestScene_02.h"

MainGame::MainGame()
{
	
}


MainGame::~MainGame()
{

}

HRESULT MainGame::Init()
{
	GameNode::Init();
	
	IMAGEMANAGER->AddImage("배경화면", "images/background.bmp", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->AddFrameImage("ufo", "images/ufo.bmp", 530, 32, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("bullet", "images/bullet.bmp", 21, 21, true, RGB(255, 0, 255));

	//씬 추가
	
	SCENEMANAGER->AddScene("Scene1", new TestScene_01);
	SCENEMANAGER->AddScene("Scene2", new TestScene_02);
	
	//씬 초기화
	SCENEMANAGER->ChangeScene("Scene1");
	
	return S_OK;
}
void MainGame::Release()
{
	GameNode::Release();
	
	m_rocket->Release();
	SAFE_DELETE(m_rocket);

	m_enemyManager->Release();
	SAFE_RELEASE(m_enemyManager);
	/*for (int i = 0; i < 18; i++)
		SAFE_DELETE(m_enemy[i]);*/
	
}
void MainGame::Update()
{
	GameNode::Update();
	SCENEMANAGER->Update();


	

}
void MainGame::Render()
{
	//흰색 빈 비트맵
	PatBlt(GetMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=============================================================
	////백그라운드 먼저 이미지 랜더
	SCENEMANAGER->Render();
	//IMAGEMANAGER->Render("배경화면", GetMemDC());

	TIMER->Render(GetMemDC());

	//==============================================================
	//백버퍼의 내용을 HDC에 그린다 (지우지 말것!!)
	this->GetBackBuffer()->Render(GetHDC(), 0, 0);

}

//void MainGame::Collision()
//{
//	for (int i = 0; i < m_rocket->GetMissile()->GetVBullet().size(); i++)
//	{
//		for (int j = 0; j < m_enemyManager->GetVMinion().size(); j++)
//		{
//			RECT rc;
//			if (IntersectRect(&rc, &m_rocket->GetMissile()->GetVBullet()[i].rc,
//				&m_enemyManager->GetVMinion()[j]->GetRect()))
//			{
//				m_rocket->GetMissile()->RemoveMissile(i);
//				m_enemyManager->RemoveMinion(j);
//				break;
//			}
//		}
//	}

	/*for (int i = 0; i < m_enemyManager->GetBullet()->GetVBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &m_rocket->GetRocketImage()->GetBoundingBox(),
			&m_enemyManager->GetBullet()->GetVBullet()[i].rc))
		{
			m_enemyManager->GetBullet()->RemoveMissile(i);
			m_rocket->Damage();
			break;
		}
	}*/
//}
