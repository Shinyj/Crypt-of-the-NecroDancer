#pragma once

#include "MonsterBase.h"
class OMonsterSlimeBlue : public MonsterBase
{
private :

public:
	OMonsterSlimeBlue();
	~OMonsterSlimeBlue();

	HRESULT Init(string key, int pos);
	void Release();
	void Update();
	void Render();

	void Anim();
};

