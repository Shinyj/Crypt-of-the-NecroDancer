#pragma once
#include "MonsterBase.h"

class OMonsterBatGreen : public MonsterBase
{
private :

public:
	OMonsterBatGreen();
	~OMonsterBatGreen();

	HRESULT Init(string key, int pos);
	void Release();
	void Update();
	void Render();

	void Anim();
};

