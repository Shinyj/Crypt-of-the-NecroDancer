#pragma once
#include "./Image/Image.h"

// 벡버퍼 이미지 스태틱으로 변경
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
	//Image* m_backBuffer; //백버퍼
	void SetBackBuffer(); //백버퍼 셋팅

	HDC m_hdc;



public:
	GameNode();
	virtual ~GameNode();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	int _ctrlSelect; // 선택 여부 판단
	virtual void SetMap();
	virtual void Save();
	virtual void Load();

	void SetCtrlSelect(int num) { _ctrlSelect = num; }

	//백버퍼 얻어오기
	Image* GetBackBuffer() { return m_backBuffer;}

	// 메모리 DC 얻기
	HDC GetMemDC() { return m_backBuffer->getMemDC();  }
	// HDC 얻기
	HDC GetHDC() { return m_hdc; }

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

