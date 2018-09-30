#pragma once

#include "MonsterBase.h"

class OMonsterSkeletonYellow : public MonsterBase
{
private :
	Image * headImage;
	bool isPattern;
	DIRECTION patternDIr;
public:
	OMonsterSkeletonYellow();
	~OMonsterSkeletonYellow();

	HRESULT Init(string key, int pos);
	void Release();
	void Update();
	void Render();
	
	void Anim();

	void Defence(int damage);

	void PatternMove();

};

