#pragma once
#include "../GameNode.h"
class ProgressBar : public GameNode
{
private :
	RECT _rcProgress; // ü�� �� ��Ʈ
	int _x, _y; // ��ǥ
	int _width; // ü�¹� ���� ���� ( �����Ͽ� HP ǥ�� )

	Image * _progressBarFront; // ü�� �� �� �̹���
	Image * _progressBarBack; // ü�� �� �� �̹���
public:
	ProgressBar();
	~ProgressBar();

	// ü�� �� �ʱ�ȭ ( �� �̹���, �� �̹���, x, y, ���α���, ���α���)
	HRESULT Init(char * frontImage, char * backImage, float x, 
		float y, int width, int height);
	void Release();
	void Update();
	void Render();

	// Progress bar ������ ����
	void SetGauge(float currentGauge, float maxGauge);
	// Progress bar ��ġ
	void SetX(int x) { _x = x; }
	void SetY(int y) { _y = y; }
};

