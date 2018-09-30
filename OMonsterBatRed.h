#pragma once
#include "MonsterBase.h"
class OMonsterBatRed : public MonsterBase
{
private :

public:
	OMonsterBatRed();
	~OMonsterBatRed();

	HRESULT Init(string key, int pos);
	void Release();
	void Update();
	void Render();

	void Anim();
};

