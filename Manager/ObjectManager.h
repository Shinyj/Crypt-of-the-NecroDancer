#pragma once
#include "../LevelEdit.h"
#include "../GameObject.h"
#include "../GameNode.h"
class Image;

class SingletonBase;
class OPlayer1;

class GameObject;

// �ٴ�
class OFloorZone1;
class OFloorStairs;
class OFloorBoss;

// ��
class OWallDoor;
class OWallGold;

class OWallBossWall;

class OWallEnd;
class OWallZone1Dirt;
class OWallZone1Stone;
class OWallZone2Dirt;
class OWallZone2Stone;
// ������

class OItemShovelBasic;
class OItemArmorLeader;
class OItemArmorGi;
class OItemArmorGlass;
class OItemArmorSpiked;
class OItemPosionFood2;
class OItemShovelTitanium;
class OItemTorch1;
class OItemTorch2;
class OItemTorch3;
class OItemWeaponBow;
class OItemWeaponBroad;
class OItemWeaponDagger;
class OItemWeaponFlail;
class OItemWeaponGun;
class OItemWeaponLongSword;
class OItemWeaponRapier;
class OItemWeaponSpear;

// ����

class OMonsterBanshee;
class OMonsterBanshee2;
class OMonsterBat;
class OMonsterBatBlack;
class OMonsterBatGreen;
class OMonsterBatMiniBoss;
class OMonsterBatRed;
class OMonsterDragonRed;
class OMonsterMageBlack;
class OMonsterMageWhite;
class OMonsterMageYellow;
class OMonsterMiniBossYellow;
class OMonsterMinotaur;
class OMonsterMinotaur2;
class OMonsterShopKeeper;
class OMonsterSkeleton;
class OMonsterSkeletonBlack;
class OMonsterSkeletonYellow;
class OMonsterSlimeGreen;
class OMonsterSlimeBlue;
class OMonsterShopkeeper;
class OMonsterZombie;
class OMonsterKingconga;


class ObjectManager :public singletonBase<ObjectManager>, public GameNode
{
private :

	// ��Ʈ ��, ��Ʈ ������ �̹��� ����
	Image * heartImage;
	Image * blueBarImage;
	Image * greenBarImage;
	Image * redBarImage;

	// ����Ʈ�� ���� ������ �̹���
	Image * backgroundBlack;
	Image * backgroundRed;
	Image * backgroundWhite;
	Image * backgroundGray;

	// gui ���� �̹���
	Image * coinMultiple;
	Image * numberImage;
	Image * numberImageBig;
	//Image * 
	// �÷��̾� ���� ui ���� �̹���

	Image * titleImage;
	Image * scoreImage;
	Image * goLobbyImage;
	Image * goLobbyImage_s;
	Image * restartImage;
	Image * restartImage_s;
	// ������Ʈ���� �迭
	GameObject * objTile[TILEX * TILEY];
	GameObject * FloorTile[TILEX * TILEY]; // ���� �ȵ����� Ÿ�������ϴ� �迭
	vector<GameObject*> m_vObj;
	vector<GameObject*>::iterator m_viObj;
	vector<GameObject*>::iterator m_viObj2;

	vector<int> m_vBeat;
	vector<int>::iterator m_viBeat;

	OPlayer1 * player;

	int feverTime;

	bool isPlayerDie;
	int selectNum;
	bool selectOption[2];

	float curTime;
	float frameDelta;

public:
	ObjectManager();
	~ObjectManager();

	HRESULT Init();

	// �÷��̾� ���� UI
	void UpdateDeatUI();
	void RenderDeathUI();


	// ���� ������Ʈ ����

	bool isGiveBeatTime = false;

	void ObjClear(); // ���� Ŭ����
	GameObject * ObjPush(GameObject obj); // ���Ϳ� ������Ʈ ����
	void ObjNormalUpdate(); // ������Ʈ (����)
	void ObjTurnUpdate(); // 

	void SetCamera(POINT camera); // ī�޶� ����
	void ObjSort(); // ������Ʈ ����

	void AllObjUpdate(); // Ÿ�� �迭�� ���� obj ������Ʈ;

	void DeleteObj(GameObject * obj);

	void SetPlayerDie() { isPlayerDie = true;}
	float bit = 2.35;
	// ���� ������Ʈ ����
	int frameX_heart = 0;
	int count = 0; // �Ŵ������� ����� ī��Ʈ

	float arr[1000] = { 0, };
	int arr_start = 0;
	int arr_end = 0;
	int heart_count = 0; // ���� ������ ���� ī��Ʈ

	float bgmVolum = 0.4f;//0.4f;// 0.4f;
	float effectVolum = 1.0f;// 1.0f;//1.0f;
	// ���� ������Ʈ �Լ�


	GameObject * CreateFloor(GameObject obj);
	GameObject * CreateWall(GameObject obj);
	GameObject * CreateItem(GameObject obj);
	GameObject * CreateMonster(GameObject obj);
	GameObject * CreatePlayer(GameObject obj);

	// ui ���� �Լ�
	int killCount;


	// ���� ������Ʈ �Լ�

	void SetBeat();
	void Release();
	void Update();
	void Render();

	// ���� �� ��
	vector<GameObject*> GetVObj() { return m_vObj; }
	vector<GameObject*>::iterator GetViObj() { return m_viObj; }

	// ����Ʈ ���� ����
	int isFlash;
	// Ÿ�� �迭 ����
	void SetTilePos(GameObject * obj,int pos)
	{

		objTile[obj->GetPos()] = nullptr;
		obj->SetPos(pos);
		objTile[pos] = obj;
	}

	GameObject * GetIsThereObj(int pos)
	{
		return objTile[pos];
	}

	GameObject * GetIsThereFloor(int pos)
	{
		return FloorTile[pos];
	}

	GameObject ** GetTileArr() { return objTile; }

	OPlayer1 * GetPlayer() { return player; }

	float GetBgmVolum() { return bgmVolum; }
	float GetEffectVolum() { return effectVolum; }

	void SetBgmVolum(float n) { bgmVolum = n; }
	void SetEffectVolum(float n) { effectVolum = n; }

	int GetFever() { return feverTime; }
	void SetFever();
	void LostFever();

	void InitLight();
	void InitSight();
	void PushObject(GameObject * obj)
	{
		m_vObj.push_back(obj);
		SetTilePos(obj, obj->GetPos());
	}
	//////////////////////////
	//
	//  ȿ���� ����Ʈ ���� �Լ�

	void Flash();
	void FlashOn() { isFlash = 1; }
};

