#pragma once

#include "../Timer/Timer.h"

class SingletonBase;
class Timer;

class TimeManager : public singletonBase<TimeManager>
{
private :
	Timer * _timer;
public:
	TimeManager();
	~TimeManager();

	HRESULT Init();
	void Release();
	void Update(float lock);
	void Render(HDC hdc);

	// 한프레임당 경과시간 가져오기 1/60
	float GetElapsedTime() const { return _timer->GetElapsedTime(); }
	// 전체 시간 경과량 가져오기
	float GetWorldTime() const { return _timer->GetWorldTime(); }
};

#define TIMER TimeManager::GetSingleton()