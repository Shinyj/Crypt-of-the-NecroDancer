#pragma once
#include "MonsterBase.h"

class OMonsterBanshee2 : public MonsterBase
{
private :

	bool isPattern;
public:
	OMonsterBanshee2();
	~OMonsterBanshee2();

	HRESULT Init(string key,int pos);
	void Release();
	void Update();
	void Render();

	void Defence(int num);
	void Anim();
};

