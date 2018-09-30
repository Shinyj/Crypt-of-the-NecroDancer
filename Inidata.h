#pragma once

class SingletonBase;

// init 파일은
// 3가지 section key value 를 넣을 수 있음
//        [  ]   { }  ( ) 
//       클래스  함수 변수

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
	
	// 데이터  추가용
	void AddData(char * section, char * key, char * value);
	
	// 세이브 -> 파일 이름만 넣어도 자동 저장
	void InitSave(char * fileName);
	
	// 문자값 로드
	char * LoadDataString(char * fileName, char * section, char * key);

	// 정수값 로드
	int LoadDataInteger(char * fileName, char * section, char * key);
};

#define INIDATA Inidata::GetSingleton()