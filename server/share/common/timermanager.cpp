#include "timermanager.h"
#include "timemanager.h"
#include "servercommon.h"
#include "common/gamelog.h"

Timer::Timer()
{
    //
}

Timer::Timer(uint32 i, uint32 t, void (*c)()) : interval(i), loopTimes(t), nextTime(TimeManager::Now() + interval), callBack(c)
{
    //
}

Timer::~Timer()
{
    //
}

SINGLETON_DEFINITION(TimerManager)

TimerManager::TimerManager()
{
    //
}

TimerManager::~TimerManager()
{
    //
}

void TimerManager::Exec()
{
    uint32 now = TimeManager::NowMilliSecond();
    //LOG_WARN("TimerManager::Exec:%u", time);
    if (timerVec.size() == 0)
    {
        usleep(1000);
        return;
    }

    std::pop_heap(timerVec.begin(), timerVec.end());
    Timer *pTimer = timerVec[timerVec.size() - 1];
    if (this->delTimerSet.find(pTimer) != this->delTimerSet.end() || pTimer->loopTimes == 0)
    {
        delete pTimer;
        timerVec.pop_back();
        return;
    }

    if (pTimer->nextTime > now)
    {
        std::push_heap(timerVec.begin(), timerVec.end());
        return;
    }  
    

    pTimer->nextTime = now + pTimer->interval;
    if (pTimer->loopTimes != -1)
    {
        pTimer->loopTimes -= 1;
    }

    std::push_heap(timerVec.begin(), timerVec.end());

    pTimer->callBack();
}

Timer *TimerManager::AddTimer(uint32 interval, uint32 times)
{
    Timer *pTimer = new Timer();
    this->AddTimer(pTimer);
    return pTimer;
}

void TimerManager::DelTimer(Timer *pTimer)
{
    delTimerSet.insert(pTimer);
}

void TimerManager::AddTimer(Timer *pTimer)
{
    timerVec.push_back(pTimer);
    std::push_heap(timerVec.begin(), timerVec.end());
}