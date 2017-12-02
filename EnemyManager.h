#pragma once // �̹� ��Ŭ����� �ش��� �ι����� �ʰڴ�
#include "GameNode.h"
#include "Bullet.h"
#include "Minion.h"

// ���ʹ� ������ ������ Ŭ����
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

	// �̴Ͼ� ����(�����Ҵ� ��);
	void SetMinion();
	// �̴Ͼ� �Ѿ� �߻�
	void MinionBulletFire();

	// �̴Ͼ� ����, �ݺ��� Get
	vEnemy GetVMinion() { return _vMinion; }
	viEnemy GetViMinion() { return _viMinion; }

	// �̴Ͼ� �Ѿ� ��������
	Bullet * GetBullet() { return _bullet; }

	// �̴Ͼ� ����
	void RemoveMinion(int arrNum);

	void Collision();
	void SetRocketMemoryLink(Rocket * rocket) { _rocket = rocket; }
};

