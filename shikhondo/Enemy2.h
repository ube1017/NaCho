#pragma once
#include "Enemy.h"
class Enemy2 : public Enemy
{
private:
	TimerHandle idleTimer;
	ImageDrawInfo CircleImage;
	float ImageSize1;
	float ImageSize2;
	int countSize;
	int ShootCount;
public:

	HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	void Release();				// 메모리 해제
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);		// 프레임 단위 출력 (이미지, 텍스트 등

	void RandLocation();
	void LocationReset();

	void Death() override;

private:
	void Idle();
};

