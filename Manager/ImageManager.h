#pragma once
#include"../Image/Image.h"
class SingletonBase;
class Image;

class ImageManager : public singletonBase<ImageManager>
{
private: 
	//맵으로 만든 이미지 목록
	typedef map<string, Image*> mapImageList;
	//map<key, data> 
	//맵으로 만든 이미지 목록 반복자(포인터)
	typedef map<string, Image*>::iterator mapImageListIter;

	mapImageList m_mImageList;

public:
	ImageManager();
	~ImageManager();

	HRESULT Init(); //매니져에 대한 초기화
	void Release(); //매니져에 대한 삭제

	//키 값으로 빈 비트맵 초기화
	Image* AddImage(string strKey, int width, int height);
	//키 값으로 이미지 파일 초기화(주 사용)
	Image* AddImage(string strKey, const char* fileName,
		int width, int height, bool isTrans = false,
		COLORREF transColor = RGB(0, 0, 0));
	Image* AddImage(string strKey, const char* fileName,
		float x, float y, int width, int height, bool isTrans = false,
		COLORREF transColor = RGB(0, 0, 0));


	//키 값으로 프레임 이미지 파일 초기화
	Image* AddFrameImage(string strKey, const char* fileName,
		int width, int height, int frameX, int frameY,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	Image* AddFrameImage(string strKey, const char* fileName,
		int x, int y, int width, int height, int frameX, int frameY,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	// 키 값으로 이미지 찾기
	Image* FindImage(string strKey);

	// 키 값으로 이미지 삭제
	bool DeleteImage(string strKey);
	// 이미지 전체삭제
	bool DeleteAll();

	//일반 랜더
	void Render(string strKey, HDC hdc);
	void Render(string strKey, HDC hdc, int destX, int destY);
	void Render(string strKey, HDC hdc, int destX, int destY,
		int sourX, int sourY, int sourWidth, int sourHeight);

	// 알파랜더
	void AlphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);

	// 프레임 랜더
	void FrameRender(string strKey, HDC hdc, int destX, int destY);
	void FrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void FrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	// 프레임 이미지 애니메이션 랜더 ( 자동 프레임 랜더 )
	void FrameAniRender(string strKey, HDC hdc, int destX, int destY);
//=============== 충돌 처리 // 바운드 박스

	RECT GetBoundBox(string strKey)
	{
		Image * image = this->FindImage(strKey);
		RECT  rc = this->FindImage(strKey)->GetBoundingBox();
		return rc;
	}
	
	/////////////////// 겟 프레임 위드
	int GetFrameWidth(string strKey)
	{
		Image * image = this->FindImage(strKey);
		return image->GetFrameWidth();
	}

	int GetFrameHeight(string strKey)
	{
		Image * image = this->FindImage(strKey);
		return image->GetFrameHeight();
	}

};

