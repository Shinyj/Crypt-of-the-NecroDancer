#pragma once
#include "MonsterBase.h"
class OMonsterShopKeeper : public MonsterBase
{
private :


	bool isAnim;

public:
	OMonsterShopKeeper();
	~OMonsterShopKeeper();

	HRESULT Init(string key, int pos);
	void Release();
	void Update();
	void Render();

	void Anim();

	void AStarLoad();

	// A스타 관련된 함수
	
	void TileInitializing(); // 타일 배치 후 속성에 맞게 타일 초기화
	void AddOpenList(); // 오픈 리스트에 추가
	void CalculateH(); // 오픈 리스트 내 H 값계산
	void CalculateF(); // F 계산
	void AddCloseList(); // 클로즈 리스트에 추가
	void CheckArrive(); // 도착여부
};

