#pragma once
#include "GameNode.h"
#include "Bullet.h"
#include "ProgressBar.h"

class EnemyManager;

// ��üȭ�� ����
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

	// �̻��� ����
	void RemoveMissile(int arrNum);
	// �浹 �Լ�
	void Collision();
	// ü�� ���ҿ� �Լ�
	void HitDamage(float damage);

	// ���� �̹��� ��������
	Image * GetRocketImage() { return m_player; }
	// �̻��� M1 ��������
	MissileM1 * GetMissile() { return m_missileM1; }

	// ��ȣ �����ϱ� ���� �Ŵ��� �ּҰ��� ����
	void SetEnemyMemotyLink(EnemyManager * em) { _em = em; }

	//void Damage();
};

