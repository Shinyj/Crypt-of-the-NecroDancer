#pragma once
#include "ItemBase.h"
class OItemArmorGi : public ItemBase
{
public:
	OItemArmorGi();
	~OItemArmorGi();


	HRESULT Init(string key, int pos, ITEMKIND kind);
	void Release();
	void Update();
	void Render();

	virtual void ShowInfo();
};

