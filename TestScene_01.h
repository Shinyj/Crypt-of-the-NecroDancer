#pragma once
#include "GameNode.h"
class TestScene_01 : public GameNode
{
public:
	TestScene_01();
	~TestScene_01();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

};

