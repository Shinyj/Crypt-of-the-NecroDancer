#pragma once
class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	//리로스 로딩
		LOAD_FILE,			//파일로딩
		LOAD_EMPTY,			//빈 비트맵 파일
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		resID;		//리소스ID
		HDC			hMemDC;		//메모리DC
		HBITMAP		hBit;		//비트맵(새로운 비트맵 핸들)
		HBITMAP		hOBit;		//올드 비트맵(기존 비트맵 핸들)
		float		x;			//이미지 x좌표
		float       y;			//이미지 y좌표
		int			width;		//이미지 가로크기
		int			height;		//이미지 세로크기
		int			currentFrameX; // 현재 프레임 x;
		int			currentFrameY; //현재 프레임 y;
		int			maxFrameX;		//최대 프레임 x;
		int			maxFrameY;		//최대 프레임 y;
		int			frameWidth;		//1프레임 가로길이
		int			frameHeight;	//1프레임 세로길이
		BYTE		loadType;	//로드 타입

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
	LPIMAGE_INFO m_imageInfo;	//이미지 정보
	char*		m_fileName;		//이미지 이름
	bool		m_isTranse;		//배경색 없앨거냐?(마젠타)
	COLORREF	m_transColor;	//배경색 없앨 RGB(마젠타 = RGB(255,0,255))

	BLENDFUNCTION m_blendFunc;  //알파블렌드(이미지를 투명하게)를 위한 정보
	LPIMAGE_INFO  m_blendImage; //알파블렌드를 사용하기 위한 이미지 정보

public:
	Image();
	~Image();

	//빈 비트맵 초기화
	HRESULT Init(int width, int height);
	//이미지 리소스 초기화(사용안함)
	HRESULT Init(const DWORD resID, int width, int height,
		bool isTrans = false, COLORREF transeColor = RGB(255, 0, 255));
	//이미지 파일 초기화
	HRESULT Init(const char* fileName, int width, int height,
		bool isTrans = false, COLORREF transeColor = RGB(255, 0, 255));

	HRESULT Init(const char* fileName, float x, float y, int width, int height,
		bool isTrans = false, COLORREF transeColor = RGB(255, 0, 255));

	//프레임 이미지 파일 초기화
	HRESULT Init(const char* fileName, int width, int height,
		int frameX, int frameY, bool isTrans = false, COLORREF transeColor = RGB(255, 0, 255));

	HRESULT Init(const char* fileName, int x, int y, int width, int height,
		int frameX, int frameY, bool isTrans = false, COLORREF transeColor = RGB(255, 0, 255));

	//투명키 셋팅
	void SetTransColor(bool isTrans, COLORREF transColor);

	//릴리즈
	void Release();

	//렌더(내가 지정한 위치에 이미지를 출력)
	void Render(HDC hdc);
	void Render(HDC hdc, int destX, int destY);
	void Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//알파 렌더
	void AlphaRender(HDC hdc, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//프레임 랜더
	void FrameRender(HDC hdc, int destX, int destY);
	void FrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void FrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	//루프 랜더 (hdc , 루프시킬 영역 , x오프셋, y오프셋
	//LPRECT == RECT*
	void LoopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void LoopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	///////////////////////////////////////////////////////

	//Get , Set 함수

	//DC 얻어온다
	inline HDC getMemDC() { return m_imageInfo->hMemDC; }

	//이미지 좌표 X 값 
	inline float GetX() { return m_imageInfo->x; }
	inline void SetX(float x) { m_imageInfo->x = x; }

	//이미지 좌표 Y 값
	inline float GetY() { return m_imageInfo->y; }
	inline void SetY(float y) { m_imageInfo->y = y; }

	//이미지 센터 좌표 셋팅
	inline void SetCenter(float x, float y)
	{
		m_imageInfo->x = x - (m_imageInfo->width / 2);
		m_imageInfo->y = y - (m_imageInfo->height / 2);
	}

	//가로 크기 세로크기 
	inline int GetWidth() { return m_imageInfo->width; }
	inline int GetHeight() { return m_imageInfo->height; }

	//바운딩 박스 (충돌용)
	inline RECT GetBoundingBox()
	{
		RECT rc = RectMake(m_imageInfo->x, m_imageInfo->y,
			m_imageInfo->width, m_imageInfo->height);
		return rc;
	}
	//프레임 이미지용 바운딩 박스
	inline RECT GetBoundingFrameBox()
	{
		RECT rc = RectMake(m_imageInfo->x, m_imageInfo->y,
			m_imageInfo->frameWidth, m_imageInfo->frameHeight);
		return rc;
	}

	//프레임 x 셋팅

	inline int GetFrameX() { return m_imageInfo->currentFrameX; }
	inline void SetFrameX(int frameX)
	{
		m_imageInfo->currentFrameX = frameX;

		if (frameX > m_imageInfo->maxFrameX)
		{
			m_imageInfo->currentFrameX = m_imageInfo->maxFrameX;
		}
	}

	//프레임 x 셋팅
	inline int GetFrameY() { return m_imageInfo->currentFrameY; }
	inline void SetFrameY(int frameY)
	{
		m_imageInfo->currentFrameY = frameY;

		if (frameY > m_imageInfo->maxFrameY)
		{
			m_imageInfo->currentFrameY = m_imageInfo->maxFrameY;
		}
	}
	//1프레임 가로 세로 크기
	inline int GetFrameWidth() { return m_imageInfo->frameWidth; }
	inline int GetFrameHeight() { return m_imageInfo->frameHeight; }

	//맥스 프레임 x, y
	inline int GetMaxFrameX() { return m_imageInfo->maxFrameX; }
	inline int GetMaxFrameY() { return m_imageInfo->maxFrameY; }

};

