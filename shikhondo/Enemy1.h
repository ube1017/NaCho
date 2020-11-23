#pragma once
#include "Enemy.h"

class Enemy1 : public Enemy
{
private:
	TimerHandle idleTimer;
	int pattenX;
	int pattenY;
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
	void monsterPatten(int locationCount);
	void monsterPatten2();
};

