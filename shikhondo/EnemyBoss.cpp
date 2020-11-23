#include "EnemyBoss.h"
#include "PlayScene.h"
#include "GamePlayStatic.h"
#include "Missile.h"

HRESULT EnemyBoss::Init()
{
	hp = 3000;
	damge = 1;
	speed = 1.0f;
	missileSpeed = 1.5f;
	size.cx = 80;
	size.cy = 160;
	hitBoxSize = size;
	ShootCount = 0;
	angleNum = 20;
	angleNum2 = 14;

	pattenCheck = false;
	// 시작 위치 설정
	RandLocation();
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

	checkTime += TimerManager::GetSingleton()->GettimeElapsed();
	ShootCount += TimerManager::GetSingleton()->GettimeElapsed();
	hitBox = { (LONG)pos.x - hitBoxSize.cx / 2, (LONG)pos.y - hitBoxSize.cy / 2,
				(LONG)pos.x + hitBoxSize.cx / 2, (LONG)pos.y + hitBoxSize.cy / 2 };
	if (checkTime >= 0.5f)
	{
		if (!AutomaticMissile)
		{
			// 1패턴
			// 탄 발사전 좌표지정
			PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
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
			if (checkTime >= 5.0f)
			{
				ShootCount = 0;
				checkTime = 0;
				AutomaticMissile = false;
				speed = 1.0f;
			}
		}
	}

	//if (ShootCount >= 0.3f)
	//{
	//	PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
	//	// 각도를 받고
	//	for (int i = 0; i < 18; i++)
	//	{
	//		Missile* Em = playScene->SpawnMissile(this, "21", this->pos, { 25, 25 });
	//		Em->SetAngle(DegreeToRadian(angleNum2));		// 각도 값
	//		Em->SetSpeed(2.5f);					// 총알 스피드
	//		Em->SetMovePatten(Patten::ANGLEMOVE);	// 초알 패턴
	//		angleNum2 += 9;
	//		if (angleNum2 == 81)
	//		{
	//			angleNum2 = 99;
	//		}
	//	}
	//	angleNum2 = 9;
	//	ShootCount = 0;
	//}

	if (ShootCount >= 0.3f)
	{
		PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
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

void EnemyBoss::Render(HDC hdc)
{
#ifdef _DEBUG
	Rectangle(hdc, pos.x - (size.cx / 2), pos.y - (size.cy / 2), pos.x + (size.cx / 2), pos.y + (size.cy / 2));
#endif // _DEBUG
	ImageManager::GetSingleton()->DrawAnimImage(hdc, imageinfo);
}

void EnemyBoss::RandLocation()
{
	this->pos.x = WINSIZE_X / 2;
	this->pos.y = 150;
	imageinfo.MovePos(this->pos);
}

void EnemyBoss::LocationReset()
{

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

void EnemyBoss::Idle()
{
	imageinfo.framex++;
	if (imageinfo.framex > 3)
		imageinfo.framex = 0;
}
