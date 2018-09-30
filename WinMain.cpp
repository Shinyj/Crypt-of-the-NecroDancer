#include "stdafx.h"
#include "./MainGame/COTND/MainGame.h"

MainGame* mg;

HINSTANCE hInstance;
HWND hWnd;
POINT ptMouse = { 0, 0 };
//�Լ� ���漱��
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);
//������ �����Լ�

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{
	//���ΰ��� Ŭ���� �����Ҵ�
	mg = new MainGame;
	
	//HBRUSH hb = ::CreateSolidBrush(RGB(222, 231, 249));
	hInstance = hInstance;
	//WNDCLASS : ������ â�� ������ �����ϱ� ���� ����ü
	//������â ����ü ���� �� �ʱ�ȭ
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;	//������ Ŭ�������� ����ϰ��� �ϴ� ������ �޸𸮾��� ����Ʈ ������ ����
	wndClass.cbWndExtra = 0;	//cbClsExtra �����ϵ� ���� �����쿡�� ����ϰ��� �ϴ� ������ �޸𸮾��� ����
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//������ �۾������� ĥ�� ��� �귯�ø� ����
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//Ŭ���� Ŀ���� ����
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//Ÿ��Ʋ���� �»�ܿ� ������ �����ܰ� �����찡 �ּ�ȭ �Ǿ����� ������ �������� ����
	wndClass.hInstance = hInstance;	//������ Ŭ������ ����� �������α׷��� �ν��Ͻ� �ڵ�
	wndClass.lpfnWndProc = (WNDPROC)WndProc;	//�޼����� ó���ϴ� �Լ��� ����(������ ���ν���)
	wndClass.lpszClassName = WINNAME;	//����ϰ��� �ϴ� ������ Ŭ���� �̸�
	wndClass.lpszMenuName = NULL;			//Ŭ�����κ��� ������� �����찡 ����� �޴��� ����
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	//������ Ŭ������ ��Ÿ���� ����
	
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	int FrameX, FrameY, CaptionY;
	FrameX = GetSystemMetrics(SM_CXFRAME);
	FrameY = GetSystemMetrics(SM_CYFRAME);
	CaptionY = GetSystemMetrics(SM_CYCAPTION);

	//������ Ŭ���� ���
	RegisterClass(&wndClass);

	//������ â ����
	hWnd = CreateWindow(
		WINNAME,			//������ Ŭ������ �̸�
		WINNAME,			//������ Ÿ��Ʋ�� �̸�
		WS_OVERLAPPEDWINDOW,//������ ��Ÿ��
		WINSTARTX,			//������ ȭ���� x��ǥ
		WINSTARTY,			//������ ȭ���� y��ǥ
		WINSIZEX + (FrameX<<1),			//������ ȭ���� ����ũ��
		WINSIZEY + (FrameY<<1) + CaptionY + 8,			//������ ȭ���� ����ũ��
		NULL,				//�θ�������
		(HMENU)NULL,		//�޴��ڵ�
		hInstance,			//�ν��Ͻ� ����
		NULL);				//������� ����

							//ȭ�鿡 ������ �����ֱ�
	ShowWindow(hWnd, nCmdShow);

	//���ΰ��� Ŭ���� �ʱ�ȭ ���н� �����ض�
	//SUCCEDED() ������ ���ǹ�
	//���������� ���ǹ� 
	if (FAILED(mg->Init()))
	{
		return 0;
	}

	//MSG : �ü������ �߻��ϴ� �޼��� ������ �����ϱ� ���� ����ü
	MSG message;

	//TranslateMessage : Ű���� �Է¸޼����� ó�� ���
	//�Էµ� Ű�� �������� Ȯ�� �� �빮��,�ҹ���,�ѱ�,���� ���
	//WM_CHAR �޼����� �߻���Ų��.

	//DispatchMessage : ������ ���ν����� ���޵� �޼����� ���� ������� 
	//�������ش�.

	//GetMessage : ������


	//�޽��� ���� /////////////////////////////////////////////////
	
	
	//���ӿ� �޼��� ����
	
	while(true)
	{  // ���� ���� ������ ���ϸ� �̺κ��� ���� ��
		if(PeekMessage(&message, NULL,0,0, PM_REMOVE))
		{
			if(message.message == WM_QUIT) break;

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{ // ���� ������ ������ ���� ���¸��� �ڵ����� ���ư�
			TIMER->Update(60.0f);
			mg->Update();
			mg->Render();
		}
	}


	// �Ϲݿ� ����
	/*while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}*/

	return message.wParam;
}


//������ ���ν��� : �޼����� �ü���� ���� ������ �ü���� ȣ�����ش�.
//hWnd : ��� �����쿡�� �߻��� �޼������� ����
//iMessage : �޼��� ���� ��ȣ
//wParam : unsigned int ���콺 ��ư�� ����, Ű���� ����Ű�� ���¸� �����Ѵ�.
//lParam : unsigned long ���콺 Ŭ�� ��ǥ�� ����
//CALLBACK �Լ��� � �̺�Ʈ�� �߻� ���� �� ������ �˷��޶�� �ϴ� ��!(�� ȣ�� �Ǵ� ���̶�� ������)
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return mg->MainProc(hWnd, iMessage, wParam, lParam);
}
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	//���� ������ ũ�� ����
	AdjustWindowRect(&rc, WINSTYLE, false);
	//�� RECT ������ ������ ������ ����
	SetWindowPos(hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);

}
//���� 
/*
1. �ݹ��Լ�
2. DC
3. PAINTSTRUCT
4. GetDc/ReleaseDC
5. BeginPaint() / EndPaint()
6. WM_CREATE
7. WM_PAINT
*/