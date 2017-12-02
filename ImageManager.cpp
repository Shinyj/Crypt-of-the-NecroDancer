#include "stdafx.h"
#include "ImageManager.h"


ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
}

HRESULT ImageManager::Init() //매니져에 대한 초기화
{
	return S_OK;
}
void ImageManager::Release() //매니져에 대한 삭제
{
	DeleteAll();
}

//키 값으로 빈 비트맵 초기화
Image* ImageManager::AddImage(string strKey, int width, int height)
{
	//추가 하려는 키 값으로 이미지가 존재하는지 확인
	Image* img = FindImage(strKey);
	//추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴
	if (img) return img;

	img = new Image;
	//이미지가 재대로 초기화 되지 않았다면 NULL 리턴
	if (FAILED(img->Init(width, height)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//생성된 이미지를 맵으로 만든 이미지 목록에 추가한다.
	//m_mImageList.insert(pair<string, Image*>(strKey, img));
	m_mImageList.insert(make_pair(strKey, img));

	return img;
}
//키 값으로 이미지 파일 초기화(주 사용)
Image* ImageManager::AddImage(string strKey, const char* fileName, int width, int height, bool isTrans /*= false*/, COLORREF transColor /*= RGB(0, 0, 0)*/)
{
	//추가 하려는 키 값으로 이미지가 존재하는지 확인
	Image* img = FindImage(strKey);
	//추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴
	if (img) return img;

	img = new Image;
	//이미지가 재대로 초기화 되지 않았다면 NULL 리턴
	if (FAILED(img->Init(fileName, width, height,isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//생성된 이미지를 맵으로 만든 이미지 목록에 추가한다.
	//m_mImageList.insert(pair<string, Image*>(strKey, img));
	m_mImageList.insert(make_pair(strKey, img));

	return img;
}
Image* ImageManager::AddImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans /*= false*/, COLORREF transColor /*= RGB(0, 0, 0)*/)
{
	//추가 하려는 키 값으로 이미지가 존재하는지 확인
	Image* img = FindImage(strKey);
	//추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴
	if (img) return img;

	img = new Image;
	//이미지가 재대로 초기화 되지 않았다면 NULL 리턴
	if (FAILED(img->Init(fileName,x,y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//생성된 이미지를 맵으로 만든 이미지 목록에 추가한다.
	//m_mImageList.insert(pair<string, Image*>(strKey, img));
	m_mImageList.insert(make_pair(strKey, img));

	return img;
}
//키 값으로 프레임 이미지 파일 초기화
Image* ImageManager::AddFrameImage(string strKey, const char* fileName,int width, int height, int frameX, int frameY,bool isTrans /*= false*/, COLORREF transColor /*= RGB(0, 0, 0)*/)

{
	//추가 하려는 키 값으로 이미지가 존재하는지 확인
	Image* img = FindImage(strKey);
	//추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴
	if (img) return img;

	img = new Image;
	//이미지가 재대로 초기화 되지 않았다면 NULL 리턴
	if (FAILED(img->Init(fileName, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//생성된 이미지를 맵으로 만든 이미지 목록에 추가한다.
	//m_mImageList.insert(pair<string, Image*>(strKey, img));
	m_mImageList.insert(make_pair(strKey, img));

	return img;
}
Image* ImageManager::AddFrameImage(string strKey, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool isTrans /*= false*/, COLORREF transColor /*= RGB(0, 0, 0)*/)

{
	//추가 하려는 키 값으로 이미지가 존재하는지 확인
	Image* img = FindImage(strKey);
	//추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴
	if (img) return img;

	img = new Image;
	//이미지가 재대로 초기화 되지 않았다면 NULL 리턴
	if (FAILED(img->Init(fileName, x, y, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//생성된 이미지를 맵으로 만든 이미지 목록에 추가한다.
	//m_mImageList.insert(pair<string, Image*>(strKey, img));
	m_mImageList.insert(make_pair(strKey, img));

	return img;
}
// 키 값으로 이미지 찾기
Image* ImageManager::FindImage(string strKey)
{
	//해당키를 검색
	mapImageListIter key = m_mImageList.find(strKey);

	//m_mImageList.begin();
	//검색한 키가 마지막이 아니라면
	if (key != m_mImageList.end())
	{
		return key->second;
	}

	//검색한 키로 찾지 못하면
	return nullptr;

}
// 키 값으로 이미지 삭제
bool ImageManager::DeleteImage(string strKey)
{
	//해당키를 검색
	mapImageListIter key = m_mImageList.find(strKey);
	
	//검색한 키를 찾았다면
	if (key != m_mImageList.end())
	{
		//키 -> Image* ->Release();
		key->second->Release();
		//SAFE_DELETE(Image*);
		SAFE_DELETE(key->second);
		m_mImageList.erase(key);
		
		return true;
	}
	return false;

}
// 이미지 전체삭제
bool ImageManager::DeleteAll()
{
	mapImageListIter iter = m_mImageList.begin();
	//맵에 저장되어있는 이미지 데이터 삭제
	for (iter; iter != m_mImageList.end();)
	{
		if (iter->second != nullptr)
		{
			iter->second->Release();
			SAFE_DELETE(iter->second);
			iter = m_mImageList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	//저장 목록 삭제
	m_mImageList.clear();

	return true;
}

//일반 랜더
void ImageManager::Render(string strKey, HDC hdc)
{
	//이미지를 찾은후 랜더
	Image* img = FindImage(strKey);
	if (img) img->Render(hdc);
}
void ImageManager::Render(string strKey, HDC hdc, int destX, int destY)
{
	//이미지를 찾은후 랜더
	Image* img = FindImage(strKey);
	if (img) img->Render(hdc, destX, destY);
}
void ImageManager::Render(string strKey, HDC hdc, int destX, int destY,int sourX, int sourY, int sourWidth, int sourHeight)
{
	//이미지를 찾은후 랜더
	Image* img = FindImage(strKey);
	if (img) img->Render(hdc, destX, destY, sourX,sourY, sourWidth, sourHeight);
}

void ImageManager::FrameRender(string strKey, HDC hdc, int destX, int destY)
{
	// 이미지를 찾은 후 랜더
	Image * img = FindImage(strKey);
	if (img) img->FrameRender(hdc, destX, destY);
}

void ImageManager::FrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	// 이미지를 찾은 후 랜더
	Image * img = FindImage(strKey);
	if (img) img->FrameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void ImageManager::FrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	// 이미지를 찾은 후 랜더
	Image * img = FindImage(strKey);
	if (img) img->FrameRender(hdc, destX, destY, currentFrameX, currentFrameY, alpha);
}
