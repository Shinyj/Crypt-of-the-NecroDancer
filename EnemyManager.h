#pragma once // 이미 인클루드한 해더를 두번하지 않겠다
#include "GameNode.h"
#include "Bullet.h"
#include "Minion.h"

// 에너미 관리가 목적인 클래스
class Rocket;
class EnemyManager : public GameNode
{
private :
	typedef vector<Enemy*> vEnemy;
	typedef vector<Enemy*>::iterator viEnemy;

private :
	vEnemy _vMinion;
	viEnemy _viMinion;
	Bullet * _bullet;

	Rocket * _rocket;
public:
	EnemyManager() {};
	~EnemyManager() {};

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	// 미니언 셋팅(동적할당 후);
	void SetMinion();
	// 미니언 총알 발사
	void MinionBulletFire();

	// 미니언 벡터, 반복자 Get
	vEnemy GetVMinion() { return _vMinion; }
	viEnemy GetViMinion() { return _viMinion; }

	// 미니언 총알 가져오기
	Bullet * GetBullet() { return _bullet; }

	// 미니언 삭제
	void RemoveMinion(int arrNum);

	void Collision();
	void SetRocketMemoryLink(Rocket * rocket) { _rocket = rocket; }
};

