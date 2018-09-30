#include "stdafx.h"
#include "../../stdafx.h"
#include "Loading.h"
#include "../ProgressBar/ProgressBar.h"
//Ű������ �� ��Ʈ�� �ʱ�ȭ
HRESULT LoadItem::InitForImage(string keyName, int width, int height)
{
	_kind = LOAD_KIND_IMAGE_0;

	//�̹��� ����ü
	memset(&_imageResource, 0, sizeof(tagImageResource));
	_imageResource.keyName = (string)keyName;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
} 
//Ű������ �̹��� ���� �ʱ�ȭ

HRESULT LoadItem::InitForImage(string keyName, const char* fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	_kind = LOAD_KIND_IMAGE_1;

	//�̹��� ����ü
	memset(&_imageResource, 0, sizeof(tagImageResource));
	_imageResource.keyName = (string)keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}
HRESULT LoadItem::InitForImage(string keyName, const char* fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	_kind = LOAD_KIND_IMAGE_2;

	//�̹��� ����ü
	memset(&_imageResource, 0, sizeof(tagImageResource));
	_imageResource.keyName = (string)keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}
//Ű������ ������ �̹��� ���� �ʱ�ȭ
HRESULT LoadItem::InitForFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	//�̹��� ����ü
	memset(&_imageResource, 0, sizeof(tagImageResource));
	_imageResource.keyName = (string)keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}
HRESULT LoadItem::InitForFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	//�̹��� ����ü
	memset(&_imageResource, 0, sizeof(tagImageResource));
	_imageResource.keyName = (string)keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT LoadItem::IniteForSound(string KeyName, const char* fileName, bool bgm, bool Loop)
{
	_kind = LOAD_KIND_SOUND;

	memset(&_soundResource, 0, sizeof(tagSoundResouce));
	_soundResource.keyName = (string)KeyName;
	_soundResource.fileName = fileName;
	_soundResource.bgm = bgm;
	_soundResource.loop = Loop;

	return S_OK;
}

HRESULT Loading::Init()
{
	//�ε�ȭ�� ��׶��� �ʱ�ȭ
	_background = IMAGEMANAGER->AddImage("backLoading", "images/intro/mainmenu.bmp", 960, 540);
	_loading = IMAGEMANAGER->AddImage("endLoading","images/intro/console_loading.bmp",WINSIZEX/2 - 96,500,192,46,true,RGB(255,0,255));
	_endLoading = IMAGEMANAGER->AddImage("loading","images/intro/continue.bmp",
		WINSIZEX/2 - 220,500,440,36,true,RGB(255,0,255));
	

	
	//�ε��� �ʱ�ȭ
	_loadingBar = new ProgressBar;
	_loadingBar->Init("images/intro/continue.bmp", "images/intro/continue.bmp",
		100, 500, 600, 20);
	_loadingBar->SetGauge(0, 0);

	////�ε��� ������ �ʱ�ȭ
	_currentGauge = 0;
	return S_OK;
}
void  Loading::Release()
{
	//SAFE_DELETE(_loadingBar);
	SAFE_DELETE(_background);
	SAFE_DELETE(_loading);
	SAFE_DELETE(_endLoading);
	
}
void  Loading::Update()
{
	_loadingBar->Update();
}
void  Loading::Render()
{
	_background->Render(GetMemDC());
	
	if (LoadingDone())
		_endLoading->Render(GetMemDC(), 960 / 2 - 196, 540 - 40);
	else
		_loading->Render(GetMemDC(), 960 / 2 - 120, 540 - 40);
	
	// ���׶��� 
}

//Ű������ �� ��Ʈ�� �ʱ�ȭ
HRESULT  Loading::InitForImage(string keyName, int width, int height)
{
	LoadItem * item = new LoadItem;
	item->InitForImage(keyName, width, height);

	_vLoadItem.push_back(item);
	return S_OK;
}
//Ű������ �̹��� ���� �ʱ�ȭ
HRESULT  Loading::InitForImage(string keyName, const char* fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	LoadItem * item = new LoadItem;
	item->InitForImage(keyName,fileName, width, height,isTrans,transColor);

	_vLoadItem.push_back(item);
	return S_OK;
}
HRESULT  Loading::InitForImage(string keyName, const char* fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	LoadItem * item = new LoadItem;
	item->InitForImage(keyName, fileName, x,y,width, height, isTrans, transColor);

	_vLoadItem.push_back(item);
	return S_OK;
}
//Ű������ ������ �̹��� ���� �ʱ�ȭ
HRESULT  Loading::InitForFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	LoadItem * item = new LoadItem;
	item->InitForFrameImage(keyName, fileName, width, height, frameX,frameY, isTrans, transColor);

	_vLoadItem.push_back(item);
	return S_OK;
}
HRESULT  Loading::InitForFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	LoadItem * item = new LoadItem;
	item->InitForFrameImage(keyName, fileName,x,y, width, height, frameX, frameY, isTrans, transColor);

	_vLoadItem.push_back(item);
	return S_OK;
}

HRESULT Loading::InitForSound(string keyName, const char * fileName, bool bgm, bool loop)
{
	LoadItem * item = new LoadItem;
	item->IniteForSound(keyName, fileName, bgm, loop);

	_vLoadItem.push_back(item);
	return S_OK;
}

// Ű������ ������ �̹��� ���� �ʱ�ȭ

//�ε��� �Ϸ� ���???????(�ε� �Ϸ��� �� ����)
BOOL  Loading::LoadingDone()
{
	if (_currentGauge >= _vLoadItem.size())
	{
		return true;
	}

	LoadItem * item = _vLoadItem[_currentGauge];
	tagImageResource img;
	tagSoundResouce sound;

	if (item->GetLoadingKind() != LOAD_KIND_SOUND)
		 img = item->GetImageResource();
	else
		 sound = item->GetSoundResource();

	switch (item->GetLoadingKind())
	{
	case  LOAD_KIND_IMAGE_0      :
		IMAGEMANAGER->AddImage(img.keyName,
			img.width, img.height);
		break;
	case  LOAD_KIND_IMAGE_1		 :
		IMAGEMANAGER->AddImage(img.keyName,img.fileName,
			img.width, img.height,img.trans,img.transColor);
		break;
	case  LOAD_KIND_IMAGE_2		 :
		IMAGEMANAGER->AddImage(img.keyName, img.fileName,
			img.x, img.y,
			img.width, img.height, img.trans, img.transColor);
		break;
	case  LOAD_KIND_FRAMEIMAGE_0 :
		IMAGEMANAGER->AddFrameImage(img.keyName, img.fileName,
			img.width, img.height, 
			img.frameX, img.frameY,
			img.trans, img.transColor);
		break;
	case  LOAD_KIND_FRAMEIMAGE_1 :
		IMAGEMANAGER->AddFrameImage(img.keyName, img.fileName,
			img.x, img.y,
			img.width, img.height,
			img.frameX, img.frameY,
			img.trans, img.transColor);
		break;
	case  LOAD_KIND_SOUND		 :
		SOUNDMANAGER->AddSound(sound.keyName, sound.fileName, sound.bgm, sound.loop);
		// ���߿� ������ �߰��ϱ�
		break;
	}
	//// �ε��� �̹��� ����
	_loadingBar->SetGauge(_currentGauge, _vLoadItem.size());
	////ī��Ʈ
	_currentGauge++;
	return false;
}