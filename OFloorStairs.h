#pragma once

class GameObject;

#include "LevelEdit.h"

class OFloorStairs : public GameObject
{
private :

	//int m_pos;
	//int x, y;
	string goScene;

public:
	OFloorStairs();
	~OFloorStairs();

	HRESULT Init(int pos);
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

	void SetGoScene(string key) { goScene = key; };
};

