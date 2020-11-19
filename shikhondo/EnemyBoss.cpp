#include "EnemyBoss.h"
#include "PlayScene.h"
#include "GamePlayStatic.h"
#include "Missile.h"

HRESULT EnemyBoss::Init()
{
	hp = 1000;
	damge = 1;
	speed = 1.0f;
	size.cx = 80;
	size.cy = 160;
	hitBoxSize = size;
	ShootCount = 0;
	angleNum = 20;
	angleNum2 = 9;

	pattenCheck = false;
	// ���� ��ġ ����
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
	imageinfo.MovePos(pos);

	checkTime += TimerManager::GetSingleton()->GettimeElapsed();
	ShootCount += TimerManager::GetSingleton()->GettimeElapsed();
	hitBox = { (LONG)pos.x - hitBoxSize.cx / 2, (LONG)pos.y - hitBoxSize.cy / 2,
				(LONG)pos.x + hitBoxSize.cx / 2, (LONG)pos.y + hitBoxSize.cy / 2 };
	if (checkTime >= 0.5f)
	{
		if (!AutomaticMissile)
		{
			// 1����
			// ź �߻��� ��ǥ����
			PlayScene* playScene = dynamic_cast<PlayScene*>(GamePlayStatic::GetScene());
			// ������ �ް�
			for (int i = 0; i < 8; i++)
			{
				Em[i] = playScene->SpawnMissile(this, "21", this->pos, { 25, 25 });
				Em[i]->SetAngle(DegreeToRadian(angleNum));		// ���� ��
				Em[i]->SetSpeed(speed);					// �Ѿ� ���ǵ�
				Em[i]->SetMovePatten(Patten::ANGLEMOVE);	// �ʾ� ����
				angleNum += 45;
			}
			angleNum = 20;

			//�� ������ �����̴� �ڵ�
			checkTime = 0;
			AutomaticMissile = true;
			pattenCheck = true;
		}
		else if (AutomaticMissile)
		{
			if (checkTime >= 0.5f && pattenCheck)
			{
				// 1����
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
	//	// ������ �ް�
	//	for (int i = 0; i < 18; i++)
	//	{
	//		Missile* Em = playScene->SpawnMissile(this, "21", this->pos, { 25, 25 });
	//		Em->SetAngle(DegreeToRadian(angleNum2));		// ���� ��
	//		Em->SetSpeed(2.5f);					// �Ѿ� ���ǵ�
	//		Em->SetMovePatten(Patten::ANGLEMOVE);	// �ʾ� ����
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
		// ������ �ް�
		for (int i = 0; i < 18; i++)
		{
			Missile* Em = playScene->SpawnMissile(this, "21", this->pos, { 25, 25 });
			Em->SetAngle(DegreeToRadian(angleNum2));		// ���� ��
			Em->SetSpeed(2.5f);					// �Ѿ� ���ǵ�
			Em->SetMovePatten(Patten::ANGLEMOVE);	// �ʾ� ����
			angleNum2 += 9;
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
	Rectangle(hdc, pos.x - (size.cx / 2), pos.y - (size.cy / 2), pos.x + (size.cx / 2), pos.y + (size.cy / 2));
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
		Em->SetAngle(MAngle);		// ���� ��
		Em->SetSpeed(speed);					// �Ѿ� ���ǵ�
		Em->SetMovePatten(Patten::ANGLEMOVE);	// �ʾ� ����
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
