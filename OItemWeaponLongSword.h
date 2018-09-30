#pragma once
#include "ItemBase.h"
class OItemWeaponLongSword : public ItemBase
{
private :

	bool longRange; // �ռҵ��� �����Ÿ��� ���� ���� ��� ����

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

