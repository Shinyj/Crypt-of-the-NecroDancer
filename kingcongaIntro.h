#pragma once
#include "GameNode.h"
class kingcongaIntro : public GameNode
{
private :
	Image * top;
	Image * bottom;
	Image * center;
	Image * logo;
	Image * bossName;

	Image * darkImage;

	POINT topPos;
	POINT botPos;
	POINT midPos;

	int alpha;

	bool turnOn;
public:

	kingcongaIntro();
	~kingcongaIntro();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	void TopAnim(int speed);
	void BottomAnim(int speed);
	bool MidAnim(int speed);

	void FadeOut();

};

