#pragma once
#include "MonsterBase.h"

enum MinotaurState
{
	MINO_IDLE,
	MINO_CHARGE,
	MINO_STURN
};

class OMonsterMinotaur : public MonsterBase
{
private :
	MinotaurState m_state;

public:
	OMonsterMinotaur();
	~OMonsterMinotaur();

	HRESULT Init(string key, int pos);
	void Release();
	void Update();
	void Render();

	void Anim();

	bool SearchTarget();
	void Charged();
	void Sturn();
};

