#pragma once
#include "MonsterBase.h"

class OMonsterKingconga : public MonsterBase
{
private :

	bool isDrumming;
	int drummingCount;
	int zombieDieCount;

	Image * chairImage;
	int chairX;
	int chairY;
public:
	OMonsterKingconga();
	~OMonsterKingconga();

	HRESULT Init(string key, int pos);
	void Release();
	void Update();
	void Render();

	void Anim();
	
	void Die();
	void SetZombieDieCount() { zombieDieCount++; }


	void AStarLoad();

	// A��Ÿ ���õ� �Լ�
	void TileComposition(); // Ÿ�� ��ġ
	void TileInitializing(); // Ÿ�� ��ġ �� �Ӽ��� �°� Ÿ�� �ʱ�ȭ
	void AddOpenList(); // ���� ����Ʈ�� �߰�
	void CalculateH(); // ���� ����Ʈ �� H �����
	void CalculateF(); // F ���
	void AddCloseList(); // Ŭ���� ����Ʈ�� �߰�
	void CheckArrive(); // ��������

	void JumpMove();
	void Defence(int damage);
};

