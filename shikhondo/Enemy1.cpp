#include "Enemy1.h"
#include "PlayScene.h"
#include "GamePlayStatic.h"
#include "Missile.h"

HRESULT Enemy1::Init()
{
	hp = 10;
	damge = 1;
	speed = 1.0f;
	size.cx = 30;
	size.cy = 60;
	hitBoxSize = size;
	locationCount = 0;
	// 시작 위치 설정
	RandLocation();
	LocationReset();

	checkTime = 0;
	AutomaticMissile = false;

	//imageinfo.imageName = "enemy1";
	imageinfo.DrawRectSetting("enemy1", this->pos, { 100,100 }, true, { 100,100 });
	TimerManager::GetSingleton()->SetTimer(idleTimer, this, &Enemy1::Idle, 0.070f);

	return E_NOTIMPL;
}

void Enemy1::Release()
{
}

void Enemy1::Update()
{
	pos.x += cosf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;
	pos.y += sinf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;
	imageinfo.MovePos(pos);
	hitBox = {	(LONG)pos.x - hitBoxSize.cx / 2, (LONG)pos.y - hitBoxSize.cy / 2, 
				(LONG)pos.x + hitBoxSize.cx / 2, (LONG)pos.y + hitBoxSize.cy / 2 };
	

	if (!AutomaticMissile)
	{
		if (pos.x < RandPos.x + 5 && pos.x >= RandPos.x - 5)
		{
			if (pos.y < RandPos.y + 5 && pos.y >= RandPos.y - 5)
			{// 탄 발사전 좌표지정
				PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
				// 각도를 받고
				Missile* Em1 = playScene->SpawnMissile(this, "21", this->pos, { 10, 10 });
			
				Em1->SetAngle(this->GetAngle());		// 각도 값
				Em1->SetSpeed(speed);					// 총알 스피드
				Em1->SetMovePatten(Patten::ANGLEMOVE);	// 초알 패턴
			   //그 각도로 움직이는 코드
				checkTime = 0;
				speed = 0;
				AutomaticMissile = true;
				speed = 0;
			}
		}
	}
	else if (AutomaticMissile)
	{
		checkTime += TimerManager::GetSingleton()->GettimeElapsed();
		if (checkTime >= 2.0f)
		{
			LocationReset();

			checkTime = 0;
			AutomaticMissile = false;
			speed = 1.0f;
		}
	}
	//else if (checkTime >= 1.3f && AutomaticMissile)
	//{
	//	checkTime = 0;
	//}

	// 위치 초기화할때 위에꺼도 초기화
}

void Enemy1::Render(HDC hdc)
{
	ImageManager::GetSingleton()->DrawAnimImage(hdc, imageinfo);
	Rectangle(hdc, hitBox.left, hitBox.top, hitBox.right, hitBox.bottom);
	//Rectangle(hdc, pos.x - (size.cx / 2), pos.y - (size.cy / 2), pos.x + (size.cx / 2), pos.y + (size.cy / 2));
}

void Enemy1::RandLocation()
{
	RandNum = rand() % 2;
	RandPos.x = rand() % PlayXSize + Play_LeftX;
	RandPos.y = rand() % (WINSIZE_Y / 2);
	if (RandNum == 0)
	{
		RandPos.y = -100;
	}
	else if (RandNum == 1)
	{
		if (RandPos.x > WINSIZE_X / 2)
		{
			RandPos.x = 1000;
		}
		else
		{
			RandPos.x = 0;
		}
	}


	this->pos.x = RandPos.x;
	this->pos.y = RandPos.y;
	imageinfo.MovePos(RandPos);
}

void Enemy1::LocationReset()
{
	locationCount++;
	if (locationCount < 4)
	{
		RandPos.x = (rand() % (PlayXSize - size.cx)) + (size.cx / 2 + Play_LeftX);
		RandPos.y = (rand() % (WINSIZE_Y / 2 - size.cy)) + (size.cy / 2);
	}
	else if (locationCount < 5)
	{
		RandPos.x = rand() % PlayXSize + Play_LeftX;
		RandPos.y = rand() % (WINSIZE_Y / 2) + 50;

		if (RandPos.x > WINSIZE_X / 2)
		{
			RandPos.x = 2000;
		}
		else
		{
			RandPos.x = -100;
		}
	}
	else
	{
		//죽이고 싶으면 여기서 주기면댐
	}
}

void Enemy1::Death()
{
	Character::Death();
	TimerManager::GetSingleton()->DeleteTimer(idleTimer);
}

void Enemy1::Idle()
{
	imageinfo.framex++;
	if(imageinfo.framex > 12)
	{
		imageinfo.framex = 0;
	}
}
