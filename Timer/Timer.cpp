#include "stdafx.h"
#include "../stdafx.h"
#include "Timer.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
// TimeGetTime 함수를 사용하기 위한 라이브러리 추가
// 윈도우가 시작되고 난 뒤의 시간을 리턴


Timer::Timer()
{
}


Timer::~Timer()
{
}

HRESULT Timer::Init()
{
	// 고성능 타이머 지원 여부를 체크
	// (1/1000000)
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		// 64비트 정수를 사용할 수 있도록 정의한 이유는 
		// 마이크로 세컨드(1/1000000)초 까지 측정하여
		// 좀 더 정확한 시간 값을 저장하기 위함
		_isHardWare = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);
		// 초당 시간 계산 범위
		_timeScale = 1.0f / _periodFrequency;
	}
	else
	{
		_isHardWare = false;
		// 밀리 세컨드 단위의 시간으로 초당 1000번 카운트
		_lastTime = timeGetTime();
		_timeScale = 0.001;
	}
	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPStimeElapsed = 0;
	_worldTime = 0;

	return S_OK;
}
// 현재 시간 계산
void Timer::Tick(float lockFPS)
{
	// 고성능 타이머를 지원하면 
	if (_isHardWare)
	{
		//초 정밀 마이크로 초 단위 계산 1/1000000
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else
	{
		// 지원하지 않으면 time .. 함수를 이용 밀리세컨드 1/1000
		_curTime = timeGetTime();
	}
	// (현 프레임이 끝날 떄 - 이전 프레임이 끝날 때) <- 한 프레임 당 시간
	// 마지막 시간과 현재 시간의 경과량
	_timeElapsed = (_curTime - _lastTime) * _timeScale; // 한프레임당 경과 시간

	if (lockFPS > 0.0f)
	{
		// 고정 프레임의 시간을 만족할 때 까지 루프 시켜라
		// FPS 고정 
		while (_timeElapsed < (1.0f / lockFPS))
		{
			if (_isHardWare) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else _curTime = timeGetTime();

			// 마지막 시간과 현재 시간의 경과량
			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}
	_lastTime = _curTime; // 마지막 시간 기록
	_FPSFrameCount++;     // 자동으로 프레임 카운트 증가
	_FPStimeElapsed += _timeElapsed; // 초당 프레임 시간 경과량 증가
	_worldTime += _timeElapsed; // 전체 시간 경과량 증가

	// 프레임 초기화를 1초마다 진행
	if (_FPStimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPStimeElapsed = 0.0;
	}
}

unsigned long Timer::GetFrameRate(char * str) const
{
	if (str != NULL)
	{
		wsprintf(str, "FPS : %d", _frameRate);
	}
	return _frameRate;
}
