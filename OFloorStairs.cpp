#include "stdafx.h"
#include "OFloorStairs.h"
#include "GameObject.h"
#include "OPlayer1.h"

OFloorStairs::OFloorStairs()
{
}


OFloorStairs::~OFloorStairs()
{
}

HRESULT OFloorStairs::Init(int pos)
{
	mainImage = IMAGEMANAGER->FindImage("floor_stairs");
	

	m_pos = pos;
	x = pos % TILEX * TILESIZE;
	y = pos / TILEY * TILESIZE;
	light = 0;
	m_objKind = OBJ_FLOOR;
	return S_OK;
}

void OFloorStairs::Release()
{
}

void OFloorStairs::Update()
{
	GameObject * player = NULL;
	vector<GameObject*> v = OBJECTMANAGER->GetVObj();
	vector<GameObject*>::iterator vi = OBJECTMANAGER->GetViObj();

		for (vi = v.begin(); vi != v.end(); vi++)
		{
			if ((*vi)->GetObjKind() == OBJ_PLAYER)
			{
				player = *vi;
				break;
			}
		}

		//player = OBJECTMANAGER->GetPlayer();

	if (player != NULL)
	{
		if (goScene == "lobby")
		{
			int num = 5;
			num++;
		}
		if (player->GetPos() == m_pos && !player->GetIsMoving())
		{

			SOUNDMANAGER->Stop(SOUNDMANAGER->GetBgmKey());

			SCENEMANAGER->ChangeScene(goScene);
		}
	}
}

void OFloorStairs::Render()
{
	//IMAGEMANAGER->Render("floor_stairs",GetMemDC(),x,y);
	
	
	//mainImage->Render(GetMemDC(),x,y);


	if (isFirstSight)
	{
		if (isSight)
		{
			if (light)
				mainImage->Render(GetMemDC(), x, y);
			else
				mainImage->AlphaRender(GetMemDC(), x, y,150);
		}
		else
		{
			mainImage->AlphaRender(GetMemDC(), x, y,150);
		}
	}

	//light = false;
	//isSight = false;
}
