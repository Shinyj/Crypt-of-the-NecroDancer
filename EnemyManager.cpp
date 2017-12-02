#include "stdafx.h"
#include "EnemyManager.h"
#include "Rocket.h"


HRESULT EnemyManager::Init()
{
	this->SetMinion();

	_bullet = new Bullet;
	_bullet->Init("bullet", 15, 1000);
	return S_OK;
}

void EnemyManager::Release()
{
	_bullet->Release();
	SAFE_DELETE(_bullet);

}

void EnemyManager::Update()
{
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->Update();
	}
	_bullet->Update();

	this->MinionBulletFire();
	Collision();
}

void EnemyManager::Render()
{
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->Render();
	}
	_bullet->Render();
}

void EnemyManager::SetMinion()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			Enemy* ufo;
			ufo = new Minion; //미니언이 에너미를 상속받고 있기떄문에 이렇게 해줘도 가능하다.
			ufo->Init("ufo", PointMake(100 + j * 180, 100 + i * 100));
			_vMinion.push_back(ufo);
		}
	}
}

void EnemyManager::MinionBulletFire()
{
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->BulletCountFire())
		{
			RECT rc = (*_viMinion)->GetRect();
			/*_bullet->Fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + 30, -PI_2, 5.0f);*/
			_bullet->Fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.bottom - rc.top) / 2,
				GetAngle(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.bottom - rc.top) / 2,
					_rocket->GetRocketImage()->GetX() +
					_rocket->GetRocketImage()->GetWidth() / 2,
					_rocket->GetRocketImage()->GetY()), 5.0f);
			// 에너미의 총알이 플레이어의 좌표로 발사되도록 플레이어 위치 정보를 받음
		}
	}
}

void EnemyManager::RemoveMinion(int arrNum)
{
	_vMinion.erase(_vMinion.begin() + arrNum);
}

void EnemyManager::Collision()
{
	for (int i = 0; i < _bullet->GetVBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_bullet->GetVBullet()[i].rc,
			&_rocket->GetRocketImage()->GetBoundingBox()))
		{
			_bullet->RemoveMissile(i);
			_rocket->HitDamage(10);
		}
	}
	// 로켓과 본인의 총알이 충돌됐는지 알기 위해서 사용
	// 로켓 내부의 히트 함수를 호출하여 데미지를 입힘
}
