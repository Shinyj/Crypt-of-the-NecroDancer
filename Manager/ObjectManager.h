#pragma once
#include "../LevelEdit.h"
#include "../GameObject.h"
#include "../GameNode.h"
class Image;

class SingletonBase;
class OPlayer1;

class GameObject;

// 바닥
class OFloorZone1;
class OFloorStairs;
class OFloorBoss;

// 벽
class OWallDoor;
class OWallGold;

class OWallBossWall;

class OWallEnd;
class OWallZone1Dirt;
class OWallZone1Stone;
class OWallZone2Dirt;
class OWallZone2Stone;
// 아이템

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

// 몬스터

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

	// 비트 바, 하트 렌더할 이미지 변수
	Image * heartImage;
	Image * blueBarImage;
	Image * greenBarImage;
	Image * redBarImage;

	// 이펙트를 위해 렌더할 이미지
	Image * backgroundBlack;
	Image * backgroundRed;
	Image * backgroundWhite;
	Image * backgroundGray;

	// gui 관련 이미지
	Image * coinMultiple;
	Image * numberImage;
	Image * numberImageBig;
	//Image * 
	// 플레이어 죽음 ui 관련 이미지

	Image * titleImage;
	Image * scoreImage;
	Image * goLobbyImage;
	Image * goLobbyImage_s;
	Image * restartImage;
	Image * restartImage_s;
	// 오브젝트들의 배열
	GameObject * objTile[TILEX * TILEY];
	GameObject * FloorTile[TILEX * TILEY]; // 맘에 안들지만 타일저장하는 배열
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

	// 플레이어 죽음 UI
	void UpdateDeatUI();
	void RenderDeathUI();


	// 게임 오브젝트 변수

	bool isGiveBeatTime = false;

	void ObjClear(); // 벡터 클리어
	GameObject * ObjPush(GameObject obj); // 벡터에 오브젝트 삽입
	void ObjNormalUpdate(); // 업데이트 (에니)
	void ObjTurnUpdate(); // 

	void SetCamera(POINT camera); // 카메라 적용
	void ObjSort(); // 오브젝트 정렬

	void AllObjUpdate(); // 타일 배열을 통한 obj 업데이트;

	void DeleteObj(GameObject * obj);

	void SetPlayerDie() { isPlayerDie = true;}
	float bit = 2.35;
	// 음악 오브젝트 변수
	int frameX_heart = 0;
	int count = 0; // 매니져에서 사용할 카운트

	float arr[1000] = { 0, };
	int arr_start = 0;
	int arr_end = 0;
	int heart_count = 0; // 심장 프레임 관리 카운트

	float bgmVolum = 0.4f;//0.4f;// 0.4f;
	float effectVolum = 1.0f;// 1.0f;//1.0f;
	// 게임 오브젝트 함수


	GameObject * CreateFloor(GameObject obj);
	GameObject * CreateWall(GameObject obj);
	GameObject * CreateItem(GameObject obj);
	GameObject * CreateMonster(GameObject obj);
	GameObject * CreatePlayer(GameObject obj);

	// ui 관련 함수
	int killCount;


	// 음악 오브젝트 함수

	void SetBeat();
	void Release();
	void Update();
	void Render();

	// 벡터 겟 셋
	vector<GameObject*> GetVObj() { return m_vObj; }
	vector<GameObject*>::iterator GetViObj() { return m_viObj; }

	// 이펙트 관련 변수
	int isFlash;
	// 타일 배열 조작
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
	//  효과나 이펙트 관련 함수

	void Flash();
	void FlashOn() { isFlash = 1; }
};

