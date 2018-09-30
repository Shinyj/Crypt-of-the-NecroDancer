#pragma once
#include "../../GameNode.h"
#include "../../Image/Image.h"

class MapTool;
class LevelEdit;
class LobbyScene;
class LoadingScene;
class Zone1_1;
class BossStatge;
class kingcongaIntro;
class IntroScene;
class TestScene;

class MainGame : public GameNode
{
private:

	LoadingScene * m_loading;
	LevelEdit * m_levelEdit;
	LobbyScene * m_lobby;
	Zone1_1 * m_zone1_1;
	BossStatge * m_bossStage;
	kingcongaIntro * m_bossIntro;
	IntroScene * m_Intro;
	TestScene * m_testMap;
public:
	MainGame();
	~MainGame();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

};
