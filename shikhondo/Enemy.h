#pragma once
#include "Character.h"

class Enemy : public Character
{
public:
	Enemy();
	HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	void Release();				// 메모리 해제
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);		// 프레임 단위 출력 (이미지, 텍스트 등

	virtual void RandLocation() {}
	virtual void LocationReset() {}
	bool GetMapOutCheck() { return mapOutCheck; }
	bool GetMapInCheck() { return mapInCheck; }

	bool GetMonStop() { return stop; }

	float GetAngle();
	float GetAngle(FPOINT GetPos);

	void OnHit(class Missile* hitMissile) override;

	void SetTargetPOS(FPOINT POS) { this->RandPos = POS; }
	FPOINT GetPos() { return  this->RandPos; }
	void SetPatCheck(bool pattenCheck) { this->pattenCheck = pattenCheck; }

protected:
	string missileName;
	FPOINT RandPos;
	int RandNum;
	int locationCount;
	int socre;
	float missileSpeed;
	float checkTime;
	float moveTime;
	bool AutomaticMissile;
	bool mapInCheck;
	bool mapOutCheck;
	bool pattenCheck;
	bool stop;
	class Impact* impact;
};

