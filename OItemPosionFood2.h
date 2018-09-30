#pragma once
#include "ItemBase.h"
class OItemPosionFood2 : public ItemBase
{
private :
	POINT paticlePos[26];
	int paticleSpeed[26];
	Image * paticle;
public:
	OItemPosionFood2();
	~OItemPosionFood2();

	HRESULT Init(string key, int pos, ITEMKIND kind);
	void Release();
	void Update();
	void Render();

	void ShowInfo();

	bool UseIt(int pos, int dir);

	void EffectAnim();
	void EffectRender();

};

