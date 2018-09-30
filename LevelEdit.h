#pragma once
#include "../../GameNode.h"
#include "../../Image/Image.h"
#include "GameObject.h"
#define X * 2
//ȭ�� ���� ����ȭ��� �� 640 * 640
#define TILESIZE 52 //Ÿ�� ������
#define TILEX 50 //Ÿ�� ����
#define TILEY 50 //Ÿ�� ����
#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

//ȭ�� ������ �̹��� Ÿ�� ����
#define SAMPLETILEX 20
#define SAMPLETILEY 8

#define WALLHEIGHT 104
#define WALLWIDTH 48

class GameObject;

// �ٴ�
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

// ������Ʈ

//������Ʈ
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
//��ġ ��ǥ
enum pos
{
	POS_FLAG1,
	POS_FLAG2,
	POS_TANK1,
	POS_TANK2
};

//Ÿ�� ����ü (���ӿ��� ����ϴ� Ÿ��)
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


	// �ڽ��� ������ ��ü�� �����ϴ� �Լ�
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

//�̹��� Ÿ�� ����ü
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};
//���� Ÿ�� ����ü 
struct tagCurrentTile
{
	int x;
	int y;
};

class LevelEdit : public GameNode
{
private :

	bool isSave;
	// ���� ���̽� ���� ����
	POINT m_camera;
	RECT m_backGround;
	POINT curMounse;// = ptMouse;

	RECT m_interfaceRC[10]; // 

	RECT m_MenualRC; // �޴��� ����
	bool m_isShowMenual; // �޴��� ��¿���

	int curPlayerPos; // �ʱ� �÷��̾� ��ǥ

	int selectNum = 0;

	GameObject  selectObj;

	// ��ư��Ʈ�� ui ��Ʈ��

	// ���� Ÿ�ϰ�, �� �迭, ����Ÿ��
	tagCurrentTile _currentTile;
	tagTile _tiles[TILEX * TILEY];
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];
	
	int _corPos[2];
	int _pos[2]; // �÷��̾� ��ġ

	// �巡�� �׸��� ���� ��Ʈ
	RECT m_startRC;
	RECT m_endRC;
	bool isErase = false;
	// ������Ʈ ����

	vector<GameObject> m_vObj;
	vector<GameObject>::iterator m_viObj;

public:
	LevelEdit();
	~LevelEdit();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	// ���� ����
	void MapToolSetUp();
	void SetMap(); // �ʿ� �׸��ô�

	void Save();
	void Load();

	void SaveTest();

	// �� �� �������̽� �Լ�
	void SetInterface(); // �������̽� �ʱ�ȭ
	void MoveCamera(); // ī�޶� �̵�
	void MoveMenual();
	void SelectTile(); // Ÿ�� ����
	


	void ShowMap();
	void ShowMenual();
	void ShowObject(int selectNum);


	// ���� ������Ʈ
	FLOOR TerrainSelect(int frameX, int frameY);
	OBJECT ObjSelect(int frameX, int frameY);


};

