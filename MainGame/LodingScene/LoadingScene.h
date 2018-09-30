#pragma once
#include "../../GameNode.h"
#include "../../Loading/Loading.h"

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

	// �ε� �Լ�
	void TotalLoading();
};

