#pragma once
#include "GameNode.h"
#include "Image.h"
#include "Rocket.h"
#include "Enemy.h"
#include "EnemyManager.h" // 에너미 매니저 추가

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

	// 충돌 함수
	void Collision(); // 총알이 삭제되게끔
};
// FPS = Frame per Second

// 60fps 
/*
사람이 인식할 수 있는 프레임은 60fps
*/

//120fps

/*
최소로 가져야할 프레임은 30fps 

*/