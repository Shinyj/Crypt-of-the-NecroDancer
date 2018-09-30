#pragma once
#include "ItemBase.h"
class OItemTorch3 : public ItemBase
{
public:
	OItemTorch3();
	~OItemTorch3();

	HRESULT Init(string key, int pos, ITEMKIND kind);
	void Release();
	void Update();
	void Render();

	void ShowInfo();
};

