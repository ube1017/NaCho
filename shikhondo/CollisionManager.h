#pragma once
#include "GameNode.h"
class CollisionManager : public GameNode
{
public:
	CollisionManager() 
	{ 
#ifdef _DEBUG
		this->isRender = true;
#else
		this->isRender = false;
#endif // _DEBUG
	
	}
	HRESULT Init() override;
	void Release() override;
	void Update()  override;
	void Render(HDC hdc)override;

	inline void ManagerSetting(class EnemyManager* enemyManager, class MissileManager* missileManager) { this->enemyManager = enemyManager; this->missileManager = missileManager; }
	inline void PlayerSetting(class Player* player) { this->player = player; }

private:
	void CollisinCheck();
private:
	class EnemyManager* enemyManager;
	class MissileManager* missileManager;
	class Player* player;
};

