#pragma once
#include "Enemy.h"
class Enemy2 : public Enemy
{
private:
	TimerHandle idleTimer;
	ImageDrawInfo CircleImage;

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

