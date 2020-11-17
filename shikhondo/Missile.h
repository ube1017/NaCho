#pragma once
#include "GameNode.h"
class Character;
class Missile :public GameNode
{
public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void SetOwner(Character* owner)  { this->owner = owner; }
	const Character* GetOnwer() const  { return this->owner; }
private:
	Character* owner;
	FPOINT pos;

};