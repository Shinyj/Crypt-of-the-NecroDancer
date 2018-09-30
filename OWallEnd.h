#pragma once
#include "WallBase.h"
class OWallEnd : public WallBase
{
private :
	

public:
	OWallEnd();
	~OWallEnd();

	HRESULT Init(string key, int pos);

	void Release();
	void Update();
	void Render();
};

