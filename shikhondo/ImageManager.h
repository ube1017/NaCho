#pragma once
#include "pch.h"
#include "Singleton.h"
#include <map>

using namespace std;

struct ImageDrawInfo
{
	// 그릴 이미지 사각형 사이즈
	RECT drwrc;
	// 그림 사이즈
	SIZE size;
	// 이미지 이름
	string imageName;
	// 몇번째 이미지인지 x축
	int framex;
	// 몇번째 이미지인지 y축
	int framey;
	// 애니메이션 사이즈
	SIZE animSize;
	bool isAnimSizeReset = false;


	bool isAnimStartRest = false;
	int startx;
	int starty;

	enum class MovePosType
	{
		X_AIS,
		Y_AIS,
		XY_AIS,
	};

	void MovePos(FPOINT pos)
	{
		drwrc = {	(LONG)pos.x - (size.cx / 2) ,(LONG)pos.y - (size.cy / 2),
					(LONG)pos.x + (size.cx / 2) ,(LONG)pos.y + (size.cy / 2) };
	}

	template<typename T>
	void MovePos(MovePosType type, T value, T XY_AIS_YValue = 0)
	{
		switch (type)
		{
		case ImageDrawInfo::MovePosType::X_AIS:
			drwrc.left += static_cast<LONG>(value);
			drwrc.right += static_cast<LONG>(value);
			break;
		case ImageDrawInfo::MovePosType::Y_AIS:
			drwrc.top += static_cast<LONG>(value);
			drwrc.bottom += static_cast<LONG>(value);
			break;
		case ImageDrawInfo::MovePosType::XY_AIS:
			drwrc.left += static_cast<LONG>(value);
			drwrc.right += static_cast<LONG>(value);
			if (XY_AIS_YValue != 0)
			{
				drwrc.top += static_cast<LONG>(XY_AIS_YValue);
				drwrc.bottom += static_cast<LONG>(XY_AIS_YValue);
			}
			else
			{
				drwrc.top += static_cast<LONG>(value);
				drwrc.bottom += static_cast<LONG>(value);
			}
			break;
		default:
			break;
		}
	}

	void DrawRectSetting(std::string imageName, FPOINT pos, SIZE size, bool isAnimSizeReset = false, SIZE animSize = { 0,0 }, bool isAnimStartRest = false,SIZE animStart = {0,0})
	{
		drwrc = { (LONG)pos.x - (size.cx / 2) ,(LONG)pos.y - (size.cy / 2),
				  (LONG)pos.x + (size.cx / 2) ,(LONG)pos.y + (size.cy / 2) };
		this->imageName = imageName;
		this->size = size;
		this->isAnimSizeReset = isAnimSizeReset;
		this->animSize = animSize;
		this->framex = 0;
		this->framey = 0;
		this->isAnimStartRest = isAnimStartRest;
		this->startx = animStart.cx;
		this->starty = animStart.cy;
	}

};

typedef ImageDrawInfo::MovePosType MovePosType;

enum class ImageType : UINT8
{
	IMAGE,
	SPRITE
};

const int enemyMissileImageToken_Max = 5;
class ImageManager : public Singleton<ImageManager>
{
public:
	typedef const char* Token;
	Token enemyMissileImage[enemyMissileImageToken_Max] =
	{
		"21",
		"22",
		"23",
		"24",
		"25",
	};
	
public:
	ImageManager();
	~ImageManager();

	void Init();

	// 비트맵 로드 확장자 안적어도 됨
	void _LoadBitmap(string fileName, SIZE bitmapSzie, ImageType type = ImageType::IMAGE, UINT transColor = RGB(255, 0, 255));
	void _LoadBitmap(string key ,string fileName, SIZE bitmapSzie, ImageType type = ImageType::IMAGE, UINT transColor = RGB(255, 0, 255));
	void _LoadBitmap(string key, string fileName, SIZE bitmapSzie, SIZE animSize,ImageType type = ImageType::IMAGE, UINT transColor = RGB(255, 0, 255));

	//이미지찾기 key = 이미지 이름
	class Image* FindImage(string key);

	void DeleteImage(string key);
	// 그림 그리기
	void DrawImage(HDC hdc , string imageName, const ImageDrawInfo& imageDrawInfo);
	void DrawImage(HDC hdc , const ImageDrawInfo& imageDrawInfo);
	// 스프라이트 애니매이션
	void DrawAnimImage(HDC hdc, string imageName, const ImageDrawInfo& imageDrawInfo);
	void DrawAnimImage(HDC hdc, const ImageDrawInfo& imageDrawInfo);

	void AlphaRender(HDC hdc, const ImageDrawInfo& imageDrawInfo, BYTE alpha);


	inline Token GetRandMissileImageName()	{ return enemyMissileImage[rand() % enemyMissileImageToken_Max]; }
	inline Token GetIndexMissileImageName(int index) { if (index < enemyMissileImageToken_Max) return enemyMissileImage[index]; return ""; }
private:
	std::map <string, class Image*> images;

};
