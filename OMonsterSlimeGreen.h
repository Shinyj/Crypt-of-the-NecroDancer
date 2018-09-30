#pragma once

#include "MonsterBase.h"
class OMonsterSlimeGreen : public MonsterBase
{
private :

public:
	OMonsterSlimeGreen();
	~OMonsterSlimeGreen();

	HRESULT Init(string key, int pos);
	void Release();
	void Update();
	void Render();

	void Anim();
};

