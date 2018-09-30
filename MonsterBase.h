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


struct aStarTile
{
	RECT rc;
	COLORREF color;
	bool walkable;
	bool listOn;
	int i, j;
	int F, G, H;
	// G 시작 지점에서 현재 노드까지 비용
	// H 현재 노드에서 도착점까지 비용
	// F 총 비용
	char str[128];
	aStarTile * parent; // 부모 타일 주소
	TILE_TYPE type; //타일 속성
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

	int m_hp; // 피통
	int m_currentHp;
	//string m_imageKey; // 이미지 키
	int damage; // 가하는 데미자
	int count; // 에니메이션 카운트
	int isRight; // 오른쪽 보고 있니
	
	int g; // 점프시 중력값
	int jump; // 점프 높이 ( 렌더시 y 축 높이 )

	int m_maxFrameX; // 출력할 이미지 프레임 x 
	int m_maxFrameY; // 출력할 이미지 프레임 y 

	bool isShowHp;
	bool isHalfMove;
	int subX;
	int subY; // 렌더떄 사용될 보조 좌표

	int MoveLoad; // 다음

	DIRECTION m_move;
	int moveCount = 0;

	// A* 관련된 변수

	aStarTile _tile[TILEX][TILEY];
	vector<aStarTile*> _openList;
	vector<aStarTile*> _closeList;

	ASTAR_STATE _aStarState; // 상태

	TILE_TYPE _selectedType;
	COLORREF _selectedTypeColor;

	int _startX, _startY;
	int _endX, _endY;
	int _lastIndex; // 가장 마지막에 추가된
					// 클로즈 리스트 인덱스

	int myMoveBeat;
	int myCurrentMoveBeat;

	bool _startPointSet; // 시작지점 배치 여부
	bool _endPointSet; // 도착지점 베치 여부

	int Ci; // 마지막으로 추가된 클로즈 리스트 I
	int Cj; // 마지막으로 추가된 클로즈 리스트 j
	int Cg; // 마지막으로 추가된 클로즈 리스트 비용

	bool isEffectAnim;
	DIRECTION direction;
	int effectCount = 0;
	int effectX;
	int effectY;
	int posX, posY;


public:
	MonsterBase();
	~MonsterBase();

	HRESULT Init(string key, int pos); // 몹마다 재정의 해야할듯
	void Release();					   // 몹마다 재정의 해야할듯
	void Update();					   // 몹마다 재정의 해야할듯
	void Render();					   // 몹마다 재정의 해야할듯

	void Anim(); // 몹마다 재정의 해야할듯

	void Move(); 
	void Attcked(DIRECTION dir);
	virtual void Defence(int damage);

	void Die();

	void JumpMove();

	void RendomLoad();
	void PatternLoad();
	bool AStarLoad();

	// A스타 관련된 함수
	void TileComposition(); // 타일 배치
	void TileInitializing(); // 타일 배치 후 속성에 맞게 타일 초기화
	void AddOpenList(); // 오픈 리스트에 추가
	void CalculateH(); // 오픈 리스트 내 H 값계산
	void CalculateF(); // F 계산
	void AddCloseList(); // 클로즈 리스트에 추가
	void CheckArrive(); // 도착여부
	
	void EffectAnim(); // 이펙트 애니메이션
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

