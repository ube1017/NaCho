#include "PlayScene.h"
#include "ImageManager.h"
#include "Enemy.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "EnemyBoss.h"
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
	imageManager->_LoadBitmap("enemy2_1", "enemy2_1", { 3600 , 400 }, { 9,1 });
	imageManager->_LoadBitmap("enemy2_2", "enemy2_2", { 6000 , 500 }, { 12,1 });
	imageManager->_LoadBitmap("enemy3", "enemy3", { 512 , 512 }, { 3,3 });
	imageManager->_LoadBitmap("Boss", "Boss", { 204 , 403 }, { 1,1 });
	imageManager->_LoadBitmap("21", "21", { 400,100 }, { 4,1 });
	imageManager->_LoadBitmap("Background2", "Background2", { 512,512 }, { 1,1 });
	imageManager->_LoadBitmap("Background5", "Background5", { 512,1024 }, { 1,1 });
	imageManager->_LoadBitmap("Background3", "Background3", { 512,1024 }, { 1,1 });
	imageManager->_LoadBitmap("Background4", "Background4", { 512,1024 }, { 1,1 });
	imageManager->_LoadBitmap("PlayerMissile", "PlayerMissile", { 128,128 }, { 1,1 });
	imageManager->_LoadBitmap("LeftSideDownBackground", "LeftSideDownBackground", { 512,512 }, { 1,1 });
	imageManager->_LoadBitmap("LeftBackground", "LeftBackground", { 512,512 }, { 1,1 });
	imageManager->_LoadBitmap("LeftUpBackground", "LeftUpBackground", { 1024,512 }, { 1,1 });
	imageManager->_LoadBitmap("RightBackground", "RightBackground", { 512,512 }, { 1,1 });
	imageManager->_LoadBitmap("RightSideDownBackground", "RightSideDownBackground", { 512,512 }, { 1,1 });
	imageManager->_LoadBitmap("RightUpBackground", "RightUpBackground", { 1024,512 }, { 1,1 });
	imageManager->_LoadBitmap("Soulgeiji", "Soulgeiji", { 512,1024 }, { 1,1 });
	imageManager->_LoadBitmap("SkillGeiji", "SkillGeiji", { 2048,128 }, { 1,1 });
	
		

	
	GamePlayStatic::SetScene(this);
	backGround = CreateObject<BackGround>();
	player = CreateObject<Player>();
	GamePlayStatic::SetPlayerCharacter(player);
	enemyManager = CreateObject<EnemyManager>(false);
	missileManager = CreateObject<MissileManager>(false);
	player->SetMissileManager(missileManager);
	enemyManager->SetMainGame(this);

	for (int i = 0 ; i <20 ;i++)
		enemyManager->CreateEeney<Enemy1>(missileManager);
	for (int i = 0; i < 5;i++)
		enemyManager->CreateEeney<Enemy2>(missileManager);
	for (int i = 0; i < 2;i++)
		enemyManager->CreateEeney<Enemy3>(missileManager);
	for (int i = 0; i < 1; i++)
		enemyManager->CreateEeney<EnemyBoss>(missileManager);
	for (int i = 0; i < MAX_MISSILE; i++)
		missileManager->CreateMissile();

	collsionManager = CreateObject<CollisionManager>();
	collsionManager->ManagerSetting(enemyManager, missileManager);
	collsionManager->PlayerSetting(player);


	nowPatten = SpawnPatten::ENEMY1;
	spawnCount = 0;

	TimerManager::GetSingleton()->SetTimer(spawnTimer,this,&PlayScene::StageSpawn , 2.0f);
	return S_OK;
}

void PlayScene::Release()
{
	GameNode::Release();
}

void PlayScene::Update()
{
	GameNode::Update();
	// 테스트용
	if (KeyManager::GetSingleton()->IsOnceKeyDown(0x51)) //q
		enemyManager->SpawnEeney<Enemy1>();
	if (KeyManager::GetSingleton()->IsOnceKeyDown(0x57)) //w
		enemyManager->SpawnEeney<Enemy2>();
	if (KeyManager::GetSingleton()->IsOnceKeyDown(0x45)) //e~
		enemyManager->SpawnEeney<Enemy3>();
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
		enemyManager->SpawnEeney<EnemyBoss>();
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

void PlayScene::StageSpawn()
{
	switch (nowPatten)
	{
	case SpawnPatten::ENEMY1:
		TimerManager::GetSingleton()->SetTimer(spawnTimer, this, &PlayScene::SpawnPatten1, 0.5f);
		break;
	case SpawnPatten::ENEMY2:
		TimerManager::GetSingleton()->SetTimer(spawnTimer, this, &PlayScene::SpawnPatten2, 1.0f);
		break;
	case SpawnPatten::ENEMY3:
		TimerManager::GetSingleton()->SetTimer(spawnTimer, this, &PlayScene::SpawnPatten3, 1.0f);
		break;
	default:
		break;
	}
}

void PlayScene::SpawnPatten1()
{
	enemyManager->SpawnEeney<Enemy1>();
	spawnCount++;
	if (spawnCount == 10)
	{
		spawnCount = 0;
		TimerManager::GetSingleton()->SetTimer(spawnTimer, this, &PlayScene::StageSpawn, 2.0f);
		nowPatten = SpawnPatten::ENEMY2;
	}

}

void PlayScene::SpawnPatten2()
{
	enemyManager->SpawnEeney<Enemy2>();
	spawnCount++;
	if (spawnCount == 2)
	{
		spawnCount = 0;
		TimerManager::GetSingleton()->SetTimer(spawnTimer, this, &PlayScene::StageSpawn, 2.0f);
		nowPatten = SpawnPatten::ENEMY3;
	}
}

void PlayScene::SpawnPatten3()
{
	enemyManager->SpawnEeney<Enemy3>();
	spawnCount++;
	if (spawnCount == 1)
	{
		spawnCount = 0;
		TimerManager::GetSingleton()->SetTimer(spawnTimer, this, &PlayScene::StageSpawn, 10.0f);
		nowPatten = SpawnPatten::ENEMY1;
	}
}
