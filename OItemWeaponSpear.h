#pragma once
#include "ItemBase.h"
class OItemWeaponSpear : public ItemBase
{
public:
	OItemWeaponSpear();
	~OItemWeaponSpear();

	HRESULT Init(string key, int pos, ITEMKIND kind);
	void Release();
	void Update();
	void Render();

	void ShowInfo();

	bool UseIt(int pos, int dir);

	void EffectAnim();
	void EffectRender();
};

