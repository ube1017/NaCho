#pragma once
#include "Enemy.h"
class EnemyBoss : public Enemy
{
private:
	TimerHandle idleTimer;
	int angleNum;
	int angleNum2;
	float ShootCount;
	float pTime;
	float P3Check;
	bool pattenCheck;
	float missileSpeed2 = 4.0f;
	class Missile* Em[8];
	int movePCheck;
	int movePosCheck;
	int roundCheck;
	bool stopAttack;
	bool boom;
	int num;
public:

	HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	void Release();				// 메모리 해제
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);		// 프레임 단위 출력 (이미지, 텍스트 등

	void RandLocation();
	void LocationReset();

	void patten1(FPOINT MPos, float MAngle);
	void patten2(float MSpeed);
	void patten3(float MSpeed);
	void patten4(float MSpeed);
	void patten5(float MSpeed);
	void patten6(FPOINT MPos, float speed);
	void patten7(float MSpeed, float Mtime);
	void patten8(float MSpeed, float Mtime);
	void bossMove();

private:
	void Idle();

};

