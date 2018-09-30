#pragma once
class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	//���ν� �ε�
		LOAD_FILE,			//���Ϸε�
		LOAD_EMPTY,			//�� ��Ʈ�� ����
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		resID;		//���ҽ�ID
		HDC			hMemDC;		//�޸�DC
		HBITMAP		hBit;		//��Ʈ��(���ο� ��Ʈ�� �ڵ�)
		HBITMAP		hOBit;		//�õ� ��Ʈ��(���� ��Ʈ�� �ڵ�)
		float		x;			//�̹��� x��ǥ
		float       y;			//�̹��� y��ǥ
		int			width;		//�̹��� ����ũ��
		int			height;		//�̹��� ����ũ��
		int			currentFrameX; // ���� ������ x;
		int			currentFrameY; //���� ������ y;
		int			maxFrameX;		//�ִ� ������ x;
		int			maxFrameY;		//�ִ� ������ y;
		int			frameWidth;		//1������ ���α���
		int			frameHeight;	//1������ ���α���
		BYTE		loadType;	//�ε� Ÿ��

		tagImage()
		{
			resID = 0;
			hMemDC = nullptr;
			hBit = nullptr;
			hOBit = nullptr;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO m_imageInfo;	//�̹��� ����
	char*		m_fileName;		//�̹��� �̸�
	bool		m_isTranse;		//���� ���ٰų�?(����Ÿ)
	COLORREF	m_transColor;	//���� ���� RGB(����Ÿ = RGB(255,0,255))

	BLENDFUNCTION m_blendFunc;  //���ĺ���(�̹����� �����ϰ�)�� ���� ����
	LPIMAGE_INFO  m_blendImage; //���ĺ��带 ����ϱ� ���� �̹��� ����

public:
	Image();
	~Image();

	//�� ��Ʈ�� �ʱ�ȭ
	HRESULT Init(int width, int height);
	//�̹��� ���ҽ� �ʱ�ȭ(������)
	HRESULT Init(const DWORD resID, int width, int height,
		bool isTrans = false, COLORREF transeColor = RGB(255, 0, 255));
	//�̹��� ���� �ʱ�ȭ
	HRESULT Init(const char* fileName, int width, int height,
		bool isTrans = false, COLORREF transeColor = RGB(255, 0, 255));

	HRESULT Init(const char* fileName, float x, float y, int width, int height,
		bool isTrans = false, COLORREF transeColor = RGB(255, 0, 255));

	//������ �̹��� ���� �ʱ�ȭ
	HRESULT Init(const char* fileName, int width, int height,
		int frameX, int frameY, bool isTrans = false, COLORREF transeColor = RGB(255, 0, 255));

	HRESULT Init(const char* fileName, int x, int y, int width, int height,
		int frameX, int frameY, bool isTrans = false, COLORREF transeColor = RGB(255, 0, 255));

	//����Ű ����
	void SetTransColor(bool isTrans, COLORREF transColor);

	//������
	void Release();

	//����(���� ������ ��ġ�� �̹����� ���)
	void Render(HDC hdc);
	void Render(HDC hdc, int destX, int destY);
	void Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//���� ����
	void AlphaRender(HDC hdc, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//������ ����
	void FrameRender(HDC hdc, int destX, int destY);
	void FrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void FrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	//���� ���� (hdc , ������ų ���� , x������, y������
	//LPRECT == RECT*
	void LoopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void LoopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	///////////////////////////////////////////////////////

	//Get , Set �Լ�

	//DC ���´�
	inline HDC getMemDC() { return m_imageInfo->hMemDC; }

	//�̹��� ��ǥ X �� 
	inline float GetX() { return m_imageInfo->x; }
	inline void SetX(float x) { m_imageInfo->x = x; }

	//�̹��� ��ǥ Y ��
	inline float GetY() { return m_imageInfo->y; }
	inline void SetY(float y) { m_imageInfo->y = y; }

	//�̹��� ���� ��ǥ ����
	inline void SetCenter(float x, float y)
	{
		m_imageInfo->x = x - (m_imageInfo->width / 2);
		m_imageInfo->y = y - (m_imageInfo->height / 2);
	}

	//���� ũ�� ����ũ�� 
	inline int GetWidth() { return m_imageInfo->width; }
	inline int GetHeight() { return m_imageInfo->height; }

	//�ٿ�� �ڽ� (�浹��)
	inline RECT GetBoundingBox()
	{
		RECT rc = RectMake(m_imageInfo->x, m_imageInfo->y,
			m_imageInfo->width, m_imageInfo->height);
		return rc;
	}
	//������ �̹����� �ٿ�� �ڽ�
	inline RECT GetBoundingFrameBox()
	{
		RECT rc = RectMake(m_imageInfo->x, m_imageInfo->y,
			m_imageInfo->frameWidth, m_imageInfo->frameHeight);
		return rc;
	}

	//������ x ����

	inline int GetFrameX() { return m_imageInfo->currentFrameX; }
	inline void SetFrameX(int frameX)
	{
		m_imageInfo->currentFrameX = frameX;

		if (frameX > m_imageInfo->maxFrameX)
		{
			m_imageInfo->currentFrameX = m_imageInfo->maxFrameX;
		}
	}

	//������ x ����
	inline int GetFrameY() { return m_imageInfo->currentFrameY; }
	inline void SetFrameY(int frameY)
	{
		m_imageInfo->currentFrameY = frameY;

		if (frameY > m_imageInfo->maxFrameY)
		{
			m_imageInfo->currentFrameY = m_imageInfo->maxFrameY;
		}
	}
	//1������ ���� ���� ũ��
	inline int GetFrameWidth() { return m_imageInfo->frameWidth; }
	inline int GetFrameHeight() { return m_imageInfo->frameHeight; }

	//�ƽ� ������ x, y
	inline int GetMaxFrameX() { return m_imageInfo->maxFrameX; }
	inline int GetMaxFrameY() { return m_imageInfo->maxFrameY; }

};

