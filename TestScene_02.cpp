#include "stdafx.h"
#include "TestScene_02.h"


TestScene_02::TestScene_02()
{
}


TestScene_02::~TestScene_02()
{
}

HRESULT TestScene_02::Init()
{
	IMAGEMANAGER->AddImage("�ҳ�", "images/�ҳ�.bmp", WINSIZEX, WINSIZEY);
	return S_OK;
}

void TestScene_02::Release()
{
}

void TestScene_02::Update()
{
	if (KEYMANAGER->IsOnceKeyDown('1'))
	{
		SCENEMANAGER->ChangeScene("Scene1");
	}
}

void TestScene_02::Render()
{
	IMAGEMANAGER->Render("�ҳ�", GetMemDC());
}
