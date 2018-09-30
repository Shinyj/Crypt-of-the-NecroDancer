#pragma once
#include "ItemBase.h"
class OItemWeaponDagger : public ItemBase
{
private :

	int direction; // ����Ʈ ���� 4 8 6 2 // ���ڹ���Ű
	int posX; // ����Ʈ ����� ��ġ
	int posY;
	int effectX; // ����Ʈ ������ x
	int effectY; // ����Ʈ ������ y
	int effectCount; // ����Ʈ ī��Ʈ

	bool isEffectAnim; // ����Ʈ ��� ����

public:
	OItemWeaponDagger();
	~OItemWeaponDagger();

	HRESULT Init(string key, int pos, ITEMKIND kind);
	void Release();
	void Update();
	void Render();

	void ShowInfo();
	virtual bool UseIt(int pos, int dir);

	void EffectAnim(); // ����Ʈ �ִϸ��̼�
	void EffectRender();
};

