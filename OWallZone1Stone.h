#pragma once
#include "WallBase.h"

class OWallZone1Stone : public WallBase
{
private :

public:
	OWallZone1Stone();
	~OWallZone1Stone();

	HRESULT Init(string key, int pos, bool torch);
	void Release();
	void Update();
	void Render();

};

