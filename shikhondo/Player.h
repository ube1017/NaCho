#pragma once
#include "Character.h"

enum class MoveState
{
	NORMAL,
	SLOW,
};

const float missileSpeed = 7.0f;
const int maxSoulGauge = 200;

class Player : public Character
{
public:

	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)


	void AddSoulGauge(int value) { this->soulGauge += value; }
	int GetSoulGauge() { return this->soulGauge; }
	//int* GetSoulGauge_ptr() { return &this->soulGauge; }
	
	void AddBoom(int value) { this->boomCount += value; }
	int GetBoom() { return this->boomCount; }
	//int* GetBoom_ptr() { return &this->boomCount; }

	int GetHp() { return this->hp; }

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
	void SpecialAbility();

	// ����
	void Invincibility();
private:
	void Idle();
private:
	FPOINT homingShooterPos[2];
	MoveState moveState;
	ImageDrawInfo soulGaugeLeft;
	ImageDrawInfo soulGaugeRight;
	//HeroProgress
	// ��ź ����
	int boomCount;
	int soulGauge;
	
	bool testMode;
	bool isFire;
	TimerHandle idleTimer;
	TimerHandle fireTimer;
	TimerHandle invincibilityTimer;
};

