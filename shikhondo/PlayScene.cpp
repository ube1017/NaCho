#include "PlayScene.h"
#include "ImageManager.h"
#include "Enemy.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "GamePlayStatic.h"
#include "Player.h"
#include "EnemyManager.h"
#include "MissileManager.h"
#include "BackGround.h"
#include "Missile.h"
#include "CollisionManager.h"

HRESULT PlayScene::Init()
{
	ImageManager* imageManager = ImageManager::GetSingleton();
	imageManager->_LoadBitmap("leftBack", "leftBack", { 448, 512 }, { 2, 1 });
	imageManager->_LoadBitmap("leftCloud", "leftCloud", { 1024 , 512 });
	imageManager->_LoadBitmap("Player", "player", { 2706 , 141 }, { 22,1 });
	imageManager->_LoadBitmap("enemy1", "enemy1", { 1300 , 100 }, { 13,1 });
	imageManager->_LoadBitmap("21", "21", { 400,100 }, { 4,1 });

	GamePlayStatic::SetScene(this);
	backGround = CreateObject<BackGround>();
	player = CreateObject<Player>();
	GamePlayStatic::SetPlayerCharacter(player);
	enemyManager = CreateObject<EnemyManager>(false);
	missileManager = CreateObject<MissileManager>(false);
	player->SetMissileManager(missileManager);
	enemyManager->SetMainGame(this);
	for (int i = 0 ; i <10 ;i++)
		enemyManager->CreateEeney<Enemy1>(missileManager);
	for (int i = 0; i < MAX_MISSILE; i++)
		missileManager->CreateMissile();
	/*FPOINT ppos;*/
	/*Missile* missile;*/
	//for (int i = 0; i < 300; i++)
	//{
	//	ppos.x = (float)(rand() % PlayXSize + Play_LeftX);
	//	ppos.y = (float)(rand() % WINSIZE_X);

	//	missile = this->SpawnMissile(player, "21", ppos, { 20,20 });
	//}


	collsionManager = CreateObject<CollisionManager>();
	collsionManager->ManagerSetting(enemyManager,missileManager);
	collsionManager->PlayerSetting(player);
	return S_OK;
}

void PlayScene::Release()
{
	GameNode::Release();
}

void PlayScene::Update()
{
	GameNode::Update();
	// 테스트 용
	static Enemy* test[10];
	static int i = 0;
	static int j = 0;
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN))
		test[i++] = enemyManager->SpawnEeney<Enemy1>();
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_UP))
	{
		enemyManager->DieEnemy(test[j++]);
		i = 0;
	}
}

void PlayScene::Render(HDC hdc)
{
	GameNode::Render(hdc);
}

Missile* PlayScene::SpawnMissile(Character* owner, string imageName, FPOINT missilePos, SIZE MissileSize)
{
	Missile* missile;
	missile = missileManager->SpawnMissile(owner, imageName, missilePos, MissileSize);
	return missile;
}
