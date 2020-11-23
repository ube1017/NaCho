#pragma once
#include "Character.h"

class Enemy : public Character
{
public:
	HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	void Release();				// 메모리 해제
	void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);		// 프레임 단위 출력 (이미지, 텍스트 등

	virtual void RandLocation() {}
	virtual void LocationReset() {}
	bool GetMapOutCheck() { return mapOutCheck; }
	bool GetMapInCheck() { return mapInCheck; }

	float GetAngle();
	float GetAngle(FPOINT GetPos);

	void OnHit(class Missile* hitMissile) override;

	void SetTargetPOS(FPOINT POS) { this->RandPos = POS; }
	FPOINT GetPos() { return  this->RandPos; }
protected:
	FPOINT RandPos;
	int RandNum;
	int locationCount;
	int missileSpeed;
	float checkTime;
	
	bool AutomaticMissile;
	bool mapInCheck;
	bool mapOutCheck;
};

