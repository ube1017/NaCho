#pragma once
#include "Enemy.h"
class Enemy3 : public Enemy
{
private:
	TimerHandle idleTimer;
	int angleNum;
	int ShootCount;
public:

	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��

	void RandLocation();
	void LocationReset();

	void Death() override;
private:
	void Idle();

};

