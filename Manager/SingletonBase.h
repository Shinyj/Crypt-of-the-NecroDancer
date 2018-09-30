#pragma once

//SingletonBase.h (�̱��� ���̽�)

//������ -> �ڵ��� ������ �ۼ��ϴ°�

//������ ���� -> ������ �Ҷ� ����� ������ �����ؼ� ����ȭ ��Ų��

//�̱��� ���� -> ��ü�� 1���� ����ڴ�.

//��ü = (�ڷ� (date, �ൿ)) ->Ŭ���� (���� , �Լ�)

// new Ŭ����(�����Ҵ�) ������ (���ҽ�) ���������� ���� ���ȴ�.


template<typename T>
class singletonBase
{
protected:
	//�̱��� �ν��Ͻ� ����
	static T* singleton;

	singletonBase() {};
	~singletonBase() {};

public:
	//�̱��� ��ü ��������
	static T* GetSingleton();
	void ReleaseSingleton();

};

//�̱��� �ν��Ͻ� ����

template <typename T>
T* singletonBase<T>::singleton = nullptr; 

//�̱��� ��ü ��������

template <typename T>
T* singletonBase<T>::GetSingleton()
{
	//�̱��� ��ü�� ������ ���� ����
	if (!singleton) singleton = new T;

	return singleton;
}

//�̱��� ��ü �޸𸮿��� ����
template <typename T>
void singletonBase<T>::ReleaseSingleton()
{
	if (singleton)
	{
		delete singleton;
		singleton = nullptr;
	}
}
