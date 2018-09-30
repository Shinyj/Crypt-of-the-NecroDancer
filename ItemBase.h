#pragma once
//#include "GameNode.h"
class GameObject;
class MonsterBase;
#include "LevelEdit.h"

class ItemBase : public GameObject
{
protected :

	Image * infoImage;

	Image * effectR;
	Image * effectU;
	Image * effectD;
	Image * effectL;

	int count;
	int g;
	int jump;

	float speedX;
	float speedY;
	bool isGoInven;
	//bool isHereInven;
	int goX;
	int goY;
	ITEMKIND m_kind;

	//int attribute; // 공격력, 방어력, 회복력
	
	// 무기 관련 변수
	int direction; // 이펙트 방향 4 8 6 2 // 숫자방향키
	int posX; // 이펙트 출력할 위치
	int posY;
	int effectX; // 이펙트 프레임 x
	int effectY; // 이펙트 프레임 y
	int effectCount; // 이펙트 카운트

	bool isEffectAnim; // 이펙트 출력 여부
public:
	ItemBase();
	~ItemBase();


	HRESULT Init(string key,int pos, ITEMKIND kind);
	void Release();
	void Update();
	void Render();

	void GoInventory(int x, int y);

	ITEMKIND GetItemKind() { return m_kind; }
	bool GetIsHereInven() { return isHereInven; }

	void SetXY2(int x, int y)
	{
		if (isHereInven)
		{
			this->x = x; this->y = y;
		}
	}

	void Anim();
	void goInven();

	virtual void SetIsHereInven(bool b) { isHereInven = b; }
	virtual void SetIsGoInven(bool b) { isGoInven = b; }
	virtual void ShowInfo() {};
	virtual bool UseIt(int pos, int dir) { return false; }

};

