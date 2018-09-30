#pragma once
class GameObject;
class ItemBase;
class Image;
#include "LevelEdit.h"


enum MOVING
{
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	RU,
	RD,
	LU,
	LD,
};



struct Inventory
{
	POINT pos;
	string uiKey;
	GameObject * obj;
};
class OPlayer1 : public GameObject
{
	// �̹��� ����

	// ĳ����
	Image * headImage;
	Image * bodyImage;

	// ������
	Image * heartImage;
	Image * heratLargeImage;
	Image * heartHalfImage;
	Image * heartHalfLageImage;
	Image * heartEmpty;
	Image * numberImage;
	Image * XImage;
	
	
	Image * euipWImage; // ��� ���� (���� �Ƹ� ���� �� ȶ��)
	Image * euipAImage;	// ��� ���� (���� �Ƹ� ���� �� ȶ��)
	Image * euipPImage;	// ��� ���� (���� �Ƹ� ���� �� ȶ��)
	Image * euipSImage;	// ��� ���� (���� �Ƹ� ���� �� ȶ��)
	Image * euipTImage;	// ��� ���� (���� �Ƹ� ���� �� ȶ��)
	
	Image * euipRImage; // ��� ���� ( ��, ���� ����)
	Image * euipGImage;	// ��� ���� ( ��, ���� ����)

	Image * coin;
	Image * diamond;
	
	bool isPlayerDie = false;
	bool isCheat;
	int sight; // �÷��̾� �þ�

	char m_headImageKey[126];
	char m_bodyImageKey[126];

	int m_frameX; // x ������ �ε���
	int m_frameY; // y ������ �ε���

	int m_headFrameX;
	int m_headFrameY;

	int m_maxX; // ������ �ƽ�
	int m_maxY;

	//int m_pos; // ������ ���� ��ǥ
	MOVING m_move;
	//int x; // ���� ��ǥ
	//int y; // ���� ��ǥ

	int moveCount; // �̵� �� ó���ϴ� ����
	int jump;	// �̵� �� ���� ����
	int count;	// ������ ���� ���� �� ���� ���� 
	bool isRight = true; // ���������մ�?

	bool isJumpMoving = true;

	int defence;
	// ui ���õ� ������ ����

	int m_HP; // �÷��̾��� ��
	int m_MaxHP;
	int hpBeatCount = 0;
	int hpBeate = 0;

	int curCoin;
	int curDia = 0;
	GameObject * m_equipWeapon; // ���� ����
	GameObject * m_equipArmor; // ���� ��
	GameObject * m_posion; // ���� ����
	GameObject * m_shovel; // ���� ��
	GameObject * m_torch; // ���� ȶ��

	Inventory inven[5];
	bool isUseInven[5];
	// ui ���� end

	GameObject * putObj = nullptr;
	int putPos; // ���� ��ǥ

	// ����ȿ��
	bool isEarthquake;
	int earthquakeCount;
	int beforX;	// ���� ���� ��ǥ
	int beforY;	// ���� ���� ��ǥ

	// int light; // ������ ������ �ִ� ���
	// bool isSight; // �÷��̾��� ���ðŸ��� �ִ°�
	// bool isFirstSight; // �÷��̾�� �̹� �����°�


	//////////////////////////

	// ���� ���� ����

	float x1;// �÷��̾��� x �ε���
	float y1;// �÷��̾��� y �ε���

	float layVal;
	float layMax;
	float r;
	float angle;
	int tempX;
	int tempY;

public:
	OPlayer1();
	~OPlayer1();

	HRESULT Init(int pos);
	void Release();
	void Update();
	void Render();

	void PlayerMove(); // �÷��̾� �̵�
	void Anim(); // ������ �ε��� ����

	void Defence(int damage);
	void Die();
	void Moving(bool isJump);

	// ������� ui ���õ� �Լ� 
	
	void RenderUI();
	void hp_beat();
	//// get set

	void SetXY(POINT camera)
	{
		x += camera.x; y += camera.y;
	}

	int GetX() { return x; }
	int GetY() { return y; }
	int GetPos() { return m_pos; }
	bool GetIsPlayerDie() { return isPlayerDie; }
	void SetWeapon(GameObject * obj) { m_equipWeapon = obj; };
	void SetArmor(GameObject * obj) { m_equipArmor = obj; };
	void SetPosion(GameObject * obj) { m_posion = obj; };
	void SetShovel(GameObject * obj) { m_shovel = obj; };
	void SetTorch(GameObject * obj) { m_torch = obj; };

	GameObject *  GetWeapon() { return m_equipWeapon; };
	GameObject *  GetArmor() { return m_equipArmor; };
	GameObject *  GetPosion() { return m_posion; };
	GameObject *  GetShovel() { return m_shovel; };
	GameObject *  GetTorch() { return m_torch; };

	int GetGold() { return curCoin; }

	void UpdateEquit();

	void SetEarthquake() { isEarthquake = true; };

	void SetPosionNull() { m_posion = nullptr; }

	void SetIsJump(MOVING num) {
		isJumpMoving = false; m_move
			= num; moveCount = TILESIZE;
	}

	bool OPlayer1::GetIsMoving(); // �������̴�

	 void SetInven(GameObject * obj);// �κ��丮 ����

	 void PutItem(GameObject * obj);
	 void ShowItemInfo();// �ֺ� ������ ���� ����϶�

	 void SetCurrentHp(int num) 
	 { 
		 int n = m_HP + num;
		 if (n > m_MaxHP)
			 m_HP = m_MaxHP;
		 else
			 m_HP = n;
	 } // ü��ȸ��
	///

	int countNum = 0;

	void Earthquake();

	void LayCast();
};

