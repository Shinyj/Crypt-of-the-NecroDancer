#pragma once

//SingletonBase.h (싱글톤 베이스)

//디자인 -> 코드의 구조를 작성하는것

//디자인 패턴 -> 디자인 할때 생기는 오류를 수정해서 정형화 시킨것

//싱글톤 패턴 -> 객체를 1개만 만들겠다.

//객체 = (자료 (date, 행동)) ->클래스 (변수 , 함수)

// new 클래스(동적할당) 데이터 (리소스) 관리용으로 많이 사용된다.


template<typename T>
class singletonBase
{
protected:
	//싱글톤 인스턴스 선언
	static T* singleton;

	singletonBase() {};
	~singletonBase() {};

public:
	//싱글톤 객체 가져오기
	static T* GetSingleton();
	void ReleaseSingleton();

};

//싱근톤 인스턴스 성언

template <typename T>
T* singletonBase<T>::singleton = nullptr; 

//싱글톤 객체 가져오기

template <typename T>
T* singletonBase<T>::GetSingleton()
{
	//싱글톤 객체가 없으면 새로 생성
	if (!singleton) singleton = new T;

	return singleton;
}

//싱글톤 객체 메모리에서 해제
template <typename T>
void singletonBase<T>::ReleaseSingleton()
{
	if (singleton)
	{
		delete singleton;
		singleton = nullptr;
	}
}
