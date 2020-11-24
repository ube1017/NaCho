#include "BackGround.h"
#include "Image.h"

HRESULT BackGround::Init()
{
	Background1.imageName = "Background1";
	Background1.drwrc = { (LONG)Play_LeftX , (LONG)0 , (LONG)Play_RightX , WINSIZE_Y };
	Background2.imageName = "Background2";
	Background2.drwrc = { (LONG)Play_LeftX , (LONG)0 , (LONG)Play_RightX , WINSIZE_Y };
	Background5.imageName = "Background5";
	Background5.drwrc = { (LONG)Play_LeftX , (LONG)0 , (LONG)Play_RightX , WINSIZE_Y };
	Background3.imageName = "Background3";
	Background3.drwrc = { (LONG)Play_LeftX , (LONG)0 , (LONG)Play_RightX , WINSIZE_Y };
	Background4.imageName = "Background4";
	Background4.drwrc = { (LONG)Play_LeftX , (LONG)0 , (LONG)Play_RightX , WINSIZE_Y };
	mapImage.imageName = "mapImage";
	mapImage.drwrc = { (LONG)Play_LeftX , (LONG)0 , (LONG)Play_RightX , WINSIZE_Y };
	
	
	return E_NOTIMPL;
}

void BackGround::Release()
{
	BaseUI::Release();
}

void BackGround::Update()
{

}

void BackGround::Render(HDC hdc)
{ 
	//return;
	BaseUI::Render(hdc);
	ImageManager* imageManager = ImageManager::GetSingleton();

	//imageManager->DrawAnimImage(hdc, Background5);
	//imageManager->DrawAnimImage(hdc, Background3);
	imageManager->DrawAnimImage(hdc, Background2);
	imageManager->DrawAnimImage(hdc, Background4);
	imageManager->DrawAnimImage(hdc, Background1);
	//imageManager->DrawAnimImage(hdc, mapImage);
	
	//  //ÁÂ¿ì¹®¿ÀÇÁ´×
	//
	
	
	
	
	//imageManager->DrawAnimImage(hdc, Soulgeiji);
	//imageManager->DrawAnimImage(hdc, SkillGeiji);
	
	

	//imageManager->DrawAnimImage(hdc, Background2);   
	//imageManager->DrawAnimImage(hdc, Background4);

	//Rectangle(hdc, Play_LeftX, 0, Play_RightX, WINSIZE_Y);
	//leftCloud
	//leftBack->FrameRender(hdc, leftBack1pos.x, leftBack1pos.y,224, WINSIZE_Y ,0,0);
	//leftBack->FrameRender(hdc, leftBack2pos.x, leftBack2pos.y, 224, WINSIZE_Y , 1, 0);
	//Image* image = ImageManager::GetSingleton()->FindImage("leftCloud");
	//image->Render(hdc,0,0);
}
