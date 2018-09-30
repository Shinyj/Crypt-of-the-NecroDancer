#pragma once
class Timer
{
private :
	bool _isHardWare; // 고성능 타이머를 지원하는지 판별
	// 일반 1초 == 1000
	// 고성능 1초 == 1000000

	// 평균 60f == 1s     1f == 1/60s
	float _timeScale; // 시간 경과량
	float _timeElapsed;// 한 프레임당 경과 시간
	
	__int64 _curTime; // 현재 시간
	__int64 _lastTime; // 마지막 시간
	__int64 _periodFrequency; // 시간 주기

	unsigned long _frameRate; // fps
	unsigned long _FPSFrameCount; // FPS 카운트
	float _FPStimeElapsed; // 프레임 사이의 시간 0 59
	float _worldTime; // 전체 시간 경과량

public:
	Timer();
	~Timer();

	// 타이머 초기화
	HRESULT Init();
	// 현재 시간 계싼
	void Tick(float lockFPS = 0.0f);
	// 현재 FPS 가져오기
	unsigned long GetFrameRate(char * str = nullptr) const;
	// 한 프레임당 경과 시간
	float GetElapsedTime() const { return _timeElapsed; }
	// 전체 경과 시간 가져오기
	float GetWorldTime() const { return _worldTime; }

};

