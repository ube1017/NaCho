#include "ImageManager.h"
#include "Image.h"

ImageManager::ImageManager()
{
	
}

ImageManager::~ImageManager()
{
	map<string, Image*>::iterator it;
	Image* image = nullptr;
	for (it = images.begin(); it != images.end(); it++)
	{
		image = it->second;
		if (image != nullptr)
		{
			image->Release();
			delete image;
			image = nullptr;
		}
	}
	images.clear();


}

void ImageManager::Init()
{


}

void ImageManager::_LoadBitmap(string fileName, SIZE bitmapSzie, ImageType type, UINT transColor)
{
	Image* newImage = new Image;
	string image = "Image/";
	string bmp = ".bmp";
	string filename = image + fileName + bmp;

	switch (type)
	{
	case ImageType::IMAGE:
		if (FAILED((newImage->Init(filename.c_str(), bitmapSzie.cx, bitmapSzie.cy, true, transColor))))
		{
			DEBUG_MASSAGE("비트맵 블러오기 실패");
			delete newImage;
			newImage = nullptr;
			return;
		}
		images.insert(make_pair(fileName, newImage));
		break;
	case ImageType::SPRITE:
		if (FAILED((newImage->Init(filename.c_str(), bitmapSzie.cx, bitmapSzie.cy, true, transColor))))
		{
			DEBUG_MASSAGE("비트맵 블러오기 실패");
			delete newImage;
			newImage = nullptr;
			return;
		}
		images.insert(make_pair(fileName, newImage));
		break;
	default:
		break;
	}
}

void ImageManager::_LoadBitmap(string key, string fileName, SIZE bitmapSzie, ImageType type, UINT transColor)
{
	if (this->FindImage(key) != nullptr)
		return;
	Image* newImage = new Image;
	string image = "Image/";
	string bmp = ".bmp";
	string filename = image + fileName + bmp;

	switch (type)
	{
	case ImageType::IMAGE:
		if (FAILED((newImage->Init(filename.c_str(), bitmapSzie.cx, bitmapSzie.cy, true, transColor))))
		{
			DEBUG_MASSAGE("비트맵 블러오기 실패");
			delete newImage;
			newImage = nullptr;
			return;
		}
		images.insert(make_pair(key, newImage));
		break;
	case ImageType::SPRITE:
		if (FAILED((newImage->Init(filename.c_str(), bitmapSzie.cx, bitmapSzie.cy, true, transColor))))
		{
			DEBUG_MASSAGE("비트맵 블러오기 실패");
			delete newImage;
			newImage = nullptr;
			return;
		}
		images.insert(make_pair(key, newImage));
		break;
	default:
		break;
	}
}

void ImageManager::_LoadBitmap(string key, string fileName, SIZE bitmapSzie, SIZE animSize, ImageType type, UINT transColor)
{
	if (this->FindImage(key) != nullptr)
		return;
	Image* newImage = new Image;
	string image = "Image/";
	string bmp = ".bmp";
	string filename = image + fileName + bmp;

	switch (type)
	{
	case ImageType::IMAGE:
		if (FAILED((newImage->Init(filename.c_str(), bitmapSzie.cx, bitmapSzie.cy, animSize.cx, animSize.cy,true, transColor))))
		{
			DEBUG_MASSAGE("비트맵 블러오기 실패");
			delete newImage;
			newImage = nullptr;
			return;
		}
		images.insert(make_pair(key, newImage));
		break;
	case ImageType::SPRITE:
		if (FAILED((newImage->Init(filename.c_str(), bitmapSzie.cx, bitmapSzie.cy, animSize.cx, animSize.cy, true, transColor))))
		{
			DEBUG_MASSAGE("비트맵 블러오기 실패");
			delete newImage;
			newImage = nullptr;
			return;
		}
		images.insert(make_pair(key, newImage));
		break;
	default:
		break;
	}
}

Image* ImageManager::FindImage(string key)
{
	map<string, Image*>::iterator it;
	if (images.size() == 0)
		return nullptr;
	it = images.find(key);
	if (it != images.end())
		return it->second;
	return nullptr;
}

void ImageManager::DeleteImage(string key)
{
	Image* findImage = this->FindImage(key);
	findImage->Release();
	delete findImage;
	images.erase(key);
}

void ImageManager::DrawImage(HDC hdc, string imageName, const ImageDrawInfo& imageDrawInfo)
{
	Image* drawImage = this->FindImage(imageName);
	if (drawImage)
		drawImage->Render(hdc , imageDrawInfo.drwrc.left, imageDrawInfo.drwrc.top , 
				imageDrawInfo.drwrc.right - imageDrawInfo.drwrc.left, imageDrawInfo.drwrc.bottom - imageDrawInfo.drwrc.top);
	else
	{
		string errorString = "Not Find '" + imageName + "''";
		MessageBox(g_hWnd, errorString.c_str(), "Image Error", MB_ICONWARNING);
	}
}

void ImageManager::DrawImage(HDC hdc, const ImageDrawInfo& imageDrawInfo)
{
	Image* drawImage = this->FindImage(imageDrawInfo.imageName);

	if (drawImage)
		drawImage->Render(hdc, imageDrawInfo.drwrc.left, imageDrawInfo.drwrc.top,
			imageDrawInfo.drwrc.right - imageDrawInfo.drwrc.left, imageDrawInfo.drwrc.bottom - imageDrawInfo.drwrc.top);
	else
	{
		string errorString = "Not Find '" + imageDrawInfo.imageName + "''";
		MessageBox(g_hWnd, errorString.c_str(), "Image Error", MB_ICONWARNING);
	}
}

void ImageManager::DrawAnimImage(HDC hdc, string imageName, const ImageDrawInfo& imageDrawInfo)
{
	Image* drawImage = this->FindImage(imageName);
	//int animX = (imageDrawInfo.animSize.cx * imageDrawInfo.framex);
	//int animY = (imageDrawInfo.animSize.cy * imageDrawInfo.framey);
	if (drawImage)
		drawImage->AnimRender(hdc, imageDrawInfo.drwrc.left, imageDrawInfo.drwrc.top, 
											imageDrawInfo.drwrc.right - imageDrawInfo.drwrc.left, imageDrawInfo.drwrc.bottom - imageDrawInfo.drwrc.top,
											imageDrawInfo.framex, imageDrawInfo.framey);
		//drawImage->AnimRender(hdc, imageDrawInfo.drwrc.left, imageDrawInfo.drwrc.top, 
		//								imageDrawInfo.drwrc.right - imageDrawInfo.drwrc.left, imageDrawInfo.drwrc.bottom - imageDrawInfo.drwrc.top,
		//								animX, animY, imageDrawInfo.animSize.cx, imageDrawInfo.animSize.cy);
	else
	{
		string errorString = "Not Find '" + imageName + "''";
		MessageBox(g_hWnd, errorString.c_str() , "Image Error",  MB_ICONWARNING);
	}
}

void ImageManager::DrawAnimImage(HDC hdc, const ImageDrawInfo& imageDrawInfo)
{
	Image* drawImage = this->FindImage(imageDrawInfo.imageName);
	//int animX = (imageDrawInfo.animSize.cx * imageDrawInfo.framex);
	//int animY = (imageDrawInfo.animSize.cy * imageDrawInfo.framey);
	if (drawImage)
		drawImage->AnimRender(hdc, imageDrawInfo.drwrc.left, imageDrawInfo.drwrc.top, 
											imageDrawInfo.drwrc.right - imageDrawInfo.drwrc.left, imageDrawInfo.drwrc.bottom - imageDrawInfo.drwrc.top,
											imageDrawInfo.framex, imageDrawInfo.framey);
		//drawImage->AnimRender(hdc, imageDrawInfo.drwrc.left, imageDrawInfo.drwrc.top,
		//	imageDrawInfo.drwrc.right - imageDrawInfo.drwrc.left, imageDrawInfo.drwrc.bottom - imageDrawInfo.drwrc.top,
		//	animX, animY, imageDrawInfo.animSize.cx, imageDrawInfo.animSize.cy);
	else
	{
		string errorString = "Not Find '" + imageDrawInfo.imageName + "''";
		MessageBox(g_hWnd, errorString.c_str(), "Image Error", MB_ICONWARNING);
	}
}

void ImageManager::AlphaRender(HDC hdc, const ImageDrawInfo & imageDrawInfo, BYTE alpha)
{
	Image* drawImage = this->FindImage(imageDrawInfo.imageName);
	if (drawImage)
	{
		drawImage->blendFun.SourceConstantAlpha = alpha;
		drawImage->AlphaRender(hdc, imageDrawInfo.drwrc.left, imageDrawInfo.drwrc.top,
										imageDrawInfo.drwrc.right - imageDrawInfo.drwrc.left, imageDrawInfo.drwrc.bottom - imageDrawInfo.drwrc.top,
										imageDrawInfo.framex, imageDrawInfo.framey, alpha);
	}
}

