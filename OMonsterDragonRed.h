#pragma once
#include "MonsterBase.h"

enum DSTATE
{
	D_IDLE,
	D_PREFIRE,
	D_FIRE
};

class OMonsterDragonRed : public MonsterBase
{
private :

	Image * fire0;
	Image * fire1;

	DSTATE m_state;
	bool isFire;
	
	bool reload = true;

	bool fireRight;

	int fireWay[50];
	int fireWayY;
	int fireFrameX = 0;

public:
	OMonsterDragonRed();
	~OMonsterDragonRed();

	HRESULT Init(string key, int pos);
	void Release();
	void Update();
	void Render();

	void Anim();

	void JumpMove();

	bool SearchTarget();

	void Fire();

	void FireRender();
};

