#include "EnemyBoss.h"
#include "PlayScene.h"
#include "GamePlayStatic.h"
#include "Missile.h"

HRESULT EnemyBoss::Init()
{
	hp = 1500;
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
	pattenCheck = false;
	stop = true;
	// 시작 위치 설정
	LocationReset();
	RandLocation();
	bossMove();
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
	imageinfo.MovePos(pos);
	DEBUG_MASSAGE("보스체력이다 : %d \n", this->hp);
	if (!stop)
	{
		if (roundCheck == 0)
		{
			if (hp > 500)
			{
				checkTime += TimerManager::GetSingleton()->GettimeElapsed();
				ShootCount += TimerManager::GetSingleton()->GettimeElapsed();
				hitBox = { (LONG)pos.x - hitBoxSize.cx / 2, (LONG)pos.y - hitBoxSize.cy / 2,
							(LONG)pos.x + hitBoxSize.cx / 2, (LONG)pos.y + hitBoxSize.cy / 2 };

				pos.x += cosf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;
				pos.y += sinf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;

				if (pos.x < RandPos.x + 5 && pos.x >= RandPos.x - 5)
				{
					if (pos.y < RandPos.y + 5 && pos.y >= RandPos.y - 5)
					{
						bossMove();
					}
				}
				if (checkTime >= 1.0f)
				{
					patten2();
					checkTime = 0;
				}
			}
			else if (hp <= 500)
			{
				roundCheck++;
				hp = 2000;
				speed = 2;
				stop = true;
			}
		}
		else if (roundCheck == 1)
		{
			if (hp > 300)
			{
				checkTime += TimerManager::GetSingleton()->GettimeElapsed();
				ShootCount += TimerManager::GetSingleton()->GettimeElapsed();
				hitBox = { (LONG)pos.x - hitBoxSize.cx / 2, (LONG)pos.y - hitBoxSize.cy / 2,
							(LONG)pos.x + hitBoxSize.cx / 2, (LONG)pos.y + hitBoxSize.cy / 2 };

				pos.x += cosf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;
				pos.y += sinf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;

				if (pos.x < RandPos.x + 5 && pos.x >= RandPos.x - 5)
				{
					if (pos.y < RandPos.y + 5 && pos.y >= RandPos.y - 5)
					{
						bossMove();
					}
				}
				if (checkTime >= 0.5f)
				{
					patten2();
					patten3();
					checkTime = 0;
				}
			}
			else if (hp <= 300)
			{
				roundCheck++;
				hp = 3000;
				speed = 2;
				stop = true;
			}
		}
		else if (roundCheck == 2)
		{
			if (hp > 0)
			{
				checkTime += TimerManager::GetSingleton()->GettimeElapsed();
				ShootCount += TimerManager::GetSingleton()->GettimeElapsed();
				hitBox = { (LONG)pos.x - hitBoxSize.cx / 2, (LONG)pos.y - hitBoxSize.cy / 2,
							(LONG)pos.x + hitBoxSize.cx / 2, (LONG)pos.y + hitBoxSize.cy / 2 };

				pos.x += cosf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;
				pos.y += sinf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;

				if (pos.x < RandPos.x + 5 && pos.x >= RandPos.x - 5)
				{
					if (pos.y < RandPos.y + 5 && pos.y >= RandPos.y - 5)
					{
						bossMove();
					}
				}
				if (checkTime >= 0.5f)
				{
					patten4();
					patten5();
					checkTime = 0;
				}
			}
			else if (hp <= 0)
			{
				roundCheck++;
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
		Em->SetSpeed(speed);					// 총알 스피드
		Em->SetMovePatten(Patten::ANGLEMOVE);	// 초알 패턴
		speed += 0.06f;
		if (speed > 1.06f)
		{
			speed += 0.1f;
		}
	}
	speed = 1.0;
}

void EnemyBoss::patten2()
{
	PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
	float angle = 0.0f;

	for (int i = 0; i < 20; i++)
	{
		Missile* Em = playScene->SpawnMissile(this, "21", this->pos, { 30, 30 });
		Em->SetSpeed(missileSpeed2);
		Em->SetAngle(angle);
		Em->SetMovePatten(Patten::TEST2);

		Missile* Em1 = playScene->SpawnMissile(this, "21", this->pos, { 30, 30 });
		Em1->SetSpeed(missileSpeed2);
		Em1->SetAngle(angle);
		Em1->SetMovePatten(Patten::TEST);

		angle += 0.3f;//(6.14 / 20.0f);
	}

}

void EnemyBoss::patten3()
{
	PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
	if (!AutomaticMissile)
	{
		// 1패턴
		// 탄 발사전 좌표지정

		// 각도를 받고
		for (int i = 0; i < 8; i++)
		{
			Em[i] = playScene->SpawnMissile(this, "21", this->pos, { 25, 25 });
			Em[i]->SetAngle(DegreeToRadian(angleNum));		// 각도 값
			Em[i]->SetSpeed(missileSpeed);					// 총알 스피드
			Em[i]->SetMovePatten(Patten::ANGLEMOVE);	// 초알 패턴
			angleNum += 45;
		}
		angleNum = 20;

		//그 각도로 움직이는 코드
		checkTime = 0;
		AutomaticMissile = true;
		pattenCheck = true;
	}
	else if (AutomaticMissile)
	{
		if (checkTime >= 0.5f && pattenCheck)
		{
			// 1패턴
			for (int i = 0; i < 8; i++)
			{
				patten1(Em[i]->GetPos(), Em[i]->GetAngle());
			}
			pattenCheck = false;
		}
		if (checkTime >= 3.0f)
		{
			ShootCount = 0;
			checkTime = 0;
			AutomaticMissile = false;
			speed = 1.0f;
		}
	}
}

void EnemyBoss::patten4()
{
	PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
	if (ShootCount >= 1.0f)
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
		ShootCount = 0;
	}
}

void EnemyBoss::patten5()
{
	PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
	if (ShootCount >= 1.0f)
	{
		// 각도를 받고
		for (int i = 0; i < 14; i++)
		{
			Missile* Em = playScene->SpawnMissile(this, "21", this->pos, { 25, 25 });
			Em->SetAngle(DegreeToRadian(angleNum2));		// 각도 값
			Em->SetSpeed(2.5f);					// 총알 스피드
			Em->SetMovePatten(Patten::ANGLEMOVE);	// 초알 패턴
			angleNum2 += 14;
			if (angleNum2 == 81)
			{
				//angleNum2 = 99;
			}
		}
		//angleNum2 = 9;
		ShootCount = 0;
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

void EnemyBoss::Idle()
{
	imageinfo.framex++;
	if (imageinfo.framex > 3)
		imageinfo.framex = 0;
}
