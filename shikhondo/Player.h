#pragma once
#include "Character.h"

enum class MoveState
{
	NORMAL,
	SLOW,
};

class Player : public Character
{
public:

	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)


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

private:
	void Idle();
private:

	MoveState moveState;
	// ��ź ����
	int boomCount;

	bool isFire;
	TimerHandle idleTimer;
	TimerHandle fireTimer;
};

