#pragma once
#include "GameNode.h"
#include "Image.h"
#include "Rocket.h"
#include "Enemy.h"
#include "EnemyManager.h" // ���ʹ� �Ŵ��� �߰�

class MainGame : public GameNode
{
private:
	Rocket * m_rocket;
	//Enemy * m_enemy[18];
	EnemyManager * m_enemyManager;
public:
	MainGame();
	~MainGame();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	// �浹 �Լ�
	void Collision(); // �Ѿ��� �����ǰԲ�
};
// FPS = Frame per Second

// 60fps 
/*
����� �ν��� �� �ִ� �������� 60fps
*/

//120fps

/*
�ּҷ� �������� �������� 30fps 

*/