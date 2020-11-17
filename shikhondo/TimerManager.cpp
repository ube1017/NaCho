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
	Const_IteratorTimerMap it;
	for (it = timers.begin(); it != timers.end(); it++)
		it->second->Tick();

}

void TimerManager::Render(HDC hdc)
{
	if (timer)
	{
		wsprintf(szText,"FPS : %d",timer->GetFPS());
		TextOut(hdc,0,0,szText , strlen(szText));
	}
}
