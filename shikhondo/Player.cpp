#include "Player.h"
#include "KeyManager.h"
#include "GamePlayStatic.h"
#include "PlayScene.h"
#include "MissileManager.h"
#include "Missile.h"
#include "EnemyManager.h"

HRESULT Player::Init()
{
	
	imageinfo.imageName = "Player";
	this->hp = 4;
	this->boomCount = 4;
	this->soulGauge = 0;
	this->pos = { 640.0f ,WINSIZE_Y - 100.0f };
	this->size = { 123,141 };
	this->hitBoxSize = { 20,20 };
	imageinfo.DrawRectSetting("Player", this->pos, { 123,141 });
	idleTimer.timerName = "플레이어 아이들 애니메이션타이머";
	TimerManager::GetSingleton()->SetTimer(idleTimer,this,&Player::Idle , 0.035f);
	fireTimer.timerName = "플레이어 발사딜레이 간격";
	TimerManager::GetSingleton()->SetTimer(fireTimer, this, &Player::FireDelay, 0.085f);
	isFire = true;
	speed = 4.0f;


	testMode = false;
	isSoulGaudeRender = false;
	isSpecialAbility = false;

	missileSize = normalMissileSize;

	soulGaugeLeft.DrawRectSetting("LProgress", { this->pos.x, this->pos.y }, { 64,128 }, true, {64,128});
	soulGaugeRight.DrawRectSetting("RProgress", this->pos, { 64,128 }, true, {64,64});
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

	//this->soulGauge = 2000;
	// 특수능력 해제부분
	if (isSpecialAbility)
	{
		//isSpecialAbility = false;
		this->soulGauge -= 3;
		if (this->soulGauge <= 0)
		{
			this->soulGauge = 0;
			isSpecialAbility = false;
			this->damge = 1;
			missileSize = normalMissileSize;
		}
	}
	
	if (this->soulGauge < maxSoulGauge / 4)
	{
		soulGaugeRight.animSize.cx = 64 * (float)((float)this->soulGauge /(maxSoulGauge / 4));
		soulGaugeRight.animSize.cy = 64;
		soulGaugeRight.drwrc = {	(LONG)this->pos.x  , (LONG)this->pos.y - 94 ,
									(LONG)this->pos.x + soulGaugeRight.animSize.cx , (LONG)this->pos.y - 30 };
		soulGaugeLeft.animSize = { 0,0 };
		soulGaugeLeft.size = { 0,0 };
		
	}
	else if (this->soulGauge < maxSoulGauge / 2)
	{
		soulGaugeRight.animSize.cx = 64;
		soulGaugeRight.animSize.cy = 128 * (float)((float)this->soulGauge / (maxSoulGauge / 2));
		soulGaugeRight.drwrc = {	(LONG)this->pos.x  , (LONG)this->pos.y - 94 ,
									(LONG)this->pos.x + 64 , (LONG)this->pos.y - 94 + soulGaugeRight.animSize.cy };
		soulGaugeLeft.animSize = { 0,0 };
		soulGaugeLeft.size = { 0,0 };
	}
	else if (this->soulGauge < ((maxSoulGauge / 4) * 3))
	{
		soulGaugeRight.animSize.cx = 64;
		soulGaugeRight.animSize.cy = 128;
		soulGaugeRight.drwrc = { (LONG)this->pos.x ,(LONG)this->pos.y - 94,
								 (LONG)this->pos.x + 64 , (LONG)this->pos.y + 34  };
	
	
		soulGaugeLeft.animSize.cx = 64  * (float)((float)(this->soulGauge - maxSoulGauge/2) / (maxSoulGauge / 4));
		soulGaugeLeft.animSize.cy = 64;
		soulGaugeLeft.startx = 64 - soulGaugeLeft.animSize.cx;
		soulGaugeLeft.starty = 64;
		soulGaugeLeft.isAnimStartRest = true;
		soulGaugeLeft.framey = 1;
		soulGaugeLeft.framex = 0;
		soulGaugeLeft.drwrc = { (LONG)pos.x - soulGaugeLeft.animSize.cx , (LONG)pos.y - 30,
								(LONG)pos.x , (LONG)pos.y + 34 };
	}
	else
	{
		soulGaugeRight.animSize.cx = 64;
		soulGaugeRight.animSize.cy = 128;
		soulGaugeRight.drwrc = { (LONG)this->pos.x ,(LONG)this->pos.y - 94,
								 (LONG)this->pos.x + 64 , (LONG)this->pos.y + 34 };

		
		
		soulGaugeLeft.animSize.cx = 64;
		soulGaugeLeft.animSize.cy = 128 * (float)((float)(this->soulGauge - (maxSoulGauge / 2)) / (maxSoulGauge / 2));
		soulGaugeLeft.startx = 0;// -soulGaugeLeft.animSize.cx;
		soulGaugeLeft.starty = 128 - soulGaugeLeft.animSize.cy;
		soulGaugeLeft.isAnimStartRest = true;
		soulGaugeLeft.framey = 0;
		soulGaugeLeft.framex = 0;
		soulGaugeLeft.drwrc = { (LONG)pos.x - 64 , (LONG)pos.y + 34 - soulGaugeLeft.animSize.cy,
								(LONG)pos.x , (LONG)pos.y + 34 };
	}

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
			}
			//homingShooterPos[1] = { homingShooterPos[0].x + 110.0f,homingShooterPos[0].y };
		}
	}
	else
	{

		homingShooterPos[0] = { (float)hitBox.left - 50, (float)hitBox.top + 10 };
		homingShooterPos[1] = { (float)hitBox.right + 50, (float)hitBox.top + 10 };
	}
	
}

void Player::Render(HDC hdc)
{
	Character::Render(hdc);
	ImageManager::GetSingleton()->DrawAnimImage(hdc, imageinfo);
	Rectangle(hdc, (LONG)homingShooterPos[0].x -25 , (LONG)homingShooterPos[0].y - 25, (LONG)homingShooterPos[0].x + 25, (LONG)homingShooterPos[0].y + 25);
	Rectangle(hdc, (LONG)homingShooterPos[1].x -25 , (LONG)homingShooterPos[1].y - 25, (LONG)homingShooterPos[1].x + 25, (LONG)homingShooterPos[1].y + 25);

#ifdef _DEBUG
	Rectangle(hdc, hitBox.left, hitBox.top, hitBox.right, hitBox.bottom);
	Rectangle(hdc, boomtest.left, boomtest.top, boomtest.right, boomtest.bottom);
#else
	if (isSoulGaudeRender)
#endif // _DEBUG
	{
		ImageManager::GetSingleton()->DrawAnimImage(hdc, soulGaugeLeft);
		ImageManager::GetSingleton()->DrawAnimImage(hdc, soulGaugeRight);
	}
	
}


void Player::OnHit(Missile * hitMissile)
{
	if (isInvincibility || testMode)
		return;
	if (hitMissile->GetIsSoul())
		return;
	this->hp--;
	isInvincibility = true;
	TimerManager::GetSingleton()->SetTimer(invincibilityTimer, this, &Player::Invincibility, 0.5f);
	PlayScene* playScene = Cast<PlayScene>(GamePlayStatic::GetScene());
	MissileManager* missilemanager = playScene->GetMissileManager();
	const list<Missile*>* enemyMissile = missilemanager->GetSpawnMissileList();
	list<Missile*>::const_iterator const_it;
	for (const_it = enemyMissile->begin(); const_it != enemyMissile->end(); const_it++)
	{
		(*const_it)->OnHit();
	}
	if (this->hp == 0)
		isActivation = false;
}


void Player::KeyChack()
{
	KeyManager* keyManager = KeyManager::GetSingleton();
	if (keyManager)
	{
		if (keyManager->IsStayKeyDown(VK_RIGHT))
		{
			if (pos.x + speed < Play_RightX)
			{
				imageinfo.MovePos(MovePosType::X_AIS, speed);
				pos.x += speed;
			}
		}
		else if (keyManager->IsStayKeyDown(VK_LEFT))
		{
			if (pos.x - speed > Play_LeftX)
			{
				imageinfo.MovePos(MovePosType::X_AIS, -speed);
				pos.x -= speed;
			}
		}

		if (keyManager->IsStayKeyDown(VK_UP))
		{
			if (pos.y - speed > 0)
			{
				imageinfo.MovePos(MovePosType::Y_AIS, -speed);
				pos.y -= speed;
			}
		}
		else if (keyManager->IsStayKeyDown(VK_DOWN))
		{
			if (pos.y + speed < WINSIZE_Y)
			{
				imageinfo.MovePos(MovePosType::Y_AIS, +speed);
				pos.y += speed;
			}
		}


		if (keyManager->IsStayKeyDown(ZKey))
			this->Fire();
		if (keyManager->IsOnceKeyDown(XKey))
			this->SlowMove();
		else if (keyManager->IsOnceKeyUp(XKey))
			this->SlowMove();
		if (keyManager->IsOnceKeyDown(CKey))
			this->SpecialAbility();
		// 테스트모드
		if (keyManager->IsOnceKeyDown(VK_SPACE))
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

		missile = missileManager->SpawnPlayerMissile(this, "PlayerMissile", missilePos, this->missileSize);
		missile->SetSpeed(-missileSpeed);
		missile->SetMovePatten(Patten::NORMALMOVE);

		missilePos.x -= 30.0f;
		missile = missileManager->SpawnPlayerMissile(this, "PlayerMissile", missilePos, this->missileSize);
		missile->SetSpeed(-missileSpeed);
		missile->SetMovePatten(Patten::NORMALMOVE);

		missilePos.x += 15.0f;
		missilePos.y -= 15.0f;
		missile = missileManager->SpawnPlayerMissile(this, "PlayerMissile", missilePos, this->missileSize);
		missile->SetSpeed(-missileSpeed);
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
				homing[i] = missileManager->SpawnPlayerMissile(this, "PlayerMissile", missilePos, this->missileSize);


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
			homing[1] = missileManager->SpawnPlayerMissile(this, "PlayerMissile", missilePos, this->missileSize);

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

void Player::SlowMove()
{
	if (moveState == MoveState::NORMAL)
	{
		moveState = MoveState::SLOW;
		speed = 2.0f;
		isSoulGaudeRender = !isSoulGaudeRender;
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
		const list<Missile*>* enemyMissile = missilemanager->GetSpawnMissileList();
		list<Missile*>::const_iterator const_it;
		for (const_it = enemyMissile->begin(); const_it != enemyMissile->end(); const_it++)
		{
			//(*const_it)->OnHit();
			(*const_it)->ChangeSoul(this);
		}

		isSpecialAbility = true;
		damge = 2;
		missileSize = specialAbilityMissileSize;
	}
	else if (this->boomCount != 0)
	{
		Boom();
		this->boomCount--;
		if (this->boomCount <= 0)
			this->boomCount = 0;
	}
}

void Player::Invincibility()
{
	isInvincibility = false;
	//TimerManager::GetSingleton()->DeleteTimer(invincibilityTimer);
}

void Player::Boom()
{
	boomtest = { Play_LeftX + (PlayXSize / 4) * ((LONG)boom) ,0,Play_LeftX + (PlayXSize / 4 ) * (1 + (LONG)boom) , WINSIZE_Y };
	TimerManager::GetSingleton()->SetTimer(boomTimer, this, &Player::Boom, 0.5f);
	boom++;
	if (boom == 4)
		TimerManager::GetSingleton()->DeleteTimer(boomTimer);
}

void Player::Idle()
{
	imageinfo.framex++;
	if (imageinfo.framex > 21)
		imageinfo.framex = 0;
}
