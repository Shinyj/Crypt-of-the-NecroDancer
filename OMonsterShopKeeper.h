#pragma once
#include "MonsterBase.h"
class OMonsterShopKeeper : public MonsterBase
{
private :


	bool isAnim;

public:
	OMonsterShopKeeper();
	~OMonsterShopKeeper();

	HRESULT Init(string key, int pos);
	void Release();
	void Update();
	void Render();

	void Anim();

	void AStarLoad();

	// A��Ÿ ���õ� �Լ�
	
	void TileInitializing(); // Ÿ�� ��ġ �� �Ӽ��� �°� Ÿ�� �ʱ�ȭ
	void AddOpenList(); // ���� ����Ʈ�� �߰�
	void CalculateH(); // ���� ����Ʈ �� H �����
	void CalculateF(); // F ���
	void AddCloseList(); // Ŭ���� ����Ʈ�� �߰�
	void CheckArrive(); // ��������
};

