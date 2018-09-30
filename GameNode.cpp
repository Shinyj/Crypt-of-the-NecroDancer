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
	//�ʱ�ȭ
	//SetTimer(�ڵ� , ��ȣ , �ð� , �Լ�);
	//������ �ð��� ���缭 WM_TIMER�� �����Ѵ�.
	//�ð��� 1000 = 1�� 
	m_hdc = GetDC(hWnd);
	
	SetTimer(hWnd, 1, 10, NULL);
	KEYMANAGER->Init();
	TIMER->Init();
	SOUNDMANAGER->Init();

	SetBackBuffer(); // ����� �ʱ�ȭ(���߿� �����)
	return S_OK;
}
void GameNode::Release()
{
	//���� (������ â�� �����ҋ�)
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
	//���� ���� ������� �� �༮
	
	SOUNDMANAGER->Update();
	//���߿� ���� Ÿ�̸Ӹ� �����Ŀ��� ������� ����
	//������۸� ���� ������� �ʴ´� (true->false);
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

void GameNode::SetBackBuffer() //����� ����
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
		//���콺 ��ǥ
		ptMouse.x = LOWORD(lParam);
		ptMouse.y = HIWORD(lParam);
		
		if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON)) this->SetMap();
		break;
	case WM_COMMAND :
		// ���α׷� ���� �� ����ϰ� �޷� �׸��� �����ϸ� �߻�
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
