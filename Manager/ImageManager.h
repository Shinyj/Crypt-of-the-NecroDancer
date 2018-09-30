#pragma once
#include"../Image/Image.h"
class SingletonBase;
class Image;

class ImageManager : public singletonBase<ImageManager>
{
private: 
	//������ ���� �̹��� ���
	typedef map<string, Image*> mapImageList;
	//map<key, data> 
	//������ ���� �̹��� ��� �ݺ���(������)
	typedef map<string, Image*>::iterator mapImageListIter;

	mapImageList m_mImageList;

public:
	ImageManager();
	~ImageManager();

	HRESULT Init(); //�Ŵ����� ���� �ʱ�ȭ
	void Release(); //�Ŵ����� ���� ����

	//Ű ������ �� ��Ʈ�� �ʱ�ȭ
	Image* AddImage(string strKey, int width, int height);
	//Ű ������ �̹��� ���� �ʱ�ȭ(�� ���)
	Image* AddImage(string strKey, const char* fileName,
		int width, int height, bool isTrans = false,
		COLORREF transColor = RGB(0, 0, 0));
	Image* AddImage(string strKey, const char* fileName,
		float x, float y, int width, int height, bool isTrans = false,
		COLORREF transColor = RGB(0, 0, 0));


	//Ű ������ ������ �̹��� ���� �ʱ�ȭ
	Image* AddFrameImage(string strKey, const char* fileName,
		int width, int height, int frameX, int frameY,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	Image* AddFrameImage(string strKey, const char* fileName,
		int x, int y, int width, int height, int frameX, int frameY,
		bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	// Ű ������ �̹��� ã��
	Image* FindImage(string strKey);

	// Ű ������ �̹��� ����
	bool DeleteImage(string strKey);
	// �̹��� ��ü����
	bool DeleteAll();

	//�Ϲ� ����
	void Render(string strKey, HDC hdc);
	void Render(string strKey, HDC hdc, int destX, int destY);
	void Render(string strKey, HDC hdc, int destX, int destY,
		int sourX, int sourY, int sourWidth, int sourHeight);

	// ���ķ���
	void AlphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);

	// ������ ����
	void FrameRender(string strKey, HDC hdc, int destX, int destY);
	void FrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void FrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	// ������ �̹��� �ִϸ��̼� ���� ( �ڵ� ������ ���� )
	void FrameAniRender(string strKey, HDC hdc, int destX, int destY);
//=============== �浹 ó�� // �ٿ�� �ڽ�

	RECT GetBoundBox(string strKey)
	{
		Image * image = this->FindImage(strKey);
		RECT  rc = this->FindImage(strKey)->GetBoundingBox();
		return rc;
	}
	
	/////////////////// �� ������ ����
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

