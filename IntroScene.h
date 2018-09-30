#pragma once
#pragma comment( lib, "vfw32.lib" )

#include "GameNode.h"
class IntroScene : public GameNode
{
private  :

public:
	IntroScene();
	~IntroScene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();


};

