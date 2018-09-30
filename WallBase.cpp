#include "stdafx.h"
#include "WallBase.h"


WallBase::WallBase()
{
}


WallBase::~WallBase()
{
}

HRESULT WallBase::Init(string key, int pos, bool torch)
{
	mainImage = IMAGEMANAGER->FindImage(key);
	darkImage = IMAGEMANAGER->FindImage("black");
	m_imageKey = key;
	
	isTorch = torch;

	if (torch)
		torchImage = IMAGEMANAGER->FindImage("wall_torch");

	m_pos = pos;
	x = pos % TILEX * TILESIZE;
	y = pos / TILEY * TILESIZE - 35; // 32

	m_frameX = 0;
	m_frameY = 0;
	
	torchFrame = 0;
	torchCount = 0;
	//sight = 3;
	//light = 0;

	isFirstSight = false;
	isSight = false;
	return S_OK;
}

void WallBase::Release()
{
}

void WallBase::Update()
{
	if (isTorch)
	{
		torchCount++;
		if (torchCount % 10 == 0)
		{
			torchFrame = (torchFrame + 1) % 4;
		}

		RayCast();

	}
}

void WallBase::Render()
{
	if (isTorch)
	{
		light = true;

		if (isSight)
			isFirstSight = true;
	}	
	
	//RayCast();


	//mainImage->FrameRender(GetMemDC(), x, y, m_frameX, m_frameY);
	
	if (isFirstSight)
	{
		mainImage->FrameRender(GetMemDC(), x, y, m_frameX, m_frameY);

		if (isTorch)
			torchImage->FrameRender(GetMemDC(), x + 13, y, torchFrame, 0);

		if (isSight)
		{
			if (light)
			{
				
			}
			else
			{
				darkImage->AlphaRender(GetMemDC(), x, y, 0, 0, 52, 52, 105);
				
			}
		}
		else
		{
			darkImage->AlphaRender(GetMemDC(), x, y, 0, 0, 52, 52, 105);
			
		}
	}
	else
	{
		darkImage->Render(GetMemDC(), x, y, 0, 0, 52, 52);
	}


	
	// 원래 사용됐던 시야 처리
	///if (isSight)
	///{
	///	mainImage->FrameRender(GetMemDC(), x, y, m_frameX, m_frameY);
	///
	///	if (light == 1)
	///		darkImage->AlphaRender(GetMemDC(), x, y, 0, 0, 52, 52, 140);
	///	else if (light == 2)
	///		darkImage->AlphaRender(GetMemDC(), x, y, 0, 0, 52, 52, 70);
	///	else if (light == 3)
	///		darkImage->AlphaRender(GetMemDC(), x, y, 0, 0, 52, 52, 0);
	///
	///
	///	if(isTorch)
	///		torchImage->FrameRender(GetMemDC(), x + 13, y - 18, torchFrame,0);
	///
	///}
	///else
	///{
	///	if (isFirstSight)
	///	{
	///		mainImage->FrameRender(GetMemDC(), x, y, m_frameX, m_frameY);
	///		if (isTorch)
	///			torchImage->FrameRender(GetMemDC(), x + 13, y - 18, torchFrame, 0);
	///		darkImage->AlphaRender(GetMemDC(), x, y, 0, 0, 52, 52, 125);
	///	}
	///}


	//
	//char str[10];
	//sprintf(str, "%d", isFirstSight);
	//TextOut(GetMemDC(), x, y, str, strlen(str));
	//sprintf(str, "%d", isSight);
	//TextOut(GetMemDC(), x + 20, y, str, strlen(str));
	//sprintf(str, "%d", light);
	//TextOut(GetMemDC(), x, y + 20, str, strlen(str));
	//
	//light = false;
	//isSight = false;

}

bool WallBase::CanCrush(int hard)
{
	if (Hard > hard)
	{
		SOUNDMANAGER->Play("mov_dig_fail",OBJECTMANAGER->GetEffectVolum());
		return false;
	}
	else
	{
		if (m_imageKey == "wall_door_side" || m_imageKey == "wall_door_front")
		{
			SOUNDMANAGER->Play("obj_door_open", OBJECTMANAGER->GetEffectVolum());
		}
		else if (m_imageKey == "wall_z1_drit" || m_imageKey == "wall_z2")
		{
			SOUNDMANAGER->Play("mov_dig_dirt", OBJECTMANAGER->GetEffectVolum());
		}
		else
		{
			SOUNDMANAGER->Play("mov_dig_stone", OBJECTMANAGER->GetEffectVolum());
		}
		return true;
	}
}

void WallBase::RayCast()
{
	light = true;
	
	if(isSight)
		isFirstSight = true;

	GameObject * obj;
	GameObject * floor;
	GameObject * obj2;
	GameObject * floor2;


	obj = OBJECTMANAGER->GetIsThereObj(m_pos - 51);
	floor = OBJECTMANAGER->GetIsThereFloor(m_pos - 51);

	if (obj != NULL)
	{
		obj->SetLight(true);
		if (obj->GetIsSight() == true) obj->SetFirstSight();
	}
	if (floor != NULL)
	{
		floor->SetLight(true);
		if (floor->GetIsSight() == true) floor->SetFirstSight();
	}



	obj = OBJECTMANAGER->GetIsThereObj(m_pos - 49);
	floor = OBJECTMANAGER->GetIsThereFloor(m_pos - 49);

	if (obj != NULL)
	{
		obj->SetLight(true);
		if (obj->GetIsSight() == true) obj->SetFirstSight();
	}
	if (floor != NULL)
	{
		floor->SetLight(true);
		if (floor->GetIsSight() == true) floor->SetFirstSight();
	}

	
	obj = OBJECTMANAGER->GetIsThereObj(m_pos + 51);
	floor = OBJECTMANAGER->GetIsThereFloor(m_pos + 51);

	if (obj != NULL)
	{
		obj->SetLight(true);
		if (obj->GetIsSight() == true) obj->SetFirstSight();
	}
	if (floor != NULL)
	{
		floor->SetLight(true);
		if (floor->GetIsSight() == true) floor->SetFirstSight();
	}

	obj = OBJECTMANAGER->GetIsThereObj(m_pos + 49);
	floor = OBJECTMANAGER->GetIsThereFloor(m_pos + 49);

	if (obj != NULL)
	{
		obj->SetLight(true);
		if (obj->GetIsSight() == true) obj->SetFirstSight();
	}
	if (floor != NULL)
	{
		floor->SetLight(true);
		if (floor->GetIsSight() == true) floor->SetFirstSight();
	}

	//

	//



	obj = OBJECTMANAGER->GetIsThereObj(m_pos - 50);
	floor = OBJECTMANAGER->GetIsThereFloor(m_pos - 50);

	if (floor != NULL)
	{
		floor->SetLight(true);
		if (floor->GetIsSight() == true) floor->SetFirstSight();


	}

	if (obj != NULL)
	{
		obj->SetLight(true);
		if (obj->GetIsSight() == true) obj->SetFirstSight();


		if (obj->GetObjKind() != OBJ_WALL)
		{
			if ((obj2 = OBJECTMANAGER->GetIsThereObj(m_pos - 100)) != NULL)
			{
				obj2->SetLight(true);
				if (obj2->GetIsSight() == true) obj2->SetFirstSight();


			}

			if ((floor2 = OBJECTMANAGER->GetIsThereFloor(m_pos - 100)) != NULL)
			{
				floor2->SetLight(true);
				if (floor2->GetIsSight() == true) floor2->SetFirstSight();


			}
		}
	}
	else
	{
		if ((obj2 = OBJECTMANAGER->GetIsThereObj(m_pos - 100)) != NULL)
		{
			obj2->SetLight(true);
			if (obj2->GetIsSight() == true) obj2->SetFirstSight();


		}

		if ((floor2 = OBJECTMANAGER->GetIsThereFloor(m_pos - 100)) != NULL)
		{
			floor2->SetLight(true);
			if (floor2->GetIsSight() == true) floor2->SetFirstSight();


		}
	}


	obj = OBJECTMANAGER->GetIsThereObj(m_pos + 50);
	floor = OBJECTMANAGER->GetIsThereFloor(m_pos + 50);

	if (floor != NULL)
	{
		floor->SetLight(true);
		if (floor->GetIsSight() == true) floor->SetFirstSight();


	}

	if (obj != NULL)
	{
		obj->SetLight(true);

		if (obj->GetIsSight() == true) obj->SetFirstSight();


		if (obj->GetObjKind() != OBJ_WALL)
		{
			if ((obj2 = OBJECTMANAGER->GetIsThereObj(m_pos + 100)) != NULL)
			{
				obj2->SetLight(true);
				if (obj2->GetIsSight() == true) obj2->SetFirstSight();


			}

			if ((floor2 = OBJECTMANAGER->GetIsThereFloor(m_pos + 100)) != NULL)
			{
				floor2->SetLight(true);
				if (floor2->GetIsSight() == true) floor2->SetFirstSight();

			}
		}
	}
	else
	{
		if ((obj2 = OBJECTMANAGER->GetIsThereObj(m_pos + 100)) != NULL)
		{
			obj2->SetLight(true);
			if (obj2->GetIsSight() == true) obj2->SetFirstSight();


		}

		if ((floor2 = OBJECTMANAGER->GetIsThereFloor(m_pos + 100)) != NULL)
		{
			floor2->SetLight(true);
			if (floor2->GetIsSight() == true) floor2->SetFirstSight();

		}
	}

	obj = OBJECTMANAGER->GetIsThereObj(m_pos - 1);
	floor = OBJECTMANAGER->GetIsThereFloor(m_pos - 1);

	if (floor != NULL)
	{
		floor->SetLight(true);
		if (floor->GetIsSight() == true) floor->SetFirstSight();


	}

	if (obj != NULL)
	{
		obj->SetLight(true);
		if (obj->GetIsSight() == true) obj->SetFirstSight();


		if (obj->GetObjKind() != OBJ_WALL)
		{
			if ((obj2 = OBJECTMANAGER->GetIsThereObj(m_pos - 2)) != NULL)
			{
				obj2->SetLight(true);
				if (obj2->GetIsSight() == true) obj2->SetFirstSight();

			}

			if ((floor2 = OBJECTMANAGER->GetIsThereFloor(m_pos - 2)) != NULL)
			{
				floor2->SetLight(true);
				if (floor2->GetIsSight() == true) floor2->SetFirstSight();


			}
		}
	}
	else
	{
		if ((obj2 = OBJECTMANAGER->GetIsThereObj(m_pos - 2)) != NULL)
		{
			obj2->SetLight(true);
			if (obj2->GetIsSight() == true) obj2->SetFirstSight();

		}

		if ((floor2 = OBJECTMANAGER->GetIsThereFloor(m_pos - 2)) != NULL)
		{
			floor2->SetLight(true);
			if (floor2->GetIsSight() == true) floor2->SetFirstSight();
		}
	}

	obj = OBJECTMANAGER->GetIsThereObj(m_pos + 1);
	floor = OBJECTMANAGER->GetIsThereFloor(m_pos + 1);

	if (floor != NULL)
	{
		floor->SetLight(true);
		if (floor->GetIsSight() == true) floor->SetFirstSight();


	}

	if (obj != NULL)
	{
		obj->SetLight(true);
		if (obj->GetIsSight() == true) obj->SetFirstSight();


		if (obj->GetObjKind() != OBJ_WALL)
		{
			if ((obj2 = OBJECTMANAGER->GetIsThereObj(m_pos + 2)) != NULL)
			{
				obj2->SetLight(true);
				if (obj2->GetIsSight() == true) obj2->SetFirstSight();


			}

			if ((floor2 = OBJECTMANAGER->GetIsThereFloor(m_pos + 2)) != NULL)
			{
				floor2->SetLight(true);
				if (floor2->GetIsSight() == true) floor2->SetFirstSight();


			}
		}
	}
	else
	{
		if ((obj2 = OBJECTMANAGER->GetIsThereObj(m_pos + 2)) != NULL)
		{
			obj2->SetLight(true);
			if (obj2->GetIsSight() == true) obj2->SetFirstSight();


		}

		if ((floor2 = OBJECTMANAGER->GetIsThereFloor(m_pos + 2)) != NULL)
		{
			floor2->SetLight(true);
			if (floor2->GetIsSight() == true) floor2->SetFirstSight();


		}
	}

}

/*
float x1 = (float)(m_pos % 50); // 플레이어의 x 인덱스
float y1 = (float)(m_pos / 50); // 플레이어의 y 인덱스

float layVal = 0.0f;
float layMax = (float)2.0f - 0.25;

float bright = 0.0f;

float sightMax = 5.0f;
float curSight = 0.0f;



float r = 0.0f; // 쏠 레이의 각도
float angle = (15.0f * 3.141592) / 180.0f; // 레이 각도의 증가량



while (r < 2 * 3.141592)
{
if (KEYMANAGER->IsStayKeyDown('B'))
{
HPEN pen, oldPen;
pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 255));
oldPen = (HPEN)SelectObject(GetMemDC(), pen);
LineMake(GetMemDC(), this->x + 26, this->y + 26,
this->x + 26 + layVal * cos(r) * TILESIZE, this->y + 26 + layVal * (-sin(r)) * TILESIZE);
SelectObject(GetMemDC(), oldPen);
DeleteObject(pen);

char str[25];
sprintf(str, "%.1f", r);
TextOut(GetMemDC(), x, y - 20, str, strlen(str));
}

//tempX = x1 + layVal * cos(r);
//tempY = y1 + layVal * (-sin(r));
//
if (layVal > layMax)
bright = 0.0f;
else
bright = layVal;

if (curSight > sightMax)
{
curSight = 0.0f;
bright = 0.0f;
layVal = 0.0f;
r += angle;
}
//break;

int tempX = x1 + curSight * cos(r) + 0.5;
int tempY = y1 + curSight * (-sin(r)) + 0.5;

if (x1 < 0 || y1 < 0)
{
curSight = sightMax + 0.1f;
continue;
}

int a = tempX - x1;
if (a < 0) a *= -1;
int b = tempY - y1;
if (b < 0) b *= -1;
int s;
if (a > b) s = a; else s = b;
s = a + b;
GameObject * obj = OBJECTMANAGER->GetIsThereObj(tempX + tempY * 50);
GameObject * floorObj = OBJECTMANAGER->GetIsThereFloor(tempX + tempY * 50);


if (x1 == x && y1 == y)
{
continue;
}


if (obj != NULL)
{

if (obj->GetIsSight() == false)
{
//obj->SetLight(3 - s);

if (s <= 2)
{
obj->SetLight(true);
//obj->SetFirstSight();
}

//obj->SetIsSight(true);

}


if (obj->GetObjKind() == OBJ_WALL)
{
if (obj->GetImageKey() == "wall_door_side")
{
if (floorObj->GetIsSight() == false)
{
//floorObj->SetLight(3 - s);
if (s <= 2)
{
floorObj->SetLight(true);

}

}
}


if (!(obj->GetObjKind() == OBJ_WALL && obj->GetPos() != m_pos))
{
layVal = 0.0f;
curSight = 0.0f;
r += angle;
continue;
}

}

}

if (floorObj != NULL)
{
if (floorObj->GetIsSight() == false)
{
//floorObj->SetLight(3 - s);
if (s <= 2)
{
floorObj->SetLight(true);

}

}
}

layVal += 0.25;
curSight += 0.25;
}*/
