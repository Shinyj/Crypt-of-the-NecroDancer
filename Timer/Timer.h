#pragma once
class Timer
{
private :
	bool _isHardWare; // ���� Ÿ�̸Ӹ� �����ϴ��� �Ǻ�
	// �Ϲ� 1�� == 1000
	// ���� 1�� == 1000000

	// ��� 60f == 1s     1f == 1/60s
	float _timeScale; // �ð� �����
	float _timeElapsed;// �� �����Ӵ� ��� �ð�
	
	__int64 _curTime; // ���� �ð�
	__int64 _lastTime; // ������ �ð�
	__int64 _periodFrequency; // �ð� �ֱ�

	unsigned long _frameRate; // fps
	unsigned long _FPSFrameCount; // FPS ī��Ʈ
	float _FPStimeElapsed; // ������ ������ �ð� 0 59
	float _worldTime; // ��ü �ð� �����

public:
	Timer();
	~Timer();

	// Ÿ�̸� �ʱ�ȭ
	HRESULT Init();
	// ���� �ð� ���
	void Tick(float lockFPS = 0.0f);
	// ���� FPS ��������
	unsigned long GetFrameRate(char * str = nullptr) const;
	// �� �����Ӵ� ��� �ð�
	float GetElapsedTime() const { return _timeElapsed; }
	// ��ü ��� �ð� ��������
	float GetWorldTime() const { return _worldTime; }

};

