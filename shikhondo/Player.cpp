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

	soulGauge = 0;
	boomCount = 0;
	testMode = false;

	soulGaugeLeft.DrawRectSetting("LProgress", { this->pos.x, this->pos.y }, { 100,180 }, true, {64,128});
	soulGaugeRight.DrawRectSetting("RProgress", this->pos, { 100,180 }, true, {64,128});
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

	FPOINT Rgauge = { this->pos.x + 50 , this->pos.y - 10};
	FPOINT Lgauge = { this->pos.x - 50 , this->pos.y - 10};
	soulGauge++;
	if (soulGauge == 200)
		soulGauge = 0;
	if (this->soulGauge < maxSoulGauge / 4)
	{
		soulGaugeRight.animSize.cx = 64 * (float)((float)this->soulGauge /(maxSoulGauge / 4));
		soulGaugeRight.animSize.cy = 64;
		soulGaugeRight.size.cx = 100 * (float)((float)this->soulGauge / (maxSoulGauge / 4));
		soulGaugeRight.size.cy = 90;
		soulGaugeRight.drwrc = {	(LONG)this->pos.x  , (LONG)this->pos.y - 80 ,
									(LONG)this->pos.x + soulGaugeRight.size.cx , (LONG)this->pos.y + 10 };
		soulGaugeLeft.animSize = { 0,0 };
		soulGaugeLeft.size = { 0,0 };
		
	}
	else if (this->soulGauge < maxSoulGauge / 2)
	{
		soulGaugeRight.animSize.cx = 64;
		soulGaugeRight.animSize.cy = 128 * (float)((float)this->soulGauge / (maxSoulGauge / 2));
		soulGaugeRight.size.cx = 100;
		soulGaugeRight.size.cy = 180 * (float)((float)this->soulGauge / (maxSoulGauge / 2));
		soulGaugeRight.drwrc = {	(LONG)this->pos.x  , (LONG)this->pos.y -80 ,
									(LONG)this->pos.x + 100 , (LONG)this->pos.y - 80 + soulGaugeRight.size.cy };
		soulGaugeLeft.animSize = { 0,0 };
	}
	else if (this->soulGauge < ((maxSoulGauge / 4) * 3))
	{
		soulGaugeRight.animSize.cx = 64;
		soulGaugeRight.animSize.cy = 128;
		soulGaugeRight.size.cx = 100;
		soulGaugeRight.size.cy = 180;
		soulGaugeRight.drwrc = { (LONG)this->pos.x ,(LONG)this->pos.y - 80,
								 (LONG)this->pos.x + 100 , (LONG)this->pos.y + 100 };


		soulGaugeLeft.animSize.cx = 64 * (float)((float)this->soulGauge / (maxSoulGauge / 4));
		soulGaugeLeft.animSize.cy = 64;
		soulGaugeLeft.size.cx = 100 * (float)(((float)this->soulGauge - 100) / (maxSoulGauge / 4));
		soulGaugeLeft.size.cy = 90;
		soulGaugeRight.drwrc = { (LONG)pos.x - 100 , (LONG)pos.x + 10,
								 (LONG)pos.x , (LONG)pos.x + 100 };
	}
	else
	{
		soulGaugeRight.animSize.cx = 64;
		soulGaugeRight.animSize.cy = 128;
		soulGaugeRight.size.cx = 100;
		soulGaugeRight.size.cy = 180;
		soulGaugeRight.drwrc = { (LONG)this->pos.x ,(LONG)this->pos.y - 80,
								 (LONG)this->pos.x + 100 , (LONG)this->pos.y + 100 };


		soulGaugeLeft.animSize.cx = 64;
		soulGaugeLeft.animSize.cy = 128;
		soulGaugeLeft.size.cx = 100;
		soulGaugeLeft.size.cy = 90 * (float)((float)(this->soulGauge - 100) / ((maxSoulGauge / 2)));
		soulGaugeRight.drwrc = { (LONG)pos.x - 100 , (LONG)pos.x + 100 - soulGaugeLeft.size.cy ,
								(LONG)pos.x , (LONG)pos.x + 100 };
	}

	soulGaugeLeft.MovePos(Lgauge);
	//soulGaugeRight.MovePos(Rgauge);
	
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
	//ImageManager::GetSingleton()->DrawAnimImage(hdc, soulGaugeLeft);
	//ImageManager::GetSingleton()->DrawAnimImage(hdc, soulGaugeRight);
	ImageManager::GetSingleton()->DrawAnimImage(hdc, imageinfo);
#ifdef _DEBUG
	Rectangle(hdc, hitBox.left, hitBox.top, hitBox.right, hitBox.bottom);
#endif // _DEBUG
	//Rectangle(hdc, (LONG)homingShooterPos[0].x -25 , (LONG)homingShooterPos[0].y - 25, (LONG)homingShooterPos[0].x + 25, (LONG)homingShooterPos[0].y + 25);
	//Rectangle(hdc, (LONG)homingShooterPos[1].x -25 , (LONG)homingShooterPos[1].y - 25, (LONG)homingShooterPos[1].x + 25, (LONG)homingShooterPos[1].y + 25);

	
}

void Player::OnHit(Missile * hitMissile)
{
	if (isInvincibility || testMode)
		return;
	this->hp--;
	isInvincibility = true;
	TimerManager::GetSingleton()->SetTimer(invincibilityTimer, this, &Player::Invincibility, 0.5f);
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

		missile = missileManager->SpawnPlayerMissile(this, "PlayerMissile", missilePos, { 30,30 });
		missile->SetSpeed(-missileSpeed);
		missile->SetMovePatten(Patten::NORMALMOVE);

		missilePos.x -= 30.0f;
		missile = missileManager->SpawnPlayerMissile(this, "PlayerMissile", missilePos, { 30,30 });
		missile->SetSpeed(-missileSpeed);
		missile->SetMovePatten(Patten::NORMALMOVE);

		missilePos.x += 15.0f;
		missilePos.y -= 15.0f;
		missile = missileManager->SpawnPlayerMissile(this, "PlayerMissile", missilePos, { 30,30 });
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
				homing[i] = missileManager->SpawnPlayerMissile(this, "PlayerMissile", missilePos, { 30,30 });


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
			
			break;
		}
		

		if (i == 1)
		{
			missilePos = homingShooterPos[1];
			homing[1] = missileManager->SpawnPlayerMissile(this, "PlayerMissile", missilePos, { 30,30 });

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
	}
	else
	{
		moveState = MoveState::NORMAL;
		speed = 5.0f;
	}
}

void Player::SpecialAbility()
{
	if (this->soulGauge >= maxSoulGauge)
	{
		PlayScene* playScene =Cast<PlayScene>(GamePlayStatic::GetScene());
		MissileManager* missilemanager = playScene->GetMissileManager();
		const list<Missile*>* enemyMissile = missilemanager->GetSpawnMissileList();
		list<Missile*>::const_iterator const_it;
		for (const_it = enemyMissile->begin(); const_it != enemyMissile->end(); const_it++)
		{
			(*const_it)->OnHit();
		}
	}
}

void Player::Invincibility()
{
	isInvincibility = false;
	//TimerManager::GetSingleton()->DeleteTimer(invincibilityTimer);
}

void Player::Idle()
{
	imageinfo.framex++;
	if (imageinfo.framex > 21)
		imageinfo.framex = 0;
}
