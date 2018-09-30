#include "stdafx.h"
#include "OItemShovelBasic.h"
#include "OPlayer1.h"

OItemShovelBasic::OItemShovelBasic()
{
}


OItemShovelBasic::~OItemShovelBasic()
{
}

HRESULT OItemShovelBasic::Init(string key, int pos, ITEMKIND kind)
{
	ItemBase::Init(key,pos,kind);
	infoImage = IMAGEMANAGER->FindImage("hint_1dig");
	Hard = 1;
	isEffectAnim = false;
	return S_OK;
}

void OItemShovelBasic::Release()
{
	ItemBase::Release();
}

void OItemShovelBasic::Update()
{
	ItemBase::Update();

	EffectAnim();
}

void OItemShovelBasic::Render()
{

	ItemBase::Render();

	EffectRender();

	//char str[100];
	//sprintf(str,"%d %d %d", x, y, m_pos);
	//TextOut(GetMemDC(), 0, 500, str, strlen(str));
}

void OItemShovelBasic::ShowInfo()
{
	infoImage->Render(GetMemDC(), x + 26 - 42  , y - 18 );
}

bool OItemShovelBasic::UseIt(int pos, int dir)
{
	GameObject * obj = OBJECTMANAGER->GetIsThereObj(pos);
	OPlayer1 * player = OBJECTMANAGER->GetPlayer();
	
	posX = OBJECTMANAGER->GetPlayer()->GetX();
	posY = OBJECTMANAGER->GetPlayer()->GetY();

	switch (dir)
	{
	case 8:
		posY -= 52;
		break;
	case 2:
		posY += 52;
		break;
	case 4:
		posX -= 52;
		break;
	case 6:
		posX += 52;
		break;
	}
	effectCount = 0;
	isEffectAnim = true;


	if (obj != NULL)
	{
		if (obj->GetObjKind() == OBJ_WALL)
		{
			if (obj->CanCrush(Hard))
			{
				OBJECTMANAGER->DeleteObj(obj);
				return true;
			}
			else
				OBJECTMANAGER->LostFever();
		}
	}


	return false;
}

void OItemShovelBasic::EffectAnim()
{
	if (isEffectAnim)
	{
		effectCount++;

		if (effectCount == 20)
			isEffectAnim = false;
	}
}

void OItemShovelBasic::EffectRender()
{
	if(isEffectAnim)
		mainImage->FrameRender(GetMemDC(), posX, posY - 20);
}
