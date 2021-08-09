#include "timermanager.h"
#include "timemanager.h"
#include "servercommon.h"
#include "common/gamelog.h"


Timer::Timer()
{
    interval = 0;
    loopTimes = 0;
    callBack = NULL;
    nextTime = 0;
}

Timer::Timer(uint32 i, uint32 t, void (*c)()) : interval(i), loopTimes(t), callBack(c), nextTime(TimeManager::NowMilliSecond() + interval), del(false)
{
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
    uint64 now = TimeManager::NowMilliSecond();
    if (timerVec.size() == 0)
    {
        static uint32 a = 0;
        if (a%500 == 0)
        {
            LOG_DEBUG("TimerManager Exec %d", a/500);
        }
        a += 1;
        //usleep(1000000);    //没活干睡1秒 //TODO:
        sleep(0);
        return;
    }

    std::pop_heap(timerVec.begin(), timerVec.end());
    Timer *pTimer = timerVec[timerVec.size() - 1];
    if (pTimer->del || pTimer->loopTimes == 0)
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
    pTimer->del = true;
}

void TimerManager::AddTimer(Timer *pTimer)
{
    timerVec.push_back(pTimer);
    std::push_heap(timerVec.begin(), timerVec.end());
}