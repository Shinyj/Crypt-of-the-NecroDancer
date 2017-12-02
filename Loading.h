#pragma once
#include "GameNode.h"
#include "ProgressBar.h"

// 로드 아이템 종류
enum LOAD_KIND
{
	LOAD_KIND_IMAGE_0,		// 빈 비트 맵
	LOAD_KIND_IMAGE_1,		// 일반 이미지
	LOAD_KIND_IMAGE_2,		// 일반 이미지 (위치좌표)
	LOAD_KIND_FRAMEIMAGE_0, // 프레임 이미지
	LOAD_KIND_FRAMEIMAGE_1, // 프레임 이미지 (위치좌표)
	LOAD_KIND_SOUND,		// 사운드
	LOAD_KIND_END			// 마지막을 알려줄 END
};

// 이미지 리소스 구조체
struct tagImageResource
{
	string keyName;			// 이미지 키값
	const char * fileName;	// 파일 이름
	int x, y;				// 좌표
	int width, height;		// 크기
	int frameX, frameY;		// 프레임
	bool isTrans;				// 배경 제거 여부
	COLORREF transColor;	// 투명 컬러키
};

class LoadItem // 리소스들을 부를 때 아이템이라고도 함
{
private :
	LOAD_KIND _kind;
	tagImageResource _imageResource;

public :
	// 키 값으로 빈 비트맵 초기화
	HRESULT IniForImage(string ketName, int width, int height);
	
	// 키 값으로 이미지 파일 초기화
	HRESULT InitForImage(string keyName, const char * fileName,
		int width, int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT InitForImage(string keyName, const char * fileName, float x, float y,
		int width, int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	
	// 키 앖으로 프레임 이미지 파일 초기화
	HRESULT InitForFrameImage(string keyName, const char * fileName, int width, int height,
		int frameX, int frameY,bool isTrans = false, COLORREF transColor = RGB(255,0,255));
	HRESULT InitForFrameImage(string keyName, const char * fileName,float x, float y, int width, int height,
		int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));

	// 로딩 아이템 종류 가져오기
	LOAD_KIND GetLoadingKind() { return _kind; }
	// 이미지 리소스 가져오기
	tagImageResource GetImageResource() { return _imageResource; }

};

class Loading : public GameNode
{
private :
	typedef vector<LoadItem*> arrLoadItem;
private :
	arrLoadItem _vLoadItem;
	
	// 로딩화면에서 사용할 이미지 및 로딩 바
	Image * _background;
	ProgressBar * _loadingBar;
	int _currentGauge;

public:
	Loading();
	~Loading();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	// 키 값으로 빈 비트맵 초기화
	HRESULT IniForImage(string ketName, int width, int height);

	// 키 값으로 이미지 파일 초기화
	HRESULT InitForImage(string keyName, const char * fileName,
		int width, int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT InitForImage(string keyName, const char * fileName, float x, float y,
		int width, int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));

	// 키 앖으로 프레임 이미지 파일 초기화
	HRESULT InitForFrameImage(string keyName, const char * fileName, int width, int height,
		int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT InitForFrameImage(string keyName, const char * fileName, float x, float y, int width, int height,
		int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));

	// 로딩이 완료 됐는가 ? (로딩 완료 후 씬 변경)
	bool LoadingDone();
	// 로드 아이템 벡터 가져오기
	vector<LoadItem*> GetLoadItem() { return _vLoadItem; }

};

