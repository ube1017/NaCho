#pragma once
#include "GameNode.h"


class Character;
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

	
	void SetTaget(Character* tager)		{ this->taget = tager; }
	void SetSize(SIZE sizs)				{ this->size = size; }

	void SetPos(FPOINT pos)				{ this->pos = pos; }

	FPOINT GetPos()						{ return pos; }

	void SetOwner(Character* owner)		{ this->owner = owner; }
	Character* GetOnwer() const	{ return this->owner; }

	void SetMovePatten(Patten movePatten);

	void SetHitBox(RECT rect) { this->hitBox = rect; }

private:
	void NormalMove();
	void HomingMove();
	void AngleMove();
private:
	Character* owner;
	Character* taget;
	FPOINT pos;
	SIZE size;
	RECT hitBox;

	ImageDrawInfo imaginfo;

	float angle;
	float speed;
	Patten nowMovePatten;

	void(Missile::*movePatten[static_cast<int>(Patten::MaX)])();
};