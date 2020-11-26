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
#include "UI.h"

PlayScene::PlayScene()
{
	spawnStart.BindObject(this, &PlayScene::SpawnStartFun);
}

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
	imageManager->_LoadBitmap("22", "22", { 400,100 }, { 4,1 });
	imageManager->_LoadBitmap("23", "23", { 400,100 }, { 4,1 });
	imageManager->_LoadBitmap("24", "24", { 400,100 }, { 4,1 });
	imageManager->_LoadBitmap("25", "25", { 400,100 }, { 4,1 });
	imageManager->_LoadBitmap("EnemyMissile", "EnemyMissile", { 192,72 }, { 8,1 });
	imageManager->_LoadBitmap("Background2", "Background2", { 512,512 }, { 1,1 });
	imageManager->_LoadBitmap("Background5", "Background5", { 512,1024 }, { 1,1 });
	imageManager->_LoadBitmap("Background3", "Background3", { 512,1024 }, { 1,1 });
	imageManager->_LoadBitmap("Background4", "Background4", { 512,1024 }, { 1,1 });
	imageManager->_LoadBitmap("Background1", "Background1", { 512,512 }, { 1,1 });
	imageManager->_LoadBitmap("PlayerMissile", "PlayerMissile", { 128,128 }, { 1,1 });
	imageManager->_LoadBitmap("PlayerMissile2", "PlayerMissile2", { 128,128 }, { 1,1 });
	imageManager->_LoadBitmap("LeftSideDownBackground", "LeftSideDownBackground", { 512,512 }, { 1,1 });
	imageManager->_LoadBitmap("LeftBackground", "LeftBackground", { 512,512 }, { 1,1 });
	imageManager->_LoadBitmap("LeftUpBackground", "LeftUpBackground", { 1024,512 }, { 1,1 });
	imageManager->_LoadBitmap("RightBackground", "RightBackground", { 512,512 }, { 1,1 });
	imageManager->_LoadBitmap("RightSideDownBackground", "RightSideDownBackground", { 512,512 }, { 1,1 });
	imageManager->_LoadBitmap("RightUpBackground", "RightUpBackground", { 1024,512 }, { 1,1 });
	imageManager->_LoadBitmap("LProgress", "LProgress", { 64,128 }, { 1,1 });
	imageManager->_LoadBitmap("RProgress", "RProgress", { 64,128 }, { 1,1 });
	imageManager->_LoadBitmap("Soulgeiji2", "Soulgeiji2", { 512,1024 }, { 2,3 });
	imageManager->_LoadBitmap("SkillGeiji", "SkillGeiji", { 2048,128 }, { 33,1 });
	imageManager->_LoadBitmap("Life", "Life", { 220,45 }, { 4,1 });
	imageManager->_LoadBitmap("test", "test", { 1024,256 }, { 1,1 });
	imageManager->_LoadBitmap("SoulGeijiBack", "SoulGeijiBack", { 561,159 }, { 1,1 });
	imageManager->_LoadBitmap("SideSoul", "SideSoul", { 5376,256 }, { 21,1 });
	imageManager->_LoadBitmap("mapImage", "mapImage", { 1024,298 }, { 1,1 });
	imageManager->_LoadBitmap("boss_Hp_Bar1", "boss_Hp_Bar1", { 512,32 }, { 1,1 });
	imageManager->_LoadBitmap("boss_Hp_Bar2", "boss_Hp_Bar2", { 1024,128 }, { 1,1 });
	imageManager->_LoadBitmap("boss_Hp_Bar3", "boss_Hp_Bar3", { 512,32 }, { 1,1 });
	imageManager->_LoadBitmap("Font", "Font", { 256,32 }, { 10,1 });
	imageManager->_LoadBitmap("Bar1", "Bar1", { 512,128 }, { 1,1 });
	imageManager->_LoadBitmap("Bar2", "Bar2", { 512,128 }, { 1,1 });
	imageManager->_LoadBitmap("Bar3", "Bar3", { 512,128 }, { 10,1 });
	imageManager->_LoadBitmap("Impact", "Impact", { 1024,128 }, { 8,1 });
	imageManager->_LoadBitmap("Impact2", "Impact2", { 256,256 }, { 1,1 });
	imageManager->_LoadBitmap("Back", "Back", { 1280,900 }, { 1,1 });
	imageManager->_LoadBitmap("BossInit", "BossInit", { 1024,1024 }, { 1,1 });
	imageManager->_LoadBitmap("Warning", "Warning", { 1024,1024 }, { 1,1 });
	imageManager->_LoadBitmap("Impact", "Impact", { 1024,128 }, { 8,1 });
	imageManager->_LoadBitmap("BossFont1", "BossFont1", { 512,512 }, { 1,1 });
	imageManager->_LoadBitmap("BossFont2", "BossFont2", { 512,512 }, { 1,1 });
	imageManager->_LoadBitmap("BossFont3", "BossFont3", { 512,512 }, { 1,1 });
	imageManager->_LoadBitmap("BossFont4", "BossFont4", { 512,512 }, { 1,1 });
	imageManager->_LoadBitmap("BossFontBack", "BossFontBack", { 512,1024 }, { 1,1 });
	imageManager->_LoadBitmap("LeftCloud1", "LeftCloud1", { 1024,256 }, { 1,1 });
	imageManager->_LoadBitmap("LeftCloud2", "LeftCloud2", { 1024,512 }, { 1,1 });
	imageManager->_LoadBitmap("LeftCloud3", "LeftCloud3", { 1024,256 }, { 1,1 });
	imageManager->_LoadBitmap("RightCloud1", "RightCloud1", { 1024,256 }, { 1,1 });
	imageManager->_LoadBitmap("RightCloud2", "RightCloud2", { 1024,256 }, { 1,1 });
	imageManager->_LoadBitmap("RightCloud3", "RightCloud3", { 512,256 }, { 1,1 });
	imageManager->_LoadBitmap("RightCloud4", "RightCloud4", { 1024,512 }, { 1,1 });
	imageManager->_LoadBitmap("SoulGeiji3", "SoulGeiji3", { 344,512 }, { 1,1 });
	imageManager->_LoadBitmap("SkillEffect1", "SkillEffect1", { 641,257 }, { 1,1 });
	imageManager->_LoadBitmap("SkillEffect2", "SkillEffect2", { 512,512 }, { 1,1 });
	imageManager->_LoadBitmap("SkillEffect3", "SkillEffect3", { 430,138 }, { 1,1 });
	imageManager->_LoadBitmap("SkillEffect4", "SkillEffect4", { 512,512 }, { 1,1 });

	// 도영
	EPos.x = 500;
	EPos.y = 200;
	pattenX = 100;
	pattenChange = false;
	pattenChangeEnemy1 = false;

	GamePlayStatic::SetScene(this);
	backGround = CreateObject<BackGround>();
	player = CreateObject<Player>();
	GamePlayStatic::SetPlayerCharacter(player);
	player->SetIsKeyLock(true);
	ui = CreateObject<UI>();
	ui->SetZOrder(1);
	enemyManager = CreateObject<EnemyManager>(false);
	missileManager = CreateObject<MissileManager>(false);
	player->SetMissileManager(missileManager);
	enemyManager->SetMainGame(this);

	for (int i = 0; i < 20; i++)
		enemyManager->CreateEeney<Enemy1>(missileManager);
	for (int i = 0; i < 5; i++)
		enemyManager->CreateEeney<Enemy2>(missileManager);
	for (int i = 0; i < 2; i++)
		enemyManager->CreateEeney<Enemy3>(missileManager);
	for (int i = 0; i < 1; i++)
		enemyManager->CreateEeney<EnemyBoss>(missileManager);
	for (int i = 0; i < MAX_MISSILE; i++)
		missileManager->CreateMissile();

	collsionManager = CreateObject<CollisionManager>();
	collsionManager->ManagerSetting(enemyManager, missileManager);
	collsionManager->PlayerSetting(player);
#ifdef _DEBUG
	backGround->SetZOrder(11);
	collsionManager->SetZOrder(11);
#endif // _DEBUG

	nextspawnCount = 0;
	spawnNum = 1.0f;

	nowPatten = SpawnPatten::ENEMY1;
	spawnCount = 0;
	isBoss = false;

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
#ifdef _DEBUG
	//if (KeyManager::GetSingleton()->IsOnceKeyDown(0x51)) //q
	//	enemyManager->SpawnEeney<Enemy1>();
	if (KeyManager::GetSingleton()->IsOnceKeyDown(0x57)) //w
		enemyManager->SpawnEeney<Enemy2>();
	if (KeyManager::GetSingleton()->IsOnceKeyDown(0x45)) //e~
		enemyManager->SpawnEeney<Enemy3>();
	if (KeyManager::GetSingleton()->IsOnceKeyDown(0x51))
	{
		//Enemy* boss = enemyManager->SpawnEeney<EnemyBoss>();
		//ui->SetBossHp(boss->GetHp_ptr());
		ui->BossStage();
		player->SetIsKeyLock(true);
	}
#endif // _DEBUG

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

void PlayScene::BossSpawnBind()
{
	spawnStart.BindObject(this, &PlayScene::BossSpawn);
}

void PlayScene::StageSpawn()
{
	switch (nowPatten)
	{
	case SpawnPatten::ENEMY1:
		TimerManager::GetSingleton()->SetTimer(spawnTimer, this, &PlayScene::SpawnPatten1, 0.8f);
		break;
	case SpawnPatten::ENEMY2:
		TimerManager::GetSingleton()->SetTimer(spawnTimer, this, &PlayScene::SpawnPatten2, 1.0f);
		break;
	case SpawnPatten::ENEMY3:
		TimerManager::GetSingleton()->SetTimer(spawnTimer, this, &PlayScene::SpawnPatten3, 1.0f);
		break;
	case SpawnPatten::NONE:
		TimerManager::GetSingleton()->DeleteTimer(spawnTimer);
		break;
	case SpawnPatten::BOSS1:
		TimerManager::GetSingleton()->SetTimer(spawnTimer, this, &PlayScene::SpawnBoss, 0.3f);
		break;
	default:
		break;
	}
}

void PlayScene::SpawnPatten1()
{
	if (!pattenChange)
	{
		if (!pattenChangeEnemy1)
		{
			enemyManager->SpawnEeney<Enemy1>({ WINSIZE_X / 2 + 400, -40 });
			spawnCount++;
			if (spawnCount == (int)(10 * spawnNum))
			{
				spawnCount = 0;
				TimerManager::GetSingleton()->SetTimer(spawnTimer, this, &PlayScene::StageSpawn, 2.0f);
				nowPatten = SpawnPatten::ENEMY2;
			}
		}
		else
		{
			enemyManager->SpawnEeney<Enemy1>({ WINSIZE_X / 2 - 400, -40 });
			spawnCount++;
			if (spawnCount == (int)(10 * spawnNum))
			{
				spawnCount = 0;
				TimerManager::GetSingleton()->SetTimer(spawnTimer, this, &PlayScene::StageSpawn, 2.0f);
				nowPatten = SpawnPatten::ENEMY2;
			}
		}
	}
	else if (pattenChange)
	{
		enemyManager->SpawnEeney<Enemy1>(EPos, { WINSIZE_X / 2 , -100 });

		if (EPos.x == 900)
		{
			EPos.x = 950;
			EPos.y = 150;
			pattenX *= -1;
		}
		else if (EPos.x == 350)
		{
			pattenX *= -1;
			EPos.y = 150;
		}
		else if (EPos.x == 950)
		{
			pattenX *= -1;
			EPos.y = 150;
		}
		spawnCount++;
		if (spawnCount == (int)(10 * spawnNum))
		{
			spawnCount = 0;
			TimerManager::GetSingleton()->SetTimer(spawnTimer, this, &PlayScene::StageSpawn, 2.0f);
			nowPatten = SpawnPatten::ENEMY2;
		}

		EPos.x += pattenX;
		EPos.y -= 5;
	}
}

void PlayScene::SpawnPatten2()
{
	enemyManager->SpawnEeney<Enemy2>();
	spawnCount++;
	if (spawnCount == (int)(2 * (spawnNum + 0.5f)))
	{
		spawnCount = 0;
		TimerManager::GetSingleton()->SetTimer(spawnTimer, this, &PlayScene::StageSpawn, 2.0f);
		nextspawnCount++;
		if (nextspawnCount == 2)
			nowPatten = SpawnPatten::ENEMY3;
		else
		{
			pattenChangeEnemy1 = true;
			nowPatten = SpawnPatten::ENEMY1;
		}
	}
}

void PlayScene::SpawnPatten3()
{
	enemyManager->SpawnEeney<Enemy3>();
	spawnCount++;
	if (spawnCount == (int)(1 * (spawnNum + 0.5f)))
	{
		spawnCount = 0;
		TimerManager::GetSingleton()->SetTimer(spawnTimer, this, &PlayScene::StageSpawn, 10.0f);
		spawnNum += 0.5f;
		if (spawnNum == 2.0f)
		{
			nowPatten = SpawnPatten::BOSS1;
		}
		else
		{
			nowPatten = SpawnPatten::ENEMY1;
			if (!pattenChange)
				pattenChange = true;
		}
		nextspawnCount = 0;
	}
}

void PlayScene::SpawnBoss()
{
	const list<Enemy*>* enemys = enemyManager->GetSpawnEnemyList();
	list<Enemy*>::const_iterator const_it;
	if (enemys->size() == 0)
	{
		ui->BossStage();
		//Enemy* boss = enemyManager->SpawnEeney<EnemyBoss>();
		nowPatten = SpawnPatten::NONE;
		this->PlayScene::StageSpawn();
		//ui->SetBossHp(boss->GetHp_ptr());
		
	}
	//else
	//	TimerManager::GetSingleton()->SetTimer(spawnTimer, this, &PlayScene::SpawnBoss, 0.3f);
}

void PlayScene::SpawnStartFun()
{
	TimerManager::GetSingleton()->SetTimer(spawnTimer, this, &PlayScene::StageSpawn, 2.0f);
	player->SetIsKeyLock(false);

}

void PlayScene::BossSpawn()
{
	Enemy* boss = enemyManager->SpawnEeney<EnemyBoss>();
	ui->SetBossHp(boss->GetHp_ptr());
	player->SetIsKeyLock(false);
	missileManager->MissileAllChangeSoul(player);
}
