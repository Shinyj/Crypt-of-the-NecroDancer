#pragma once
#include "GameNode.h"

//���ʹ� �θ� Ŭ���� 
//�̳��� ��� �޾Ƽ� ������ �Ϲ� ���͸� ����� 
class Enemy : public GameNode
{
private:
	//�⺻ �̹���, �浹�� RECT
	Image* _image;
	RECT _rc;
	//������ �̹����� ������ ���� ����
	int _count;
	int _currentFrameX;
	int _currentFrameY;

	//�������� �Ѿ� ��Ÿ�� �߰�
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

