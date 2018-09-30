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
	// 이미지 변수

	// 캐릭터
	Image * headImage;
	Image * bodyImage;

	// 유아이
	Image * heartImage;
	Image * heratLargeImage;
	Image * heartHalfImage;
	Image * heartHalfLageImage;
	Image * heartEmpty;
	Image * numberImage;
	Image * XImage;
	
	
	Image * euipWImage; // 장비 슬롯 (무기 아머 포션 삽 횃불)
	Image * euipAImage;	// 장비 슬롯 (무기 아머 포션 삽 횃불)
	Image * euipPImage;	// 장비 슬롯 (무기 아머 포션 삽 횃불)
	Image * euipSImage;	// 장비 슬롯 (무기 아머 포션 삽 횃불)
	Image * euipTImage;	// 장비 슬롯 (무기 아머 포션 삽 횃불)
	
	Image * euipRImage; // 장비 슬롯 ( 총, 장전 슬롯)
	Image * euipGImage;	// 장비 슬롯 ( 총, 장전 슬롯)

	Image * coin;
	Image * diamond;
	
	bool isPlayerDie = false;
	bool isCheat;
	int sight; // 플레이어 시야

	char m_headImageKey[126];
	char m_bodyImageKey[126];

	int m_frameX; // x 프레임 인덱스
	int m_frameY; // y 프레임 인덱스

	int m_headFrameX;
	int m_headFrameY;

	int m_maxX; // 프레임 맥스
	int m_maxY;

	//int m_pos; // 본인의 현재 좌표
	MOVING m_move;
	//int x; // 랜더 좌표
	//int y; // 랜더 좌표

	int moveCount; // 이동 시 처리하는 변수
	int jump;	// 이동 시 점프 높이
	int count;	// 프레임 갈아 끼울 때 쓰는 변수 
	bool isRight = true; // 우측보고잇늬?

	bool isJumpMoving = true;

	int defence;
	// ui 관련된 변수들 집함

	int m_HP; // 플레이어의 피
	int m_MaxHP;
	int hpBeatCount = 0;
	int hpBeate = 0;

	int curCoin;
	int curDia = 0;
	GameObject * m_equipWeapon; // 장착 무기
	GameObject * m_equipArmor; // 장착 방어구
	GameObject * m_posion; // 장착 포션
	GameObject * m_shovel; // 장착 삽
	GameObject * m_torch; // 장착 횃불

	Inventory inven[5];
	bool isUseInven[5];
	// ui 변수 end

	GameObject * putObj = nullptr;
	int putPos; // 버릴 좌표

	// 지진효과
	bool isEarthquake;
	int earthquakeCount;
	int beforX;	// 흔들기 이전 좌표
	int beforY;	// 흔들기 이전 좌표

	// int light; // 본인이 가지고 있는 밝기
	// bool isSight; // 플레이어의 가시거리에 있는가
	// bool isFirstSight; // 플레이어에게 이미 보였는가


	//////////////////////////

	// 레이 점을 찍자

	float x1;// 플레이어의 x 인덱스
	float y1;// 플레이어의 y 인덱스

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

	void PlayerMove(); // 플레이어 이동
	void Anim(); // 프레임 인덱스 조정

	void Defence(int damage);
	void Die();
	void Moving(bool isJump);

	// 여기부턴 ui 관련된 함수 
	
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

	bool OPlayer1::GetIsMoving(); // 무빙중이니

	 void SetInven(GameObject * obj);// 인벤토리 정렬

	 void PutItem(GameObject * obj);
	 void ShowItemInfo();// 주변 아이템 설명 출력하라

	 void SetCurrentHp(int num) 
	 { 
		 int n = m_HP + num;
		 if (n > m_MaxHP)
			 m_HP = m_MaxHP;
		 else
			 m_HP = n;
	 } // 체력회복
	///

	int countNum = 0;

	void Earthquake();

	void LayCast();
};

