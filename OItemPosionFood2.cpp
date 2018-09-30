#include "stdafx.h"
#include "OItemPosionFood2.h"
#include "OPlayer1.h"

OItemPosionFood2::OItemPosionFood2()
{
}


OItemPosionFood2::~OItemPosionFood2()
{
}

HRESULT OItemPosionFood2::Init(string key, int pos, ITEMKIND kind)
{
	ItemBase::Init(key,pos,kind);
	infoImage = IMAGEMANAGER->FindImage("hint_restore2health");
	paticle = IMAGEMANAGER->FindImage("TEMP_particle_confuse");
	direction = 5;
	posX = -1;
	posY = 0;
	
	isEffectAnim = false;
	attribute = 10;

	return S_OK;
}

void OItemPosionFood2::Release()
{
	ItemBase::Release();
}

void OItemPosionFood2::Update()
{
	ItemBase::Update();

	if (isEffectAnim)
		EffectAnim();
}

void OItemPosionFood2::Render()
{
	ItemBase::Render();

	if (isEffectAnim)
		EffectRender();
}

void OItemPosionFood2::ShowInfo()
{
	infoImage->Render(GetMemDC(), x + 26 - 55, y - 18);
}

bool OItemPosionFood2::UseIt(int pos, int dir)
{
	OPlayer1 * player = OBJECTMANAGER->GetPlayer();
	posX = OBJECTMANAGER->GetPlayer()->GetX();
	posY = OBJECTMANAGER->GetPlayer()->GetY();

	SOUNDMANAGER->Play("sfx_item_food",OBJECTMANAGER->GetEffectVolum());

	player->SetCurrentHp(attribute);
//	player->SetPosionNull();
	isEffectAnim = true;

	for (int i = 0; i < 26; i++)
	{
		paticlePos[i] = {RND->GetFromInto(0,26), RND->GetFromInto(25,35) };
		paticleSpeed[i] = RND->GetFromInto(4,7);
	}

	//SAFE_DELETE(this);
	return  false;
}

void OItemPosionFood2::EffectAnim()
{
	effectCount++;
	
	if (effectCount == 10)
		isEffectAnim = false;
	else
	{
		for (int i = 0; i < 26; i++)
		{
			paticlePos[i].y -= paticleSpeed[i];
		}
	}

}

void OItemPosionFood2::EffectRender()
{
	for (int i = 0; i < 26; i++)
	{
		paticle->Render(GetMemDC(), posX + paticlePos[i].x, posY + paticlePos[i].y);
	}
}
