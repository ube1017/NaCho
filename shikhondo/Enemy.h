#pragma once
#include "Character.h"

class Enemy : public Character
{
public:
	Enemy();
	HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();				// �޸� ����
	void Update();				// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��

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

