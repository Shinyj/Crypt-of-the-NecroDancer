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

	// ������ ������ ���� ���� ���� Ű���� �������� �з���, ���� Ű���̸� �������
	tagIniData iniData;
	iniData.section = section;
	iniData.key = key;
	iniData.value = value;

	// ini������ ����ü ���Ϳ� ���
	arrIniData vIniData;
	vIniData.push_back(iniData);

	// ��� �����ʹ� _vInidata�� ����ü�� ���� ���͸� ���
	_vIniData.push_back(vIniData);

}

void Inidata::InitSave(char * fileName)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\Save/%s.ini", fileName);
	// \\ / <- ���� ������ ���� 
	GetCurrentDirectory(356, str); // ���� �� ��ġ������ ��θ� ��ȯ
	strcat(str, dir);
	for (int i = 0; i < _vIniData.size(); i++)
	{
		arrIniData vData = _vIniData[i];
		WritePrivateProfileString(
			vData[0].section,   // ū ����
			vData[0].key,     	// ���� ���
			vData[0].value,		// ���� ��ҿ� �ۼ��� ����
			str); // ini ���� ���
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
		"",			// ���� �̸��̳� Ű�̸��� ã�� ���ϸ� ����Ʈ ��ȯ
		data,		// Ű ������ ����Ű�� ���� ������ ����
		64,			// Ű ���� ������ ���� ������
		str			// Ű ���� ã�� ini���� ���
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
