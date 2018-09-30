#pragma once
#include "WallBase.h"
class OWallZone2Dirt : public WallBase
{
private :

public:
	OWallZone2Dirt();
	~OWallZone2Dirt();

	HRESULT Init(string key, int pos, bool torch);
	void Release();
	void Update();
	void Render();
};

