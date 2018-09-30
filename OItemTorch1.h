#pragma once
#include "ItemBase.h"
class OItemTorch1 : public ItemBase
{
public:
	OItemTorch1();
	~OItemTorch1();

	HRESULT Init(string key, int pos, ITEMKIND kind);
	void Release();
	void Update();
	void Render();

	void ShowInfo();
};

