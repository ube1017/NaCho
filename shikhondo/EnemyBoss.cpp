#include "EnemyBoss.h"
#include "PlayScene.h"
#include "GamePlayStatic.h"
#include "Missile.h"
#include "UI.h"
#include "PlayScene.h"
#include "MainGame.h"
#include "MissileManager.h"
/*
시작하자마자 멈추게 하고

패턴 발사

후 움직임 시작
*/
HRESULT EnemyBoss::Init()
{
	hp = 2000;
	damge = 1;
	speed = 1.5f;
	missileSpeed = 1.5f;
	size.cx = 80;
	size.cy = 160;
	hitBoxSize = size;
	ShootCount = 0;
	angleNum = 20;
	angleNum2 = 14;
	movePCheck = 0;
	movePosCheck = 0;
	roundCheck = 0;
	pTime = 0;
	P1Check = 0;
	P2Check = 0;
	num = 50;
	pattenCheck = false;
	boom = false;
	stopAttack = true;
	stop = true;
	socre = 10000;
	// 시작 위치 설정
	LocationReset();
	RandLocation();
	//bossMove();
	////imageinfo.imageName = "enemy1";
	imageinfo.DrawRectSetting("Boss", this->pos, { 110,220 }, true, { 204,403 });
	//TimerManager::GetSingleton()->SetTimer(idleTimer, this, &EnemyBoss::Idle, 0.035f);
	return E_NOTIMPL;
}

void EnemyBoss::Release()
{

}

void EnemyBoss::Update()
{
	Enemy::Update();
	PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
	imageinfo.MovePos(pos);
	DEBUG_MASSAGE("보스체력이다 : %d \n", this->hp);
	hitBox = { (LONG)pos.x - hitBoxSize.cx / 2, (LONG)pos.y - hitBoxSize.cy / 2,
							(LONG)pos.x + hitBoxSize.cx / 2, (LONG)pos.y + hitBoxSize.cy / 2 };

	checkTime += TimerManager::GetSingleton()->GettimeElapsed();
	ShootCount += TimerManager::GetSingleton()->GettimeElapsed();
	pTime += TimerManager::GetSingleton()->GettimeElapsed();
	P3Check += TimerManager::GetSingleton()->GettimeElapsed();
	P1Check += TimerManager::GetSingleton()->GettimeElapsed();
	P2Check += TimerManager::GetSingleton()->GettimeElapsed();

	if (!stop)
	{
		if (roundCheck == 0)
		{
			if (hp > 500)
			{

				pos.x += cosf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;
				pos.y += sinf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;
				if (stopAttack)
				{
					speed = 0;
					patten8(2.5f, 0.4f);
					if (checkTime >= 5.0f)
					{
						stopAttack = false;
					}
				}
				else if (!stopAttack)
				{
					if (pos.x < RandPos.x + 5 && pos.x >= RandPos.x - 5)
					{
						if (pos.y < RandPos.y + 5 && pos.y >= RandPos.y - 5)
						{
							if (speed == 0) {
								speed = 1.5f;
							}
							bossMove();
						}
					}

					patten5(1.0f);
					patten7(4.5f, 0.5f);
				}
			}
			else if (hp <= 500)
			{
				roundCheck++;
				socre += socre + 2000;
				playScene->GetUI()->AddScore(socre);
				playScene->GetMissileManager()->MissileAllChangeSoul(GamePlayStatic::GetPlayerCharacter());
				hp = 3000;
				speed = 2;
				stop = true;
				stopAttack = true;
				checkTime = 0;
				ShootCount = 0;
				P3Check = 0;
				P1Check = 0;
				P2Check = 0;
				pTime = 0;
			}
		}
		else if (roundCheck == 1)
		{
			if (hp > 300)
			{
				pos.x += cosf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;
				pos.y += sinf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;
				if (stopAttack)
				{
					speed = 0;
					patten4(0.4f);
					patten7(4.5f, 0.5f);
					if (checkTime >= 5.0f)
					{
						stopAttack = false;
					}
				}
				else if (!stopAttack)
				{
					if (pos.x < RandPos.x + 5 && pos.x >= RandPos.x - 5)
					{
						if (pos.y < RandPos.y + 5 && pos.y >= RandPos.y - 5)
						{
							if (speed == 0) {
								speed = 1.5f;
							}
							bossMove();
						}
					}
					patten3(0.7f);
					patten7(4.5f, 0.5f);
				}
			}
			else if (hp <= 300)
			{
				roundCheck++;
				socre += socre + 1500;
				playScene->GetUI()->AddScore(socre);
				playScene->GetMissileManager()->MissileAllChangeSoul(GamePlayStatic::GetPlayerCharacter());
				hp = 3500;
				speed = 2;
				stop = true;
				stopAttack = true;
				checkTime = 0;
				ShootCount = 0;
				pTime = 0;
				P1Check = 0;
				P2Check = 0;
				P3Check = 0;
			}
		}
		else if (roundCheck == 2)
		{
			if (hp > 0)
			{
				pos.x += cosf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;
				pos.y += sinf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;
				if (stopAttack)
				{
					speed = 0;
					patten3(0.7f);
					patten7(4.5f, 0.5f);
					if (checkTime >= 5.0f)
					{
						stopAttack = false;
					}
				}
				else if (!stopAttack)
				{
					if (pos.x < RandPos.x + 5 && pos.x >= RandPos.x - 5)
					{
						if (pos.y < RandPos.y + 5 && pos.y >= RandPos.y - 5)
						{
							if (speed == 0) {
								speed = 1.5f;
							}
							bossMove();
						}
					}
					if (checkTime >= 0.5f)
					{
						patten2(1.0f);
						patten7(4.5f, 0.5f);
						if (hp < 2000)
						{
							patten4(0.7f);
						}
						if (hp < 1000)
						{
							patten3(2.0f);
						}
						checkTime = 0;
					}
				}
			}
			else if (hp <= 0)
			{
				roundCheck++;
				socre += socre + 5000;
				playScene->GetMissileManager()->MissileAllChangeSoul(GamePlayStatic::GetPlayerCharacter());
				if (this->hp <= 0)
					GamePlayStatic::GetMainGame()->GetUI()->SetCloseTimer(1.0f);
			}
		}
		else
		{
			// 죽음
		}
	}
	else if (stop)
	{
		LocationReset();
		pos.x += cosf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;
		pos.y += sinf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;
		if (pos.x < RandPos.x + 5 && pos.x >= RandPos.x - 5)
		{
			if (pos.y < RandPos.y + 5 && pos.y >= RandPos.y - 5)
			{
				stop = false;
				speed = 2.0f;
			}
		}
		//이미지 여기에
	}
}

void EnemyBoss::Render(HDC hdc)
{
#ifdef _DEBUG
	Rectangle(hdc, (int)(pos.x - (size.cx / 2)), (int)(pos.y - (size.cy / 2)), (int)(pos.x + (size.cx / 2)), (int)(pos.y + (size.cy / 2)));
#endif // _DEBUG
	ImageManager::GetSingleton()->DrawAnimImage(hdc, imageinfo);
}

void EnemyBoss::RandLocation()
{
	this->pos.x = WINSIZE_X / 2;
	this->pos.y = 150;
}

void EnemyBoss::LocationReset()
{
	RandPos.x = WINSIZE_X / 2;
	RandPos.y = 150;
}

void EnemyBoss::patten1(FPOINT MPos, float MAngle)
{
	PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
	for (int i = 0; i < 7; i++)
	{
		Missile* Em = playScene->SpawnMissile(this, "21", MPos, { 25, 25 });
		Em->SetAngle(MAngle);		// 각도 값
		Em->SetSpeed(missileSpeed);					// 총알 스피드
		Em->SetMovePatten(Patten::ANGLEMOVE);	// 초알 패턴
		missileSpeed += 0.06f;
		if (missileSpeed > 1.06f)
		{
			missileSpeed += 0.2f;
		}
	}
	missileSpeed = 1.0;
}

void EnemyBoss::patten2(float MSpeed)
{
	PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
	float angle = 0.0f;

	if (P1Check >= MSpeed)
	{
		for (int i = 0; i < 20; i++)
		{
			Missile* Em = playScene->SpawnMissile(this, "23", this->pos, { 30, 30 });
			Em->SetSpeed(missileSpeed2);
			Em->SetAngle(angle);
			Em->SetMovePatten(Patten::TEST2);

			Missile* Em1 = playScene->SpawnMissile(this, "24", this->pos, { 30, 30 });
			Em1->SetSpeed(missileSpeed2);
			Em1->SetAngle(angle);
			Em1->SetMovePatten(Patten::TEST);

			angle += 0.3f;//(6.14 / 20.0f);
		}
		P1Check = 0;
	}
}

void EnemyBoss::patten3(float MSpeed)
{
	PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());

	if (ShootCount >= MSpeed && !boom)
	{
		for (int i = 0; i < 8; i++)
		{
			Em[i] = playScene->SpawnMissile(this, "21", this->pos, { 25, 25 });
			Em[i]->SetAngle(DegreeToRadian(angleNum));		// 각도 값
			Em[i]->SetSpeed(missileSpeed);					// 총알 스피드
			Em[i]->SetMovePatten(Patten::ANGLEMOVE);	// 초알 패턴
			angleNum += 45;
		}
		angleNum = 20;
		ShootCount = 0;
		boom = true;
	}
	if (P3Check >= (MSpeed + 1.5f) && boom)
	{
		// 1패턴boom
		for (int i = 0; i < 8; i++)
		{
			if (!Em[i]->GetIsSoul() && Em[i]->GetisActivation())
				patten6(Em[i]->GetPos(), 3.5f);
		}
		P3Check = 0;
		boom = false;
	}
}


void EnemyBoss::patten4(float MSpeed)// 0.3
{
	PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
	if (P2Check >= MSpeed)
	{
		// 각도를 받고
		for (int i = 0; i < 18; i++)
		{
			Missile* Em = playScene->SpawnMissile(this, "21", this->pos, { 25, 25 });
			Em->SetAngle(DegreeToRadian(angleNum2));		// 각도 값
			Em->SetSpeed(2.5f);					// 총알 스피드
			Em->SetMovePatten(Patten::ANGLEMOVE);	// 초알 패턴
			angleNum2 += 9;
			if (angleNum2 == 81)
			{
				angleNum2 = 99;
			}
		}
		angleNum2 = 9;
		P2Check = 0;
	}
}

void EnemyBoss::patten5(float MSpeed)//1.0
{
	PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
	if (ShootCount >= MSpeed)
	{
		// 각도를 받고
		for (int i = 0; i < 14; i++)
		{
			Missile* Em = playScene->SpawnMissile(this, "24", this->pos, { 25, 25 });
			Em->SetAngle(DegreeToRadian(angleNum2));		// 각도 값
			Em->SetSpeed(2.5f);					// 총알 스피드
			Em->SetMovePatten(Patten::ANGLEMOVE);	// 초알 패턴
			angleNum2 += 14;
			if (angleNum2 == 81)
			{
				angleNum2 = 99;
			}
		}
		angleNum2 = 9;
		ShootCount = 0;
	}
}

void EnemyBoss::patten6(FPOINT MPos, float speed)
{
	PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());

	int angleNum3 = 20;
	// 1패턴

	for (int i = 0; i < 8; i++)
	{
		Missile* Emg;
		Emg = playScene->SpawnMissile(this, "23", MPos, { 25, 25 });
		Emg->SetAngle(DegreeToRadian(angleNum3));		// 각도 값
		Emg->SetSpeed(speed);					// 총알 스피드
		Emg->SetMovePatten(Patten::ANGLEMOVE);	// 초알 패턴
		angleNum3 += 45;
	}
	angleNum3 = 20;
}

void EnemyBoss::patten7(float MSpeed, float Mtime)
{
	PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
	if (pTime >= Mtime)
	{
		// 각도를 받고
		Missile* Em7;
		Em7 = playScene->SpawnMissile(this, "25", this->pos, { 30, 30 });
		Em7->SetAngle(this->GetAngle());		// 각도 값
		Em7->SetSpeed(MSpeed);			// 총알 스피드
		Em7->SetMovePatten(Patten::ANGLEMOVE);	// 초알 패턴
		pTime = 0;
	}
}

void EnemyBoss::patten8(float MSpeed, float Mtime)
{
	if (pTime >= Mtime)
	{
		// 탄 발사전 좌표지정
		PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
		// 각도를 받고
		for (int i = 0; i < 5; i++)
		{
			Missile* Em = playScene->SpawnMissile(this, "25", this->pos, { 25, 25 });
			Em->SetAngle(DegreeToRadian(num));		// 각도 값
			Em->SetSpeed(MSpeed);					// 총알 스피드
			Em->SetMovePatten(Patten::ANGLEMOVE);	// 초알 패턴
			num += 20;
		}
		num = 50;
		pTime = 0;
	}
}

void EnemyBoss::bossMove()
{
	switch (movePCheck)
	{
	case 0:
		movePosCheck++;
		switch (movePosCheck)
		{
		case 1:
			RandPos.y = 550;
			break;
		case 2:
			RandPos.x = 100 + Play_LeftX;
			RandPos.y = 400;
			break;
		case 3:
			RandPos.y = 200;
			break;
		case 4:
			LocationReset();
			break;
		case 5:
			RandPos.x = Play_RightX - 100;
			RandPos.y = 200;
			break;
		case 6:
			RandPos.y = 400;
			break;
		case 7:
			LocationReset();
			RandPos.y = 550;
			break;
		case 8:
			LocationReset();
			movePosCheck = 0;
			movePCheck++;
			break;
		default:
			break;
		}
		break;
	case 1:
		movePosCheck++;
		switch (movePosCheck)
		{
		case 1:
			RandPos.x = 100 + Play_LeftX;
			RandPos.y = 400;
			break;
		case 2:
			RandPos.x = Play_RightX - 100;
			break;
		case 3:
			RandPos.x = 200 + Play_LeftX;
			break;
		case 4:
			RandPos.x = Play_RightX - 100;
			break;
		case 5:
			LocationReset();
			movePosCheck = 0;
			movePCheck++;
			break;
		default:
			break;
		}
		break;
	case 2:
		movePosCheck++;
		switch (movePosCheck)
		{
		case 1:
			RandPos.y = 750;
			break;
		case 2:
			RandPos.x = 200 + Play_LeftX;
			RandPos.y = 450;
			break;
		case 3:
			RandPos.x = Play_RightX - 200;
			break;
		case 4:
			LocationReset();
			movePosCheck = 0;
			movePCheck++;
			break;
		default:
			break;
		}
		break;
	case 3:
		movePosCheck++;
		switch (movePosCheck)
		{
		case 1:
			RandPos.y = 350;
			break;
		case 2:
			RandPos.x = 100 + Play_LeftX;
			RandPos.y = 600;
			break;
		case 3:
			RandPos.y = 200;
			break;
		case 4:
			RandPos.x = Play_RightX - 100;
			RandPos.y = 600;
			break;
		case 5:
			RandPos.y = 200;
			break;
		case 6:
			LocationReset();
			RandPos.y = 350;
			break;
		case 7:
			LocationReset();
			movePosCheck = 0;
			movePCheck = 0;
			movePCheck++;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}







}

void EnemyBoss::OnHit(class Missile* hitMissile)
{

	Enemy::OnHit(hitMissile);

}

void EnemyBoss::Idle()
{
	imageinfo.framex++;
	if (imageinfo.framex > 3)
		imageinfo.framex = 0;
}
