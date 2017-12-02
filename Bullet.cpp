#include "stdafx.h"
#include "Bullet.h"
#include <memory>



HRESULT Missile::Init(int bulletMax, float range)
{
	// ��Ÿ� �ʱ�ȭ
	_range = range;
	// �Ѿ� ����ü �ʱ�ȭ
	for (int i = 0; i < bulletMax; i++)
	{
		// �Ѿ� ����ü ����
		tagBullet bullet;
		/*bullet.bulletImage = NULL;
		bullet.fire = false;
		bullet.x = 0;
		bullet.y = 0; */
		// �̷��� �ʱ�ȭ �ϱ� �Ұ����� ������ ���� ����� ���� ��ü�� �Ʒ��� ���� �ʱ�ȭ
		ZeroMemory(&bullet, sizeof(tagBullet)); // ���� �̾߱��ϸ� 0���� �ʱ�ȭ
				 //�ʱ�ȭ����� �ּ� , �׸��� �� ������ �� ���ڷ� �޾Ƽ� 0���� �ʱ�ȭ���ش�
		bullet.bulletImage = new Image;
		bullet.bulletImage->Init("images/missile3.bmp",
			26,124,true,RGB(255,0,255));
		bullet.speed = 5.0f;
		bullet.fire = false;
		// ���Ϳ� ��Ƽ� �̻����� ����
		_vBullet.push_back(bullet); // ���Ϳ� ��Ƽ� ��� ������ ���
	}
	return S_OK;
}

void Missile::Release()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		SAFE_DELETE(_vBullet[i].bulletImage);
	}
	_vBullet.clear();
}

void Missile::Update()
{
	Move();
}

void Missile::Render()
{
	_viBullet = _vBullet.begin();
	// ������ ��� ���� ������ ������� �ݺ� 
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;

		_viBullet->bulletImage->Render(GetMemDC(),
			_viBullet->rc.left, _viBullet->rc.top);
	}
}

// �Ѿ� �߻�
void Missile::Fire(float x, float y)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet) // �̷��� �ϸ� _vBullet�� ó������ ������ �����µ� bullet���� �� ��ҿ� ����
	{
		if (_viBullet->fire) continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->bulletImage->GetWidth(),
			_viBullet->bulletImage->GetHeight());
		break;
	}
	// �߰�
	//int num[20];
	//array   �굵 ���������� �迭 
	//std::unique_ptr<int> // ��� ������ ( �޸� ����� �߰��ؾ��� )
	//unique_ptr<int> p;
	//p.get(); // p�� ������ �ִ� �ּҰ��� �� ������
	
}
// �Ѿ� ����
void Missile::Move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;

		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->GetWidth(), 
			_viBullet->bulletImage->GetHeight());
		// �Ѿ��� ��Ÿ����� Ŀ���� ��
		if (_range < UTIL::GetDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			_viBullet->fire = false;
		}
	}
}

///////////////////////// ���� �Ѿ�  Bullet Ŭ���� �Լ���  /////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

HRESULT Bullet::Init(char * imageName, int bulletMax, int range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void Bullet::Release()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		SAFE_DELETE(_vBullet[i].bulletImage);
	}
	_vBullet.clear();
}

void Bullet::Update()
{
	Move();
}

void Bullet::Render()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->Render(
			GetMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

void Bullet::Fire(float x, float y, float angle, float speed)
{
	// �߻��� �� �ִ� �Ѿ��� �� ���� ���� ������ �뷮�� ũ�� �� ��� �ؾ���
	if (_bulletMax <= _vBullet.size()) return;
	// �Ѿ� ����ü ����
	tagBullet bullet;
	ZeroMemory(&bullet,sizeof(tagBullet));
	bullet.bulletImage = new Image;
	bullet.bulletImage = IMAGEMANAGER->FindImage(_imageName);
	bullet.angle = angle;
	bullet.speed = speed;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->GetWidth(), bullet.bulletImage->GetHeight());
	// ���Ϳ� �־��ֱ�
	_vBullet.push_back(bullet);
}

void Bullet::Move()
{
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += (-sinf(_viBullet->angle)) * _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x , _viBullet->y, 
			_viBullet->bulletImage->GetWidth(), _viBullet->bulletImage->GetHeight());
		
		//�߻� �� �Ÿ��� ��Ÿ����� �������
		if (_range < GetDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			//SAFE_DELETE(_viBullet->bulletImage);
			_viBullet = _vBullet.erase(_viBullet); // ���� �Ŀ� ���ͷ����Ϳ� �ٽ� �־���� ��
			// ��ũ�� ����Ʈ ���� ���� ó��
		}
		else ++_viBullet;

	}
}

void Bullet::RemoveMissile(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}
///////////////////////////// �ʻ�� MissileM1 ///////////////////////
//////////////////////////////////////////////////////////////////////

HRESULT MissileM1::Init(int bulletMax, int range)
{
	_bulletMax = bulletMax;
	_range = range;
	return S_OK;
}

void MissileM1::Release()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		SAFE_DELETE(_vBullet[i].bulletImage);
	}
	_vBullet.clear();
}

void MissileM1::Update()
{
	Move();
}

void MissileM1::Render()
{
	// �׸��� �κ�
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->FrameRender(GetMemDC(),
			_viBullet->rc.left, _viBullet->rc.top,
			_viBullet->bulletImage->GetFrameX(), 0);
		_viBullet->count++;
		
		// ������ �����ϴ� �κ�
		if (_viBullet->count % 10 == 0)
		{
			_viBullet->bulletImage->SetFrameX(_viBullet->bulletImage->GetFrameX() + 1);
			if (_viBullet->bulletImage->GetFrameX() >=
				_viBullet->bulletImage->GetMaxFrameX())
			{
				_viBullet->bulletImage->SetFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

void MissileM1::Fire(float x, float y)
{
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.bulletImage = new Image;
	bullet.bulletImage->Init(
	"images/missile.bmp",416,64,13,1,true,RGB(255,0,255));
	bullet.speed = 5.0f;

	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->GetFrameWidth(),
		bullet.bulletImage->GetFrameHeight());

	_vBullet.push_back(bullet);

}

void MissileM1::Move()
{
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->GetFrameWidth(), 
			_viBullet->bulletImage->GetFrameHeight());

		// �߻� �� �Ÿ��� ��Ÿ����� �������
		if (_range < GetDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			SAFE_DELETE(_viBullet->bulletImage);
			_viBullet = _vBullet.erase(_viBullet); // ���� �Ŀ� ���ͷ����Ϳ� �ٽ� �־���� ��
												   // ��ũ�� ����Ʈ ���� ���� ó��
		}
		else ++_viBullet;

	}
}
void MissileM1::RemoveMissile(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}