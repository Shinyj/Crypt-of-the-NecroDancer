#include "stdafx.h"
#include "./MainGame/COTND/MainGame.h"

MainGame* mg;

HINSTANCE hInstance;
HWND hWnd;
POINT ptMouse = { 0, 0 };
//함수 전방선언
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);
//윈도우 메인함수

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{
	//메인게임 클래스 동적할당
	mg = new MainGame;
	
	//HBRUSH hb = ::CreateSolidBrush(RGB(222, 231, 249));
	hInstance = hInstance;
	//WNDCLASS : 윈도우 창의 정보를 저장하기 위한 구조체
	//윈도우창 구조체 선언 후 초기화
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;	//윈도우 클래스에서 사용하고자 하는 여분의 메모리양을 바이트 단위로 지정
	wndClass.cbWndExtra = 0;	//cbClsExtra 유사하되 개별 윈도우에서 사용하고자 하는 여분의 메모리양을 지정
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//윈도우 작업영역에 칠할 배경 브러시를 지정
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//클래스 커서를 지정
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//타이틀바의 좌상단에 보여줄 아이콘과 윈도우가 최소화 되었을대 보여줄 아이콘을 지정
	wndClass.hInstance = hInstance;	//윈도우 클래스를 등록한 응용프로그램의 인스턴스 핸들
	wndClass.lpfnWndProc = (WNDPROC)WndProc;	//메세지를 처리하는 함수를 지정(윈도우 프로시져)
	wndClass.lpszClassName = WINNAME;	//등록하고자 하는 윈도우 클래스 이름
	wndClass.lpszMenuName = NULL;			//클래스로부터 만들어진 윈도우가 사용할 메뉴를 지정
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	//윈도우 클래스의 스타일을 지정
	
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	int FrameX, FrameY, CaptionY;
	FrameX = GetSystemMetrics(SM_CXFRAME);
	FrameY = GetSystemMetrics(SM_CYFRAME);
	CaptionY = GetSystemMetrics(SM_CYCAPTION);

	//윈도우 클래스 등록
	RegisterClass(&wndClass);

	//윈도우 창 생성
	hWnd = CreateWindow(
		WINNAME,			//윈도우 클래스의 이름
		WINNAME,			//윈도우 타이틀바 이름
		WS_OVERLAPPEDWINDOW,//윈도우 스타일
		WINSTARTX,			//윈도우 화면의 x좌표
		WINSTARTY,			//윈도우 화면의 y좌표
		WINSIZEX + (FrameX<<1),			//윈도우 화면의 가로크기
		WINSIZEY + (FrameY<<1) + CaptionY + 8,			//윈도우 화면의 세로크기
		NULL,				//부모윈도우
		(HMENU)NULL,		//메뉴핸들
		hInstance,			//인스턴스 지정
		NULL);				//사용하지 않음

							//화면에 윈도우 보여주기
	ShowWindow(hWnd, nCmdShow);

	//메인게임 클래스 초기화 실패시 종료해라
	//SUCCEDED() 성공시 조건문
	//실패했을떄 조건문 
	if (FAILED(mg->Init()))
	{
		return 0;
	}

	//MSG : 운영체제에서 발생하는 메세지 정보를 저장하기 위한 구조체
	MSG message;

	//TranslateMessage : 키보드 입력메세지를 처리 담당
	//입력된 키가 문자인지 확인 후 대문자,소문자,한글,영문 등등
	//WM_CHAR 메세지를 발생시킨다.

	//DispatchMessage : 윈도우 프로시져에 전달된 메세지를 실제 윈도우로 
	//전달해준다.

	//GetMessage : 대기상태


	//메시지 루프 /////////////////////////////////////////////////
	
	
	//게임용 메세지 루프
	
	while(true)
	{  // 내가 뭔가 조작을 가하면 이부분이 실행 됨
		if(PeekMessage(&message, NULL,0,0, PM_REMOVE))
		{
			if(message.message == WM_QUIT) break;

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{ // 내가 동작을 취하지 않은 상태면은 자동으로 돌아감
			TIMER->Update(60.0f);
			mg->Update();
			mg->Render();
		}
	}


	// 일반용 루프
	/*while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}*/

	return message.wParam;
}


//윈도우 프로시져 : 메세지를 운영체제에 전달 강제로 운영체제가 호출해준다.
//hWnd : 어느 윈도우에서 발생한 메세지인지 구분
//iMessage : 메세지 구분 번호
//wParam : unsigned int 마우스 버튼의 상태, 키보드 조합키의 상태를 전달한다.
//lParam : unsigned long 마우스 클릭 좌표를 전달
//CALLBACK 함수는 어떤 이벤트가 발생 했을 때 나에게 알려달라고 하는 것!(즉 호출 되는 것이라고 봐야함)
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

	//실제 윈도우 크기 조정
	AdjustWindowRect(&rc, WINSTYLE, false);
	//위 RECT 정보로 윈도우 사이즈 셋팅
	SetWindowPos(hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);

}
//조사 
/*
1. 콜백함수
2. DC
3. PAINTSTRUCT
4. GetDc/ReleaseDC
5. BeginPaint() / EndPaint()
6. WM_CREATE
7. WM_PAINT
*/