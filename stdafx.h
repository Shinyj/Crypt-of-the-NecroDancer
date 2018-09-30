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

//////  자주사용하는 STL ////////
#include <string>
#include <map>
#include <vector>

//내가 만든 헤더 파일 이곳에 추가
#include "CommonMacroFunction.h"
#include "./RandomFunction.h"
#include "./Util/Util.h"
using namespace UTIL;



//////매니져////////////////
#include "./Manager/KeyManager.h"
#include "./Manager/ImageManager.h"
#include "./Manager/SceneManager.h"
#include "./Manager/TimeManager.h"
#include "Inidata.h"
#include "./Manager/SoundManager.h"

// "GameObject.h"
//싱글톤 추가
#define KEYMANAGER KeyManager::GetSingleton()
#define RND RandomFunction::GetSingleton()
#define IMAGEMANAGER ImageManager::GetSingleton()
#define SCENEMANAGER SceneManager::GetSingleton()
#define SOUNDMANAGER SoundManager::GetSingleton()
#define TIMEMANAGER TimeManager::GetSingleton()

// 타임 매니져는 본인 헤더에서 선언 했음 딱히 안해줘도 됨

// 디파인문 (윈도우 초기화 셋팅) 
#define WINNAME (LPTSTR)(TEXT("2D API FrameWork"))
#define WINSTARTX 100
#define WINSTARTY 50
#define WINSIZEX 1600 //960 // 1600 // 왼쪽 + 빈 공간 + 오른쪽 파일 이미지
#define WINSIZEY 900 //540// 900
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define WINSIZEX2 960
#define WINSIZEY2 540

//매크로 함수 (메인게임의 릴리즈(삭제) 부분에서 사용);
#define SAFE_DELETE(p)  {if(p) {delete(p); (p) =nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p){if(p) {(p)->Release(); delete(p); (p) = nullptr;}}

#include "./Manager/ObjectManager.h"
#define OBJECTMANAGER ObjectManager::GetSingleton()

//전역변수(인스턴스 , 원도우 핸들 , 마우스 좌표)

extern HINSTANCE hInstance;
extern HWND hWnd;
extern POINT ptMouse;
//extern RECT globalRC = { 0,0,960,540 };
// TODO: reference additional headers your program requires here
