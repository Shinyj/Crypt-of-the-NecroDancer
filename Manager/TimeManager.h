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

	// �������Ӵ� ����ð� �������� 1/60
	float GetElapsedTime() const { return _timer->GetElapsedTime(); }
	// ��ü �ð� ����� ��������
	float GetWorldTime() const { return _timer->GetWorldTime(); }
};

#define TIMER TimeManager::GetSingleton()