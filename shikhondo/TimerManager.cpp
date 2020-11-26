#include "TimerManager.h"
#include "Timer.h"


TimerManager::TimerManager()
{
}


TimerManager::~TimerManager()
{
}

HRESULT TimerManager::Init()
{
	timer = new Timer;
	timer->Init();
	timerCount = 0;
	return S_OK;
}

void TimerManager::Release()
{
	Const_IteratorTimerMap it;
	for (it = timers.begin(); it != timers.end(); it++)
		delete it->second;
	delete timer;

	timers.clear();
}

void TimerManager::Update()
{
	timer->Tick();
}

void TimerManager::TimerUpdate()
{
	Const_IteratorTimerMap it;
	std::map<TimerHandle, Timer*> copyTimersmap = timers;
	for (it = copyTimersmap.begin(); it != copyTimersmap.end();)
	{
		Timer* timer = it->second;
		it++;
		timer->Tick();
	}
	copyTimersmap.clear();
}

void TimerManager::Render(HDC hdc)
{
	if (timer)
	{
		wsprintf(szText,"FPS : %d",timer->GetFPS());
		TextOut(hdc,0,0,szText , (int)strlen(szText));
	}
}

float TimerManager::GettimeElapsed()
{
	return timer->GettimeElapsed();
}

void TimerManager::AllDeleteTimer()
{
	Const_IteratorTimerMap it;
	for (it = timers.begin(); it != timers.end(); it++)
	{
		it->second->timer.UnBind();
		delete it->second;
	}
	timers.clear();
}

void TimerManager::DeleteTimer(TimerHandle & timerHandle)
{
	map<TimerHandle, Timer*>::iterator it;
	it = timers.find(timerHandle);
	if (it != timers.end())
	{
		Timer* newTimer = it->second;
		newTimer->timer.UnBind();
		delete newTimer;
		timers.erase(it);
	}

}