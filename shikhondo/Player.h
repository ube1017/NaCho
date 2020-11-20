#pragma once
#include "Character.h"

enum class MoveState
{
	NORMAL,
	SLOW,
};

const float missileSpeed = 7.0f;

class Player : public Character
{
public:

	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	void OnHit(class Missile* hitMissile) override;
private:
	// Ű üũ �Լ�
	void KeyChack();
	// zŰ�Լ�
	void Fire();
	// zŰ�Լ�
	void FireDelay();
	// ���� ������
	void SlowMove();
	// ��ź
	void Boom();

	// ����
	void Invincibility();
private:
	void Idle();
private:
	FPOINT homingShooterPos[2];
	MoveState moveState;
	// ��ź ����
	int boomCount;

	bool isFire;
	TimerHandle idleTimer;
	TimerHandle fireTimer;
};

