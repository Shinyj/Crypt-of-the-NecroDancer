#pragma once
class GameObject;
#include "GameObject.h"
class OFloorBoss : public GameObject
{
private :

	Image * body;

	bool myPattern;

	int m_frameX;
	int m_frameY;

	int count;

	int alph;

public:
	OFloorBoss();
	~OFloorBoss();

	HRESULT Init(int pos);
	void Release();
	void Update();
	void Render();

	void CheckPattern(int pos);
	void Anim();

	virtual void SetXY(POINT camera)
	{
		x += camera.x; y += camera.y;
	}

	virtual int GetX() { return x; }
	virtual int GetY() { return y; }
};

