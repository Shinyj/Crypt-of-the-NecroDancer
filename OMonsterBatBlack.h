#pragma once
#include "MonsterBase.h"

class OMonsterBatBlack : public MonsterBase
{
private :

public:
	OMonsterBatBlack();
	~OMonsterBatBlack();

	HRESULT Init(string key, int pos);
	void Release();
	void Update();
	void Render();

	void Anim();

};

