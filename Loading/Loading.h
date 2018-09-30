#pragma once

#include "../GameNode.h"
class ProgressBar;

//로드 아이템 종류
enum LOAD_KIND
{
	LOAD_KIND_IMAGE_0, //빈 비트맵
	LOAD_KIND_IMAGE_1, //일반 이미지
	LOAD_KIND_IMAGE_2, //일반 이미지(위치 좌표를 가지고 있는)
	LOAD_KIND_FRAMEIMAGE_0, //프레임이미지
	LOAD_KIND_FRAMEIMAGE_1, //프레임이미지(위치 좌표)
	LOAD_KIND_SOUND,
	LOAD_KIND_END
};
//이미지 리소스 구조체
struct tagImageResource
{
	string keyName;			//이미지 키값
	const char* fileName;	//파일 이름
	int x, y;				//좌표
	int width, height;		//크기
	int frameX, frameY;		//프레임
	bool trans;				//배경 제거 여부
	COLORREF transColor;	//투명 컬러키
};
// 사운드 리소스 구조체
struct tagSoundResouce
{
	string keyName;
	const char* fileName;
	bool bgm;
	bool loop;
};
class LoadItem
{
private:
	LOAD_KIND _kind;
	tagImageResource _imageResource;
	tagSoundResouce _soundResource;
	
public:
	//키값으로 빈 비트맵 초기화
	HRESULT InitForImage(string keyName, int width, int height);
	//키값으로 이미지 파일 초기화
	HRESULT InitForImage(string keyName, const char* fileName, int width,
		int height, BOOL isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT InitForImage(string keyName, const char* fileName, float x, float y,
		int width, int height, BOOL isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	//키값으로 프레임 이미지 파일 초기화
	HRESULT InitForFrameImage(string keyName, const char* fileName, int width,
		int heightm, int frameX, int frameY, BOOL isTrans = false,
		COLORREF transColor = RGB(255, 0, 255));
	HRESULT InitForFrameImage(string keyName, const char* fileName, float x, float y,
		int width, int height, int frameX, int frameY, BOOL isTrans = false,
		COLORREF transColor = RGB(255, 0, 255));

	// 키 값으로 사운드 파일 초기화
	HRESULT IniteForSound(string KeyName, const char* fileName, bool bgm = FALSE, bool Loop = false);

	//로딩 아이템 종류 가져오기
	LOAD_KIND GetLoadingKind() { return _kind; }
	//이미지 리소스 가져오기
	tagImageResource GetImageResource() { return _imageResource; }
	tagSoundResouce GetSoundResource() { return _soundResource; }
};

class Loading :public GameNode
{
private:
	typedef vector<LoadItem*> arrLoadItem;
private:
	arrLoadItem _vLoadItem;

	//로딩화면에서 사용할 이미지 및 로딩바
	Image* _background;
	Image* _loading;
	Image * _endLoading;
	ProgressBar* _loadingBar;
	int _currentGauge;

public:
	Loading() {};
	~Loading() {};

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	//키값으로 빈 비트맵 초기화
	HRESULT InitForImage(string keyName, int width, int height);
	//키값으로 이미지 파일 초기화
	HRESULT InitForImage(string keyName, const char* fileName, int width,
		int height, BOOL isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT InitForImage(string keyName, const char* fileName, float x, float y,
		int width, int height, BOOL isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	//키값으로 프레임 이미지 파일 초기화
	HRESULT InitForFrameImage(string keyName, const char* fileName, int width,
		int heightm, int frameX, int frameY, BOOL isTrans = false,
		COLORREF transColor = RGB(255, 0, 255));
	HRESULT InitForFrameImage(string keyName, const char* fileName, float x, float y,
		int width, int height, int frameX, int frameY, BOOL isTrans = false,
		COLORREF transColor = RGB(255, 0, 255));
	// 키값으로 사운드 파일 초기화
	HRESULT InitForSound(string keyName, const char* fileName, bool bgm = false, bool loop = false);
	//로딩이 완료 됬니???????(로딩 완료휴 씬 변경)
	BOOL LoadingDone();
	//로드 아이템 벡터 가져오기
	vector<LoadItem*> GetLoadItem() { return _vLoadItem; }
};

