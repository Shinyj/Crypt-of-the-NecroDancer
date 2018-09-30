#pragma once
#include "ItemBase.h"
class OItemWeaponGun : public ItemBase
{
private :
	bool isReload;
	int back;
public:
	OItemWeaponGun();
	~OItemWeaponGun();

	HRESULT Init(string key, int pos, ITEMKIND kind);
	void Release();
	void Update();
	void Render();

	void ShowInfo();

	bool UseIt(int pos, int dir);

	void EffectAnim();
	void EffectRender();
};

