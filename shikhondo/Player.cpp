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
	this->pos = { 640.0f ,100.0f };
	this->size = { 123,141 };
	this->hitBoxSize = { 20,20 };
	imageinfo.DrawRectSetting("Player", this->pos, { 123,141 });
	idleTimer.timerName = "플레이어 아이들 애니메이션타이머";
	TimerManager::GetSingleton()->SetTimer(idleTimer,this,&Player::Idle , 0.035f);
	fireTimer.timerName = "플레이어 발사딜레이 간격";
	TimerManager::GetSingleton()->SetTimer(fireTimer, this, &Player::FireDelay, 0.085f);
	isFire = true;
	speed = 4.0f;
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
#ifdef _DEBUG
	Rectangle(hdc, hitBox.left, hitBox.top, hitBox.right, hitBox.bottom);
#endif // _DEBUG
	Rectangle(hdc, (LONG)homingShooterPos[0].x -25 , (LONG)homingShooterPos[0].y - 25, (LONG)homingShooterPos[0].x + 25, (LONG)homingShooterPos[0].y + 25);
	Rectangle(hdc, (LONG)homingShooterPos[1].x -25 , (LONG)homingShooterPos[1].y - 25, (LONG)homingShooterPos[1].x + 25, (LONG)homingShooterPos[1].y + 25);

	
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
			this->Boom();
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

void Player::Boom()
{
}

void Player::Idle()
{
	imageinfo.framex++;
	if (imageinfo.framex > 21)
		imageinfo.framex = 0;
}
