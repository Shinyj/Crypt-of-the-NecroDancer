#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}
HRESULT Enemy::Init()
{
	return S_OK;
}
HRESULT Enemy::Init(const char* imageName, POINT position)
{
	//프레임 초기화
	_count = 0;
	_currentFrameX = _currentFrameY = 0;
	_fireCount = 0;
	_rndFireCount = RND->GetFromInto(1, 1000);

	//이미지 RECT
	_image = IMAGEMANAGER->FindImage(imageName);
	_rc = RectMakeCenter(position.x, position.y,
		_image->GetFrameWidth(), _image->GetFrameHeight());
	return S_OK;
}
void Enemy::Release()
{
	SAFE_DELETE(_image);
}
void Enemy::Update()
{
	Move();
	Animation();
}
void Enemy::Render()
{
	Draw();
}

void Enemy::Move()
{
	//나중에
}
void Enemy::Draw()
{
	_image->FrameRender(GetMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}
void Enemy::Animation()
{
	_count++;
	if (_count % 3 == 0)
	{
		_image->SetFrameX(_currentFrameX);
		_currentFrameX++;
		if (_currentFrameX >= _image->GetMaxFrameX())
		{
			_currentFrameX = 0;
		}
	}
}

bool Enemy::BulletCountFire()
{
	_fireCount++;
	if (_fireCount % _rndFireCount == 0)
	{
		_rndFireCount = RND->GetFromInto(1, 1000);
		_fireCount = 0;
		return true;
	}
	return false;
}