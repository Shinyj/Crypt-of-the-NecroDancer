#pragma once

class GameObject;

#include "LevelEdit.h"
#include "WallBase.h"
class OWallDoor : public WallBase
{
private :
	//int m_pos;
	//int x, y;
	Image * mainImage2;
	bool isVertical;

public:
	OWallDoor();
	~OWallDoor();

	HRESULT Init(int pos,bool isVertical);
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

