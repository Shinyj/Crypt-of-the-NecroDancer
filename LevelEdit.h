#pragma once
#include "../../GameNode.h"
#include "../../Image/Image.h"
#include "GameObject.h"
#define X * 2
//화면 왼쪽 게임화면용 맵 640 * 640
#define TILESIZE 52 //타일 사이즈
#define TILEX 50 //타일 갯수
#define TILEY 50 //타일 갯수
#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

//화면 오른쪽 이미지 타일 갯수
#define SAMPLETILEX 20
#define SAMPLETILEY 8

#define WALLHEIGHT 104
#define WALLWIDTH 48

class GameObject;

// 바닥
enum FLOOR
{
	FLOOR_ZONE1,
	FLOOR_ZONE2,
	FLOOR_ZONE3_COLD,
	FLOOR_ZONE3_HOT,
	FLOOR_ZONE4,
	FLOOR_NPC,
	FLOOR_SHOP,
	FLOOR_SHOP_NEXT,
	FLOOR_SHOP_RESET,
	FLOOR_STAIRS,
	FLOOR_STAIRS_LOCKED,
	FLOOR_BOSS,
	FLOOR_NONE
};

// 오브젝트

//오브젝트
enum OBJECT
{
	WALL_ZONE1_DIRT,
	WALL_ZONE2_DIRT,
	WALL_ZONE3_DIRT_COLD,
	WALL_ZONE3_DIRT_HOT,
	WALL_ZONE4_DIRT,
	WALL_ZONE1_STONE,
	WALL_ZONE1_STONE_CRACKED,
	WALL_ZONE2_STONE,
	WALL_ZONE2_STONE_CRACKED,
	WALL_ZONE3_STONE_COLD,
	WALL_ZONE3_STONE_COLD_CRACKED,
	WALL_ZONE3_STONE_HOT,
	WALL_ZONE3_STONE_HOT_CRACKED,
	WALL_ZONE4_STONE,
	WALL_ZONE4_STONE_CRACKED,
	WALL_SHOP_STONE,
	WALL_SHOP_STONE_CRACKED,
	WALL_DOOR_FRONT,
	WALL_DOOR_SIDE,
	WALL_END,

	OBJECT_NONE
};
//위치 좌표
enum pos
{
	POS_FLAG1,
	POS_FLAG2,
	POS_TANK1,
	POS_TANK2
};

//타일 구조체 (게임에서 사용하는 타일)
struct tagTile
{
	
	GameObject * floor;
	GameObject * item;
	GameObject * monster;
	GameObject * wall;
	GameObject * player;


	char floorKey[50];
	int floorPos;
	OBJECTKIND floorObj;

	char objKey[50];
	int objPos;
	OBJECTKIND objObj;

	RECT rc;

	bool isTorch = false;

	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;


	// 자신의 정보로 객체를 생성하는 함수
	void SetObj()
	{
		floor = nullptr;
		item = nullptr;
		monster = nullptr;
		wall = nullptr;
		player = nullptr;
		GameObject * temp;
		
		
		if (floorObj == OBJ_FLOOR)
		{
			temp = new GameObject;
			temp->Init(floorKey, floorPos, floorObj);
			floor = temp;
		}
		if (objObj != OBJ_NONE)
		{
			switch (objObj)
			{
			case OBJ_ITEM :
				temp = new GameObject;
				temp->Init(objKey, objPos, objObj);
				item = temp;
				break;
			case OBJ_MONSTER :
				temp = new GameObject;
				temp->Init(objKey, objPos, objObj);
				monster = temp;
				break;
			case OBJ_WALL :
				temp = new GameObject;
				temp->Init(objKey, objPos, objObj);
				wall = temp;
				break;
			case OBJ_PLAYER :
				temp = new GameObject;
				temp->Init(objKey, objPos, objObj);
				player = temp;
			}
		}
		if (isTorch)
		{
			temp->SetTorch(true);
		}
	}
};

//이미지 타일 구조체
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};
//현재 타일 구조체 
struct tagCurrentTile
{
	int x;
	int y;
};

class LevelEdit : public GameNode
{
private :

	bool isSave;
	// 인터 페이스 관련 변수
	POINT m_camera;
	RECT m_backGround;
	POINT curMounse;// = ptMouse;

	RECT m_interfaceRC[10]; // 

	RECT m_MenualRC; // 메뉴얼 몸통
	bool m_isShowMenual; // 메뉴얼 출력여부

	int curPlayerPos; // 초기 플레이어 좌표

	int selectNum = 0;

	GameObject  selectObj;

	// 버튼렉트와 ui 렉트들

	// 현재 타일과, 맵 배열, 샘플타일
	tagCurrentTile _currentTile;
	tagTile _tiles[TILEX * TILEY];
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];
	
	int _corPos[2];
	int _pos[2]; // 플레이어 위치

	// 드래그 그릴때 쓰는 렉트
	RECT m_startRC;
	RECT m_endRC;
	bool isErase = false;
	// 오브젝트 벡터

	vector<GameObject> m_vObj;
	vector<GameObject>::iterator m_viObj;

public:
	LevelEdit();
	~LevelEdit();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	// 맵툴 셋팅
	void MapToolSetUp();
	void SetMap(); // 맵에 그립시다

	void Save();
	void Load();

	void SaveTest();

	// 맵 툴 인터페이스 함수
	void SetInterface(); // 인터페이스 초기화
	void MoveCamera(); // 카메라 이동
	void MoveMenual();
	void SelectTile(); // 타일 고르기
	


	void ShowMap();
	void ShowMenual();
	void ShowObject(int selectNum);


	// 지형 오브젝트
	FLOOR TerrainSelect(int frameX, int frameY);
	OBJECT ObjSelect(int frameX, int frameY);


};

