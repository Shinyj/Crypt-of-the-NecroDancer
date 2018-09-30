#pragma once
#include "ItemBase.h"
class OItemTorch2 : public ItemBase
{
public:
	OItemTorch2();
	~OItemTorch2();

	HRESULT Init(string key, int pos, ITEMKIND kind);
	void Release();
	void Update();
	void Render();

	void ShowInfo();
};

