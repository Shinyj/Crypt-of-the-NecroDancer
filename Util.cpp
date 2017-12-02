#include "stdafx.h"
#include "Util.h"

namespace UTIL
	// 추가하고 싶은 계산식등을 넣고 이름도 본인이 편한 이름으로 변경해도 된다
{
	float GetAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;
		float distance = sqrtf(x * x + y * y);
		float angle = acosf(x / distance);

		if (endY > startY)
		{
			angle = -angle;
			if (angle >= PI2) angle -= PI2;
		}

		return angle;
	}
	float GetDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;
		return sqrtf(x * x + y * y);
	}

}