#pragma once

#include <Windows.h>
#include <math.h>
#include <string>
#include <ctime>

using namespace std;

#define WINSIZE_X	1280
#define WINSIZE_Y	720
#define PI			3.141592f
#define DegreeToRadian(x)	(x * PI / 180.0f)
#define RadianToDegree(x)	(x * 180.0f / PI)
#define ZKey 0x5A
#define XKey 0x58
#define CKey 0x43
// 실제 플레이 영역
#define PlayXSize 650
#define Play_LeftX 315
#define Play_RightX Play_LeftX + PlayXSize


struct FPOINT
{
	float x;
	float y;
};

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;