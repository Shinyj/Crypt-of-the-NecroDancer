#include "stdafx.h"
#include "../../stdafx.h"
#include "../GameNode.h"

#include "ProgressBar.h"


ProgressBar::ProgressBar()
{
}


ProgressBar::~ProgressBar()
{
}

HRESULT ProgressBar::Init(char * frontImage, char * backImage, float x, float y, int width, int height)
{
	// 체력 바 위치 초기화
	_x = x;
	_y = y;
	// 체력바 렉트 위치 및 크기 초기화
	_rcProgress = RectMake(x, y, width, height);
	// 체력바 이미지 초기화
	_progressBarFront = new Image;
	_progressBarFront->Init(frontImage, x, y, width, height,true,RGB(255,0,255));
	_progressBarBack = new Image;
	_progressBarBack->Init(backImage, x, y, width, height, true, RGB(255, 0, 255));

	// 가로 길이 초기화
	_width = _progressBarFront->GetWidth();

	return S_OK;
}

void ProgressBar::Release()
{
	SAFE_DELETE(_progressBarFront);
	SAFE_DELETE(_progressBarBack);
}

void ProgressBar::Update()
{
	_rcProgress = RectMakeCenter(
		_x + _progressBarBack->GetWidth() / 2,
		_y + _progressBarBack->GetHeight() / 2,
		_progressBarBack->GetWidth(),
		_progressBarBack->GetHeight());
}

void ProgressBar::Render()
{
	_progressBarBack->Render(GetMemDC(),_rcProgress.left, _y,
		0,0,_progressBarBack->GetWidth(),_progressBarBack->GetHeight());

	_progressBarFront->Render(GetMemDC(), _rcProgress.left, _y,
		0, 0, _width , _progressBarBack->GetHeight());
}

void ProgressBar::SetGauge(float currentGauge, float maxGauge)
{
	// 게이지 세팅은 숙제
	_width = (currentGauge / maxGauge) * _progressBarBack->GetWidth();
}
