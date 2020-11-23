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

	HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	void Release();				// 메모리 해제
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);		// 프레임 단위 출력 (이미지, 텍스트 등)


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
	// 키 체크 함수
	void KeyChack();
	// z키함수
	void Fire();
	// z키함수
	void FireDelay();
	// 느린 움직임
	void SlowMove();
	// C키
	void SpecialAbility();
	// 무적
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

	// 폭탄 갯수
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

