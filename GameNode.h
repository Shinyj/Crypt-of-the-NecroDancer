#pragma once
#include "Image.h"

// ������ �̹��� ����ƽ���� ����
static Image * m_backBuffer = IMAGEMANAGER->AddImage("backBuffer", WINSIZEX, WINSIZEY);

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

	//����� ������
	Image* GetBackBuffer() { return m_backBuffer;}

	// �޸� DC ���
	HDC GetMemDC() { return m_backBuffer->getMemDC();  }
	// HDC ���
	HDC GetHDC() { return m_hdc; }

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

