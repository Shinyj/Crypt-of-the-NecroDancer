#pragma once

class SingletonBase;

//��ȣ ����
class GameNode;
class SceneManager : public singletonBase<SceneManager>
{
private:
	typedef map<string, GameNode*> mSceneList;
	typedef map<string, GameNode*>::iterator miSceneList;

private:
	static GameNode* _currentScene;  //���� ��
	mSceneList _mSceneList;		  //�����

public:
	SceneManager();
	~SceneManager();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	//�� �߰�
	GameNode* AddScene(string sceneName, GameNode* scene);
	//�� ����
	HRESULT ChangeScene(string sceneName);

};

