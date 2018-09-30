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
	IMAGEMANAGER->AddImage("배경", "images/배경.bmp", WINSIZEX * 2, WINSIZEY);
	IMAGEMANAGER->AddImage("카메라", "images/카메라.bmp", WINSIZEX / 10, WINSIZEY / 10, true, RGB(255,0,255));
	IMAGEMANAGER->AddImage("미니맵", "images/배경.bmp", WINSIZEX / 5, WINSIZEY / 10);
	IMAGEMANAGER->AddImage("미니캐릭", "images/mini.bmp", 3, 4, true, RGB(255, 0, 255));
	_megaman = IMAGEMANAGER->AddFrameImage("메가맨", "images/megaman.bmp", 640, 720, 9, 8, true, RGB(254, 0, 254));
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

	//_count += TIMER->GetElapsedTime(); // 현재 시간을 받아오는 함수
	// 타이머를 이용한 애니메이션
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
	IMAGEMANAGER->Render("배경", GetMemDC(), _camera, 0);
	IMAGEMANAGER->Render("미니맵", GetMemDC(), 700, 50);
	IMAGEMANAGER->Render("미니캐릭", GetMemDC(),703 + _megaman->GetX() / 10 - _camera / 10, 
		50 + _megaman->GetY() / 10);
	IMAGEMANAGER->Render("카메라", GetMemDC(), 700 - _camera / 10, 50);
	_megaman->FrameRender(GetMemDC(), _megaman->GetX(), _megaman->GetY(),
		_megaman->GetFrameX(), _megaman->GetFrameY());
}
