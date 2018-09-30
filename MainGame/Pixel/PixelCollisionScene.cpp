#include "stdafx.h"
#include "../../stdafx.h"
#include "../../GameNode.h"
#include "PixelCollisionScene.h"

PixelCollisionScene::PixelCollisionScene()
{
}


PixelCollisionScene::~PixelCollisionScene()
{
}

HRESULT PixelCollisionScene::Init()
{
	IMAGEMANAGER->AddImage("산",
		"images/mountain.bmp",800,600,
		true, RGB(255,0,255));
	_ball = IMAGEMANAGER->AddImage("ball",
		"images/ball.bmp", 60, 60, true, RGB(255, 0, 255));
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2 - 30;
	_rc = RectMakeCenter(_x, _y, 
		_ball->GetWidth(),
		_ball->GetHeight());

	// y축으로 탐지 (공 하단에 작은 사각형 만들기 )
	_probeY = _y + _ball->GetHeight() / 2;


	return S_OK;
}

void PixelCollisionScene::Release()
{
}

void PixelCollisionScene::Update()
{
	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
	{
		_x -= 2.0f;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
	{
		_x += 2.0f;
	}
	if (KEYMANAGER->IsOnceKeyDown(VK_UP))
	{
		_y -= 2.0f;
	}
	if (KEYMANAGER->IsOnceKeyDown(VK_DOWN))
	{
		_y += 2.0f;
	}
	// 탐지할 y값도 계속 업데이트
	_probeY = _y + _ball->GetHeight() / 2;

	// 탐지할 y값 범위를 위 아래로 원하는
	// 만큼 검사

	for (int i =  _probeY - 10; i < _probeY + 10 ; i++)
	{
		COLORREF color =
			GetPixel(IMAGEMANAGER->FindImage("산")->getMemDC(),
				_x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		
		// 여기 조건은 본인이 원하는 색을 넣으면 된다.
		if (!(r == 255 && g == 0, b == 255))
		{
			_y = i - _ball->GetHeight() / 2;
			break;
		}
	}
	// 사각형 위치도 계속 업데이트
	_rc = RectMakeCenter(_x, _y,
		_ball->GetWidth(), _ball->GetHeight());
}

void PixelCollisionScene::Render()
{
	IMAGEMANAGER->FindImage("산")->Render(GetMemDC());

	_ball->Render(GetMemDC(),_rc.left,_rc.top);

	// 감지할 사각형
	if (KEYMANAGER->IsToggleKey(VK_F1))
	{
		Rectangle(GetMemDC(), _x, _probeY, _x + 10, _probeY + 10);
	}

}
