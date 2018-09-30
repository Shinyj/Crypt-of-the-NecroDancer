#include "stdafx.h"
#include "IntroScene.h"


IntroScene::IntroScene()
{
}


IntroScene::~IntroScene()
{
}
	static HWND hWndVideo = 0;
	TCHAR strMsg[128];

HRESULT IntroScene::Init()
{
	HWND MCIWndCreate(
		HWND hWnd,
		HINSTANCE hInstance,
		DWORD MCIWnd,
		LPSTR device
	);

	return S_OK;
}

void IntroScene::Release()
{
}

void IntroScene::Update()
{
	MCI_ANIM_OPEN_PARMS mciOp;

	mciOp.dwCallback = NULL;

	mciOp.wDeviceID = 0;

	mciOp.lpstrDeviceType = "AVIVideo";

	mciOp.lpstrElementName = "video/intro_silent.ogv";

	//mciOp.lpstrAlias = WS_CHILD;

	mciOp.hWndParent = NULL;


		mciSendCommand(0, MCI_OPEN, MCI_WAIT | MCI_OPEN_ELEMENT |

			MCI_ANIM_OPEN_WS | MCI_ANIM_OPEN_PARENT,

			(DWORD)(LPVOID)&mciOp);



		MCI_PLAY_PARMS mciPP;



	mciPP.dwCallback = 0;

	mciPP.dwFrom = 0;

	mciPP.dwTo = 0;

	//mciPP.dwSpeed = 0;



	mciSendCommand(mciOp.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPP);
}

void IntroScene::Render()
{
}
