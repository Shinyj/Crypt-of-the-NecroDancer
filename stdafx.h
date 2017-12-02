// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//////  ���ֻ���ϴ� STL ////////
#include <string>
#include <map>
#include <vector>

//���� ���� ��� ���� �̰��� �߰�
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "Util.h"

using namespace UTIL;

//////�Ŵ���////////////////
#include "KeyManager.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "Inidata.h"

//�̱��� �߰�
#define KEYMANAGER KeyManager::GetSingleton()
#define RND RandomFunction::GetSingleton()
#define IMAGEMANAGER ImageManager::GetSingleton()
#define SCENEMANAGER SceneManager::GetSingleton()
// Ÿ�� �Ŵ����� ���� ������� ���� ���� ���� �����൵ ��

// �����ι� (������ �ʱ�ȭ ����) 
#define WINNAME (LPTSTR)(TEXT("2D API FrameWork"))
#define WINSTARTX 100
#define WINSTARTY 100
#define WINSIZEX 1024
#define WINSIZEY 768
#define WINSTYLE WS_CAPTION | WS_SYSMENU

//��ũ�� �Լ� (���ΰ����� ������(����) �κп��� ���);
#define SAFE_DELETE(p)  {if(p) {delete(p); (p) =nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p){if(p) {(p)->Release(); delete(p); (p) = nullptr;}}

//��������(�ν��Ͻ� , ������ �ڵ� , ���콺 ��ǥ)

extern HINSTANCE hInstance;
extern HWND hWnd;
extern POINT ptMouse;

// TODO: reference additional headers your program requires here
