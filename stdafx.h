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

//////  자주사용하는 STL ////////
#include <string>
#include <map>
#include <vector>

//내가 만든 헤더 파일 이곳에 추가
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "Util.h"

using namespace UTIL;

//////매니져////////////////
#include "KeyManager.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "Inidata.h"

//싱글톤 추가
#define KEYMANAGER KeyManager::GetSingleton()
#define RND RandomFunction::GetSingleton()
#define IMAGEMANAGER ImageManager::GetSingleton()
#define SCENEMANAGER SceneManager::GetSingleton()
// 타임 매니져는 본인 헤더에서 선언 했음 딱히 안해줘도 됨

// 디파인문 (윈도우 초기화 셋팅) 
#define WINNAME (LPTSTR)(TEXT("2D API FrameWork"))
#define WINSTARTX 100
#define WINSTARTY 100
#define WINSIZEX 1024
#define WINSIZEY 768
#define WINSTYLE WS_CAPTION | WS_SYSMENU

//매크로 함수 (메인게임의 릴리즈(삭제) 부분에서 사용);
#define SAFE_DELETE(p)  {if(p) {delete(p); (p) =nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p){if(p) {(p)->Release(); delete(p); (p) = nullptr;}}

//전역변수(인스턴스 , 원도우 핸들 , 마우스 좌표)

extern HINSTANCE hInstance;
extern HWND hWnd;
extern POINT ptMouse;

// TODO: reference additional headers your program requires here
