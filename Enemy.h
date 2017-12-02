#pragma once
#include "GameNode.h"

//에너미 부모 클래스 
//이놈을 상속 받아서 보스나 일반 몬스터를 만든다 
class Enemy : public GameNode
{
private:
	//기본 이미지, 충돌용 RECT
	Image* _image;
	RECT _rc;
	//프레임 이미지를 돌리기 위한 변수
	int _count;
	int _currentFrameX;
	int _currentFrameY;

	//랜덤으로 총알 쿨타임 추가
	int _fireCount;
	int _rndFireCount;

public:
	Enemy();
	virtual ~Enemy();

	virtual HRESULT Init();
	virtual HRESULT Init(const char* imageName, POINT position);
	virtual void Release();
	virtual void Update();
	virtual void Render();

	virtual void Move();
	virtual void Draw();
	virtual void Animation();

	bool BulletCountFire();

	RECT GetRect() { return _rc; }
};

