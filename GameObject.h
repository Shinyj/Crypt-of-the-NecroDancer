#pragma once
#include "GameNode.h"
class Image;
//class GameNode;
enum OBJECTKIND
{
	OBJ_FLOOR,
	OBJ_WALL,
	OBJ_ITEM,
	OBJ_MONSTER,
	OBJ_ETC,
	OBJ_PLAYER,
	OBJ_NONE
};

enum ITEMKIND
{
	ITEM_WEAPON,
	ITEM_ARMOR,
	ITEM_POSION,
	ITEM_SHOVEL,
	ITEM_TORCH,
	ITEM_GOLD,
	ITEM_NONE
};

class GameObject : public GameNode
{
protected :
	
	// 이미지
	Image * mainImage;
	Image * darkImage; // 알파 블랜드 위한 이미지

	Image * shadowImage;

	string m_imageKey;
	OBJECTKIND m_objKind;
	int m_pos;

	int x, y;

	bool isTorch;

	RECT rc; // 맵툴에서 쓸 렉트

	int m_frameX; // x 프레임 인덱스
	int m_frameY; // y 프레임 인덱스
	int m_frameCount = 0;

	bool isBeatTime = false;

	
	
	//int light =0; // 본인이 가지고 있는 밝기
	bool light = false; //  본인이 밝기를 가지고 있는가
	
	bool isSight;// = false; // 플레이어의 가시거리에 있는가
	bool isFirstSight;// = false; // 플레이어에게 이미 보였는가

	int attribute;

	// 급한 아이템
	bool isHereInven;
	bool isGoInven;
	//bool isHereInven;

public:

	GameObject();
	~GameObject();

	virtual HRESULT Init(string imageKey, int pos, OBJECTKIND obj);
	virtual void Release();
	virtual void Update();
	virtual void Render();


	string GetImageKey() { return m_imageKey; }
	OBJECTKIND GetObjKind() { return m_objKind; }

	void SetRC(RECT rc) { this->rc = rc; };
	RECT GetRC() { return rc; }

	void SetObjKind(OBJECTKIND obj) { m_objKind = obj; }

	virtual void SetPos(int num) { m_pos = num;
	}
	virtual int GetPos() { return m_pos; }

	virtual void SetXY(POINT camera)
	{
		x += camera.x; y += camera.y;
	}
	virtual void SetXY2(int x, int y)
	{
		this->x = x; this->y = y;
	}
	virtual int GetX() { return x; }
	virtual int GetY() { return y; }
	virtual void SetBeatTime(bool b) { isBeatTime = b; }
	virtual bool GetBeatTime() { return isBeatTime; }
	virtual int GetFrameX() { return m_frameX; }
	virtual int GetFrameY() { return m_frameY; }
	virtual void SetTorch(bool b) { isTorch = b; }
	virtual bool GetIsTorch() { return isTorch; }
	//virtual int GetHard() { return Hard; }

	// 여기는 급한 버츄얼 함수

	// 플레이어
	virtual bool GetIsMoving() { return true; } // 움직이고잇니

	// 아이템
	virtual void GoInventory(int x, int y) { };
	virtual ITEMKIND GetItemKind() { return ITEM_NONE; };
	virtual void SetIsHereInven(bool b) { isHereInven = b; }
	virtual void ShowInfo() {};
	virtual bool UseIt(int pos, int dir) { return false; }
	virtual int GetAttribute() { return attribute; }

	virtual void SetIsGoInven(bool b) { isGoInven = b; }
	//virtual void SetIsHereInven(bool b) { isHereInven = b; }

	// 몬스터
	virtual void Defence(int damage) {};
	virtual void Die() {};
	//타일
	virtual void SetGoScene(string key) {  } // 계단이 갈 씬

	// 벽
	virtual bool CanCrush(int hard) { return false; }

	virtual void LayCast() {};// 레이케스트

	//virtual void SetLight(int num) 
	//{ 
	//	light = light + num;
	//	if (light > 3) light = 3;
	//}

	virtual void SetLight(bool b) {light = b; }

	virtual void SetIsSight(bool a) { isSight = a; }
	virtual void SetFirstSight() { 
		
		isFirstSight = true; }

	virtual bool GetIsSight() { return isSight; }
};


struct less_than_key
{
	inline bool operator() ( GameObject * a,  GameObject * b)
	{
		return (a->GetPos() < b->GetPos());
	}
};
