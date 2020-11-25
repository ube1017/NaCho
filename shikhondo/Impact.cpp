#include "Impact.h"
#include "Image.h"

HRESULT Impact::Init()
{
	return E_NOTIMPL;
}

void Impact::Release()
{
}

void Impact::Update()
{
}

void Impact::Render(HDC hdc)
{
	BaseUI::Render(hdc);
	ImageManager::GetSingleton()->DrawAnimImage(hdc, impactimageinfo);

}

void Impact::SpawnImpact(string name, FPOINT pos, SIZE size, float framdelay)
{
	impactimageinfo.imageName = name;
	impactimageinfo.size = size;
	impactimageinfo.MovePos(pos);
	impactimageinfo.framex = 0;
	impactimageinfo.framey = 0;
	this->SetIsValid(true);
	TimerManager::GetSingleton()->SetTimer(idleTimer,this,&Impact::idle, framdelay);
}

void Impact::idle()
{
	Image* image =  ImageManager::GetSingleton()->FindImage(impactimageinfo.imageName);
	if (image == nullptr)
		return;
	int maxFramx = image->GetMaxFramX();
	int maxFramy = image->GetMaxFramY();

	impactimageinfo.framex++;
	if (impactimageinfo.framex >= maxFramx)
	{
		impactimageinfo.framex = 0;
		impactimageinfo.framey++;
		if (impactimageinfo.framey >= maxFramy)
		{
			//impactimageinfo.framey = 0;
			TimerManager::GetSingleton()->DeleteTimer(idleTimer);
		}
	}
	
}
