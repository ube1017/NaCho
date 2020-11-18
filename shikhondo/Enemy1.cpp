#include "Enemy1.h"
#include "PlayScene.h"
#include "GamePlayStatic.h"

HRESULT Enemy1::Init()
{
	hp = 10;
	damge = 1;
	speed = 1.0f;
	size.cx = 30;
	size.cy = 60;
	locationCount = 0;
	// ���� ��ġ ����
	RandLocation();
	LocationReset();

	checkTime = 0;
	AutomaticMissile = false;

	//imageinfo.imageName = "enemy1";
	imageinfo.DrawRectSetting("enemy1", this->pos, { 145,155 }, true, { 145,158 });
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

	checkTime += TimerManager::GetSingleton()->GettimeElapsed();

	if (!AutomaticMissile)
	{
		if (pos.x < RandPos.x + 5 && pos.x >= RandPos.x - 5)
		{
			if (pos.y < RandPos.y + 5 && pos.y >= RandPos.y - 5)
			{// ź �߻��� ��ǥ����
				PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
				// ������ �ް�
				playScene->SpawnMissile(this, "21", this->pos, { 10, 10 });
				//cosf(this->GetAngle()) * speed;
				//sinf(this->GetAngle()) * speed;

			   //�� ������ �����̴� �ڵ�
				checkTime = 0;
				AutomaticMissile = true;
			}
		}
	}
	//else if (checkTime >= 1.3f && AutomaticMissile)
	//{
	//	checkTime = 0;
	//}

	// ��ġ �ʱ�ȭ�Ҷ� �������� �ʱ�ȭ
}

void Enemy1::Render(HDC hdc)
{
	ImageManager::GetSingleton()->DrawAnimImage(hdc, imageinfo);
	Rectangle(hdc, pos.x - (size.cx / 2), pos.y - (size.cy / 2), pos.x + (size.cx / 2), pos.y + (size.cy / 2));
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
	if (locationCount < 3)
	{
		RandPos.x = (rand() % (PlayXSize - size.cx)) + (size.cx / 2 + Play_LeftX);
		RandPos.y = (rand() % (WINSIZE_Y / 2 - size.cy)) + (size.cy / 2);
	}
	else
	{
		RandPos.x = rand() % PlayXSize + Play_LeftX;
		RandPos.y = rand() % (WINSIZE_Y / 2) + 50;

		if (RandPos.x > WINSIZE_X / 2)
		{
			RandPos.x = 1200;
		}
		else
		{
			RandPos.x = -100;
		}
		locationCount = 0;
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
	if (imageinfo.framey < 2)
	{
		if (imageinfo.framex > 2)
		{
			imageinfo.framex = 0;
			imageinfo.framey++;
		}
	}
	else
	{
		if (imageinfo.framex > 1)
		{
			imageinfo.framex = 0;
			imageinfo.framey = 0;

		}
	}
}
