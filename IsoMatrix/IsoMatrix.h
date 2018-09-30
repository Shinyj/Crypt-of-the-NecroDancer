#pragma once

#include "../GameNode.h"
// Ÿ�� ũ��
#define CELL_WIDTH 100
#define CELL_HEIGHT 50

#define RADIUS_WIDTH CELL_WIDTH /2
#define RADIUS_HEIGHT CELL_HEIGHT /2

//�ʱ�ȭ ��ǥ
#define INIT_X 400
#define INIT_Y 20

//Ÿ���� ����
#define TILE_COUNT_X 30
#define TILE_COUNT_Y 30


class IsoMatrix : public GameNode
{
private:
	int _tileMap[TILE_COUNT_X][TILE_COUNT_Y];
	int _isoX, _isoY;
	int _corner;

	char str[128];
public:
	IsoMatrix();
	~IsoMatrix();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	//Ÿ�ϸ� �׷��ִ� �Լ�
	void DrawTileMap();
	//������ �׷��ִ� �Լ�
	void DrawRhombus(int left, int top);
	//�ڳ� ���� (1~ 4�и�)
	int GetCornerIndex(int isoX, int isoY);
	//�ڳ� �ȿ� �ִ��� ����
	bool IsIRhombus(int corner, int isoX, int isoY);
};

