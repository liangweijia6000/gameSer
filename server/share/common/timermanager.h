#ifndef __TIMER_MANAGER__
#define __TIMER_MANAGER__

#include "servercommon.h"

class Timer
{
    friend class TimerManager;
public:
    ~Timer();
private:
    Timer();
    Timer(uint32 interval, uint32 times, void (*c)());
private:
    uint32 interval;
    uint32 nextTime;
    uint32 loopTimes;
    void (*callBack)();
};

class TimerManager
{
    SINGLETON_DECLARATION(TimerManager)
public:
    TimerManager();
    ~TimerManager();
public:
    void Exec();
    Timer* AddTimer(uint32 interval, uint32 times);
    void DelTimer(Timer* pTimer);
private:
    void AddTimer(Timer* pTimer);
private:
    std::vector<Timer*> timerVec;
    std::set<Timer*> delTimerSet;
};

#endif //__TIMER_MANAGER__