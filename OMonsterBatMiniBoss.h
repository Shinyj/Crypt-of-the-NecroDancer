#pragma once
#include "MonsterBase.h"

class OMonsterBatMiniBoss : public MonsterBase
{
private :

public:
	OMonsterBatMiniBoss();
	~OMonsterBatMiniBoss();

	HRESULT Init(string key, int pos);
	void Release();
	void Update();
	void Render();

	void Anim();
};

