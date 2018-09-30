#pragma once

class SingletonBase;

//»óÈ£ ÂüÁ¶
class GameNode;
class SceneManager : public singletonBase<SceneManager>
{
private:
	typedef map<string, GameNode*> mSceneList;
	typedef map<string, GameNode*>::iterator miSceneList;

private:
	static GameNode* _currentScene;  //ÇöÀç ¾À
	mSceneList _mSceneList;		  //¾À¸ñ·Ï

public:
	SceneManager();
	~SceneManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	//¾À Ãß°¡
	GameNode* AddScene(string sceneName, GameNode* scene);
	//¾À º¯°æ
	HRESULT ChangeScene(string sceneName);

};

