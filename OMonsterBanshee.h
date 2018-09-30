#pragma once

#include "MonsterBase.h"
#include "Image\Image.h"

class OMonsterBanshee : public MonsterBase
{
private :
	Image * bodyImage;
	Image * maxHpImage;
	Image * curHpImage;

	bool isPattern;

public:
	OMonsterBanshee();
	~OMonsterBanshee();

	HRESULT Init(string key, int pos);
	void Release();
	void Update();
	void Render();

	void Defence(int num);
	void Anim();
};

