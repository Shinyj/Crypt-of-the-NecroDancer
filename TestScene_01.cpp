#include "stdafx.h"
#include "TestScene_01.h"


TestScene_01::TestScene_01()
{
}


TestScene_01::~TestScene_01()
{
}

HRESULT TestScene_01::Init()
{

	return S_OK;
}

void TestScene_01::Release()
{
}

void TestScene_01::Update()
{
	if(KEYMANAGER->IsOnceKeyDown('2'))
	{ 
		// 씬 변경
		SCENEMANAGER->ChangeScene("Scene2");
	}
}

void TestScene_01::Render()
{
	IMAGEMANAGER->Render("배경화면", GetMemDC());
}
