#pragma once
#include "../../GameNode.h"
enum playerState
{
	PS_IDLE,
	PS_RUN
};

class Minimap : public GameNode
{
private :
	Image * _megaman;
	int _alpha;
	int _camera;
	int _count; // Ÿ�̸� Ȱ�� ,���� �ɷ��� �ִϰ� ������ ���� �� �ִ°� ����
	int _index;
	bool _isLeft;
	playerState _ps;

public:
	Minimap();
	~Minimap();

	HRESULT Init();
	void Release();
	void Update();
	void Render();



};

