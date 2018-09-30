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
	IMAGEMANAGER->AddImage("��",
		"images/mountain.bmp",800,600,
		true, RGB(255,0,255));
	_ball = IMAGEMANAGER->AddImage("ball",
		"images/ball.bmp", 60, 60, true, RGB(255, 0, 255));
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2 - 30;
	_rc = RectMakeCenter(_x, _y, 
		_ball->GetWidth(),
		_ball->GetHeight());

	// y������ Ž�� (�� �ϴܿ� ���� �簢�� ����� )
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
	// Ž���� y���� ��� ������Ʈ
	_probeY = _y + _ball->GetHeight() / 2;

	// Ž���� y�� ������ �� �Ʒ��� ���ϴ�
	// ��ŭ �˻�

	for (int i =  _probeY - 10; i < _probeY + 10 ; i++)
	{
		COLORREF color =
			GetPixel(IMAGEMANAGER->FindImage("��")->getMemDC(),
				_x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		
		// ���� ������ ������ ���ϴ� ���� ������ �ȴ�.
		if (!(r == 255 && g == 0, b == 255))
		{
			_y = i - _ball->GetHeight() / 2;
			break;
		}
	}
	// �簢�� ��ġ�� ��� ������Ʈ
	_rc = RectMakeCenter(_x, _y,
		_ball->GetWidth(), _ball->GetHeight());
}

void PixelCollisionScene::Render()
{
	IMAGEMANAGER->FindImage("��")->Render(GetMemDC());

	_ball->Render(GetMemDC(),_rc.left,_rc.top);

	// ������ �簢��
	if (KEYMANAGER->IsToggleKey(VK_F1))
	{
		Rectangle(GetMemDC(), _x, _probeY, _x + 10, _probeY + 10);
	}

}
