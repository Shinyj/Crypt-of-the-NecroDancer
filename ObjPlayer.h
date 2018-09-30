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

	//RECT rc; // �������� �� ��Ʈ

	//int m_frameX; // x ������ �ε���
	//int m_frameY; // y ������ �ε���
	//int m_frameCount = 0;

class ObjPlayer : public GameObject
{
private :

	char m_headImageKey[126];
	char m_bodyImageKey[126];

	int m_frameX; // x ������ �ε���
	int m_frameY; // y ������ �ε���

	int m_pos; // ������ ���� ��ǥ

	GameObject m_equipWeapon; // ���� ����
	GameObject m_equipArmor; // ���� ��
	GameObject m_posion; // ���� ����
	GameObject m_shovel; // ���� ��
	GameObject m_torch; // ���� ȶ��

public:
	ObjPlayer();
	~ObjPlayer();


	HRESULT Init(int pos);
	void Release();
	void Update();
	void Render();

	void PlayerMove(); // �÷��̾� �̵�
	
	void PutItem();
};

