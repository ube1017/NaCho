#pragma once
#include "GameNode.h"
class CollisionManager : public GameNode
{
public:
	CollisionManager() { this->isRender = false; }
	HRESULT Init() override;
	void Release() override;
	void Update()  override;


private:
	class EnemyManager* enemyManager;
	class MissileManager* missileManager;
	class Player* player;
};

