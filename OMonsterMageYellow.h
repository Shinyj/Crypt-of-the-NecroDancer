#pragma once
#include "MonsterBase.h"

class OMonsterMageYellow : public MonsterBase
{
private :
	Image * headImage;
	bool isPattern;
	DIRECTION patternDIr;

public:
	OMonsterMageYellow();
	~OMonsterMageYellow();

	HRESULT Init(string key, int pos);
	void Release();;
	void Update();
	void Render();

	void Anim();

	bool GrapMagic();

};

