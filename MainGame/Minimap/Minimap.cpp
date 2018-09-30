#include "stdafx.h"
#include "../../stdafx.h"
#include "Minimap.h"
#include "../../GameNode.h"

Minimap::Minimap()
{
}


Minimap::~Minimap()
{
}

HRESULT Minimap::Init()
{
	IMAGEMANAGER->AddImage("���", "images/���.bmp", WINSIZEX * 2, WINSIZEY);
	IMAGEMANAGER->AddImage("ī�޶�", "images/ī�޶�.bmp", WINSIZEX / 10, WINSIZEY / 10, true, RGB(255,0,255));
	IMAGEMANAGER->AddImage("�̴ϸ�", "images/���.bmp", WINSIZEX / 5, WINSIZEY / 10);
	IMAGEMANAGER->AddImage("�̴�ĳ��", "images/mini.bmp", 3, 4, true, RGB(255, 0, 255));
	_megaman = IMAGEMANAGER->AddFrameImage("�ް���", "images/megaman.bmp", 640, 720, 9, 8, true, RGB(254, 0, 254));
	_megaman->SetFrameX(0);
	_megaman->SetX(WINSIZEX / 2);
	_megaman->SetY(WINSIZEY / 2 + 80);

	_alpha = 0;
	_index = 0;
	_count = 1;
	_isLeft = false;
	_camera = 0;

	return S_OK;
}

void Minimap::Release()
{
	SAFE_DELETE(_megaman);
}

void Minimap::Update()
{
	if (KEYMANAGER->IsStayKeyDown(VK_LEFT) && _megaman->GetX() > 0 )
	{
		_isLeft = true;
		_ps = PS_RUN;
		if (_megaman->GetX() >= WINSIZEX / 2)
			_megaman->SetX(_megaman->GetX() - 5);
		else if (_camera < 0) _camera += 5;
		else _megaman->SetX(_megaman->GetX() - 5);
	}
	
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT) && _megaman->GetX() + 70 < WINSIZEX )
	{
		_isLeft = false;
		_ps = PS_RUN;
		if (_megaman->GetX() <= WINSIZEX / 2)
			_megaman->SetX(_megaman->GetX() + 5);
		else if (_camera > -1000) _camera -= 5;
		else _megaman->SetX(_megaman->GetX() + 5);
	}

	if (!KEYMANAGER->IsStayKeyDown(VK_LEFT) && !KEYMANAGER->IsStayKeyDown(VK_RIGHT))
	{
		_ps = PS_IDLE;
	}

	//_count += TIMER->GetElapsedTime(); // ���� �ð��� �޾ƿ��� �Լ�
	// Ÿ�̸Ӹ� �̿��� �ִϸ��̼�
	_count++;
	if (_isLeft == true)
	{
		if (_ps == PS_IDLE)
		{
			_megaman->SetFrameX(0);
			_megaman->SetFrameY(5);
		}
		if (_ps == PS_RUN)
		{
			_megaman->SetFrameY(1);
			if (_count % 6 == 0)
			{
				_index--;
				if (_index < 0)
				{
					_index = 8;
				}
				_megaman->SetFrameX(_index);
				_count = 0;
			}
		}
	}
	else
	{
		if (_ps == PS_IDLE)
		{
			_megaman->SetFrameX(0);
			_megaman->SetFrameY(4);
		}
		if (_ps == PS_RUN)
		{
			_megaman->SetFrameY(0);
			if (_count % 6  == 0 )
			{
				_index++;
				if (_index > 8)
				{
					_index = 0;
				}
				_megaman->SetFrameX(_index);
				_count = 0;
			}
		}
	}
}

void Minimap::Render()
{
	IMAGEMANAGER->Render("���", GetMemDC(), _camera, 0);
	IMAGEMANAGER->Render("�̴ϸ�", GetMemDC(), 700, 50);
	IMAGEMANAGER->Render("�̴�ĳ��", GetMemDC(),703 + _megaman->GetX() / 10 - _camera / 10, 
		50 + _megaman->GetY() / 10);
	IMAGEMANAGER->Render("ī�޶�", GetMemDC(), 700 - _camera / 10, 50);
	_megaman->FrameRender(GetMemDC(), _megaman->GetX(), _megaman->GetY(),
		_megaman->GetFrameX(), _megaman->GetFrameY());
}
