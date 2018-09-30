#pragma once
#include "MonsterBase.h"
class OMonsterMageBlack : public MonsterBase
{
private :

public:
	OMonsterMageBlack();
	~OMonsterMageBlack();

	HRESULT Init(string key, int pos);
	void Release();
	void Update();
	void Render();

	void Anim();

	bool GrapMagic();
};

