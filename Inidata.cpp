#include "stdafx.h"
#include "Inidata.h"

Inidata::Inidata()
{
}


Inidata::~Inidata()
{
}

void Inidata::AddData(char * section, char * key, char * value)
{

	// 섹션이 같으면 같은 섹션 내로 키값을 기준으로 분류됨, 같은 키값이면 덮어씌워짐
	tagIniData iniData;
	iniData.section = section;
	iniData.key = key;
	iniData.value = value;

	// ini데이터 구조체 벡터에 담기
	arrIniData vIniData;
	vIniData.push_back(iniData);

	// 모든 데이터는 _vInidata에 구조체를 담은 벡터를 담기
	_vIniData.push_back(vIniData);

}

void Inidata::InitSave(char * fileName)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\Save/%s.ini", fileName);
	// \\ / <- 파일 구분의 역할 
	GetCurrentDirectory(356, str); // 현재 내 위치까지의 경로를 반환
	strcat(str, dir);
	for (int i = 0; i < _vIniData.size(); i++)
	{
		arrIniData vData = _vIniData[i];
		WritePrivateProfileString(
			vData[0].section,   // 큰 제목
			vData[0].key,     	// 구성 요소
			vData[0].value,		// 구성 요소에 작성할 정보
			str); // ini 파일 경로
		vData.clear();
	}
	_vIniData.clear();
}

char * Inidata::LoadDataString(char * fileName, char * section, char * key)
{
	char str[256];
	char dir[256];
	char data[64] = { NULL };
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\Save/%s.ini", fileName);

	GetCurrentDirectory(256,str);
	strcat(str, dir);
	GetPrivateProfileString(
		section,
		key,
		"",			// 섹션 이름이나 키이름을 찾지 못하면 디폴트 반환
		data,		// 키 값에서 가리키는 값을 저장할 버퍼
		64,			// 키 값을 저장할 버퍼 사이즈
		str			// 키 값을 찾을 ini파일 경로
	);
	return data;
}

int Inidata::LoadDataInteger(char * fileName, char * section, char * key)
{
	char str[256];
	char dir[256];

	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\Save/%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strcat(str, dir);

	return GetPrivateProfileInt(section,key,0,str);
}
