#pragma once

#define ONE_RAD 0.017435
#define PI 3.141592654
#define PI2 (PI * 2)

#define PI_2  (PI / 2)
#define PI_4  (PI / 4)
#define PI_8  (PI / 8)
#define PI_16 (PI / 16)
#define PI_32 (PI / 32)

namespace UTIL 
	// 추가하고 싶은 계산식등을 넣고 이름도 본인이 편한 이름으로 변경해도 된다
{
	//두 점 사이의 각도
	float GetAngle(float startX, float startY, float endX, float endY);
	//두 점 사이의 거리
	float GetDistance(float startX, float startY, float endX, float endY);

}