#pragma once
#include"SingletonBase.h"
#include<bitset>

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

	//Ű�� �ѹ��� ���ȳ�?
	bool IsOnceKeyDown(int key);
	//Ű�� �ѹ� ������ �����?
	bool IsOnceKeyUp(int key);
	//Ű�� ��� �����ֳ�?
	bool IsStayKeyDown(int key);
	//���Ű��?(ĸ����, �ѹ��� ���)
	bool IsToggleKey(int key);
};

