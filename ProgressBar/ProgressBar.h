#pragma once
#include "../GameNode.h"
class ProgressBar : public GameNode
{
private :
	RECT _rcProgress; // 체력 바 렉트
	int _x, _y; // 좌표
	int _width; // 체력바 가로 길이 ( 조정하여 HP 표현 )

	Image * _progressBarFront; // 체력 바 앞 이미지
	Image * _progressBarBack; // 체력 바 뒤 이미지
public:
	ProgressBar();
	~ProgressBar();

	// 체력 바 초기화 ( 앞 이미지, 뒷 이미지, x, y, 가로길이, 세로길이)
	HRESULT Init(char * frontImage, char * backImage, float x, 
		float y, int width, int height);
	void Release();
	void Update();
	void Render();

	// Progress bar 게이지 세팅
	void SetGauge(float currentGauge, float maxGauge);
	// Progress bar 위치
	void SetX(int x) { _x = x; }
	void SetY(int y) { _y = y; }
};

