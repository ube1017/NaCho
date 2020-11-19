#pragma once
#include "Character.h"

enum class MoveState
{
	NORMAL,
	SLOW,
};

const float missileSpeed = 4.0f;

class Player : public Character
{
public:

	HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	void Release();				// 메모리 해제
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);		// 프레임 단위 출력 (이미지, 텍스트 등)


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
	void Boom();

private:
	void Idle();
private:
	FPOINT homingShooterPos[2];
	MoveState moveState;
	// 폭탄 갯수
	int boomCount;

	bool isFire;
	TimerHandle idleTimer;
	TimerHandle fireTimer;
};

