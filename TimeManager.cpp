#include "stdafx.h"
#include "TimeManager.h"


TimeManager::TimeManager()
{
}


TimeManager::~TimeManager()
{
}

HRESULT TimeManager::Init()
{
	_timer = new Timer;
	_timer->Init();
	return S_OK;
}

void TimeManager::Release()
{
	if (_timer != nullptr)
	{
		SAFE_DELETE(_timer);
		_timer = nullptr;
	}
}

void TimeManager::Update(float lock)
{
	if (_timer != nullptr)
	{
		_timer->Tick(lock);
	}
}

void TimeManager::Render(HDC hdc)
{
	char str[256];
	string strFrame;
	// 글자 배경 모드
	SetBkMode(hdc, TRANSPARENT);
	// 글자 색상
	SetTextColor(hdc, RGB(0, 0, 255));

#ifdef _DEBUG
	if (_timer != nullptr)
	{
		// FPS
		sprintf(str, "FPS : %d", _timer->GetFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
		// 전체 경과 시간
		sprintf(str, "WorldTime : %f", _timer->GetWorldTime());
		TextOut(hdc, 0, 20, str, strlen(str));
		// 한 프레임당 경과 시간
		sprintf(str, "ElapsedTime : %f", _timer->GetElapsedTime());
		TextOut(hdc, 0, 40, str, strlen(str));
	}
#else
	if (_timer != nullptr)
	{
		// FPS
		sprintf(str, "FPS : %d", _timer->GetFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}
#endif // _DEBUG
}
/*
ifdef  <- ~ 일때 이렇게 작성해 달라

#else  <- 그게 아닐때는 이렇게 해달라



*/