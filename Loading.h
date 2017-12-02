#pragma once
#include "GameNode.h"
#include "ProgressBar.h"

// �ε� ������ ����
enum LOAD_KIND
{
	LOAD_KIND_IMAGE_0,		// �� ��Ʈ ��
	LOAD_KIND_IMAGE_1,		// �Ϲ� �̹���
	LOAD_KIND_IMAGE_2,		// �Ϲ� �̹��� (��ġ��ǥ)
	LOAD_KIND_FRAMEIMAGE_0, // ������ �̹���
	LOAD_KIND_FRAMEIMAGE_1, // ������ �̹��� (��ġ��ǥ)
	LOAD_KIND_SOUND,		// ����
	LOAD_KIND_END			// �������� �˷��� END
};

// �̹��� ���ҽ� ����ü
struct tagImageResource
{
	string keyName;			// �̹��� Ű��
	const char * fileName;	// ���� �̸�
	int x, y;				// ��ǥ
	int width, height;		// ũ��
	int frameX, frameY;		// ������
	bool isTrans;				// ��� ���� ����
	COLORREF transColor;	// ���� �÷�Ű
};

class LoadItem // ���ҽ����� �θ� �� �������̶�� ��
{
private :
	LOAD_KIND _kind;
	tagImageResource _imageResource;

public :
	// Ű ������ �� ��Ʈ�� �ʱ�ȭ
	HRESULT IniForImage(string ketName, int width, int height);
	
	// Ű ������ �̹��� ���� �ʱ�ȭ
	HRESULT InitForImage(string keyName, const char * fileName,
		int width, int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT InitForImage(string keyName, const char * fileName, float x, float y,
		int width, int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	
	// Ű ������ ������ �̹��� ���� �ʱ�ȭ
	HRESULT InitForFrameImage(string keyName, const char * fileName, int width, int height,
		int frameX, int frameY,bool isTrans = false, COLORREF transColor = RGB(255,0,255));
	HRESULT InitForFrameImage(string keyName, const char * fileName,float x, float y, int width, int height,
		int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));

	// �ε� ������ ���� ��������
	LOAD_KIND GetLoadingKind() { return _kind; }
	// �̹��� ���ҽ� ��������
	tagImageResource GetImageResource() { return _imageResource; }

};

class Loading : public GameNode
{
private :
	typedef vector<LoadItem*> arrLoadItem;
private :
	arrLoadItem _vLoadItem;
	
	// �ε�ȭ�鿡�� ����� �̹��� �� �ε� ��
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

	// Ű ������ �� ��Ʈ�� �ʱ�ȭ
	HRESULT IniForImage(string ketName, int width, int height);

	// Ű ������ �̹��� ���� �ʱ�ȭ
	HRESULT InitForImage(string keyName, const char * fileName,
		int width, int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT InitForImage(string keyName, const char * fileName, float x, float y,
		int width, int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));

	// Ű ������ ������ �̹��� ���� �ʱ�ȭ
	HRESULT InitForFrameImage(string keyName, const char * fileName, int width, int height,
		int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT InitForFrameImage(string keyName, const char * fileName, float x, float y, int width, int height,
		int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));

	// �ε��� �Ϸ� �ƴ°� ? (�ε� �Ϸ� �� �� ����)
	bool LoadingDone();
	// �ε� ������ ���� ��������
	vector<LoadItem*> GetLoadItem() { return _vLoadItem; }

};

