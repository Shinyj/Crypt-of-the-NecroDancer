#include "stdafx.h"
#include "Rocket.h"
#include "EnemyManager.h"


Rocket::Rocket()
{
}


Rocket::~Rocket()
{
}

HRESULT Rocket::Init()
{
	// 로켓 플레이어 초기화 및 세팅 
	m_player = IMAGEMANAGER->AddImage("rocket","images/rocket.bmp",WINSIZEX/2,WINSIZEY - 200,52,64,true,RGB(255,0,255));
	m_speed = 200.0f;

	// 미사일 클래스 초기화
	m_missile = new Missile;
	m_missile->Init(10, 500);
	m_missileM1 = new MissileM1;
	m_missileM1->Init(10, 600);

	// 체력 초기화
	_maxHp = _currentHp = 100;

	_hpBar = new ProgressBar;
	_hpBar->Init("images/progressBarFront.bmp", "images/progressBarBack.bmp",
		0,0, 50, 10);
	_hpBar->SetGauge(_currentHp, _maxHp);



	return S_OK;
}

void Rocket::Release()
{
	m_player->Release();
	SAFE_DELETE(m_player);
	//m_missile->Release();
	//SAFE_DELETE(m_missile);
	SAFE_RELEASE(m_missile);
	_hpBar->Release();
	SAFE_DELETE(_hpBar);
}

void Rocket::Update()
{
	 
	// 왼쪽이동
	if (KEYMANAGER->IsStayKeyDown(VK_LEFT) && m_player->GetX() > 0)
	{
		m_player->SetX( m_player->GetX() - m_speed * TIMER->GetElapsedTime());
	}
	// 오른쪽 이동
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT) && m_player->GetX() + m_player->GetWidth() < WINSIZEX)
	{
		m_player->SetX(m_player->GetX() + m_speed* TIMER->GetElapsedTime());
	}
	// 위 이동
	if (KEYMANAGER->IsStayKeyDown(VK_UP) && m_player->GetY() > 0)
	{
		m_player->SetY(m_player->GetY() - m_speed* TIMER->GetElapsedTime());
		/*int time = 0;
		time += TIMER->GetElapsedTime();
		if (time > 1.0f)
		{
			Fire();
			time = 0.0f;
		}*/
	}
	// 아래 이동
	if (KEYMANAGER->IsStayKeyDown(VK_DOWN) && m_player->GetY() + m_player->GetHeight() < WINSIZEY)
	{
		m_player->SetY(m_player->GetY() + m_speed* TIMER->GetElapsedTime());
	}

	if (KEYMANAGER->IsOnceKeyDown(VK_SPACE))
	{
		m_missile->Fire(m_player->GetX() + m_player->GetWidth()/2,
			m_player->GetY() - m_player->GetHeight() / 2);
	}

	if (KEYMANAGER->IsOnceKeyDown('Z'))
	{
		m_missileM1->Fire(m_player->GetX() + m_player->GetWidth() / 2,
			m_player->GetY() - 50);
	}
	m_missile->Update();
	m_missileM1->Update();

	Collision();

	_hpBar->SetX(m_player->GetX() + 2);
	_hpBar->SetY(m_player->GetY() + 80);
	_hpBar->SetGauge(_currentHp, _maxHp);

	_hpBar->Update();
}

void Rocket::Render()
{
	m_player->Render(GetMemDC(), m_player->GetX(), m_player->GetY());
	m_missile->Render();
	m_missileM1->Render();
	_hpBar->Render();
}

void Rocket::RemoveMissile(int arrNum)
{
	m_missileM1->RemoveMissile(arrNum);
}

void Rocket::Collision()
{
	for (int i = 0; i < m_missileM1->GetVBullet().size(); i++)
	{
		for (int j = 0; j < _em->GetVMinion().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &m_missileM1->GetVBullet()[i].rc,
				&_em->GetVMinion()[j]->GetRect()))
			{
				m_missileM1->RemoveMissile(i);
				_em->RemoveMinion(j);
				break;
			}
		}
	}
}

void Rocket::HitDamage(float damage)
{
	_currentHp -= damage;
}
//
//void Rocket::Damage()
//{
//	_hpBar->SetGauge(10,0);
//}
