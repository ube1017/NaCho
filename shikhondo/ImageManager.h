#pragma once
#include "pch.h"
#include "Singleton.h"
#include <map>

using namespace std;
struct ImageDrawInfo
{
	// �׸� �̹��� �簢�� ������
	RECT drwrc;
	// �׸� ������
	SIZE size;
	// �̹��� �̸�
	string imageName;
	// ���° �̹������� x��
	int framex;
	// ���° �̹������� y��
	int framey;


	enum class MovePosType
	{
		X_AIS,
		Y_AIS,
		XY_AIS,
	};

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

	void DrawRectSetting(std::string imageName, FPOINT pos, SIZE size )
	{
		drwrc = { (LONG)pos.x - (size.cx / 2) ,(LONG)pos.y - (size.cy / 2),
				  (LONG)pos.x + (size.cx / 2) ,(LONG)pos.y + (size.cy / 2) };
		this->imageName = imageName;
		this->size = size;
	}

};

typedef ImageDrawInfo::MovePosType MovePosType;

enum class ImageType : UINT8
{
	IMAGE,
	SPRITE
};

class ImageManager : public Singleton<ImageManager>
{

public:
	ImageManager();
	~ImageManager();

	void Init();

	// ��Ʈ�� �ε� Ȯ���� ����� ��
	void _LoadBitmap(string fileName, SIZE bitmapSzie, ImageType type = ImageType::IMAGE, UINT transColor = RGB(255, 0, 255));
	void _LoadBitmap(string key ,string fileName, SIZE bitmapSzie, ImageType type = ImageType::IMAGE, UINT transColor = RGB(255, 0, 255));
	void _LoadBitmap(string key, string fileName, SIZE bitmapSzie, SIZE animSize,ImageType type = ImageType::IMAGE, UINT transColor = RGB(255, 0, 255));

	//�̹���ã�� key = �̹��� �̸�
	class Image* FindImage(string key);

	void DeleteImage(string key);
	// �׸� �׸���
	void DrawImage(HDC hdc , string imageName, const ImageDrawInfo& imageDrawInfo);
	void DrawImage(HDC hdc , const ImageDrawInfo& imageDrawInfo);
	// ��������Ʈ �ִϸ��̼�
	void DrawAnimImage(HDC hdc, string imageName, const ImageDrawInfo& imageDrawInfo);
	void DrawAnimImage(HDC hdc, const ImageDrawInfo& imageDrawInfo);

	void AlphaRender(HDC hdc, const ImageDrawInfo& imageDrawInfo, BYTE alpha);
private:
	std::map <string, class Image*> images;

};

