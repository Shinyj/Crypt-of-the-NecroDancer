#include "stdafx.h"
#include "KeyManager.h"


KeyManager::KeyManager()
{
}


KeyManager::~KeyManager()
{
}

HRESULT KeyManager::Init()
{
	//키 값을 전부 눌려있지 않는 상태로 초기화
	for (int i = 0; i < KEYMAX; i++)
	{
		m_keyDown.set(i, false);
		m_keyUp.set(i, false);
	}
	return S_OK;
}

//키가 한번만 눌렸냐?
bool KeyManager::IsOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!m_keyDown[key])
		{
			m_keyDown.set(key,true);
			return true;
		}
	}
	else
	{
		m_keyDown.set(key, false);
	}

	return false;
}
//키가 한번 눌렀다 띄었냐?
bool KeyManager::IsOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		m_keyUp.set(key, true);
	}
	else
	{
		if (m_keyUp[key])
		{
			m_keyUp.set(key, false);
			return true;
		}
	}
	return false;
}
//키가 계속 눌려있냐?
bool KeyManager::IsStayKeyDown(int key)
{
	/*
	if (GetAsyncKeyState(key) & 0x8000) 
	{
		return true;
	}
	*/
	if (GetAsyncKeyState(key) & 0x8000) return true;

	return false;
}
//토글키냐?(캡스락, 넘버락 등등)
bool KeyManager::IsToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}