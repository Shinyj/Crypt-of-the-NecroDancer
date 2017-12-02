#pragma once
#include "GameNode.h"
#include "Bullet.h"
#include "ProgressBar.h"

class EnemyManager;

// 객체화의 시작
class Rocket : public GameNode
{
private :
	Image * m_player;
	float m_speed;

	Missile * m_missile;
	MissileM1 * m_missileM1;
	ProgressBar * _hpBar;
	
	float _maxHp;
	float _currentHp;

	EnemyManager * _em;

public:
	Rocket();
	~Rocket();

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;

	// 미사일 삭제
	void RemoveMissile(int arrNum);
	// 충돌 함수
	void Collision();
	// 체력 감소용 함수
	void HitDamage(float damage);

	// 로켓 이미지 가져오기
	Image * GetRocketImage() { return m_player; }
	// 미사일 M1 가져오기
	MissileM1 * GetMissile() { return m_missileM1; }

	// 상호 참조하기 위한 매니져 주소값을 공유
	void SetEnemyMemotyLink(EnemyManager * em) { _em = em; }

	//void Damage();
};

