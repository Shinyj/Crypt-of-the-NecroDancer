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
	//Ű ���� ���� �������� �ʴ� ���·� �ʱ�ȭ
	for (int i = 0; i < KEYMAX; i++)
	{
		m_keyDown.set(i, false);
		m_keyUp.set(i, false);
	}
	return S_OK;
}

//Ű�� �ѹ��� ���ȳ�?
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
//Ű�� �ѹ� ������ �����?
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
//Ű�� ��� �����ֳ�?
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
//���Ű��?(ĸ����, �ѹ��� ���)
bool KeyManager::IsToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}