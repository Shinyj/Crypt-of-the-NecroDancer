#pragma once
#include "MonsterBase.h"

class OMonsterSkeletonBlack : public MonsterBase
{
private :
	bool isPattern;
	DIRECTION patternDIr;
public:
	OMonsterSkeletonBlack();
	~OMonsterSkeletonBlack();

	HRESULT Init(string key, int pos);
	void Release();
	void Update();
	void Render();

	void Anim();

	void Defence(int damage);
	void PatternMove();
	
};

