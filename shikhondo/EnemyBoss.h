#pragma once
#include "Enemy.h"
class EnemyBoss : public Enemy
{
private:
	TimerHandle idleTimer;
	int angleNum;
	int angleNum2;
	float ShootCount;
	bool pattenCheck;
	float missileSpeed2 = 4.0f;
	class Missile* Em[8];
	int movePCheck;
	int movePosCheck;
	int roundCheck;
	bool stopAttack;
	bool boom;
public:

	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��

	void RandLocation();
	void LocationReset();

	void patten1(FPOINT MPos, float MAngle);
	void patten2(float MSpeed);
	void patten3(float MSpeed);
	void patten4(float MSpeed);
	void patten5(float MSpeed);
	void patten6(FPOINT MPos);
	void bossMove();

private:
	void Idle();

};

