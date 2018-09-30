// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
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
#include "./RandomFunction.h"
#include "./Util/Util.h"
using namespace UTIL;



//////�Ŵ���////////////////
#include "./Manager/KeyManager.h"
#include "./Manager/ImageManager.h"
#include "./Manager/SceneManager.h"
#include "./Manager/TimeManager.h"
#include "Inidata.h"
#include "./Manager/SoundManager.h"

// "GameObject.h"
//�̱��� �߰�
#define KEYMANAGER KeyManager::GetSingleton()
#define RND RandomFunction::GetSingleton()
#define IMAGEMANAGER ImageManager::GetSingleton()
#define SCENEMANAGER SceneManager::GetSingleton()
#define SOUNDMANAGER SoundManager::GetSingleton()
#define TIMEMANAGER TimeManager::GetSingleton()

// Ÿ�� �Ŵ����� ���� ������� ���� ���� ���� �����൵ ��

// �����ι� (������ �ʱ�ȭ ����) 
#define WINNAME (LPTSTR)(TEXT("2D API FrameWork"))
#define WINSTARTX 100
#define WINSTARTY 50
#define WINSIZEX 1600 //960 // 1600 // ���� + �� ���� + ������ ���� �̹���
#define WINSIZEY 900 //540// 900
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define WINSIZEX2 960
#define WINSIZEY2 540

//��ũ�� �Լ� (���ΰ����� ������(����) �κп��� ���);
#define SAFE_DELETE(p)  {if(p) {delete(p); (p) =nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p){if(p) {(p)->Release(); delete(p); (p) = nullptr;}}

#include "./Manager/ObjectManager.h"
#define OBJECTMANAGER ObjectManager::GetSingleton()

//��������(�ν��Ͻ� , ������ �ڵ� , ���콺 ��ǥ)

extern HINSTANCE hInstance;
extern HWND hWnd;
extern POINT ptMouse;
//extern RECT globalRC = { 0,0,960,540 };
// TODO: reference additional headers your program requires here
