#pragma once
#include "MonsterBase.h"

class OMonsterSkeleton : public MonsterBase
{
private :

public:
	OMonsterSkeleton();
	~OMonsterSkeleton();

	HRESULT Init(string key, int pos);
	void Release();
	void Update();
	void Render();

	void Anim();
};

