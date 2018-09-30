#pragma once
#include "ItemBase.h"
class OItemWeaponRapier : public ItemBase
{
private :
	bool longRange;

	Image * subEffectU;
	Image * subEffectD;
	Image * subEffectL;
	Image * subEffectR;


public:
	OItemWeaponRapier();
	~OItemWeaponRapier();

	HRESULT Init(string key, int pos, ITEMKIND kind);
	void Release();
	void Update();
	void Render();

	void ShowInfo();

	bool UseIt(int pos, int dir);

	void EffectAnim();
	void EffectRender();
};

