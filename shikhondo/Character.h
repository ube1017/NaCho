#pragma once
#include "pch.h"
#include "GameNode.h"

class MissileManager;

class Character : public GameNode
{
public:
	Character() : isInvincibility(false) {}
	HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	void Release();				// 메모리 해제
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);		// 프레임 단위 출력 (이미지, 텍스트 등)

	virtual void OnHit(class Missile* hitMissile) {}

	void SetMissileManager(MissileManager* manager) { this->missileManager = manager; }

	void SetPos(FPOINT pos) { this->pos = pos; }
	FPOINT Getpos() { return pos; }

	SIZE GetSize() { return size; }
	const int GetDamge() { return damge; }

	void SetIsDead(bool value) { this->isDead = value; }
	const bool GetIsDead() const { return isDead; }

	const RECT GetHitBox() { return hitBox; }

	// 캐릭터 사망함수
	virtual void Death();

protected:
	int hp;
	int damge;
	FPOINT pos;
	float speed;
	SIZE size;
	bool isDead;
	bool isInvincibility;
	RECT hitBox;
	SIZE hitBoxSize;
	MissileManager* missileManager;
	// 이미지 그릴때 필요한 정보
	ImageDrawInfo imageinfo;
};

