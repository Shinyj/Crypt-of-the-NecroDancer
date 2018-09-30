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

	//int attribute; // ���ݷ�, ����, ȸ����
	
	// ���� ���� ����
	int direction; // ����Ʈ ���� 4 8 6 2 // ���ڹ���Ű
	int posX; // ����Ʈ ����� ��ġ
	int posY;
	int effectX; // ����Ʈ ������ x
	int effectY; // ����Ʈ ������ y
	int effectCount; // ����Ʈ ī��Ʈ

	bool isEffectAnim; // ����Ʈ ��� ����
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

