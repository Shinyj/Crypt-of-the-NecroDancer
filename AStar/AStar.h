#pragma once

#include "../GameNode.h"
#define TILE_X 20
#define TILE_Y 20
#define WIDTH 40
#define HEIGHT 40

#define BIGNUM 5000 // 충분히 큰 F 값

// 타일 속성
enum TILE_TYPE
{
	TILE_TYPE_EMPTY, // 빈타일 (지나갈 수 있음)
	TILE_TYPE_START,// 시작 지점
	TILE_TYPE_END,	// 도착 지점
	TILE_TYPE_WALL	// 벽
};

// 현재 상태
enum ASTAR_STATE
{
	ASTAR_STATE_SEARCHING, // 경로를 탐색 중이다.
	ASTAR_STATE_FOUND, // 최단 거리를 찾았다.
	ASTAR_STATE_NOWAY, // 경로를 찾을 수 없다.
	ASTAR_STATE_END // 타일 배치 완료전
};

struct  aStarTile
{
	RECT rc;
	COLORREF color;
	bool walkable; // 지나갈 수 있는 길인지 아닌지 여부
	bool listOn; // openList 추가 여부
	int i, j; // 배열 인덱스
	int F, G, H;
	// G 시작 지점에서 현재 노드까지 비용
	// H 현재 노드에서 도착점까지 비용
	// F 총 비용
	char str[128];
	aStarTile * parent; // 부모 타일 주소 (링크드 리스트)
	TILE_TYPE type; // 타일 속성
};

class AStar : public GameNode
{
private :
	aStarTile _tile[TILE_X][TILE_Y];
	vector<aStarTile*> _openList;
	vector<aStarTile*> _closeList;

	ASTAR_STATE _aStarState; // 상태

	TILE_TYPE _selectedType;
	COLORREF _selectedTypeColor;

	int _startX, _startY;
	int _endX, _endY;
	int _lastIndex; // 가장 마지막에 추가된
	// 클로즈 리스트 인덱스

	bool _startPointSet; // 시작지점 배치 여부
	bool _endPointSet; // 도착지점 베치 여부

	int Ci; // 마지막으로 추가된 클로즈 리스트 I
	int Cj; // 마지막으로 추가된 클로즈 리스트 j
	int Cg; // 마지막으로 추가된 클로즈 리스트 비용

public:

	AStar();
	~AStar();

	HRESULT Init();
	void Update();
	void Release();
	void Render();
	
	//Initialsize -> Init
	void TileComposition(); // 타일 배치
	void TileInitializing(); // 타일 배치 후 속성에 맞게 타일 초기화
	void AddOpenList(); // 오픈 리스트에 추가
	void CalculateH(); // 오픈 리스트 내 H값 계산
	void CalculateF(); // F 계산
	void AddCloseList(); // 클로즈 리스트에 추가
	void CheckArrive(); // 도착 여부
	void ShowWay(aStarTile * tile); // 도착후 경로를 보여줌

};

