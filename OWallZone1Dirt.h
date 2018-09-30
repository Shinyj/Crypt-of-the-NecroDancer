#pragma once
#include "WallBase.h"

class OWallZone1Dirt : public WallBase
{
private :

public:
	OWallZone1Dirt();
	~OWallZone1Dirt();

	HRESULT Init(string key, int pos, bool isTorch);
	void Release();
	void Update();
	void Render();
};

