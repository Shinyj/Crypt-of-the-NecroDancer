#pragma once
#include "ItemBase.h"
class OItemShovelTitanium : public ItemBase
{
private :
	int Hard;
public:
	OItemShovelTitanium();
	~OItemShovelTitanium();

	HRESULT Init(string key, int pos, ITEMKIND kind);
	void Release();
	void Update();
	void Render();

	void ShowInfo();

	bool UseIt(int pos, int dir);
	void EffectAnim(); // ����Ʈ �ִϸ��̼�
	void EffectRender();
};

