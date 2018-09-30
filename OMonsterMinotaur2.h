#pragma once
#include "MonsterBase.h"
#include "OMonsterMinotaur.h"
class OMonsterMinotaur;

class OMonsterMinotaur2 : public OMonsterMinotaur
{
private :
	MinotaurState m_state;
	
public:
	OMonsterMinotaur2();
	~OMonsterMinotaur2();

	HRESULT Init(string key, int pos);
	void Release();
	void Update();
	void Render();

	void Anim();

	bool SearchTarget();
	void Charged();
	void Sturn();
};

