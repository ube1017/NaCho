#pragma once
#include "Character.h"

enum class MoveState
{
	NORMAL,
	SLOW,
};

//const float missileSpeed = 4.0f;
// ���ӵ�
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
	FPOINT Getpos() { return { this->pos.x , this->pos.y - 4}; }

	void SetIsKeyLock(bool value) { this->isKeyLock = value; }
	bool GetIsKeyLock(bool value) { return this->isKeyLock; }

	// ��ź ����� ��������
	int GetBoomAttackCount() { return this->boomAttackCount; }
	RECT GetBoomBox() { return this->boomBox; }
	class Missile* GetBoomMissile() { return this->boomMissile; }

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

	//Ư�� �ɷ� ������ �÷��̾� ǥ��
	void SpecialAbilityGauge();
private:
	void Idle();
	void HomingShooterIdle();

	// ���� ���
	void StratMove();
private:
	FPOINT homingShooterPos[2];
	MoveState moveState;
	ImageDrawInfo soulGaugeLeft;
	ImageDrawInfo soulGaugeRight;
	ImageDrawInfo soulGaugeLeft2;
	ImageDrawInfo soulGaugeRight2;
	ImageDrawInfo homingShooter[2];
	
	string missileName;
	SIZE missileSize;

	// ��ź ����
	int boomCount;
	int soulGauge;
	
	// ���� ���
	bool testMode;
	bool isFire;
	bool isSoulGaudeRender;
	//Ư���ɷ� ����ߴ���
	bool isSpecialAbility;
	// Ű���
	bool isKeyLock;
	TimerHandle homingShooteridleTimer;
	TimerHandle idleTimer;
	TimerHandle fireTimer;
	TimerHandle invincibilityTimer;
	TimerHandle boomTimer;
	TimerHandle startMoveTimer;


	class Missile* boomMissile;
	RECT boomBox;
	int boomAttackCount;
	bool startMove_back;
};

