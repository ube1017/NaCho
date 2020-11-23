#pragma once
#include "Character.h"

enum class MoveState
{
	NORMAL,
	SLOW,
};

const float missileSpeed = 7.0f;
const int maxSoulGauge = 2000;
const SIZE normalMissileSize = { 30,30 };
const SIZE specialAbilityMissileSize = { 50,50 };

class Player : public Character
{
public:

	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)


	void AddSoulGauge(int value) { if (isSpecialAbility) return;  this->soulGauge += value;if (this->soulGauge >= maxSoulGauge) this->soulGauge = maxSoulGauge; }
	int GetSoulGauge() { return this->soulGauge; }
	int* GetSoulGauge_ptr() { return &this->soulGauge; }
	
	void AddBoom(int value) { this->boomCount += value; }
	int GetBoom() { return this->boomCount; }
	int* GetBoom_ptr() { return &this->boomCount; }

	int GetHp() { return this->hp; }
	int* GetHp_ptr() { return &this->hp; }
	FPOINT Getpos() { return { this->pos.x , this->pos.y - 4}; }

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
	// CŰ
	void SpecialAbility();
	// ����
	void Invincibility();

	void Boom();
private:
	void Idle();
private:
	FPOINT homingShooterPos[2];
	MoveState moveState;
	ImageDrawInfo soulGaugeLeft;
	ImageDrawInfo soulGaugeRight;
	
	SIZE missileSize;

	// ��ź ����
	int boomCount;
	int soulGauge;
	
	bool testMode;
	bool isFire;
	bool isSoulGaudeRender;
	bool isSpecialAbility;
	TimerHandle idleTimer;
	TimerHandle fireTimer;
	TimerHandle invincibilityTimer;
	TimerHandle boomTimer;

	RECT boomtest;
	int boom = 0;
};

