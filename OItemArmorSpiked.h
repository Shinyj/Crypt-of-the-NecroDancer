#pragma once
#include "ItemBase.h"
class OItemArmorSpiked : public ItemBase
{
public:
	OItemArmorSpiked();
	~OItemArmorSpiked();

	HRESULT Init(string key, int pos, ITEMKIND kind);
	void Release();
	void Update();
	void Render();

	void ShowInfo();
};

