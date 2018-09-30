#pragma once
#include "ItemBase.h"
class OItemWeaponLongSword : public ItemBase
{
private :

	bool longRange; // 롱소드의 사정거리에 따른 랜더 방식 구별

	Image * subEffectU;
	Image * subEffectD;
	Image * subEffectL;
	Image * subEffectR;

public:
	OItemWeaponLongSword();
	~OItemWeaponLongSword();

	HRESULT Init(string key, int pos, ITEMKIND kind);
	void Release();
	void Update();
	void Render();

	void ShowInfo();

	bool UseIt(int pos, int dir);

	void EffectAnim();
	void EffectRender();
};

