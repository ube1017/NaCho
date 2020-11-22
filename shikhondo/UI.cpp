#include "UI.h"
#include "GamePlayStatic.h"
#include "PlayScene.h"
#include "Player.h"

HRESULT UI::Init()
{
	leftBack1pos.x = Play_LeftX;
	leftBack1pos.y = 0;
	leftBack1.drwrc = { (LONG)Play_LeftX, (LONG)-10, (LONG)Play_LeftX + PlayXSize /2 , WINSIZE_Y+20};
	leftBack1.imageName = "leftBack";
	leftBack1.framex = 0;
	leftBack1.framey = 0;

	leftBack2pos.x = Play_LeftX + PlayXSize / 2;
	leftBack2pos.y = 0;
	leftBack2.imageName = "leftBack";
	leftBack2.drwrc = { (LONG)Play_LeftX + PlayXSize / 2   , (LONG)-10 , (LONG)Play_RightX , WINSIZE_Y + 20 };
	leftBack1.framex = 1;
	leftBack1.framey = 0;

	LeftUpBackground.imageName = "LeftUpBackground";
	LeftUpBackground.drwrc = { (LONG)0 , (LONG)0 , (LONG)650 , 350 };
	LeftBackground.imageName = "LeftBackground";
	LeftBackground.drwrc = { (LONG)0 , (LONG)150 , (LONG)600 , 700 };
	LeftSideDownBackground.imageName = "LeftSideDownBackground";
	LeftSideDownBackground.drwrc = { (LONG)0 , (LONG)400 , (LONG)430 , WINSIZE_Y };
	RightUpBackground.imageName = "RightUpBackground";
	RightUpBackground.drwrc = { (LONG)600 , (LONG)0 , (LONG)WINSIZE_X , 400 };
	RightBackground.imageName = "RightBackground";
	RightBackground.drwrc = { (LONG)650 , (LONG)150 , (LONG)WINSIZE_X , 700 };
	RightSideDownBackground.imageName = "RightSideDownBackground";
	RightSideDownBackground.drwrc = { (LONG)850 , (LONG)400 , (LONG)WINSIZE_X , WINSIZE_Y };
	isFullOpen = false;
	playerHp = 0;
	playerSoulGauge = 0;
	playerBoom = 0;
	Soulgeiji2.imageName = "Soulgeiji2";
	Soulgeiji2.drwrc = { (LONG)935 , (LONG)18 , (LONG)1010 , 115 };
	Soulgeiji2.framex = 0;
	Soulgeiji2.framey = 0;
	for (int i = 0; i < 4; i++)
	{
		SkillGeiji[i].imageName = "SkillGeiji";
		SkillGeiji[i].drwrc = { (LONG)665 + (i * 35), (LONG)798 , (LONG)729 + (i * 35) , 926 };
		SkillGeiji[i].framex = 9;
	}
	Life.imageName = "Life";
	Life.drwrc = { (LONG)0 , (LONG)300 , (LONG)1024 , 598 };
	test.imageName = "test";
	test.drwrc = { (LONG)780 , (LONG)150 , (LONG)1450, 340 };
	SoulGeijiBack.imageName = "SoulGeijiBack";
	SoulGeijiBack.drwrc = { (LONG)940 , (LONG)50 , (LONG)1300, 140 };
	SideSoul.imageName = "SideSoul";
	SideSoul.drwrc = { (LONG)350 , (LONG)700 , (LONG)500, 800 };
	boss_Hp_Bar1.imageName = "boss_Hp_Bar1";
	boss_Hp_Bar1.drwrc = { (LONG)350 , (LONG)60 , (LONG)910, 90  };
	boss_Hp_Bar2.imageName = "boss_Hp_Bar2";
	boss_Hp_Bar2.drwrc = { (LONG)350 , (LONG)60 , (LONG)910, 90 };
	boss_Hp_Bar3.imageName = "boss_Hp_Bar3";
	boss_Hp_Bar3.drwrc = { (LONG)400 , (LONG)90 , (LONG)500, 130 };
	for (int i = 0; i < 14; i++)
	{
		Font1[i].imageName = "Font";
		Font1[i].drwrc = { (LONG)350 , (LONG)10 , (LONG)400, 30 };
	}
	for (int i = 0; i < 14; i++)
	{
		Font2[i].imageName = "Font";
		Font2[i].drwrc = { (LONG)650 , (LONG)10 , (LONG)700, 30 };
	}
	for (int i = 0; i < 14; i++)
	{
		Font3[i].imageName = "Font";
		Font3[i].drwrc = { (LONG)350 , (LONG)10 , (LONG)400, 30 };
	}
	Bar1.imageName = "Bar1";
	Bar1.drwrc = { (LONG)350 , (LONG)20 , (LONG)910, 70 };
	Bar2.imageName = "Bar2";
	Bar2.drwrc = { (LONG)350 , (LONG)20 , (LONG)910, 70 };
	Bar3.imageName = "Bar3";
	Bar3.drwrc = { (LONG)350 , (LONG)20 , (LONG)910, 70 };
	return S_OK;
}

void UI::Release()
{

}

void UI::Update()
{
	if (!isFullOpen)
	Soulgeiji2.framex++;
	if (Soulgeiji2.framey > 3)
	{
		Soulgeiji2.framey = 0;
	}
	else
	{
		if (Soulgeiji2.framex >= 2)
		{
			Soulgeiji2.framex = 0;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		SkillGeiji[i].framex += 2;
		if (SkillGeiji[i].framex > 24)
		{
			SkillGeiji[i].framex = 8;
		}
	}
	return;
	if (leftBack1pos.x > Play_LeftX - 225)
	{
		if (leftBack1.drwrc.right > Play_LeftX)
		{
			//leftBack1pos.x--;
			leftBack1.MovePos(MovePosType::X_AIS, -2);
		}

		if (leftBack2.drwrc.left < Play_RightX)
		{
			//leftBack2pos.x++;
			leftBack2.MovePos(MovePosType::X_AIS, +2);
		}
		else
		{
			PlayScene* playScen = Cast<PlayScene>(GamePlayStatic::GetScene());
			playScen->spawnStart.Execute();
			playScen->spawnStart.UnBind();
			isFullOpen = true;
		}
	}

	Player* player = Cast<Player>(GamePlayStatic::GetPlayerCharacter());
	if (player)
	{
		playerHp = player->GetHp();
		playerSoulGauge = player->GetSoulGauge();
		playerBoom = player->GetBoom();
	}
}

void UI::Render(HDC hdc)
{
	BaseUI::Render(hdc);
	ImageManager* imageManager = ImageManager::GetSingleton();
	imageManager->DrawAnimImage(hdc, leftBack1);
	imageManager->DrawAnimImage(hdc, leftBack2);
	imageManager->DrawAnimImage(hdc, LeftBackground);
	imageManager->DrawAnimImage(hdc, LeftSideDownBackground);
	imageManager->DrawAnimImage(hdc, LeftUpBackground);
	imageManager->DrawAnimImage(hdc, RightBackground);
	imageManager->DrawAnimImage(hdc, RightSideDownBackground);
	imageManager->DrawAnimImage(hdc, RightUpBackground);
	imageManager->DrawAnimImage(hdc, test);
	imageManager->DrawAnimImage(hdc, SoulGeijiBack);
	imageManager->DrawAnimImage(hdc, Soulgeiji2);
	for (int i = 0; i < 4; i++)
	{
		imageManager->DrawAnimImage(hdc, SkillGeiji[i]);
	}
	//imageManager->DrawAnimImage(hdc, Life);
	//imageManager->DrawAnimImage(hdc, SideSoul);
	imageManager->DrawAnimImage(hdc, boss_Hp_Bar1);
	imageManager->DrawAnimImage(hdc, boss_Hp_Bar2);
	imageManager->DrawAnimImage(hdc, boss_Hp_Bar3);
	for (int i = 0; i < 14; i++)
	{
		imageManager->DrawAnimImage(hdc, Font1[i]);
	}
	for (int i = 0; i < 14; i++)
	{
		imageManager->DrawAnimImage(hdc, Font2[i]);
	}
	for (int i = 0; i < 14; i++)
	{
		imageManager->DrawAnimImage(hdc, Font3[i]);
	}
	
	//imageManager->DrawAnimImage(hdc, Bar1);
	//imageManager->DrawAnimImage(hdc, Bar2);
	imageManager->DrawAnimImage(hdc, Bar3);
	
	
}
