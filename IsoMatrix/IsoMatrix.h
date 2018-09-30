#pragma once

#include "../GameNode.h"
// 타일 크기
#define CELL_WIDTH 100
#define CELL_HEIGHT 50

#define RADIUS_WIDTH CELL_WIDTH /2
#define RADIUS_HEIGHT CELL_HEIGHT /2

//초기화 좌표
#define INIT_X 400
#define INIT_Y 20

//타일의 갯수
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

	//타일맵 그려주는 함수
	void DrawTileMap();
	//마름모 그려주는 함수
	void DrawRhombus(int left, int top);
	//코너 검출 (1~ 4분면)
	int GetCornerIndex(int isoX, int isoY);
	//코너 안에 있는지 검출
	bool IsIRhombus(int corner, int isoX, int isoY);
};

