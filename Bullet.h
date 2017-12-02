#pragma once
#include "GameNode.h"

// �Ѿ� ����ü
struct tagBullet
{
	Image * bulletImage;
	RECT rc; // �浹�� ��Ʈ
	float x, y;
	float fireX, fireY;
	float radius;
	float speed;
	float angle;
	bool fire; // �߻� �ߴ��� ���θ� �Ǵ��ϴ� ����
	int count;
};

///////////  ���� �Ѿ˷� ����� Ŭ����
/*
�̻����� �÷��̾ �߻��ϴ� �Ѿ�
�ٸ� �ҷ����� �ƹ��� �� �� ����
*/

class Bullet : public GameNode
{
private :
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	char * _imageName;
	float _range;
	int _bulletMax;

public:

	HRESULT Init(char * imageName, int bulletMax, int range);
	void Release();
	void Update();
	void Render();
	// �Ѿ� �߻��ϴ� �Լ�
	void Fire(float x, float y, float angle, float speed);
	// �Ѿ� �����̴� �Լ�
	void Move();

	// �̻����� ���� �Լ�
	void RemoveMissile(int arrNum);
	// �̻��� ������ ��ȯ�� �Լ�
	vector<tagBullet> GetVBullet() { return _vBullet; }
	vector<tagBullet>::iterator GetViBullet() { return _viBullet; }


	Bullet() {};
	~Bullet() {};
};

/////////////// missile /////////////////
class Missile : public GameNode
{
private :
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet; // ���ͷ�����
	// ���ͷ����ʹ� �����Ϳ� ����� ���
	float _range;

public : 

	HRESULT Init(int bulletMax, float range);
	void Release();
	void Update();
	void Render();

	// �Ѿ� �߻�
	void Fire(float x, float y);
	// �Ѿ� ����
	void Move();

	Missile() {}
	~Missile() {}
};

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
// �ʻ��? 
class MissileM1 :public GameNode
{
private :
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	float _bulletMax;

public :
	HRESULT Init(int bulletMax, int range);
	void Release();
	void Update();
	void Render();

	void Fire(float x, float y);
	void Move();
	
	// �̻����� ���� �Լ�
	void RemoveMissile(int arrNum);
	// �̻��� ������ ��ȯ�� �Լ�
	vector<tagBullet> GetVBullet() { return _vBullet; }
	vector<tagBullet>::iterator GetViBullet() { return _viBullet; }

	MissileM1() {};
	~MissileM1() {};
};