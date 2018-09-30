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
	int _count; // 타이머 활용 ,렉이 걸려도 애니가 프레임 따라갈 수 있는게 장점
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

