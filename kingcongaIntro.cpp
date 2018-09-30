#include "stdafx.h"
#include "kingcongaIntro.h"


kingcongaIntro::kingcongaIntro()
{
}


kingcongaIntro::~kingcongaIntro()
{
}

HRESULT kingcongaIntro::Init()
{
	SOUNDMANAGER->Stop("lobby");
	top = IMAGEMANAGER->FindImage("bg_topblade");
	bottom = IMAGEMANAGER->FindImage("bg_bottomblade");
	center = IMAGEMANAGER->FindImage("bg_gradient");
	logo = IMAGEMANAGER->FindImage("bosscreen");
	bossName = IMAGEMANAGER->FindImage("bossName");
	darkImage = IMAGEMANAGER->FindImage("black");
	topPos = {0,40};
	midPos = {0, 120 };
	botPos = { 230, 430 };

	topPos.x = -270;
	midPos.x = 425;
	botPos.x = 960;

	alpha = 255;
	turnOn = true;
	SOUNDMANAGER->Play("vo_announcer_kingconga",OBJECTMANAGER->GetBgmVolum());
	return S_OK;
}

void kingcongaIntro::Release()
{
}

void kingcongaIntro::Update()
{
	TopAnim(30);

	if(MidAnim(30))
		BottomAnim(50);

	FadeOut();
}

void kingcongaIntro::Render()
{
	top->Render(GetMemDC(), topPos.x, topPos.y);
	bottom->Render(GetMemDC(), botPos.x, botPos.y);
	center->Render(GetMemDC(), midPos.x, midPos.y);
	logo->Render(GetMemDC(), midPos.x, midPos.y - 95);
	bossName->Render(GetMemDC(), botPos.x + 350, botPos.y + 20);

	darkImage->AlphaRender(GetMemDC(),alpha);

	char str[50];
	sprintf(str, "%d", alpha);
	TextOut(GetMemDC(), 0, 100, str, strlen(str));
}

void kingcongaIntro::TopAnim(int speed)
{
	// 0 , 40¿¡ µµÂø
	if (topPos.x != 0)
	{
		topPos.x += speed;
		if (topPos.x > 0)
		{
			topPos.x = 0;
		}
	}
}

bool kingcongaIntro::MidAnim(int speed)
{
	// 0 ,120 ¿¡ µµÂø
	if (midPos.x != 0)
	{
		midPos.x -= speed;
		if (midPos.x < 0)
		{
			midPos.x = 0;
			
		}
	}
	else 
		return true;

	return false;
}

void kingcongaIntro::BottomAnim(int speed)
{
	// 230, 420¿¡ µµÂø
	if (botPos.x != 0)
	{
		botPos.x -= speed;
		if (botPos.x < 230)
			botPos.x = 230;
	}
}

void kingcongaIntro::FadeOut()
{
	if (!SOUNDMANAGER->isPlaySound("vo_announcer_kingconga"))
		turnOn = false;
	// Á¡Á¡ Èå·ÁÁö±â
	if (alpha > 0 && turnOn)
	{
		alpha -= 5;
	}
	else if(alpha <= 255 && !turnOn)
	{
		alpha += 5;
		if (alpha > 254)
			SCENEMANAGER->ChangeScene("boss");
	}
}
