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


public:

	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��

	void RandLocation();
	void LocationReset();

	void patten1(FPOINT MPos, float MAngle);
	void patten2();
	void patten3();
	void patten4();
	void patten5();
	void bossMove();

private:
	void Idle();

};

