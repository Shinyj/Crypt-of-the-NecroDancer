#include "stdafx.h"
#include "ObjPlayer.h"
#include "GameObject.h"

ObjPlayer::ObjPlayer()
{
}


ObjPlayer::~ObjPlayer()
{
}

HRESULT ObjPlayer::Init(int pos)
{

	strcpy(m_headImageKey, "player_head");
	strcpy(m_bodyImageKey, "player_body");
	

	 m_frameX = 0; // x 프레임 인덱스
	 m_frameY = 0 ; // y 프레임 인덱스


	m_pos = pos;
	m_equipWeapon.Init("",-1,OBJ_NONE);
	m_equipArmor.Init("", -1, OBJ_NONE);
	m_posion.Init("", -1, OBJ_NONE);
	m_shovel.Init("", -1, OBJ_NONE);
	m_torch.Init("", -1, OBJ_NONE);

	return S_OK;
}

void ObjPlayer::Release()
{
}

void ObjPlayer::Update()
{
}

void ObjPlayer::Render()
{

}

void ObjPlayer::PlayerMove()
{
	if (KEYMANAGER->IsOnceKeyDown(VK_LEFT))
	{
		
	}
	else if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT))
	{
		
	}
	else if (KEYMANAGER->IsOnceKeyDown(VK_UP))
	{

	}
	else if (KEYMANAGER->IsOnceKeyDown(VK_DOWN))
	{

	}
}
