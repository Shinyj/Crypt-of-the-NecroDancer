#pragma once

#include "../../GameNode.h"

class PixelCollisionScene : public GameNode
{
private :
	Image * _ball; // �� �̹���
	RECT _rc; // �浹 �˻� ��

	float _x, _y; // ��ġ
	int _probeY; // �ȼ� Ž���� y��ǥ


public:
	PixelCollisionScene();
	~PixelCollisionScene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

};

