#include "Character.h"

HRESULT Character::Init()
{
	return E_NOTIMPL;
}

void Character::Release()
{
}

void Character::Update()
{
}

void Character::Render(HDC hdc)
{
}

void Character::Death()
{
	this->isDead = true;
	this->SetIsValid(false);
}

