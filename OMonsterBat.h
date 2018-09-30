#pragma once
#include "MonsterBase.h"
class OMonsterBat : public MonsterBase
{
private :

public:
	OMonsterBat();
	~OMonsterBat();

	HRESULT Init(string key, int pos);
	void Release();
	void Update();
	void Render();

	void Anim();
};

