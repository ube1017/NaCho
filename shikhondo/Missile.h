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

	void MissileSetting(string imageName,FPOINT pos, SIZE size);
	void SetSize(SIZE sizs) { this->size = size; }
	void SetPos(FPOINT pos) { this->pos = pos; }
	void SetOwner(Character* owner)  { this->owner = owner; }
	const Character* GetOnwer() const  { return this->owner; }
private:
	Character* owner;
	FPOINT pos;
	SIZE size;
	ImageDrawInfo imaginfo;
	TimerHandle moveTimerHandle;
};