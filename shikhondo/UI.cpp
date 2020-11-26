#include "UI.h"
#include "GamePlayStatic.h"
#include "PlayScene.h"
#include "Player.h"

UI::UI()
{
	playerSkillEfect.BindObject(this,&UI::SkillEffectOn);
}

HRESULT UI::Init()
{
	isbossSpawn = false;
	Player* player = Cast<Player>(GamePlayStatic::GetPlayerCharacter());
	if (player)
	{
		playerHp = player->GetHp_ptr();
		playerSoulGauge = player->GetSoulGauge_ptr();
		playerBoom = player->GetBoom_ptr();
		pSoulSocre = player->GetSoulScore_ptr();
	}

	leftBack1pos.x = Play_LeftX;
	leftBack1pos.y = 0;
	leftBack1.drwrc = { (LONG)Play_LeftX - 10, (LONG)-10, (LONG)Play_LeftX + PlayXSize /2 , WINSIZE_Y+20};
	leftBack1.imageName = "leftBack";  //문
	leftBack1.framex = 0;
	leftBack1.framey = 0;

	leftBack2pos.x = Play_LeftX + PlayXSize / 2;
	leftBack2pos.y = 0;
	leftBack2.imageName = "leftBack";  //문
	leftBack2.drwrc = { (LONG)Play_LeftX + PlayXSize / 2   , (LONG)-10 , (LONG)Play_RightX + 10, WINSIZE_Y + 20 };
	leftBack1.framex = 1;
	leftBack1.framey = 0;

	UIleftBack1.drwrc = { 0, (LONG)-10, (LONG)Play_LeftX  , WINSIZE_Y + 7 };
	UIleftBack1.imageName = "leftBack";  //문

	UIleftBack2.drwrc = { Play_RightX, (LONG)-10, (LONG)WINSIZE_X  , WINSIZE_Y + 7};
	UIleftBack2.imageName = "leftBack";  //문


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
	Soulgeiji2.imageName = "Soulgeiji2";  // 오른쪽위 불꽃
	Soulgeiji2.drwrc = { (LONG)935 , (LONG)18 , (LONG)1010 , 115 };
	Soulgeiji2.framex = 0;
	Soulgeiji2.framey = 0;

	Soulgeiji2Time = 0.0f;
	for (int i = 0; i < 4; i++)
	{
		SkillGeiji[i].imageName = "SkillGeiji";  //가운데 아래 폭탄게이지
		SkillGeiji[i].drwrc = { (LONG)715 + (i * 35), (LONG)798 , (LONG)779 + (i * 35) , 926 };
		SkillGeiji[i].framex = 9;
		SkillGeijiTime = 0.0f;
	}

	for (int i = 0; i < 4; i++)
	{
		Life[i].imageName = "Life";   //왼쪽아래 나비모양
		Life[i].drwrc = { (LONG)340+(i*40) , (LONG)860 , (LONG)390 + (i * 40) , 905 };
		Life[i].framex = 0;
		LifeTime = 0.0f;
	}

	test.imageName = "test";   //오른쪽위 소울컬렉트
	test.drwrc = { (LONG)780 , (LONG)150 , (LONG)1450, 340 };
	SoulGeijiBack.imageName = "SoulGeijiBack";  //오른쪽위 소울게이지 검은바탕
	SoulGeijiBack.drwrc = { (LONG)940 , (LONG)50 , (LONG)1300, 140 };
	for (int i = 0; i < 2; i++)
	{
		SideSoul[i].imageName = "SideSoul";  //플레이어 보조무기
		SideSoul[i].drwrc = { (LONG)350 + (i * 40), (LONG)500 , (LONG)450 + (i * 40), 600 };
		SideSoul[i].framex = 0;
		SideSoulTime = 0.0f;
	}
	boss_Hp_Bar1.imageName = "boss_Hp_Bar1"; // 검은색
	boss_Hp_Bar1.drwrc = { (LONG)395 , (LONG)41 , (LONG)615, 52  };
	boss_Hp_Bar2.imageName = "boss_Hp_Bar2";  //테두리  
	boss_Hp_Bar2.drwrc = { (LONG)320 , (LONG)0 , (LONG)950, 80 };
	boss_Hp_Bar3.imageName = "boss_Hp_Bar3"; //내용물
	boss_Hp_Bar3.drwrc = { (LONG)500 , (LONG)41 , (LONG)650, 52 };
	for (int i = 0; i < 14; i++)
	{
		Font1[i].imageName = "Font"; //왼쪽위
		Font1[i].drwrc = { (LONG)370+(i*15) , (LONG)0 , (LONG)390 + (i * 15), 30 };
	}
	for (int i = 0; i < 14; i++)
	{
		Font2[i].imageName = "Font";  //오른쪽위
		Font2[i].drwrc = { (LONG)680 + (i * 15) , (LONG)0 , (LONG)700 + (i * 15), 30 };
	}
	for (int i = 0; i < 4; i++)
	{
		Font3[i].imageName = "Font";  //소울게이지숫자
		Font3[i].drwrc = { (LONG)990 + (i * 25) , (LONG)55 , (LONG)1025 + (i * 25), 105 };
	}
	Bar1.imageName = "Bar1";  //불꽃게이지바
	Bar1.drwrc = { (LONG)350 , (LONG)20 , (LONG)910, 70 };
	Bar2.imageName = "Bar2";
	Bar2.drwrc = { (LONG)Play_RightX + 30, (LONG)229 , (LONG)Play_RightX + 275, 297 };//{ (LONG)350 , (LONG)20 , (LONG)910, 70 };
	Bar2.isAnimSizeReset = true;
	Bar2.animSize = { 512,128 };
	Bar3.imageName = "Bar3";
	Bar3.drwrc = { (LONG)350 , (LONG)20 , (LONG)910, 70 };
	Impact.imageName = "Impact";
	Impact.drwrc = { (LONG)350 , (LONG)20 , (LONG)550, 70 };
	ImpactTime = 0.0f;
	Impact2.imageName = "Impact2";
	Impact2.drwrc = { (LONG)350 , (LONG)20 , (LONG)550, 70 };
	Impact2Time = 0.0f;
	Back.imageName = "Back";
	Back.drwrc = { (LONG)0 , (LONG)0 , (LONG)WINSIZE_X, WINSIZE_Y };
	Back.imageName = "Back";
	Back.drwrc = { (LONG)0 , (LONG)0 , (LONG)WINSIZE_X, WINSIZE_Y };
	BossInit.imageName = "BossInit";
	BossInit.drwrc = { (LONG)0 - (WINSIZE_X / 4) , (LONG)-(WINSIZE_Y / 3) ,
		(LONG)WINSIZE_X + (WINSIZE_X / 4), WINSIZE_Y + (WINSIZE_Y / 3) };
	Warning.imageName = "Warning";
	Warning.drwrc = { (LONG)0 + (WINSIZE_X / 4)-100 , (LONG)40 , (LONG)WINSIZE_X - (WINSIZE_X / 4)+100, WINSIZE_Y+40 };
	BossFont[0].imageName = "BossFont3";
	BossFont[0].drwrc = { (LONG)840- 20 , (LONG)-130 , (LONG)1240 - 20, 300 };
	BossFont[1].imageName = "BossFont1";
	BossFont[1].drwrc = { (LONG)800 - 20 , (LONG)130 , (LONG)1200 - 20, 560 };
	BossFont[2].imageName = "BossFont2";
	BossFont[2].drwrc = { (LONG)750 - 20, (LONG)370 , (LONG)1150 - 20,800 };
	BossFont[3].imageName = "BossFont4";
	BossFont[3].drwrc = { (LONG)720 - 20 , (LONG)600 , (LONG)1120 - 20, 1030 };
	BossFontBack.imageName = "BossFontBack";
	BossFontBack.drwrc = { (LONG)520 , (LONG)-300 , (LONG)WINSIZE_X+20, WINSIZE_Y+300 };
	SkillEffect1.imageName = "SkillEffect1"; //가운데
	SkillEffect1.drwrc = { (LONG)450, (LONG)100 , (LONG)850, 300 };
	SkillEffect2.imageName = "SkillEffect2"; //왼쪽
	SkillEffect2.drwrc = { (LONG)280, (LONG)0 , (LONG)680, 400 };
	SkillEffect3.imageName = "SkillEffect3"; //밑
	SkillEffect3.drwrc = { (LONG)500, (LONG)280 , (LONG)800, 350 };
	SkillEffect4.imageName = "SkillEffect4"; //오른쪽
	SkillEffect4.drwrc = { (LONG)650, (LONG)0 , (LONG)1000 ,400 };
	
	LeftCloud1.imageName = "LeftCloud1"; //왼쪽위
	LeftCloud1.drwrc = { (LONG)-100, (LONG)0 , (LONG)500, 200 };
	LeftCloud2.imageName = "LeftCloud2";//왼쪽가운데
	LeftCloud2.drwrc = { (LONG)-100, (LONG)350 , (LONG)320, 800 };
	LeftCloud3.imageName = "LeftCloud3";//왼쪽아래
	LeftCloud3.drwrc = { (LONG)-100, (LONG)600 , (LONG)500, 800 };
	
	RightCloud1.imageName = "RightCloud1"; //오른쪽 중간위
	RightCloud1.drwrc = { (LONG)900, (LONG)280 , (LONG)1450, 400 };
	RightCloud2.imageName = "RightCloud2"; //오른쪽 중간아래
	RightCloud2.drwrc = { (LONG)850, (LONG)650 , (LONG)1650, 850 };
	RightCloud3.imageName = "RightCloud3"; //오른쪽맨밑
	RightCloud3.drwrc = { (LONG)800, (LONG)700 , (LONG)1300, 900 };
	RightCloud4.imageName = "RightCloud4"; //오른쪽맨위
	RightCloud4.drwrc = { (LONG)750, (LONG)50 , (LONG)1650, 450 };
	
	SoulGeiji3.imageName = "SoulGeiji3";
	SoulGeiji3.drwrc = { (LONG)1015, (LONG)200 , (LONG)1265, 290 };

	
	closeCount = DoorState::OPEN;
	isWaring = false;
	isUsingBackImage = true;
	isTurn = false;
	isskillEffect = false;
	socre = 0;
	return S_OK;
}

void UI::Release()
{

}

void UI::Update()
{
	Soulgeiji2Time += TimerManager::GetSingleton()->GettimeElapsed();
	if (Soulgeiji2Time >= 0.05f)
	{
		Soulgeiji2.framex++;
		if (Soulgeiji2.framey == 0)
		{
			if (Soulgeiji2.framex >= 2)
			{
				Soulgeiji2.framex = 0;
				Soulgeiji2.framey = 1;
			}

		}
		else if (Soulgeiji2.framey == 1)
		{
			if (Soulgeiji2.framex >= 2)
			{
				Soulgeiji2.framex = 0;
				Soulgeiji2.framey = 2;
			}
		}
		else
		{
			if (Soulgeiji2.framex >= 2)
			{
				Soulgeiji2.framex = 0;
				Soulgeiji2.framey = 0;
			}
		}
		Soulgeiji2Time = 0.0f;
	}

	SkillGeijiTime += TimerManager::GetSingleton()->GettimeElapsed();
	if (SkillGeijiTime >= 0.1f)
	{
		for (int i = 0; i < 4; i++)
		{
			SkillGeiji[i].framex += 2;
			if (SkillGeiji[i].framex > 24)
			{
				SkillGeiji[i].framex = 8;
			}
		}
		SkillGeijiTime = 0.0f;
	}

	LifeTime += TimerManager::GetSingleton()->GettimeElapsed();
	if (LifeTime >= 0.1f)
	{
		for (int i = 0; i < 4; i++)
		{
			Life[i].framex++;
			if (Life[i].framex >= 4)
			{
				Life[i].framex = 0;
			}
		}
		LifeTime = 0.0f;
	}

	SideSoulTime += TimerManager::GetSingleton()->GettimeElapsed();
	if (SideSoulTime >= 0.05f)
	{
		for (int i = 0; i < 2; i++)
		{
			SideSoul[i].framex++;
			if (SideSoul[i].framex >= 21)
			{
				SideSoul[i].framex = 0;
			}
		}
		SideSoulTime = 0.0f;
	}
	ImpactTime += TimerManager::GetSingleton()->GettimeElapsed();
	if (ImpactTime >= 0.05f)
	{

		Impact.framex++;
		if (Impact.framex >= 8)
		{
			Impact.framex = 0;
		}

		ImpactTime = 0.0f;
	}

	if (!isFullOpen && (closeCount != DoorState::HOLD))
	{
		if (leftBack1pos.x > Play_LeftX - 225)
		{
			if (leftBack1.drwrc.right > Play_LeftX)
			{
				//leftBack1pos.x--;
				if (closeCount != DoorState::BOSSOPEN)
					leftBack1.MovePos(MovePosType::X_AIS, -2);
				else
					leftBack1.MovePos(MovePosType::X_AIS, -8);
			}

			if (leftBack2.drwrc.left < Play_RightX)
			{
				//leftBack2pos.x++;
				if (closeCount != DoorState::BOSSOPEN)
					leftBack2.MovePos(MovePosType::X_AIS, +2);
				else
					leftBack2.MovePos(MovePosType::X_AIS, +8);
			}
			else
			{
				closeCount = DoorState::NONE;
				PlayScene* playScen = Cast<PlayScene>(GamePlayStatic::GetScene());
				playScen->spawnStart.Execute();
				playScen->spawnStart.UnBind();
				isFullOpen = true;
			
			}
		}
	}
	else if (closeCount != DoorState::NONE)
	{
		//if (leftBack1pos.x >= Play_LeftX - 225)
		{
			if (leftBack1.drwrc.right < Play_LeftX + PlayXSize / 2)
			{
				//leftBack1pos.x--;
				leftBack1.MovePos(MovePosType::X_AIS, +8);
				if (closeCount == DoorState::BOSSCLOSE)
				{
					LeftCloud1.MovePos(MovePosType::X_AIS, +2);
					LeftCloud2.MovePos(MovePosType::X_AIS, +2);
					LeftCloud3.MovePos(MovePosType::X_AIS, +2);
				}
			}

			if (leftBack2.drwrc.left > Play_LeftX + PlayXSize / 2)
			{
				//leftBack2pos.x++;
				leftBack2.MovePos(MovePosType::X_AIS, -8);
				if (closeCount == DoorState::BOSSCLOSE)
				{
					RightCloud1.MovePos(MovePosType::X_AIS, -2);
					RightCloud2.MovePos(MovePosType::X_AIS, -2);
					RightCloud3.MovePos(MovePosType::X_AIS, -2);
					RightCloud4.MovePos(MovePosType::X_AIS, -2);
				}
			}
			else
			{
				if (closeCount != DoorState::HOLD)
					this->WarningUI();
			}
		}
	}

	int width = Play_RightX + 275 - (Play_RightX + 30);
	int drwrcR = width;
	int bar2AnimR = 512;
	if (playerSoulGauge)
	{
		drwrcR = (int)((float)((float)*playerSoulGauge / (float)maxSoulGauge) * (float)width);
		bar2AnimR = (int)((float)((float)*playerSoulGauge / (float)maxSoulGauge) * (float)512);
	}
	Bar2.drwrc = { (LONG)Play_RightX + 30, (LONG)229 , (LONG)Play_RightX + 30 + drwrcR, 297 };
	Bar2.animSize = { bar2AnimR,128 };


	if (isbossSpawn)
	{
		if (*bossHp > bossMaxHp)
			bossMaxHp = *bossHp;
		float hpPersent = (((float)*bossHp / (float)bossMaxHp));
		int width = 865 - 395;
		// 검은색
		boss_Hp_Bar1.drwrc = { (LONG)395 , (LONG)41 , (LONG)395 + (LONG)(width * hpPersent), 52 };
		int boss_bar_left  = (LONG)boss_Hp_Bar1.drwrc.right - 201;
		if (boss_bar_left <= boss_Hp_Bar2.drwrc.left)
			boss_bar_left = boss_Hp_Bar2.drwrc.left;
		//내용물
		boss_Hp_Bar3.drwrc = { boss_bar_left -20 , (LONG)41 , boss_Hp_Bar1.drwrc.right + 75, 52 };

		boss_Hp_Bar2.drwrc = { (LONG)320 , (LONG)0 , (LONG)950, 80 };
	}
	int sSocre = *pSoulSocre;
	int temp = 0;

	int j = 0;
	soulSocreCount = 0;
	for (int i = 3; i > -1; i--)
	{
		if (i != 0)
		{
 			if (sSocre - (int)pow(10, i) >= 0 && soulSocreCount == 0)
				soulSocreCount = i;

			temp = sSocre / (int)pow(10, i);
			if (temp != 0)
			{
				Font3[j].framex = temp % 10;
				j++;
			}
		}
		else
		{
			temp = sSocre % 10;
			Font3[j].framex = temp;
			j++;
		}
	}

	j = 13;
	socreCount = 0;
	for (int i = 0; i < 13; i++)
	{
		if (i != 0)
		{
			if (socre - (int)pow(10, i) >= 0 && socreCount == 0)
				socreCount = i;

			temp = socre / (int)pow(10, i);
			if (temp != 0)
			{
				Font2[j].framex = temp % 10;
				Font1[j].framex = Font2[j].framex;
				j--;
			}
		}
		else
		{
			temp = socre % 10;
			Font2[j].framex = temp;
			Font1[j].framex = Font2[j].framex;
			j--;
		}
	}

}

void UI::Render(HDC hdc)
{
	BaseUI::Render(hdc);
	ImageManager* imageManager = ImageManager::GetSingleton();
	//imageManager->DrawAnimImage(hdc, leftBack1);
	//imageManager->DrawAnimImage(hdc, leftBack2);

	//이부분 보스등장씬
	/*imageManager->DrawAnimImage(hdc, BossInit);
	imageManager->DrawAnimImage(hdc, LeftCloud1);
	imageManager->DrawAnimImage(hdc, LeftCloud2);
	imageManager->DrawAnimImage(hdc, LeftCloud3);
	imageManager->DrawAnimImage(hdc, RightCloud1);
	imageManager->DrawAnimImage(hdc, RightCloud2);
	imageManager->DrawAnimImage(hdc, RightCloud3);
	imageManager->DrawAnimImage(hdc, RightCloud4);
	imageManager->DrawAnimImage(hdc, Warning);*/

	//이부분 스킬사용시
	if (isskillEffect)
	{
		imageManager->DrawAnimImage(hdc, SkillEffect4);
		imageManager->DrawAnimImage(hdc, SkillEffect2);
		imageManager->DrawAnimImage(hdc, SkillEffect1);
		imageManager->DrawAnimImage(hdc, SkillEffect3);
	}

	if (closeCount != DoorState::NONE)
	{
		imageManager->DrawAnimImage(hdc, leftBack1);
		imageManager->DrawAnimImage(hdc, leftBack2);
	}

	if (isUsingBackImage)
		imageManager->DrawAnimImage(hdc, Back);
	else
	{
		imageManager->DrawAnimImage(hdc, UIleftBack1);
		imageManager->DrawAnimImage(hdc, UIleftBack2);
		if (isWaring)
		{
			imageManager->DrawAnimImage(hdc, BossInit);
			//imageManager->DrawAnimImage(hdc, Warning);
			imageManager->AlphaRender(hdc, Warning, Warning.alpha);
		}
		imageManager->AlphaRender(hdc, LeftCloud1, LeftCloud1.alpha);
		imageManager->AlphaRender(hdc, LeftCloud2, LeftCloud2.alpha);
		imageManager->AlphaRender(hdc, LeftCloud3, LeftCloud3.alpha);
		imageManager->AlphaRender(hdc, RightCloud1,RightCloud1.alpha);
		imageManager->AlphaRender(hdc, RightCloud2,RightCloud2.alpha);
		imageManager->AlphaRender(hdc, RightCloud3,RightCloud3.alpha);
		imageManager->AlphaRender(hdc, RightCloud4,RightCloud4.alpha);


		imageManager->DrawAnimImage(hdc, LeftBackground);
		imageManager->DrawAnimImage(hdc, LeftSideDownBackground);
		imageManager->DrawAnimImage(hdc, LeftUpBackground);
		imageManager->DrawAnimImage(hdc, RightBackground);
		imageManager->DrawAnimImage(hdc, RightSideDownBackground);
		imageManager->DrawAnimImage(hdc, RightUpBackground);
	}
	imageManager->DrawAnimImage(hdc, test);
	imageManager->DrawAnimImage(hdc, SoulGeijiBack);
	imageManager->DrawAnimImage(hdc, Soulgeiji2);
	if (playerBoom)
	{
		for (int i = 0; i < *playerBoom; i++)
		{
			SkillGeiji[0].drwrc = { (LONG)715 + (i * 35), (LONG)798 , (LONG)779 + (i * 35) , 926 };
			imageManager->DrawAnimImage(hdc, SkillGeiji[0]);
		}
	}
	if (playerHp)
	{
		for (int i = 0; i < *playerHp; i++)
		{
			Life[0].drwrc = { (LONG)340 + (i * 40) , (LONG)860 , (LONG)390 + (i * 40) , 905 };
			imageManager->DrawAnimImage(hdc, Life[0]);
		}
	}

	if (isbossSpawn)
	{
		imageManager->DrawAnimImage(hdc, boss_Hp_Bar2);
		imageManager->DrawAnimImage(hdc, boss_Hp_Bar1);
		imageManager->DrawAnimImage(hdc, boss_Hp_Bar3);
	}

	for (int i = 0; i < 14; i++)
	{
		imageManager->DrawAnimImage(hdc, Font1[i]);
	}
	for (int i = 0; i < 14; i++)
	{
		imageManager->DrawAnimImage(hdc, Font2[i]);
	}
	for (int i = 0; i < soulSocreCount + 1; i++)
	{
		imageManager->DrawAnimImage(hdc, Font3[i]);
	}
	//for (int i = 0; i < 2; i++)
	//{
	//	imageManager->DrawAnimImage(hdc, SideSoul[i]);
	//}

	//imageManager->DrawAnimImage(hdc, Bar1);
	imageManager->DrawAnimImage(hdc, Bar2);
	//imageManager->DrawAnimImage(hdc, Bar3);
	//imageManager->DrawAnimImage(hdc, Impact);
	//imageManager->DrawAnimImage(hdc, Impact2);
	/*imageManager->DrawAnimImage(hdc, BossFontBack);
	imageManager->DrawAnimImage(hdc, BossFont3);
	imageManager->DrawAnimImage(hdc, BossFont1);
	imageManager->DrawAnimImage(hdc, BossFont2);
	imageManager->DrawAnimImage(hdc, BossFont4);*/
	//imageManager->DrawAnimImage(hdc, Impact);
	//imageManager->DrawAnimImage(hdc, Impact2);
	imageManager->DrawAnimImage(hdc, SoulGeiji3);
	if (isbossFont)
	{
		imageManager->DrawAnimImage(hdc, BossFontBack);
		for (int i = 0; i < bossFontUIcount; i++)
			imageManager->DrawAnimImage(hdc, BossFont[i]);
		
	}
}

void UI::BossStage()
{
	closeCount = DoorState::BOSSCLOSE;
	isUsingBackImage = false;
}

void UI::WarningUI()
{
	isWaring = true;
	isFullOpen = true;
	closeCount = DoorState::HOLD;
	BossInit.imageName = "BossInit";
	BossInit.drwrc = { (LONG)0 - (WINSIZE_X / 4) , (LONG)-(WINSIZE_Y / 3) ,
		(LONG)WINSIZE_X + (WINSIZE_X / 4), WINSIZE_Y + (WINSIZE_Y / 3) };
	Warning.imageName = "Warning";
	Warning.drwrc = { (LONG)0 + (WINSIZE_X / 4) - 100 , (LONG)40 , (LONG)WINSIZE_X - (WINSIZE_X / 4) + 100, WINSIZE_Y + 40 };
	TimerManager::GetSingleton()->SetTimer(warningUIEndtimer, this, &UI::WarningUIEnd, 2.0f);
	TimerManager::GetSingleton()->SetTimer(AlphaTimer, this, &UI::WarningAlpha, 0.1f);
	PlayScene* plsyScene = Cast<PlayScene>(GamePlayStatic::GetScene());
	plsyScene->SetAllShaek(1,-1,2.0f);
	Warning.alpha = 0;
	isTurn = false;

}

void UI::WarningUIEnd()
{
	closeCount = DoorState::BOSSOPEN;
	isFullOpen = false;
	isWaring = false;
	TimerManager::GetSingleton()->DeleteTimer(warningUIEndtimer);
	TimerManager::GetSingleton()->DeleteTimer(AlphaTimer);
	TimerManager::GetSingleton()->SetTimer(warningUIEndtimer, this, &UI::BossFontUI, 0.5f);
	TimerManager::GetSingleton()->SetTimer(AlphaTimer, this, &UI::CloudAlhpa, 0.2f);
	bossFontUIcount = 0;
	isbossFont = true;

}

void UI::BossFontUI()
{
	bossFontUIcount++;
	if (bossFontUIcount == 5)
	{
		TimerManager::GetSingleton()->DeleteTimer(warningUIEndtimer);
		isbossFont = false;
		bossFontUIcount = 0;
		TimerManager::GetSingleton()->SetTimer(bossSpawnTimer, this, &UI::BossSpawn, 0.8f);
		isUsingBackImage = true;
	}
	else
		GamePlayStatic::GetScene()->SetSideShake(5, 0.2f);

}

void UI::BossSpawn()
{
	PlayScene* plsyScene = Cast<PlayScene>(GamePlayStatic::GetScene());
	plsyScene->BossSpawnBind();
	plsyScene->spawnStart.Execute();
	plsyScene->spawnStart.UnBind();
	TimerManager::GetSingleton()->DeleteTimer(bossSpawnTimer);
}

void UI::WarningAlpha()
{
	int alpha = Warning.alpha;
	if (!isTurn)
		alpha += 60;
	else
		alpha -= 60;

	if (alpha >= 255)
	{
		isTurn = true;
		alpha = 254;
	}
	if (alpha <= 0 )
	{ 
		isTurn = false;
		alpha = 1;
	}

	Warning.alpha = alpha;
}

void UI::CloudAlhpa()
{
	int alpha = LeftCloud1.alpha;
	alpha += 60;
	if (alpha >= 255)
		alpha = 255;

	LeftCloud1.alpha = alpha;
	LeftCloud2.alpha = alpha;
	LeftCloud3.alpha = alpha;
	RightCloud1.alpha= alpha;
	RightCloud2.alpha= alpha;
	RightCloud3.alpha= alpha;
	RightCloud4.alpha= alpha;
}

void UI::SkillEffectOn()
{
	isskillEffect = true;
	GamePlayStatic::GetScene()->SetAllShaek(2,-6,0.5f);
	TimerManager::GetSingleton()->SetTimer(skillEffectTimer, this, &UI::SkillEffectOff);
}

void UI::SkillEffectOff()
{
	isskillEffect = false;
	TimerManager::GetSingleton()->DeleteTimer(skillEffectTimer);
}
