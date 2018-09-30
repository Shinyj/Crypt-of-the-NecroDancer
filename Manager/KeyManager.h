#pragma once
#include<bitset>

//class SingletonBase;
#include "SingletonBase.h"

using namespace std;

#define KEYMAX 256

class KeyManager : public singletonBase<KeyManager>
{
private:
	bitset<KEYMAX> m_keyUp;
	bitset<KEYMAX> m_keyDown;
public:
	KeyManager();
	~KeyManager();

	HRESULT Init();

	//키가 한번만 눌렸냐?
	bool IsOnceKeyDown(int key);
	//키가 한번 눌렀다 띄었냐?
	bool IsOnceKeyUp(int key);
	//키가 계속 눌려있냐?
	bool IsStayKeyDown(int key);
	//토글키냐?(캡스락, 넘버락 등등)
	bool IsToggleKey(int key);
};

