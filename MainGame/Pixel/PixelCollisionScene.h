#pragma once

#include "../../GameNode.h"

class PixelCollisionScene : public GameNode
{
private :
	Image * _ball; // 공 이미지
	RECT _rc; // 충돌 검사 용

	float _x, _y; // 위치
	int _probeY; // 픽셀 탐지할 y좌표


public:
	PixelCollisionScene();
	~PixelCollisionScene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

};

