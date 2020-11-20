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

	HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	void Release();				// 메모리 해제
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);		// 프레임 단위 출력 (이미지, 텍스트 등)


	void AddSoulGauge(int value) { this->soulGauge += value; }
	int GetSoulGauge() { return this->soulGauge; }
	//int* GetSoulGauge_ptr() { return &this->soulGauge; }
	
	void AddBoom(int value) { this->boomCount += value; }
	int GetBoom() { return this->boomCount; }
	//int* GetBoom_ptr() { return &this->boomCount; }

	int GetHp() { return this->hp; }

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
	// 폭탄
	void SpecialAbility();

	// 무적
	void Invincibility();
private:
	void Idle();
private:
	FPOINT homingShooterPos[2];
	MoveState moveState;
	ImageDrawInfo soulGaugeLeft;
	ImageDrawInfo soulGaugeRight;
	//HeroProgress
	// 폭탄 갯수
	int boomCount;
	int soulGauge;
	
	bool testMode;
	bool isFire;
	TimerHandle idleTimer;
	TimerHandle fireTimer;
	TimerHandle invincibilityTimer;
};

