#include "Scene.h"

void Scene::SetSideShake(int strength, float time, bool isRight)
{
	this->strength = strength ;
	this->isShake = true;
	this->revision = 0;
	if (isRight)
		this->shackeMoveX = this->strength + 1;
	else
		this->shackeMoveX = -1 * (this->strength + 1);
	if (time > 0.0f)
		TimerManager::GetSingleton()->SetTimer(ShakeingTimer, this, &Scene::OffShake, time);
}

void Scene::SetAllShaek(int strength, int revision, float time)
{
	this->strength = strength;
	this->shackeMoveX = this->strength * 2 + 1;
	this->shackeMoveY = this->strength * 2 + 1;
	this->isShake = true;
	this->revision = revision;
	if (time > 0.0f)
		TimerManager::GetSingleton()->SetTimer(ShakeingTimer, this, &Scene::OffShake , time);
}

void Scene::OffShake()
{
	this->isShake = false;
	this->shackeMoveX = 0;
	this->shackeMoveY = 0;
	this->strength = 0;
	TimerManager::GetSingleton()->DeleteTimer(ShakeingTimer);
}
