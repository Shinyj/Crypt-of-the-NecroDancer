#include "stdafx.h"
#include "GameNode.h"
GameNode::GameNode()
{
}

GameNode::~GameNode()
{
}
HRESULT GameNode::Init()
{
	//초기화
	//SetTimer(핸들 , 번호 , 시간 , 함수);
	//지정한 시간에 맞춰서 WM_TIMER을 실행한다.
	//시간은 1000 = 1초 
	m_hdc = GetDC(hWnd);
	
	SetTimer(hWnd, 1, 10, NULL);
	KEYMANAGER->Init();
	TIMER->Init();
	SOUNDMANAGER->Init();

	SetBackBuffer(); // 백버퍼 초기화(나중에 지울것)
	return S_OK;
}
void GameNode::Release()
{
	//해제 (윈도우 창을 종료할떄)
	KillTimer(hWnd, 1);
	KEYMANAGER->ReleaseSingleton();
	RND->ReleaseSingleton();
	IMAGEMANAGER->Release();
	IMAGEMANAGER->ReleaseSingleton();
	SCENEMANAGER->Release();
	SCENEMANAGER->ReleaseSingleton();
	TIMER->Release();
	TIMER->ReleaseSingleton();
	SOUNDMANAGER->Release();
	SOUNDMANAGER->ReleaseSingleton();

	SAFE_DELETE(m_backBuffer);

}
void GameNode::Update() 
{
	//매초 마다 실행시켜 줄 녀석
	
	SOUNDMANAGER->Update();
	//나중에 고성능 타이머를 만든후엔느 사용하지 않음
	//더블버퍼링 이후 사용하지 않는다 (true->false);
	InvalidateRect(hWnd, NULL, false);
}
void GameNode::Render() 
{


}

void GameNode::SetMap()
{

}

void GameNode::Save()
{

}

void GameNode::Load()
{

}

void GameNode::SetBackBuffer() //백버퍼 셋팅
{
	m_backBuffer = new Image;
	m_backBuffer->Init(WINSIZEX, WINSIZEY);
}
LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage)
	{
	case WM_TIMER:
		this->Update();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->Render();
		//TIMER->Render(GetMemDC());
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		//마우스 좌표
		ptMouse.x = LOWORD(lParam);
		ptMouse.y = HIWORD(lParam);
		
		if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON)) this->SetMap();
		break;
	case WM_COMMAND :
		// 프로그램 실행 중 사용하가 메류 항목을 선택하면 발생
		switch (LOWORD(wParam))
		{
		case CTRL_SAVE :
			this->Save();
			break;
		case CTRL_LOAD :
			this->Load();
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		default :
			this->SetCtrlSelect(LOWORD(wParam));
			break;
		}
		
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		//case VK_ESCAPE:
		//	PostQuitMessage(0);
		//	break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));

}
