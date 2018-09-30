#pragma once
#include "WallBase.h"

class OWallZone2Stone : public WallBase
{
private :

public:
	OWallZone2Stone();
	~OWallZone2Stone();

	HRESULT Init(string key, int pos, bool torch);
	void Release();
	void Update();
	void Render();
};

