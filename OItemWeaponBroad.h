#pragma once
#include "ItemBase.h"
class OItemWeaponBroad : public ItemBase
{
private :

public:
	OItemWeaponBroad();
	~OItemWeaponBroad();

	HRESULT Init(string key, int pos, ITEMKIND kind);
	void Release();
	void Update();
	void Render();

	void ShowInfo();

	bool UseIt(int pos, int dir);

	void EffectAnim(); // 이펙트 애니메이션
	void EffectRender();
};

