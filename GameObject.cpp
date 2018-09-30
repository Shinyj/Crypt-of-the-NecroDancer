#include "stdafx.h"

#include "GameObject.h"
#include "GameNode.h"
#include "Image\Image.h"

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

HRESULT GameObject::Init(string imageKey, int pos, OBJECTKIND obj)
{
	//strcpy(m_imageKey,imageKey);
	m_imageKey = imageKey;
	mainImage = IMAGEMANAGER->FindImage(imageKey);

	

	m_pos = pos;
	m_objKind = obj;
	isTorch = false;
	m_frameX = 0;
	m_frameY = 0;

	//if (strcmp(m_imageKey, "floor_zone2")) 	
	//{
	//	if (obj == OBJ_FLOOR)
	//	{
	//	if (pos % 2 == 0)
	//		m_frameX = 0;
	//	else
	//		m_frameX = 2;
	//	}
	//}		

	return S_OK;
}

void GameObject::Release()
{
}

void GameObject::Update()
{
	// 바닥 타일 전용 업데이트 ( 멤툴에서도 쓰고 있음 )
	
	//m_frameCount++;
	//if (m_frameCount % 25 == 0)
	//{
	//	m_frameCount = 0;
	//
	//	if (!strcmp(m_imageKey, "floor_zone1") || !strcmp(m_imageKey, "floor_zone3_hot") || !strcmp(m_imageKey, "floor_zone3_cold") || !strcmp(m_imageKey, "floor_zone4"))
	//	{
	//		if (strcmp(m_imageKey, "floor_zone2"))
	//		{
	//			if (m_frameX != 0)
	//				m_frameX = 0;
	//			else if (m_pos % 2 == 0)
	//				m_frameX = 1;
	//			else
	//				m_frameX = 2;
	//		}
	//	}
	//
	//}
}

void GameObject::Render()
{
	int subX = 0;
	int subY = 0;
	 
	if (m_imageKey == "banshee" || m_imageKey == "banshee2")
	{
		subX = 7;
		subY = 47;
	}
	else if (m_imageKey == "bat" ||
		m_imageKey == "bat_black" ||
		m_imageKey == "bat_green" ||
		m_imageKey == "bat_red")
	{
		subX = 0;
		subY = 20;
	}
	else if (m_imageKey == "bat_miniboss" || m_imageKey == "miniboss_yellow")
	{
		subX = 12;
		subY = 20;
	}
	else if (m_imageKey == "dragon_red")
	{
		subX = 40;
		subY = 70;
	}
	else if (m_imageKey == "mage_black" ||
		m_imageKey == "mage_white" ||
		m_imageKey == "mage_yellow" ||
		m_imageKey == "skeleton_black" ||
		m_imageKey == "skeleton_yellow" ||
		m_imageKey == "skeleton")
	{
		subX = 0;
		subY = 20;
	}

	else if (m_imageKey == "minotaur" || m_imageKey == "minotaur2")
	{
		subX = 22;
		subY = 67;
	}
	else if (m_imageKey == "shopkeeper")
	{
		subX = 20;
		subY = 45;
	}
	else if (m_imageKey == "slime_green" || m_imageKey == "slime_blue")
	{
		subX = 0;
		subY = 20;
	}
	else if (m_imageKey == "king_conga")
	{
		subX = 35;
		subY = 79;
	}
	else if (m_imageKey == "zombie_snake")
	{
		subX = 0;
		subY = 20;
	}

	//IMAGEMANAGER->FrameRender(m_imageKey,GetMemDC(), rc.left, rc.top, m_frameX, m_frameY);
	mainImage->FrameRender(GetMemDC(), rc.left - subX, rc.top - subY, 0, 0);
}

