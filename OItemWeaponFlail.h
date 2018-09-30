#pragma once
#include "ItemBase.h"
class OItemWeaponFlail : public ItemBase
{
public:
	OItemWeaponFlail();
	~OItemWeaponFlail();

	HRESULT Init(string key, int pos, ITEMKIND kind);
	void Release();
	void Update();
	void Render();

	void ShowInfo();

	bool UseIt(int pos, int dir);

	void EffectAnim();
	void EffectRender();
};

