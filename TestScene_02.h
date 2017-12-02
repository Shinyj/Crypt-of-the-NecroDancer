#pragma once
#include "GameNode.h" 
class TestScene_02 : public GameNode
{
public:
	TestScene_02();
	~TestScene_02();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};

