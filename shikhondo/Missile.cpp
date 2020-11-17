#include "Missile.h"

HRESULT Missile::Init()
{
	this->imaginfo.imageName = "";
	this->imaginfo.drwrc = { 0,0,0,0 };
	this->imaginfo.size = {0,0};
	this->imaginfo.framex = 0;
	this->imaginfo.framey = 0;
	return S_OK;
}

void Missile::Release()
{
	GameNode::Release();
}

void Missile::Update()
{
	GameNode::Update();
}

void Missile::Render(HDC hdc)
{
	GameNode::Render(hdc);
	ImageManager::GetSingleton()->DrawAnimImage(hdc, imaginfo);
}

void Missile::MissileSetting(string imageName, FPOINT pos, SIZE size)
{
	this->pos = pos;
	this->size = size;
	this->imaginfo.imageName = imageName;
	this->imaginfo.drwrc = { (LONG)pos.x ,(LONG)pos.y,(LONG)pos.x + size.cx, (LONG)pos.y + size.cy };
	this->imaginfo.size = size;
	this->imaginfo.framex = 0;
	this->imaginfo.framey = 0;
}
