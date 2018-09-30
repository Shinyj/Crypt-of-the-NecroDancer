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
	// �߰��ϰ� ���� ���ĵ��� �ְ� �̸��� ������ ���� �̸����� �����ص� �ȴ�
{
	//�� �� ������ ����
	float GetAngle(float startX, float startY, float endX, float endY);
	//�� �� ������ �Ÿ�
	float GetDistance(float startX, float startY, float endX, float endY);

}