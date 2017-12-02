#pragma once
#include "GameNode.h"

// 총알 구조체
struct tagBullet
{
	Image * bulletImage;
	RECT rc; // 충돌용 렉트
	float x, y;
	float fireX, fireY;
	float radius;
	float speed;
	float angle;
	bool fire; // 발사 했는지 여부를 판단하는 변수
	int count;
};

///////////  공용 총알로 사용할 클래스
/*
미사일은 플레이어만 발사하는 총알
다른 불렛들은 아무나 쓸 수 있음
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
	// 총알 발사하는 함수
	void Fire(float x, float y, float angle, float speed);
	// 총알 움직이는 함수
	void Move();

	// 미사일을 지울 함수
	void RemoveMissile(int arrNum);
	// 미사일 정보를 반환할 함수
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
	vector<tagBullet>::iterator _viBullet; // 이터레이터
	// 이터레이터는 포인터와 비슷한 기능
	float _range;

public : 

	HRESULT Init(int bulletMax, float range);
	void Release();
	void Update();
	void Render();

	// 총알 발사
	void Fire(float x, float y);
	// 총알 무브
	void Move();

	Missile() {}
	~Missile() {}
};

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
// 필살기? 
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
	
	// 미사일을 지울 함수
	void RemoveMissile(int arrNum);
	// 미사일 정보를 반환할 함수
	vector<tagBullet> GetVBullet() { return _vBullet; }
	vector<tagBullet>::iterator GetViBullet() { return _viBullet; }

	MissileM1() {};
	~MissileM1() {};
};