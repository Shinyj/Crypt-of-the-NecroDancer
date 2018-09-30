#pragma once
#include "ItemBase.h"
//#include "OItemShovelBasic.h"
class OItemArmorLeader : public ItemBase
{
public:
	OItemArmorLeader();
	~OItemArmorLeader();

	HRESULT Init(string key, int pos, ITEMKIND kind);
	void Release();
	void Update();
	void Render();

	void ShowInfo();
};

