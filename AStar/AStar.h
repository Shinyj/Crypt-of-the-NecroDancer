#pragma once

#include "../GameNode.h"
#define TILE_X 20
#define TILE_Y 20
#define WIDTH 40
#define HEIGHT 40

#define BIGNUM 5000 // ����� ū F ��

// Ÿ�� �Ӽ�
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

struct  aStarTile
{
	RECT rc;
	COLORREF color;
	bool walkable; // ������ �� �ִ� ������ �ƴ��� ����
	bool listOn; // openList �߰� ����
	int i, j; // �迭 �ε���
	int F, G, H;
	// G ���� �������� ���� ������ ���
	// H ���� ��忡�� ���������� ���
	// F �� ���
	char str[128];
	aStarTile * parent; // �θ� Ÿ�� �ּ� (��ũ�� ����Ʈ)
	TILE_TYPE type; // Ÿ�� �Ӽ�
};

class AStar : public GameNode
{
private :
	aStarTile _tile[TILE_X][TILE_Y];
	vector<aStarTile*> _openList;
	vector<aStarTile*> _closeList;

	ASTAR_STATE _aStarState; // ����

	TILE_TYPE _selectedType;
	COLORREF _selectedTypeColor;

	int _startX, _startY;
	int _endX, _endY;
	int _lastIndex; // ���� �������� �߰���
	// Ŭ���� ����Ʈ �ε���

	bool _startPointSet; // �������� ��ġ ����
	bool _endPointSet; // �������� ��ġ ����

	int Ci; // ���������� �߰��� Ŭ���� ����Ʈ I
	int Cj; // ���������� �߰��� Ŭ���� ����Ʈ j
	int Cg; // ���������� �߰��� Ŭ���� ����Ʈ ���

public:

	AStar();
	~AStar();

	HRESULT Init();
	void Update();
	void Release();
	void Render();
	
	//Initialsize -> Init
	void TileComposition(); // Ÿ�� ��ġ
	void TileInitializing(); // Ÿ�� ��ġ �� �Ӽ��� �°� Ÿ�� �ʱ�ȭ
	void AddOpenList(); // ���� ����Ʈ�� �߰�
	void CalculateH(); // ���� ����Ʈ �� H�� ���
	void CalculateF(); // F ���
	void AddCloseList(); // Ŭ���� ����Ʈ�� �߰�
	void CheckArrive(); // ���� ����
	void ShowWay(aStarTile * tile); // ������ ��θ� ������

};

