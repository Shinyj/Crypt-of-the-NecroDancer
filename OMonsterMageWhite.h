#pragma once
#include "MonsterBase.h"
class OMonsterMageWhite : public MonsterBase
{
private :

public:
	OMonsterMageWhite();
	~OMonsterMageWhite();

	HRESULT Init(string key, int pos );
	void Release();
	void Update();
	void Render();

	void Anim();

	bool GrapMagic();

};

