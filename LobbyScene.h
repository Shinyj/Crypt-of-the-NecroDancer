#pragma once

#include "../../GameNode.h"
#include "../../Image/Image.h"
#include "GameObject.h"
#include "LevelEdit.h"

class LevelEdit;

class LobbyScene : public GameNode
{
private :
	
	POINT m_camera; // 카메라 좌표
	POINT m_player; // 플레이어의 좌표
	POINT m_curPlayer; // 현제 플레이어의 좌표

	tagTile _tiles[TILEX * TILEY]; // 타일들

	vector<GameObject*> m_vObj; // 게임 오브젝트 벡터
	vector<GameObject*>::iterator m_viObj; //이러레이러

	bool isOpenOption; // 옵션창을 띄웠는가!
	bool isOpenAudio; // 오디오 옵션창을 띄웠는가!

	int selectNum;
	bool selectOption[3];

	float bgmVolum;
	float effectVolum;

public:
	LobbyScene();
	~LobbyScene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
	
	void OptionUpdate();
	void OptionRedner();

	void Load();

	void OpenOption(); // 옵션 창을 열었다면

	void SetCamera();
};

