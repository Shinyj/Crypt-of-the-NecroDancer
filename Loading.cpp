#include "stdafx.h"
#include "Loading.h"

Loading::Loading()
{
}

Loading::~Loading()
{
}

HRESULT Loading::Init()
{
	// 로딩 화면 백그라운드 초기화
	_background = IMAGEMANAGER->AddImage("소나","images/소나.bmp",WINSIZEX, WINSIZEY);

	// 로딩바 초기화
	_loadingBar = new ProgressBar;
	_loadingBar->Init("images/progressBarFront.bmp", "images / progressBarBack.bmp", 100, 500, 600, 20);
	_loadingBar->SetGauge(0, 0);

	// 로딩 바 게이지 초기화
	_currentGauge = 0;

	return S_OK;
}

void Loading::Release()
{
}

void Loading::Update()
{
}

void Loading::Render()
{
}

HRESULT Loading::IniForImage(string ketName, int width, int height)
{
	return S_OK;
}

HRESULT Loading::InitForImage(string keyName, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	return S_OK;
}

HRESULT Loading::InitForImage(string keyName, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	return S_OK;
}

HRESULT Loading::InitForFrameImage(string keyName, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	return S_OK;
}

HRESULT Loading::InitForFrameImage(string keyName, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	return S_OK;
}

bool Loading::LoadingDone()
{
	return false;
}

HRESULT LoadItem::IniForImage(string keyName, int width, int height)
{
	_kind = LOAD_KIND_IMAGE_0;

	// 이미지 구조체
	memset(&_imageResource, 0, sizeof(tagImageResource));
	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT LoadItem::InitForImage(string keyName, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{

	_kind = LOAD_KIND_IMAGE_1;

	// 이미지 구조체
	memset(&_imageResource, 0, sizeof(tagImageResource));
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;


	return S_OK;
}

HRESULT LoadItem::InitForImage(string keyName, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{

	_kind = LOAD_KIND_IMAGE_2;

	// 이미지 구조체
	memset(&_imageResource, 0, sizeof(tagImageResource));
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;


	return S_OK;
}

HRESULT LoadItem::InitForFrameImage(string keyName, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{

	_kind = LOAD_KIND_IMAGE_0;

	// 이미지 구조체
	memset(&_imageResource, 0, sizeof(tagImageResource));
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;


	return S_OK;
}

HRESULT LoadItem::InitForFrameImage(string keyName, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	_kind = LOAD_KIND_IMAGE_0;

	// 이미지 구조체
	memset(&_imageResource, 0, sizeof(tagImageResource));
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}
