#pragma once

#include "../../GameNode.h"
#include "../../Image/Image.h"
#include "GameObject.h"
#include "LevelEdit.h"

class LevelEdit;


class Scene : public GameNode
{
protected :
	POINT m_camera; // ī�޶� ��ǥ
	POINT m_player; // �÷��̾��� ��ǥ
	POINT m_curPlayer; // ���� �÷��̾��� ��ǥ

	tagTile _tiles[TILEX * TILEY]; // Ÿ�ϵ�

	vector<GameObject*> m_vObj; // ���� ������Ʈ ����
	vector<GameObject*>::iterator m_viObj; //�̷����̷�

	bool isOpenOption; // �ɼ�â�� ����°�!
	bool isOpenAudio; // ����� �ɼ�â�� ����°�!

	int selectNum;
	bool selectOption[3];

	float bgmVolum;
	float effectVolum;
public:
	Scene();
	~Scene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	void OptionUpdate();
	void OptionRedner();

	void Load();

	void OpenOption(); // �ɼ� â�� �����ٸ�

	void SetCamera();

};

