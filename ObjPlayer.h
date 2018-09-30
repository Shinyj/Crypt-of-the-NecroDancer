#pragma once

class GameObject;

	
	//OBJECTKIND

	//OBJ_FLOOR,
	//OBJ_WALL,
	//OBJ_ITEM,
	//OBJ_MONSTER,
	//OBJ_ETC,
	//OBJ_PLAYER,
	//OBJ_NONE

	//char m_imageKey[126];
	//OBJECTKIND m_objKind;
	//int m_pos;

	//RECT rc; // 맵툴에서 쓸 렉트

	//int m_frameX; // x 프레임 인덱스
	//int m_frameY; // y 프레임 인덱스
	//int m_frameCount = 0;

class ObjPlayer : public GameObject
{
private :

	char m_headImageKey[126];
	char m_bodyImageKey[126];

	int m_frameX; // x 프레임 인덱스
	int m_frameY; // y 프레임 인덱스

	int m_pos; // 본인의 현재 좌표

	GameObject m_equipWeapon; // 장착 무기
	GameObject m_equipArmor; // 장착 방어구
	GameObject m_posion; // 장착 포션
	GameObject m_shovel; // 장착 삽
	GameObject m_torch; // 장착 횃불

public:
	ObjPlayer();
	~ObjPlayer();


	HRESULT Init(int pos);
	void Release();
	void Update();
	void Render();

	void PlayerMove(); // 플레이어 이동
	
	void PutItem();
};

