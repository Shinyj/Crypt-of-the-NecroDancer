#pragma once
class GameObject;

#include "LevelEdit.h"
#include "WallBase.h"
class OWallGold : public WallBase
{

private :

	//int m_pos;
	//
	//int x, y;

	Image * body;

	int m_frameX;
	int m_frameY;

public:
	OWallGold();
	~OWallGold();

	HRESULT Init(string key, int pos, bool torch);
	void Release();
	void Update();
	void Render();


	virtual void SetXY(POINT camera)
	{
		x += camera.x; y += camera.y;
	}

	virtual int GetX() { return x; }
	virtual int GetY() { return y; }
	int GetPos() { return m_pos; }
};
