#pragma once
#include "../../GameNode.h"
#include "../../Loading/Loading.h"

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

class GameNode;
class Loading;

class LoadingScene : public GameNode
{
private :
	Loading * _loading;
public:
	LoadingScene();
	~LoadingScene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	// 로딩 함수
	void TotalLoading();
};

