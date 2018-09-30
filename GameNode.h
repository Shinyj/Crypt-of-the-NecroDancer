#pragma once
#include "./Image/Image.h"

// ������ �̹��� ����ƽ���� ����
static Image * m_backBuffer = IMAGEMANAGER->AddImage("backBuffer", WINSIZEX, WINSIZEY);

enum CTRL
{
	CTRL_SAVE,
	CTRL_LOAD,
	CTRL_TERRAINDRAW,
	CTRL_OBJDRAW,
	CTRL_ERASER,
	CTRL_MAP1,
	CTRL_MAP2,
	CTRL_END
};

class GameNode
{
private:
	//Image* m_backBuffer; //�����
	void SetBackBuffer(); //����� ����

	HDC m_hdc;



public:
	GameNode();
	virtual ~GameNode();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	int _ctrlSelect; // ���� ���� �Ǵ�
	virtual void SetMap();
	virtual void Save();
	virtual void Load();

	void SetCtrlSelect(int num) { _ctrlSelect = num; }

	//����� ������
	Image* GetBackBuffer() { return m_backBuffer;}

	// �޸� DC ���
	HDC GetMemDC() { return m_backBuffer->getMemDC();  }
	// HDC ���
	HDC GetHDC() { return m_hdc; }

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

