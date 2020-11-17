#include "PlayScene.h"
#include "ImageManager.h"
#include "Enemy.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "GamePlayStatic.h"
#include "Player.h"
#include "EnemyManager.h"
#include "BackGround.h"

HRESULT PlayScene::Init()
{
	ImageManager* imageManager = ImageManager::GetSingleton();
	imageManager->_LoadBitmap("leftBack", "leftBack", { 448, 512 }, { 2, 1 });
	imageManager->_LoadBitmap("leftCloud", "leftCloud", { 1024 , 512 });

	player = CreateObject<Player>();
	GamePlayStatic::SetPlayerCharacter(player);
	backGround = CreateObject<BackGround>();
	sasdf = CreateObject<EnemyManager>(false);
	sasdf->SetMainGame(this);
	for (int i = 0 ; i <10 ;i++)
		sasdf->CreateEeney<Enemy1>();
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
		test[i++] = sasdf->SpwanEeney<Enemy1>();
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_UP))
	{
		sasdf->DieEnemy(test[j++]);
		i = 0;
	}
}

void PlayScene::Render(HDC hdc)
{
	GameNode::Render(hdc);
}
