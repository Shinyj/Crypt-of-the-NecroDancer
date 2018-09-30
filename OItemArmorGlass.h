#pragma once
#include "ItemBase.h"

class OItemArmorGlass : public ItemBase
{
public:
	OItemArmorGlass();
	~OItemArmorGlass();

	HRESULT Init(string key, int pos, ITEMKIND kind);
	void Release();
	void Update();
	void Render();

	void ShowInfo();

};

