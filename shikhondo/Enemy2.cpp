#include "Enemy2.h"
#include "PlayScene.h"
#include "GamePlayStatic.h"
#include "Missile.h"

HRESULT Enemy2::Init()
{
	hp = 30;
	damge = 1;
	speed = 1.0f;
	size.cx = 150;
	size.cy = 150;
	locationCount = 0;
	countSize = 0;
	ShootCount = 0;
	ImageNum = -1.0f;

	// ���� ��ġ ����
	RandLocation();
	LocationReset();

	////imageinfo.imageName = "enemy1";
	CircleImage.DrawRectSetting("enemy2_1", this->pos, size, true, { 400,400 });
	TimerManager::GetSingleton()->SetTimer(idleTimer, this, &Enemy2::Idle, 0.07f);
	imageinfo.DrawRectSetting("enemy2_2", this->pos, size, true, { 500,500 });
	TimerManager::GetSingleton()->SetTimer(idleTimer, this, &Enemy2::Idle, 0.07f);
	return E_NOTIMPL;
}

void Enemy2::Release()
{
}

void Enemy2::Update()
{
	pos.x += cosf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;
	pos.y += sinf(atan2((RandPos.y - pos.y), (RandPos.x - pos.x))) * speed;

	CircleImage.MovePos(pos);
	imageinfo.MovePos(pos);

	checkTime += TimerManager::GetSingleton()->GettimeElapsed();
	if (checkTime >= 0.1f)
	{
		if (!AutomaticMissile)
		{
			if (pos.x < RandPos.x + 5 && pos.x >= RandPos.x - 5)
			{
				if (pos.y < RandPos.y + 5 && pos.y >= RandPos.y - 5)
				{// ź �߻��� ��ǥ����
					PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
					// ������ �ް�
					Missile* Em1 = playScene->SpawnMissile(this, "21", { pos.x - (CircleImage.size.cx / 2), pos.y }, { 20, 20 });
					Missile* Em2 = playScene->SpawnMissile(this, "21", { pos.x + (CircleImage.size.cx / 2), pos.y }, { 20, 20 });
					Em1->SetAngle(this->GetAngle());		// ���� ��
					Em1->SetSpeed(speed);					// �Ѿ� ���ǵ�
					Em1->SetMovePatten(Patten::ANGLEMOVE);	// �ʾ� ����
					Em2->SetAngle(this->GetAngle());		// ���� ��
					Em2->SetSpeed(speed);					// �Ѿ� ���ǵ�
					Em2->SetMovePatten(Patten::ANGLEMOVE);	// �ʾ� ����

					ShootCount++;
					//�� ������ �����̴� �ڵ�
					checkTime = 0;

					if (ShootCount > 3)
					{
						checkTime = 0;
						AutomaticMissile = true;
						speed = 0;
					}
				}
			}
		}
		else if (AutomaticMissile)
		{
			if (checkTime >= 2.0f)
			{
				LocationReset();
				ShootCount = 0;
				checkTime = 0;
				AutomaticMissile = false;
				speed = 1.0f;
			}
		}
	}
	// �̹��� ����
	countSize++;
	if (countSize == 5)
	{
		CircleImage.size.cx += (LONG)ImageNum;
		CircleImage.size.cy += (LONG)ImageNum;

		if (CircleImage.size.cx == 150 || CircleImage.size.cx == 100)
		{
			ImageNum *= -1;
		}
		countSize = 0;
	}
}

void Enemy2::Render(HDC hdc)
{
	ImageManager::GetSingleton()->DrawAnimImage(hdc, CircleImage);
	ImageManager::GetSingleton()->DrawAnimImage(hdc, imageinfo);
	//Rectangle(hdc, pos.x - (size.cx / 2), pos.y - (size.cy / 2), pos.x + (size.cx / 2), pos.y + (size.cy / 2));
}

void Enemy2::RandLocation()
{
	RandNum = rand() % 2;
	RandPos.x = rand() % PlayXSize + Play_LeftX;
	RandPos.y = rand() % (WINSIZE_Y / 2);
	if (RandNum == 0)
	{
		RandPos.y *= -1;
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
	CircleImage.MovePos(RandPos);
}

void Enemy2::LocationReset()
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

void Enemy2::Death()
{
	Character::Death();
	TimerManager::GetSingleton()->DeleteTimer(idleTimer);
}

void Enemy2::Idle()
{
	imageinfo.framex++;
	CircleImage.framex++;
	if (CircleImage.framex > 8)
	{
		CircleImage.framex = 0;
	}
	if (imageinfo.framex > 11)
	{
		imageinfo.framex = 0;
	}
}
