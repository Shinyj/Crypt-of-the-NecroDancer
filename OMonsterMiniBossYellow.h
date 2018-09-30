#pragma once
#include "MonsterBase.h"
class OMonsterMiniBossYellow : public MonsterBase
{
private :

public:
	OMonsterMiniBossYellow();
	~OMonsterMiniBossYellow();

	HRESULT Init(string key, int pos);
	void Release();
	void Update();
	void Render();

	void Anim();
};

