#pragma once
#include "MonsterBase.h"

class OMonsterKingconga;

enum ZOMBIE_STATE
{
	Z_IDLE,
	Z_HEAD,
	Z_ALONE
};
enum ZOMBIE_DIRECTION
{
	Z_UP,
	Z_DOWN,
	Z_LEFT,
	Z_RIGHT
};
class OMonsterZombie : public MonsterBase
{
private :

	int color;
	bool isJump;
	ZOMBIE_STATE m_state;
	
	bool isZombieUpdate;
	OMonsterKingconga * king;
	OMonsterZombie * nextZombie;
	OMonsterZombie * beforeZombie;

	int nextPos;
public:
	OMonsterZombie();
	~OMonsterZombie();

	HRESULT Init(string key, int pos);
	void Release();
	void Update();
	void Render();

	void SetNextNULL();
	void SetBeforeNULL();

	void SetNext(OMonsterZombie * obj);
	void SetBefore(OMonsterZombie * obj);

	void Anim();
	void Die();
	void Defence(int damage);

	void ZomebieUpdate();

	void HeadUpdate();
	void SetKing(OMonsterKingconga * obj) {
		king = obj;
	}
};

