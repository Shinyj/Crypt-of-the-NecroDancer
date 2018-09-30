#pragma once

class GameObject;
#include "LevelEdit.h"

enum DIRECTION
{
	M_LEFT = -1,
	M_RIGHT = 1,
	M_UP = -50,
	M_DOWN = 50,
	M_NONE = 0,
	M_RU = -49,
	M_RD = 51,
	M_LU = -51,
	M_LD = 49
};

enum TILE_TYPE
{
	TILE_TYPE_EMPTY, // ��Ÿ�� (������ �� ����)
	TILE_TYPE_START,// ���� ����
	TILE_TYPE_END,	// ���� ����
	TILE_TYPE_WALL	// ��
};

// ���� ����
enum ASTAR_STATE
{
	ASTAR_STATE_SEARCHING, // ��θ� Ž�� ���̴�.
	ASTAR_STATE_FOUND, // �ִ� �Ÿ��� ã�Ҵ�.
	ASTAR_STATE_NOWAY, // ��θ� ã�� �� ����.
	ASTAR_STATE_END // Ÿ�� ��ġ �Ϸ���
};


struct aStarTile
{
	RECT rc;
	COLORREF color;
	bool walkable;
	bool listOn;
	int i, j;
	int F, G, H;
	// G ���� �������� ���� ������ ���
	// H ���� ��忡�� ���������� ���
	// F �� ���
	char str[128];
	aStarTile * parent; // �θ� Ÿ�� �ּ�
	TILE_TYPE type; //Ÿ�� �Ӽ�
};

class MonsterBase : public GameObject
{
protected : 

	Image * maxHpImage;
	Image * curHpImage;

	Image * effectU;
	Image * effectR;
	Image * effectL;
	Image * effectD;

	int m_hp; // ����
	int m_currentHp;
	//string m_imageKey; // �̹��� Ű
	int damage; // ���ϴ� ������
	int count; // ���ϸ��̼� ī��Ʈ
	int isRight; // ������ ���� �ִ�
	
	int g; // ������ �߷°�
	int jump; // ���� ���� ( ������ y �� ���� )

	int m_maxFrameX; // ����� �̹��� ������ x 
	int m_maxFrameY; // ����� �̹��� ������ y 

	bool isShowHp;
	bool isHalfMove;
	int subX;
	int subY; // ������ ���� ���� ��ǥ

	int MoveLoad; // ����

	DIRECTION m_move;
	int moveCount = 0;

	// A* ���õ� ����

	aStarTile _tile[TILEX][TILEY];
	vector<aStarTile*> _openList;
	vector<aStarTile*> _closeList;

	ASTAR_STATE _aStarState; // ����

	TILE_TYPE _selectedType;
	COLORREF _selectedTypeColor;

	int _startX, _startY;
	int _endX, _endY;
	int _lastIndex; // ���� �������� �߰���
					// Ŭ���� ����Ʈ �ε���

	int myMoveBeat;
	int myCurrentMoveBeat;

	bool _startPointSet; // �������� ��ġ ����
	bool _endPointSet; // �������� ��ġ ����

	int Ci; // ���������� �߰��� Ŭ���� ����Ʈ I
	int Cj; // ���������� �߰��� Ŭ���� ����Ʈ j
	int Cg; // ���������� �߰��� Ŭ���� ����Ʈ ���

	bool isEffectAnim;
	DIRECTION direction;
	int effectCount = 0;
	int effectX;
	int effectY;
	int posX, posY;


public:
	MonsterBase();
	~MonsterBase();

	HRESULT Init(string key, int pos); // ������ ������ �ؾ��ҵ�
	void Release();					   // ������ ������ �ؾ��ҵ�
	void Update();					   // ������ ������ �ؾ��ҵ�
	void Render();					   // ������ ������ �ؾ��ҵ�

	void Anim(); // ������ ������ �ؾ��ҵ�

	void Move(); 
	void Attcked(DIRECTION dir);
	virtual void Defence(int damage);

	void Die();

	void JumpMove();

	void RendomLoad();
	void PatternLoad();
	bool AStarLoad();

	// A��Ÿ ���õ� �Լ�
	void TileComposition(); // Ÿ�� ��ġ
	void TileInitializing(); // Ÿ�� ��ġ �� �Ӽ��� �°� Ÿ�� �ʱ�ȭ
	void AddOpenList(); // ���� ����Ʈ�� �߰�
	void CalculateH(); // ���� ����Ʈ �� H �����
	void CalculateF(); // F ���
	void AddCloseList(); // Ŭ���� ����Ʈ�� �߰�
	void CheckArrive(); // ��������
	
	void EffectAnim(); // ����Ʈ �ִϸ��̼�
	void EffectRender();

	void VoiceAtt();
	void VoiceHit();
	void VoiceDie();
	void VoiceCry();

	virtual void SetFirstSight() {

		if (isFirstSight == false)
		{
			VoiceCry();
			isFirstSight = true;
		}

		

	}


};

