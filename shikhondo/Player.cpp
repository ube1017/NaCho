#include "Player.h"
#include "KeyManager.h"
#include "GamePlayStatic.h"
#include "PlayScene.h"
#include "MissileManager.h"
#include "Missile.h"
#include "EnemyManager.h"
#include "Image.h"
#include "UI.h"

HRESULT Player::Init()
{
	
	imageinfo.imageName = "Player";
	hp = 5;
	boomCount = 4;
	soulGauge = 0;
	damge = 1;
	soulScore = 0;
	isKeyLock = false;
	//pos = { 640.0f ,WINSIZE_Y - 100.0f };
	pos = { 640.0f , WINSIZE_Y + 100.0f };
	size = { 123,141 };
	hitBoxSize = { 20,20 };
	boomAttackCount = 0;
	imageinfo.DrawRectSetting("Player", this->pos, { 123,141 });
	TimerManager* timer = TimerManager::GetSingleton();

	idleTimer.timerName = "플레이어 아이들 애니메이션타이머";
	timer->SetTimer(idleTimer,this,&Player::Idle , 0.035f);
	fireTimer.timerName = "플레이어 발사딜레이 간격";
	//timer->SetTimer(fireTimer, this, &Player::FireDelay, 0.185f);
	timer->SetTimer(fireTimer, this, &Player::FireDelay, 0.085f);
	homingShooteridleTimer.timerName = "플레이어 보조무기";
	timer->SetTimer(homingShooteridleTimer, this, &Player::HomingShooterIdle, 0.04f);
	timer->SetTimer(startMoveTimer, this, &Player::StratMove, 0.01f);
	isFire = true;
	speed = 4.0f;

	startMove_back = false;
	testMode = false;
	isSoulGaudeRender = false;
	isSpecialAbility = false;


	missileSize = normalMissileSize;
	missileName = "PlayerMissile";

	soulGaugeLeft.DrawRectSetting("LProgress", { this->pos.x, this->pos.y }, { 64,128 }, true, {64,128});
	soulGaugeRight.DrawRectSetting("RProgress", this->pos, { 64,128 }, true, {64,64});
	soulGaugeLeft2.DrawRectSetting("LProgress", { this->pos.x, this->pos.y }, { 64,128 }, true, { 64,128 });
	soulGaugeRight2.DrawRectSetting("RProgress", this->pos, { 64,128 }, true, { 64,64 });
	homingShooter[0].DrawRectSetting("SideSoul", homingShooterPos[0], { 128,128 });  //플레이어 보조무기
	homingShooter[1].DrawRectSetting("SideSoul", homingShooterPos[1], { 128,128 });  //플레이어 보조무기
	return S_OK;
}

void Player::Release()
{
	GameNode::Release();
}

void Player::Update()
{
	GameNode::Update();

	this->KeyChack();
	hitBox = {	(LONG)pos.x - hitBoxSize.cx/2 -3, (LONG)pos.y - hitBoxSize.cy - 4,
				(LONG)pos.x + hitBoxSize.cx/2 -3, (LONG)pos.y - 4 };

	
	this->SpecialAbilityGauge();
#ifdef _DEBUG
	boomCount = 4;
	//soulScore++;
	if (soulScore == 9999)
		soulScore = 9998;
#endif // _DEBUG

	
	if (moveState == MoveState::SLOW)
	{
		PlayScene* playscene = Cast<PlayScene>(GamePlayStatic::GetScene());
		EnemyManager* enemyManger = Cast<EnemyManager>(playscene->GetEnemyManager());
		const list<Enemy*>* spawnEnemyList = enemyManger->GetSpawnEnemyList();
		list<Enemy*>::const_iterator const_it;
		Enemy* homingTager = nullptr;
		RECT erect;
		//homingShooterPos[0] = { (float)hitBox.left - 50, (float)hitBox.top + 10 };
		int i = 0;
		for (const_it = spawnEnemyList->begin(); const_it != spawnEnemyList->end(); const_it++)
		{
			if ((*const_it)->GetMapInCheck())
			{
				homingTager = *const_it;
				FPOINT enemypos = (*const_it)->Getpos();
				float angle = atan2f((enemypos.y - homingShooterPos[i].y), (enemypos.x - 70.0f - homingShooterPos[i].x));

				erect = { (LONG)enemypos.x - 70 , (LONG)enemypos.y - 10 , (LONG)enemypos.x  - 50, (LONG)enemypos.y + 10 };
				if (!PtInRect(&erect, { (LONG)homingShooterPos[i].x, (LONG)homingShooterPos[i].y }))
				{
					homingShooterPos[i].x += missileSpeed * cosf(angle);
					homingShooterPos[i].y += missileSpeed * sinf(angle);
					homingShooter[i].MovePos(homingShooterPos[i]);
				}
				i++;
				if (i == 2)
					break;
				else
					continue;
			}
		}
		if (i == 1)
		{
			FPOINT enemypos = homingTager->Getpos();
			float angle = atan2f((enemypos.y - homingShooterPos[i].y), (enemypos.x + 110.0f - homingShooterPos[i].x));

			erect = { (LONG)enemypos.x + 90 , (LONG)enemypos.y - 10 , (LONG)enemypos.x + 120, (LONG)enemypos.y + 10 };
			if (!PtInRect(&erect, { (LONG)homingShooterPos[1].x, (LONG)homingShooterPos[1].y }))
			{
				homingShooterPos[1].x += missileSpeed * cosf(angle);
				homingShooterPos[1].y += missileSpeed * sinf(angle);
				homingShooter[1].MovePos(homingShooterPos[1]);
			}
			//homingShooterPos[1] = { homingShooterPos[0].x + 110.0f,homingShooterPos[0].y };
		}
	}
	else
	{

		homingShooterPos[0] = { (float)hitBox.left - 50, (float)hitBox.top + 10 };
		homingShooter[0].MovePos(homingShooterPos[0]);
		homingShooterPos[1] = { (float)hitBox.right + 50, (float)hitBox.top + 10 };
		homingShooter[1].MovePos(homingShooterPos[1]);
	}
	
}

void Player::Render(HDC hdc)
{
	Character::Render(hdc);
	ImageManager* imageManager = ImageManager::GetSingleton();
	imageManager->DrawAnimImage(hdc, imageinfo);
	imageManager->DrawAnimImage(hdc, homingShooter[0]);
	imageManager->DrawAnimImage(hdc, homingShooter[1]);
	//Rectangle(hdc, (LONG)homingShooterPos[0].x -25 , (LONG)homingShooterPos[0].y - 25, (LONG)homingShooterPos[0].x + 25, (LONG)homingShooterPos[0].y + 25);
	//Rectangle(hdc, (LONG)homingShooterPos[1].x -25 , (LONG)homingShooterPos[1].y - 25, (LONG)homingShooterPos[1].x + 25, (LONG)homingShooterPos[1].y + 25);

#ifdef _DEBUG
	Rectangle(hdc, hitBox.left, hitBox.top, hitBox.right, hitBox.bottom);
	//Rectangle(hdc, boomBox.left, boomBox.top, boomBox.right, boomBox.bottom);
#else
	if (isSoulGaudeRender)
#endif // _DEBUG
	{
		imageManager->DrawAnimImage(hdc, soulGaugeLeft);
		imageManager->DrawAnimImage(hdc, soulGaugeLeft2);
		imageManager->DrawAnimImage(hdc, soulGaugeRight);
		imageManager->DrawAnimImage(hdc, soulGaugeRight2);
	}
	
}

void Player::OnHit(Missile * hitMissile)
{
	if (isInvincibility || testMode || this->hp == 0)
		return;
	if (hitMissile->GetIsSoul())
		return;
	this->hp--;
	isInvincibility = true;
	TimerManager::GetSingleton()->SetTimer(invincibilityTimer, this, &Player::Invincibility, 0.5f);
	PlayScene* playScene = Cast<PlayScene>(GamePlayStatic::GetScene());
	MissileManager* missilemanager = playScene->GetMissileManager();
	missilemanager->MissileAllChangeSoul(this);
	playScene->SetAllShaek(2,-1,0.5f);
	//const list<Missile*>* enemyMissile = missilemanager->GetSpawnMissileList();
	//list<Missile*>::const_iterator const_it;
	//for (const_it = enemyMissile->begin(); const_it != enemyMissile->end(); const_it++)
	//{
	//	//(*const_it)->OnHit();
	//	(*const_it)->ChangeSoul(this);
	//}
	if (this->hp == 0)
		isActivation = false;
}

void Player::KeyChack()
{
	if (this->isKeyLock)
		return;
	KeyManager* keyManager = KeyManager::GetSingleton();
	if (keyManager)
	{
		if (keyManager->IsStayKeyDown(VK_RIGHT))
		{
			if (pos.x + speed < Play_RightX - 10)
			{
				imageinfo.MovePos(MovePosType::X_AIS, speed);
				pos.x += speed;
			}
		}
		else if (keyManager->IsStayKeyDown(VK_LEFT))
		{
			if (pos.x - speed > Play_LeftX + 10)
			{
				imageinfo.MovePos(MovePosType::X_AIS, -speed);
				pos.x -= speed;
			}
		}

		if (keyManager->IsStayKeyDown(VK_UP))
		{
			if (pos.y - speed > 10)
			{
				imageinfo.MovePos(MovePosType::Y_AIS, -speed);
				pos.y -= speed;
			}
		}
		else if (keyManager->IsStayKeyDown(VK_DOWN))
		{
			if (pos.y + speed < WINSIZE_Y -10)
			{
				imageinfo.MovePos(MovePosType::Y_AIS, +speed);
				pos.y += speed;
			}
		}


		if (keyManager->IsStayKeyDown(ZKey))
			this->Fire();
		if (keyManager->IsOnceKeyDown(XKey))
			this->SlowMove(true);
		else if (keyManager->IsOnceKeyUp(XKey))
			this->SlowMove(false);
		if (keyManager->IsOnceKeyDown(CKey))
			this->SpecialAbility();
		// 테스트모드
		if (keyManager->IsOnceKeyDown(0x50))
			testMode = !testMode;
	}
}

void Player::Fire()
{
	if (isFire)
	{
		Missile* missile;
		FPOINT missilePos = this->pos;
		missilePos.x += 15.0f;
		missilePos.y -= 20.0f;
		PlayScene* playscene = Cast<PlayScene>(GamePlayStatic::GetScene());
		MissileManager* missileManager = playscene->GetMissileManager();

		//float angle = 0.0f;
		//
		//for (int i = 0 ; i < 20 ; i++)
		//{
		//	missile = missileManager->SpawnPlayerMissile(this, "PlayerMissile", this->pos, this->missileSize);
		//	missile->SetSpeed(-missileSpeed);
		//	missile->SetDamage(this->damge);
		//	missile->SetAngle(angle);
		//	missile->SetMovePatten(Patten::TEST2);
		//	missilePos.x -= 30.0f;
		//	missile = missileManager->SpawnPlayerMissile(this, "PlayerMissile", this->pos, this->missileSize);
		//	missile->SetSpeed(-missileSpeed);
		//	missile->SetDamage(this->damge);
		//	missile->SetAngle(angle);
		//	missile->SetMovePatten(Patten::TEST);
		//
		//	angle += 0.3f;//(6.14 / 20.0f);
		//
		//
		//}
		//
		//	angle += 0.3f;//(6.14 / 20.0f);
		//}
		//isFire = false;
		//return;

		missile = missileManager->SpawnPlayerMissile(this, missileName, missilePos, this->missileSize);
		missile->SetSpeed(-missileSpeed);
		missile->SetDamage(this->damge);
		missile->SetMovePatten(Patten::NORMALMOVE);

		missilePos.x -= 30.0f;
		missile = missileManager->SpawnPlayerMissile(this, missileName, missilePos, this->missileSize);
		missile->SetSpeed(-missileSpeed);
		missile->SetDamage(this->damge);
		missile->SetMovePatten(Patten::NORMALMOVE);


		missilePos.x += 15.0f;
		missilePos.y -= 15.0f;
		missile = missileManager->SpawnPlayerMissile(this, missileName, missilePos, this->missileSize);
		missile->SetSpeed(-missileSpeed);
		missile->SetDamage(this->damge);
		missile->SetMovePatten(Patten::NORMALMOVE);


		EnemyManager* enemyManger = Cast<EnemyManager>(playscene->GetEnemyManager());
		const list<Enemy*>* spawnEnemyList = enemyManger->GetSpawnEnemyList();
		list<Enemy*>::const_iterator const_it;
		Missile* homing[2];
		Enemy* homingTaget = nullptr;
		int i = 0;
		for (const_it = spawnEnemyList->begin(); const_it != spawnEnemyList->end(); const_it++)
		{
			if ((*const_it)->GetMapInCheck())
			{

				missilePos = homingShooterPos[i];
				homing[i] = missileManager->SpawnPlayerMissile(this, missileName, missilePos, this->missileSize);
				homing[i]->SetDamage(this->damge);

				homing[i]->SetTaget(*const_it);
				homing[i]->SetMovePatten(Patten::HOMINGMOVE);
				homing[i]->SetSpeed(missileSpeed);
				i++;

				homingTaget = *const_it;
				if (i == 2)
					break;
				else
					continue;
			}
		}
		

		if (i == 1)
		{
			missilePos = homingShooterPos[1];
			homing[1] = missileManager->SpawnPlayerMissile(this, missileName, missilePos, this->missileSize);
			homing[1]->SetDamage(this->damge);

			homing[1]->SetTaget(homingTaget);
			homing[1]->SetMovePatten(Patten::HOMINGMOVE);
			homing[1]->SetSpeed(missileSpeed);
		}

		//for (int i = 0; i < 3; i++)
		//{
		//	missilePos.x -= (10.0f * i);
		//	missile = missileManager->SpawnPlayerMissile(this, "PlayerMissile", missilePos, { 30,30 });
		//	missile->SetSpeed(-3.0f);
		//	missile->SetMovePatten(Patten::NORMALMOVE);
		//}
		isFire = false;
	}
}

void Player::FireDelay()
{
	isFire = true;
}

void Player::SlowMove(bool vaule)
{
	if (vaule)
	{
		//if (moveState == MoveState::NORMAL)
		{
			moveState = MoveState::SLOW;
			speed = 2.0f;
			isSoulGaudeRender = !isSoulGaudeRender;
		}
	}
	else
	{
		moveState = MoveState::NORMAL;
		speed = 5.0f;
		isSoulGaudeRender = !isSoulGaudeRender;
	}
}

void Player::SpecialAbility()
{
	if (this->soulGauge >= maxSoulGauge && !isSpecialAbility )
	{
		PlayScene* playScene =Cast<PlayScene>(GamePlayStatic::GetScene());
		MissileManager* missilemanager = playScene->GetMissileManager();
		missilemanager->MissileAllChangeSoul(this);
		playScene->GetUI()->playerSkillEfect.Execute();
		isSpecialAbility = true;
		damge = 2;
		missileSize = specialAbilityMissileSize;
		missileName = "PlayerMissile2";
	}
	else if (this->boomCount != 0)
	{
		if (boomAttackCount == 0)
		{
			PlayScene* playScene = Cast<PlayScene>(GamePlayStatic::GetScene());
			MissileManager* missilemanager = playScene->GetMissileManager();
			missilemanager->MissileAllChangeSoul(this);

			Boom();
			this->boomCount--;
			if (this->boomCount <= 0)
				this->boomCount = 0;
		}
	}
}

void Player::Invincibility()
{
	isInvincibility = false;
	//TimerManager::GetSingleton()->DeleteTimer(invincibilityTimer);
}

void Player::Boom()
{
	boomAttackCount++;
	if (boomAttackCount == 5)
	{
		TimerManager::GetSingleton()->DeleteTimer(boomTimer);
		boomBox = { 0,0,0,0 };
		boomAttackCount = 0;
		PlayScene* playScene = Cast<PlayScene>(GamePlayStatic::GetScene());
		MissileManager* missilemanager = playScene->GetMissileManager();
		for (int i = 0; i < 4; i++)
			missilemanager->MissileRelease(this, boomMissile[i]);

	}
	else
	{
		PlayScene* playScene = Cast<PlayScene>(GamePlayStatic::GetScene());
		MissileManager* missilemanager = playScene->GetMissileManager();
		boomMissile[boomAttackCount - 1] = missilemanager->SpawnPlayerMissile(this, "Bomb", { Play_LeftX + (PlayXSize / 8), WINSIZE_Y / 2 }, { (PlayXSize / 4) , 1024 });
		//boomMissile = missilemanager->SpawnPlayerMissile(this, "Bomb", { Play_LeftX + (PlayXSize / 8), WINSIZE_Y / 2 }, { (PlayXSize / 4) , 80 });
		boomMissile[boomAttackCount - 1]->SetDamage(70);
		boomMissile[boomAttackCount - 1]->SetisBoom(true);
		boomMissile[boomAttackCount - 1]->MissileSetting("Bomb", { Play_LeftX + (PlayXSize / 8),WINSIZE_Y + WINSIZE_Y / 2 }, { (PlayXSize / 4) , 1024 });

		boomBox = { Play_LeftX + (PlayXSize / 4) * ((LONG) boomAttackCount - 1) ,0,Play_LeftX + (PlayXSize / 4) * ((LONG)boomAttackCount) , WINSIZE_Y };
		TimerManager::GetSingleton()->SetTimer(boomTimer, this, &Player::Boom, 0.5f);
		//boomAttackCount++;
		boomMissile[boomAttackCount - 1]->SetPos({ (float)(Play_LeftX + (PlayXSize / 8) + (PlayXSize / 4) * (boomAttackCount - 1)), (float)(WINSIZE_Y / 2) });
		boomMissile[boomAttackCount - 1]->SetMovePatten(Patten::NONE);
		boomMissile[boomAttackCount - 1]->SetHitBox(boomBox);

	}
}

void Player::SpecialAbilityGauge()
{
	//this->soulGauge = 2000;
	// 특수능력 해제부분
	if (isSpecialAbility)
	{
		//isSpecialAbility = false;
		this->soulGauge -= 3;
		if (this->soulGauge <= 0)
		{
			this->soulGauge = 0;
			this->isSpecialAbility = false;
			this->damge = 1;
			this->missileName = "PlayerMissile";
			this->missileSize = normalMissileSize;
			PlayScene* playScene = Cast<PlayScene>(GamePlayStatic::GetScene());
			MissileManager* missilemanager = playScene->GetMissileManager();
			missilemanager->MissileAllChangeSoul(this);
		}
	}
	float ratio = 0;
	if (this->soulGauge < maxSoulGauge / 4)
	{
		ratio = (float)((float)this->soulGauge / (maxSoulGauge / 4));
		soulGaugeRight.animSize.cx = (LONG)(64 * ratio);
		soulGaugeRight.animSize.cy = (LONG)(30 + 34 * ratio);
		soulGaugeRight.drwrc = { (LONG)this->pos.x  , (LONG)this->pos.y - 94 ,
									(LONG)this->pos.x + soulGaugeRight.animSize.cx , (LONG)this->pos.y - 94 + soulGaugeRight.animSize.cy };
		soulGaugeLeft.animSize = { 0,0 };
		soulGaugeLeft.size = { 0,0 };
		soulGaugeLeft2.animSize = { 0,0 };
		soulGaugeLeft2.size = { 0,0 };
		soulGaugeRight2.animSize = { 0,0 };
		soulGaugeRight2.size = { 0,0 };

	}
	else if (this->soulGauge < maxSoulGauge / 2)
	{
		soulGaugeRight.animSize.cx = 64;
		soulGaugeRight.animSize.cy = 64;
		soulGaugeRight.drwrc = { (LONG)this->pos.x  , (LONG)this->pos.y - 94 ,
									(LONG)this->pos.x + 64 , (LONG)this->pos.y - 30 };


		ratio = (float)((float)(this->soulGauge - (maxSoulGauge / 4)) / (maxSoulGauge / 4));
		soulGaugeRight2.animSize.cx = (LONG)(24 + 40 * ratio);
		soulGaugeRight2.animSize.cy = (LONG)(64 * ratio);
		soulGaugeRight2.isAnimStartRest = true;
		soulGaugeRight2.framex = 1;
		soulGaugeRight2.framey = 1;
		soulGaugeRight2.startx = 64 - soulGaugeRight2.animSize.cx;
		soulGaugeRight2.starty = 64;
		soulGaugeRight2.drwrc = { (LONG)this->pos.x + 64 - soulGaugeRight2.animSize.cx , (LONG)this->pos.y - 30 ,
									(LONG)this->pos.x + 64 , (LONG)this->pos.y - 30 + soulGaugeRight2.animSize.cy };


		soulGaugeLeft.animSize = { 0,0 };
		soulGaugeLeft.size = { 0,0 };
		soulGaugeLeft2.animSize = { 0,0 };
		soulGaugeLeft2.size = { 0,0 };
	}
	else if (this->soulGauge < ((maxSoulGauge / 4) * 3))
	{
		soulGaugeRight.animSize.cx = 64;
		soulGaugeRight.animSize.cy = 128;
		soulGaugeRight.drwrc = { (LONG)this->pos.x ,(LONG)this->pos.y - 94,
								 (LONG)this->pos.x + 64 , (LONG)this->pos.y + 34 };


		ratio = (float)((float)(this->soulGauge - maxSoulGauge / 2) / (maxSoulGauge / 4));
		soulGaugeLeft.animSize.cx = (LONG)(64 * ratio);
		soulGaugeLeft.animSize.cy = (LONG)(30 + 34 * ratio);
		soulGaugeLeft.startx = 64 - soulGaugeLeft.animSize.cx;
		soulGaugeLeft.starty = 128 - (soulGaugeLeft.animSize.cy);
		soulGaugeLeft.isAnimStartRest = true;
		soulGaugeLeft.framey = 1;
		soulGaugeLeft.framex = 0;
		soulGaugeLeft.drwrc = { (LONG)pos.x - soulGaugeLeft.animSize.cx , (LONG)pos.y + 34 - soulGaugeLeft.animSize.cy,
								(LONG)pos.x , (LONG)pos.y + 34 };

		soulGaugeRight2.animSize = { 0,0 };
		soulGaugeRight2.size = { 0,0 };
	}
	else
	{
		soulGaugeRight.animSize.cx = 64;
		soulGaugeRight.animSize.cy = 128;
		soulGaugeRight.drwrc = { (LONG)this->pos.x ,(LONG)this->pos.y - 94,
								 (LONG)this->pos.x + 64 , (LONG)this->pos.y + 34 };


		soulGaugeLeft.animSize.cx = 64;
		soulGaugeLeft.animSize.cy = 64;
		soulGaugeLeft.startx = 0;
		soulGaugeLeft.starty = 64;
		soulGaugeLeft.isAnimStartRest = true;
		soulGaugeLeft.framey = 1;
		soulGaugeLeft.framex = 0;
		soulGaugeLeft.drwrc = { (LONG)pos.x - 64 , (LONG)pos.y - 30,
								(LONG)pos.x , (LONG)pos.y + 34 };


		soulGaugeLeft2.animSize.cx = 64;
		soulGaugeLeft2.animSize.cy = 64;
		soulGaugeLeft2.drwrc = { (LONG)pos.x - 64 , (LONG)pos.y - 30,
								(LONG)pos.x , (LONG)pos.y + 34 };

		ratio = (float)((float)(this->soulGauge - ((maxSoulGauge / 4) * 3)) / (maxSoulGauge / 4));
		soulGaugeLeft2.animSize.cx = (LONG)(24 + 40 * ratio);
		soulGaugeLeft2.animSize.cy = (LONG)(64 * ratio);
		soulGaugeLeft2.startx = 0;
		soulGaugeLeft2.starty = 64 - soulGaugeLeft2.animSize.cy;
		soulGaugeLeft2.isAnimStartRest = true;
		soulGaugeLeft2.framey = 1;
		soulGaugeLeft2.framex = 0;
		soulGaugeLeft2.drwrc = { (LONG)pos.x - 64 , (LONG)pos.y - 30 - soulGaugeLeft2.animSize.cy,
								(LONG)pos.x - 64 + soulGaugeLeft2.animSize.cx, (LONG)pos.y - 30 };
		soulGaugeRight2.animSize = { 0,0 };
		soulGaugeRight2.size = { 0,0 };
	}



#pragma region 이전 코드 부자연스럽지만 기본적인 코드

	//if (this->soulGauge < maxSoulGauge / 4)
	//{
	//	soulGaugeRight.animSize.cx = 64 * (float)((float)this->soulGauge / (maxSoulGauge / 4));
	//	soulGaugeRight.animSize.cy = 64;
	//	soulGaugeRight.drwrc = { (LONG)this->pos.x  , (LONG)this->pos.y - 94 ,
	//								(LONG)this->pos.x + soulGaugeRight.animSize.cx , (LONG)this->pos.y - 30 };
	//	soulGaugeLeft.animSize = { 0,0 };
	//	soulGaugeLeft.size = { 0,0 };

	//}
	//else if (this->soulGauge < maxSoulGauge / 2)
	//{
	//	soulGaugeRight.animSize.cx = 64;
	//	soulGaugeRight.animSize.cy = 128 * (float)((float)this->soulGauge / (maxSoulGauge / 2));
	//	soulGaugeRight.drwrc = { (LONG)this->pos.x  , (LONG)this->pos.y - 94 ,
	//								(LONG)this->pos.x + 64 , (LONG)this->pos.y - 94 + soulGaugeRight.animSize.cy };
	//	soulGaugeLeft.animSize = { 0,0 };
	//	soulGaugeLeft.size = { 0,0 };
	//}
	//else if (this->soulGauge < ((maxSoulGauge / 4) * 3))
	//{
	//	soulGaugeRight.animSize.cx = 64;
	//	soulGaugeRight.animSize.cy = 128;
	//	soulGaugeRight.drwrc = { (LONG)this->pos.x ,(LONG)this->pos.y - 94,
	//							 (LONG)this->pos.x + 64 , (LONG)this->pos.y + 34 };


	//	soulGaugeLeft.animSize.cx = 64 * (float)((float)(this->soulGauge - maxSoulGauge / 2) / (maxSoulGauge / 4));
	//	soulGaugeLeft.animSize.cy = 64;
	//	soulGaugeLeft.startx = 64 - soulGaugeLeft.animSize.cx;
	//	soulGaugeLeft.starty = 64;
	//	soulGaugeLeft.isAnimStartRest = true;
	//	soulGaugeLeft.framey = 1;
	//	soulGaugeLeft.framex = 0;
	//	soulGaugeLeft.drwrc = { (LONG)pos.x - soulGaugeLeft.animSize.cx , (LONG)pos.y - 30,
	//							(LONG)pos.x , (LONG)pos.y + 34 };
	//}
	//else
	//{
	//	soulGaugeRight.animSize.cx = 64;
	//	soulGaugeRight.animSize.cy = 128;
	//	soulGaugeRight.drwrc = { (LONG)this->pos.x ,(LONG)this->pos.y - 94,
	//							 (LONG)this->pos.x + 64 , (LONG)this->pos.y + 34 };



	//	soulGaugeLeft.animSize.cx = 64;
	//	soulGaugeLeft.animSize.cy = 128 * (float)((float)(this->soulGauge - (maxSoulGauge / 2)) / (maxSoulGauge / 2));
	//	soulGaugeLeft.startx = 0;// -soulGaugeLeft.animSize.cx;
	//	soulGaugeLeft.starty = 128 - soulGaugeLeft.animSize.cy;
	//	soulGaugeLeft.isAnimStartRest = true;
	//	soulGaugeLeft.framey = 0;
	//	soulGaugeLeft.framex = 0;
	//	soulGaugeLeft.drwrc = { (LONG)pos.x - 64 , (LONG)pos.y + 34 - soulGaugeLeft.animSize.cy,
	//							(LONG)pos.x , (LONG)pos.y + 34 };
	//}
#pragma endregion

}

void Player::Idle()
{
	imageinfo.framex++;
	if (imageinfo.framex > 21)
		imageinfo.framex = 0;
}

void Player::HomingShooterIdle()
{
	ImageManager* imageManger = ImageManager::GetSingleton();
	Image* image = imageManger->FindImage(homingShooter[0].imageName);
	int maxFrameX = image->GetMaxFramX();
	homingShooter[0].framex++;
	homingShooter[1].framex++;
	if (homingShooter[0].framex == 18)
	{
		homingShooter[0].framex = 0;
		homingShooter[1].framex = 0;
	}
}

void Player::StratMove()
{
	
	if (this->pos.y <= WINSIZE_Y - 200)
		startMove_back = true;
	if (!startMove_back)
	{
		this->pos.y -= 3.0f;
		imageinfo.MovePos(this->pos);
	}
	else
	{
		this->pos.y += 2.0f;
		imageinfo.MovePos(this->pos);
		if (!isKeyLock)
			TimerManager::GetSingleton()->DeleteTimer(startMoveTimer);
	}

}
