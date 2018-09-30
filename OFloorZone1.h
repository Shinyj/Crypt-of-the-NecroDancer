#pragma once
class GameObject;

#include "LevelEdit.h"
class Image;
class OFloorZone1 : public GameObject
{
private :

	//int m_pos;
	//int x, y;

	Image * body;

	bool myPattern;

	int m_frameX;
	int m_frameY;
	
	int m_maxX;
	int m_maxY;

	int count;
	int alph;
public:
	OFloorZone1();
	~OFloorZone1();


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

