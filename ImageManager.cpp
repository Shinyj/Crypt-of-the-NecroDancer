#include "stdafx.h"
#include "ImageManager.h"


ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
}

HRESULT ImageManager::Init() //�Ŵ����� ���� �ʱ�ȭ
{
	return S_OK;
}
void ImageManager::Release() //�Ŵ����� ���� ����
{
	DeleteAll();
}

//Ű ������ �� ��Ʈ�� �ʱ�ȭ
Image* ImageManager::AddImage(string strKey, int width, int height)
{
	//�߰� �Ϸ��� Ű ������ �̹����� �����ϴ��� Ȯ��
	Image* img = FindImage(strKey);
	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �̹����� ����
	if (img) return img;

	img = new Image;
	//�̹����� ���� �ʱ�ȭ ���� �ʾҴٸ� NULL ����
	if (FAILED(img->Init(width, height)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ� �߰��Ѵ�.
	//m_mImageList.insert(pair<string, Image*>(strKey, img));
	m_mImageList.insert(make_pair(strKey, img));

	return img;
}
//Ű ������ �̹��� ���� �ʱ�ȭ(�� ���)
Image* ImageManager::AddImage(string strKey, const char* fileName, int width, int height, bool isTrans /*= false*/, COLORREF transColor /*= RGB(0, 0, 0)*/)
{
	//�߰� �Ϸ��� Ű ������ �̹����� �����ϴ��� Ȯ��
	Image* img = FindImage(strKey);
	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �̹����� ����
	if (img) return img;

	img = new Image;
	//�̹����� ���� �ʱ�ȭ ���� �ʾҴٸ� NULL ����
	if (FAILED(img->Init(fileName, width, height,isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ� �߰��Ѵ�.
	//m_mImageList.insert(pair<string, Image*>(strKey, img));
	m_mImageList.insert(make_pair(strKey, img));

	return img;
}
Image* ImageManager::AddImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans /*= false*/, COLORREF transColor /*= RGB(0, 0, 0)*/)
{
	//�߰� �Ϸ��� Ű ������ �̹����� �����ϴ��� Ȯ��
	Image* img = FindImage(strKey);
	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �̹����� ����
	if (img) return img;

	img = new Image;
	//�̹����� ���� �ʱ�ȭ ���� �ʾҴٸ� NULL ����
	if (FAILED(img->Init(fileName,x,y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ� �߰��Ѵ�.
	//m_mImageList.insert(pair<string, Image*>(strKey, img));
	m_mImageList.insert(make_pair(strKey, img));

	return img;
}
//Ű ������ ������ �̹��� ���� �ʱ�ȭ
Image* ImageManager::AddFrameImage(string strKey, const char* fileName,int width, int height, int frameX, int frameY,bool isTrans /*= false*/, COLORREF transColor /*= RGB(0, 0, 0)*/)

{
	//�߰� �Ϸ��� Ű ������ �̹����� �����ϴ��� Ȯ��
	Image* img = FindImage(strKey);
	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �̹����� ����
	if (img) return img;

	img = new Image;
	//�̹����� ���� �ʱ�ȭ ���� �ʾҴٸ� NULL ����
	if (FAILED(img->Init(fileName, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ� �߰��Ѵ�.
	//m_mImageList.insert(pair<string, Image*>(strKey, img));
	m_mImageList.insert(make_pair(strKey, img));

	return img;
}
Image* ImageManager::AddFrameImage(string strKey, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool isTrans /*= false*/, COLORREF transColor /*= RGB(0, 0, 0)*/)

{
	//�߰� �Ϸ��� Ű ������ �̹����� �����ϴ��� Ȯ��
	Image* img = FindImage(strKey);
	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �̹����� ����
	if (img) return img;

	img = new Image;
	//�̹����� ���� �ʱ�ȭ ���� �ʾҴٸ� NULL ����
	if (FAILED(img->Init(fileName, x, y, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ� �߰��Ѵ�.
	//m_mImageList.insert(pair<string, Image*>(strKey, img));
	m_mImageList.insert(make_pair(strKey, img));

	return img;
}
// Ű ������ �̹��� ã��
Image* ImageManager::FindImage(string strKey)
{
	//�ش�Ű�� �˻�
	mapImageListIter key = m_mImageList.find(strKey);

	//m_mImageList.begin();
	//�˻��� Ű�� �������� �ƴ϶��
	if (key != m_mImageList.end())
	{
		return key->second;
	}

	//�˻��� Ű�� ã�� ���ϸ�
	return nullptr;

}
// Ű ������ �̹��� ����
bool ImageManager::DeleteImage(string strKey)
{
	//�ش�Ű�� �˻�
	mapImageListIter key = m_mImageList.find(strKey);
	
	//�˻��� Ű�� ã�Ҵٸ�
	if (key != m_mImageList.end())
	{
		//Ű -> Image* ->Release();
		key->second->Release();
		//SAFE_DELETE(Image*);
		SAFE_DELETE(key->second);
		m_mImageList.erase(key);
		
		return true;
	}
	return false;

}
// �̹��� ��ü����
bool ImageManager::DeleteAll()
{
	mapImageListIter iter = m_mImageList.begin();
	//�ʿ� ����Ǿ��ִ� �̹��� ������ ����
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
	//���� ��� ����
	m_mImageList.clear();

	return true;
}

//�Ϲ� ����
void ImageManager::Render(string strKey, HDC hdc)
{
	//�̹����� ã���� ����
	Image* img = FindImage(strKey);
	if (img) img->Render(hdc);
}
void ImageManager::Render(string strKey, HDC hdc, int destX, int destY)
{
	//�̹����� ã���� ����
	Image* img = FindImage(strKey);
	if (img) img->Render(hdc, destX, destY);
}
void ImageManager::Render(string strKey, HDC hdc, int destX, int destY,int sourX, int sourY, int sourWidth, int sourHeight)
{
	//�̹����� ã���� ����
	Image* img = FindImage(strKey);
	if (img) img->Render(hdc, destX, destY, sourX,sourY, sourWidth, sourHeight);
}

void ImageManager::FrameRender(string strKey, HDC hdc, int destX, int destY)
{
	// �̹����� ã�� �� ����
	Image * img = FindImage(strKey);
	if (img) img->FrameRender(hdc, destX, destY);
}

void ImageManager::FrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	// �̹����� ã�� �� ����
	Image * img = FindImage(strKey);
	if (img) img->FrameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void ImageManager::FrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	// �̹����� ã�� �� ����
	Image * img = FindImage(strKey);
	if (img) img->FrameRender(hdc, destX, destY, currentFrameX, currentFrameY, alpha);
}
