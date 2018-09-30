#pragma once

class SingletonBase;

// init ������
// 3���� section key value �� ���� �� ����
//        [  ]   { }  ( ) 
//       Ŭ����  �Լ� ����

struct tagIniData
{
	char * section;
	char * key;
	char * value;
};

class Inidata : public singletonBase<Inidata>
{
private :
	typedef vector<tagIniData> arrIniData;
	typedef vector<arrIniData> arrIniDatas;

private :
	arrIniDatas _vIniData;

public:
	Inidata();
	~Inidata();

	HRESULT Init();
	
	// ������  �߰���
	void AddData(char * section, char * key, char * value);
	
	// ���̺� -> ���� �̸��� �־ �ڵ� ����
	void InitSave(char * fileName);
	
	// ���ڰ� �ε�
	char * LoadDataString(char * fileName, char * section, char * key);

	// ������ �ε�
	int LoadDataInteger(char * fileName, char * section, char * key);
};

#define INIDATA Inidata::GetSingleton()