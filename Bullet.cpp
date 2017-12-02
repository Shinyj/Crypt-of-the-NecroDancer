#include "stdafx.h"
#include "Bullet.h"
#include <memory>



HRESULT Missile::Init(int bulletMax, float range)
{
	// 사거리 초기화
	_range = range;
	// 총알 구조체 초기화
	for (int i = 0; i < bulletMax; i++)
	{
		// 총알 구조체 선언
		tagBullet bullet;
		/*bullet.bulletImage = NULL;
		bullet.fire = false;
		bullet.x = 0;
		bullet.y = 0; */
		// 이렇게 초기화 하기 불가능할 정도로 많은 멤버를 가진 객체는 아래와 같이 초기화
		ZeroMemory(&bullet, sizeof(tagBullet)); // 쉽게 이야기하면 0으로 초기화
				 //초기화대상의 주소 , 그리고 그 사이즈 를 인자로 받아서 0으로 초기화해준다
		bullet.bulletImage = new Image;
		bullet.bulletImage->Init("images/missile3.bmp",
			26,124,true,RGB(255,0,255));
		bullet.speed = 5.0f;
		bullet.fire = false;
		// 벡터에 담아서 미사일을 관리
		_vBullet.push_back(bullet); // 벡터에 담아서 계쏙 돌려서 사용
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
	// 벡터의 비긴 부터 벡터의 엔드까지 반복 
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;

		_viBullet->bulletImage->Render(GetMemDC(),
			_viBullet->rc.left, _viBullet->rc.top);
	}
}

// 총알 발사
void Missile::Fire(float x, float y)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet) // 이렇게 하면 _vBullet을 처음부터 끝까지 돌리는데 bullet으로 매 요소에 접근
	{
		if (_viBullet->fire) continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->bulletImage->GetWidth(),
			_viBullet->bulletImage->GetHeight());
		break;
	}
	// 추가
	//int num[20];
	//array   얘도 마찬가지로 배열 
	//std::unique_ptr<int> // 얘는 포인터 ( 메모리 헤더를 추가해야함 )
	//unique_ptr<int> p;
	//p.get(); // p가 가지고 있는 주소값을 알 수있음
	
}
// 총알 무브
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
		// 총알이 사거리보다 커졌을 때
		if (_range < UTIL::GetDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			_viBullet->fire = false;
		}
	}
}

///////////////////////// 공통 총알  Bullet 클래스 함수들  /////////////////////////////
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
	// 발사할 수 있는 총알의 수 보다 현재 벡터의 용량이 크면 못 쏘게 해야함
	if (_bulletMax <= _vBullet.size()) return;
	// 총알 구조체 선언
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
	// 벡터에 넣어주기
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
		
		//발사 후 거리가 사거리보다 길어지면
		if (_range < GetDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			//SAFE_DELETE(_viBullet->bulletImage);
			_viBullet = _vBullet.erase(_viBullet); // 삭제 후에 이터레이터에 다시 넣어줘야 함
			// 링크드 리스트 삭제 연산 처럼
		}
		else ++_viBullet;

	}
}

void Bullet::RemoveMissile(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}
///////////////////////////// 필살기 MissileM1 ///////////////////////
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
	// 그리는 부분
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->FrameRender(GetMemDC(),
			_viBullet->rc.left, _viBullet->rc.top,
			_viBullet->bulletImage->GetFrameX(), 0);
		_viBullet->count++;
		
		// 프레임 변경하는 부분
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

		// 발사 후 거리가 사거리보다 길어지면
		if (_range < GetDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			SAFE_DELETE(_viBullet->bulletImage);
			_viBullet = _vBullet.erase(_viBullet); // 삭제 후에 이터레이터에 다시 넣어줘야 함
												   // 링크드 리스트 삭제 연산 처럼
		}
		else ++_viBullet;

	}
}
void MissileM1::RemoveMissile(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}