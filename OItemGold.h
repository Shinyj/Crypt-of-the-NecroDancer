#pragma once
#include "ItemBase.h"
class OItemGold : public ItemBase
{
private :

	Image * body;



public:
	
	OItemGold();
	~OItemGold();

	HRESULT Init(string key, int pos, ITEMKIND kind);
	void Release();
	void Update();
	void Render();
};

