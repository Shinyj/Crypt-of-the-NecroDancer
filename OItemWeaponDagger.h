#pragma once
#include "ItemBase.h"
class OItemWeaponDagger : public ItemBase
{
private :

	int direction; // 이펙트 방향 4 8 6 2 // 숫자방향키
	int posX; // 이펙트 출력할 위치
	int posY;
	int effectX; // 이펙트 프레임 x
	int effectY; // 이펙트 프레임 y
	int effectCount; // 이펙트 카운트

	bool isEffectAnim; // 이펙트 출력 여부

public:
	OItemWeaponDagger();
	~OItemWeaponDagger();

	HRESULT Init(string key, int pos, ITEMKIND kind);
	void Release();
	void Update();
	void Render();

	void ShowInfo();
	virtual bool UseIt(int pos, int dir);

	void EffectAnim(); // 이펙트 애니메이션
	void EffectRender();
};

