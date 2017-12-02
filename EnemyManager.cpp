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
			ufo = new Minion; //�̴Ͼ��� ���ʹ̸� ��ӹް� �ֱ⋚���� �̷��� ���൵ �����ϴ�.
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
			// ���ʹ��� �Ѿ��� �÷��̾��� ��ǥ�� �߻�ǵ��� �÷��̾� ��ġ ������ ����
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
	// ���ϰ� ������ �Ѿ��� �浹�ƴ��� �˱� ���ؼ� ���
	// ���� ������ ��Ʈ �Լ��� ȣ���Ͽ� �������� ����
}
