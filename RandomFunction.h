#pragma once

//RandomFunction.h

#include "./Manager//SingletonBase.h"
#include <time.h>

class SingletonBase;

class RandomFunction : public singletonBase<RandomFunction>
{
public:
	RandomFunction()
	{
		srand(GetTickCount());
	}
	~RandomFunction(){}

	inline int GetInt(int num) { return rand() % num; }
	inline int GetFromInto(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}
	inline float GetFloat(float num)
	{
		return ((float)rand() / (float)RAND_MAX) * num;
	}
	inline float GetFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum);
	}

};