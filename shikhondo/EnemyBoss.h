#pragma once
#include "Enemy.h"
class EnemyBoss : public Enemy
{
private:
	TimerHandle idleTimer;
	int angleNum;
	int ShootCount;
	bool pattenCheck;

	class Missile* Em[8];

public:

	HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	void Release();				// 메모리 해제
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);		// 프레임 단위 출력 (이미지, 텍스트 등

	void RandLocation();
	void LocationReset();

	void patten1(FPOINT MPos, float MAngle);
private:
	void Idle();

};

