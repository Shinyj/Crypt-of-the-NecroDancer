#pragma once
#include "GameObject.h"
class WallBase : public GameObject
{
protected :
	int Hard; // 단단한 정도

	Image * torchImage;
	// int light; 
	// int sight;
	int torchFrame;
	int torchCount;
public:
	WallBase();
	~WallBase();

	HRESULT Init(string key, int pos, bool isTorch);
	void Release();
	void Update();
	void Render();

	bool CanCrush(int hard);

	void RayCast();
};

