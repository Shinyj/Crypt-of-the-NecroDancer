#include "stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}
//스태틱 변수인 현재씬을 널 값으로 초기화
GameNode* SceneManager::_currentScene = nullptr;

HRESULT SceneManager::Init()
{
	return S_OK;
}
void SceneManager::Release()
{
	miSceneList iter = _mSceneList.begin();
	for (iter; iter != _mSceneList.end();)
	{
		//삭제
		if (iter->second != NULL)
		{
			if (iter->second == _currentScene)
				iter->second->Release();
			SAFE_DELETE(iter->second);
			iter = _mSceneList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	_mSceneList.clear();
}
void SceneManager::Update()
{
	if (_currentScene) _currentScene->Update();
}
void SceneManager::Render()
{
	if (_currentScene) _currentScene->Render();
}

//씬 추가
GameNode* SceneManager::AddScene(string sceneName, GameNode* scene)
{
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair( sceneName, scene));

	return nullptr;
}
//씬 변경
HRESULT SceneManager::ChangeScene(string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);

	//못찾았으면 E_FAIL
	if (find == _mSceneList.end()) return E_FAIL;
	//바꾸려는 씬이 현재 씬이랑 같아도 E_FAIL
	if (find->second == _currentScene) return E_FAIL;

	//여기 까지 진행했으면 문제가 없으니 씬을 초기화 후 변경
	if (SUCCEEDED(find->second->Init()))
	{
		//혹시 기존 씬이 있으면 릴리즈
		if (_currentScene) _currentScene->Release();
		_currentScene = find->second;
		return S_OK;
	}

	return E_FAIL;
}