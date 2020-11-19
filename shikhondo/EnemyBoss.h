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

	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��

	void RandLocation();
	void LocationReset();

	void patten1(FPOINT MPos, float MAngle);
private:
	void Idle();

};

