#include "stdafx.h"
#include "../stdafx.h"
#include "Timer.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
// TimeGetTime �Լ��� ����ϱ� ���� ���̺귯�� �߰�
// �����찡 ���۵ǰ� �� ���� �ð��� ����


Timer::Timer()
{
}


Timer::~Timer()
{
}

HRESULT Timer::Init()
{
	// ���� Ÿ�̸� ���� ���θ� üũ
	// (1/1000000)
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		// 64��Ʈ ������ ����� �� �ֵ��� ������ ������ 
		// ����ũ�� ������(1/1000000)�� ���� �����Ͽ�
		// �� �� ��Ȯ�� �ð� ���� �����ϱ� ����
		_isHardWare = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);
		// �ʴ� �ð� ��� ����
		_timeScale = 1.0f / _periodFrequency;
	}
	else
	{
		_isHardWare = false;
		// �и� ������ ������ �ð����� �ʴ� 1000�� ī��Ʈ
		_lastTime = timeGetTime();
		_timeScale = 0.001;
	}
	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPStimeElapsed = 0;
	_worldTime = 0;

	return S_OK;
}
// ���� �ð� ���
void Timer::Tick(float lockFPS)
{
	// ���� Ÿ�̸Ӹ� �����ϸ� 
	if (_isHardWare)
	{
		//�� ���� ����ũ�� �� ���� ��� 1/1000000
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else
	{
		// �������� ������ time .. �Լ��� �̿� �и������� 1/1000
		_curTime = timeGetTime();
	}
	// (�� �������� ���� �� - ���� �������� ���� ��) <- �� ������ �� �ð�
	// ������ �ð��� ���� �ð��� �����
	_timeElapsed = (_curTime - _lastTime) * _timeScale; // �������Ӵ� ��� �ð�

	if (lockFPS > 0.0f)
	{
		// ���� �������� �ð��� ������ �� ���� ���� ���Ѷ�
		// FPS ���� 
		while (_timeElapsed < (1.0f / lockFPS))
		{
			if (_isHardWare) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else _curTime = timeGetTime();

			// ������ �ð��� ���� �ð��� �����
			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}
	_lastTime = _curTime; // ������ �ð� ���
	_FPSFrameCount++;     // �ڵ����� ������ ī��Ʈ ����
	_FPStimeElapsed += _timeElapsed; // �ʴ� ������ �ð� ����� ����
	_worldTime += _timeElapsed; // ��ü �ð� ����� ����

	// ������ �ʱ�ȭ�� 1�ʸ��� ����
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
