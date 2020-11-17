#include "Timer.h"



Timer::Timer()
{
}


Timer::~Timer()
{
	this->DelteTimer();
}

HRESULT Timer::Init()
{
	currTime = 0;
	timeElapsed = 0;
	fpsTimeElapsed = 0;
	fpsFrameCount = 0;
	fps = 0;
	timerDelay = 1.0f;
	isSetTimer = false;
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency))
	{
		isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
		timeScale = 1.0f / periodFrequency;
	}
	else
	{
		isHardware = false;
		lastTime = timeGetTime();
		timeScale = 0.001f;
	}
	return S_OK;
}

void Timer::Tick()
{
	if (isHardware)
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	else
		currTime = timeGetTime();
	
	timeElapsed = (currTime - lastTime) * timeScale;

	fpsTimeElapsed += timeElapsed;
	fpsFrameCount++;
	if (fpsTimeElapsed >= timerDelay)
	{
		fpsTimeElapsed = 0;
		fps = fpsFrameCount;
		fpsFrameCount = 0;
		if (isSetTimer)
			timer.Execute();
	}



	lastTime = currTime;
}

void Timer::DelteTimer()
{
	fpsTimeElapsed = 1.0f;
	timer.UnBind();
}

