#pragma once
#include "GameNode.h"


class Character;
class Impact;
class Missile :public GameNode
{
public:
	Missile();

	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	
	void OnHit();

	void MissileSetting(string imageName, FPOINT pos, SIZE size);
	void MissileRelease();

	void SetAngle(float angle) { this->angle = angle; }

	void SetSpeed(float value) { this->speed = value; }

	void SetDamage(int damage) { this->damage = damage;}
	int GetDamage() { return this->damage; }
	
	void SetTaget(Character* tager)		{ this->taget = tager; }
	void SetSize(SIZE sizs)				{ this->size = size; }

	void SetPos(FPOINT pos)				{ this->pos = pos; }

	FPOINT GetPos()						{ return pos; }
	float GetAngle()					{ return angle; }

	void SetOwner(Character* owner)		{ this->owner = owner; }
	Character* GetOnwer() const	{ return this->owner; }

	bool GetIsSoul() const { return this->isSoul; }

	void SetMovePatten(Patten movePatten);

	void SetHitBox(RECT rect) { this->hitBox = rect; }
	RECT GetHitBox() { return this->hitBox; }

	// �÷��̾ ��ų�� ����Ҷ� ��ȥ���� ���ϴ� �Լ�
	void ChangeSoul(Character* taget);

private:
	void NormalMove();
	void HomingMove();
	void AngleMove();
	void SevenMove();
	void NoneMove();
	void TestMove();
	void TestMove2();

	// �̻��� �ִϸ��̼�
	void MissileAnim();
private:
	Character* owner;
	Character* taget;
	FPOINT pos;
	SIZE size;
	RECT hitBox;
	// ����Ʈ
	Impact* impact;

	ImageDrawInfo imaginfo;

	int damage;
	bool isSoul;
	float angle;
	float angle2;
	float speed;
	Patten nowMovePatten;

	void(Missile::*movePatten[static_cast<int>(Patten::MaX)])();

	TimerHandle misiileAnimTimerHandle;
};